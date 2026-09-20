#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAXARGS 128
#define MAXLINE 80

/*---- list operation begin----*/
#define INIT_COUNT 6

struct List_Item {
    char cmd[MAXLINE];
    pid_t pid;
};

struct List {
    struct List_Item** items;
    int items_count;
    int current_item;
    int previous_item;
};

struct List_Item* new_item(char *cmd, pid_t pid)
{
    if (cmd == NULL) {
        return NULL;
    }

    struct List_Item *item = (struct List_Item*) malloc(sizeof(struct List_Item));
    if (item == NULL) {
        return NULL;
    }

    int cmd_len = strlen(cmd);
    if (cmd_len >= sizeof(item->cmd)) {
        cmd_len--;
    }

    strncmp(item->cmd, cmd, cmd_len);
    item->cmd[cmd_len] = '\0';
    item->pid = pid;
    return item;
}

void destroy_item(struct List_Item *item)
{
    free(item);
}

void free_list(struct List *li)
{
    if (li == NULL) {
        return;
    }

    if (li->items == NULL) {
        free(li);
        return;
    }

    for (int i = 0; i < li->items_count; ++i) {
        if (li->items[i] == NULL) {
            continue;
        }

        destroy_item(li->items[i]);
        li->items[i] = NULL;
    }

    free(li);
}

struct List* new_list()
{
    struct List *li = (struct List*) malloc(sizeof(struct List));
    if (li == NULL) {
        return NULL;
    }

    li->items_count = INIT_COUNT;
    li->items = (struct List_Item**) calloc(li->items_count, sizeof(struct List_Item*));
    memset(li->items, 0, li->items_count * sizeof(struct List_Item*));
    li->current_item = -1;
    li->previous_item = -1;
    return li;
}

int expand_items(struct List *li)
{
    if (li == NULL) {
        return -1;
    }

    int new_count = li->items_count * 2;
    struct List_Item **new_items = (struct List_Item**) calloc(new_count, sizeof(struct List_Item*));
    if (new_items == NULL) {
        return -1;
    }

    for (int i = 0; i < li->items_count; ++i) {
        new_items[i] = li->items[i];
    }

    for (int i = li->items_count; i < new_count; ++i) {
        new_items[i] = NULL;
    }

    free(li->items);
    li->items = new_items;
    li->items_count = new_count;
    return 0;
}

int add_item(struct List *li, char *cmd, pid_t pid)
{
    if (li == NULL) {
        return -1;
    }

    int current_item = -1;
    for (int i = 0; i < li->items_count; ++i) {
        if (li->items[i] == NULL) {
            current_item = i;
            break;
        }
    }

    if (current_item == -1) {
        if (expand_items(li) == -1) {
            return -1;
        }

        for (int i = 0; i < li->items_count; ++i) {
            if (li->items[i] == NULL) {
                current_item = i;
                break;
            }
        }

        if (current_item == -1) {
            return -1;
        }
    }

    struct List_Item* item = new_item(cmd, pid);
    if (item == NULL) {
        return -1;
    }

    li->items[current_item] = item;
    if (li->previous_item < li->current_item) {
        li->previous_item = li->current_item;
    }

    li->current_item = current_item;
    return current_item;
}

int find_item_by_pid(struct List *li, pid_t pid)
{
    if (li == NULL) {
        return -1;
    }

    for (int i = 0; i < li->current_item || i < li->previous_item; ++i) {
        if (li->items[i]->pid == pid) {
            return i;
        }
    }

    return -1;
}

int remove_item(struct List *li, int job_num)
{
    if (li == NULL) {
        return -1;
    }

    if (job_num > li->previous_item && job_num > li->current_item) {
        printf("invalid job num: %d, previous_item: %d, current_item: %d\n",
            job_num, li->previous_item, li->current_item);
        return -1;
    }

    destroy_item(li->items[job_num]);
    li->items[job_num] = NULL;
    if (job_num == li->previous_item) {
        li->previous_item = -1;
    } else if (job_num == li->current_item) {
        if (li->previous_item != -1) {
            li->current_item = li->previous_item;
            li->previous_item = -1;
        } else {
            int new_current = -1;
            for (int i = li->current_item - 1; i >= 0; --i) {
                if (li->items[i] != NULL) {
                    li->current_item = i;
                    new_current = i;
                    break;
                }
            }

            if (new_current == -1) {
                li->current_item = -1;
            } else if (new_current > 0) {
                int new_previous = new_current - 1;
                if (li->items[new_previous] != NULL) {
                    li->previous_item = new_previous;
                }
            }
        }
    }

    return job_num;
}

int remove_item_by_pid(struct List *li, pid_t pid)
{
    int idx = find_item_by_pid(li, pid);
    if (idx == -1) {
        return -1;
    }

    return remove_item(li, idx);
}
/*---- list operation end------*/

extern char **environ;

/* Function prototypes */
void eval(char *cmdline);
int parseline(char *buf, char **argv);
int builtin_command(char **argv);
void unix_error(char *msg);
void sig_handler(int sig);

static pid_t fg_pgid = -1;
static struct List *bg_jobs = NULL;

int main()
{
    bg_jobs = new_list();
    if (bg_jobs == NULL) {
        printf("init bg jobs failure\n");
        exit(EXIT_FAILURE);
    }

    struct sigaction sa = { .sa_handler = sig_handler };
    sigemptyset(&sa.sa_mask);
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGTSTP, &sa, NULL);

    char cmdline[MAXLINE]; /* Command line */

    while (1) {
        /* Read */
        printf("> ");
        fgets(cmdline, MAXLINE, stdin);
        if (feof(stdin))
            exit(0);

        /* Evaluate */
        eval(cmdline);
        cmdline[0] = 0;
    }
}

/* eval - Evaluate a command line */
void eval(char *cmdline)
{
    char *argv[MAXARGS]; /* Argument list execve() */
    char buf[MAXLINE]; /* Holds modified command line */
    int bg; /* Should the job run in bg or fg? */
    pid_t pid; /* Process id */

    if (!cmdline || !(cmdline[0])) {
        return;
    }

    strcpy(buf, cmdline);
    bg = parseline(buf, argv);
    if (argv[0] == NULL)
        return; /* Ignore empty lines */

    if (!builtin_command(argv)) {
        if ((pid = fork()) == 0) { /* Child runs user job */
            if (execve(argv[0], argv, environ) < 0) {
                printf("%s: Command not found.\n", argv[0]);
                exit(0);
            }
        }

        pid_t pgid = pid;
        if (setpgid(pid, pgid) < 0) {
            unix_error("setgpid error");
        }

        /* Parent waits for foreground job to terminate */
        if (!bg) {
            fg_pgid = pgid;
            int status;
            while ((waitpid(pid, &status, 0) < 0)) {
                if (errno != EINTR) {
                    unix_error("waitfg: waitpid error");
                }
            }

            printf("waitpid exit\n");
            fg_pgid = -1;
            /*if (waitpid(pid, &status, 0) < 0)
                unix_error("waitfg: waitpid error");*/
        } else {
            int job_num = add_item(bg_jobs, cmdline, pid);
            if (job_num == -1) {
                printf("add job to bg failure");
                exit(EXIT_FAILURE);
            } else {
                printf("[%d] %d\n", job_num + 1, pid);
            }
        }
    }
    return;
}

/* If first arg is a builtin command, run it and return true */
int builtin_command(char **argv)
{
    if (!strcmp(argv[0], "quit") || !strcmp(argv[0], "exit")) {
        exit(0);
    }

    if (!strcmp(argv[0], "&")) {
        return 1;
    }

    if (!strcmp(argv[0], "jobs")) {
        for (int i = 0; i <= bg_jobs->current_item || i <= bg_jobs->previous_item; ++i) {
            if (bg_jobs->items[i] == NULL) {
                continue;
            }

            char note = ' ';
            if (i == bg_jobs->current_item) {
                note = '+';
            } else if (i == bg_jobs->previous_item) {
                note = '-';
            }

            printf("[%d]  %c %d    %s\n", i + 1, note,
                bg_jobs->items[i]->pid,
                bg_jobs->items[i]->cmd);
        }

        return 1;
    }
    return 0;                       /* Not a builtin command */
}

/* parseline - Parse the command line and build the argv array */
int parseline(char *buf, char **argv)
{
    char *delim;    /* Points to first space delimiter */
    int argc;       /* Number of args */
    int bg;         /* Background job? */

    buf[strlen(buf)-1] = ' '; /* Replace trailing '\n' with space */
    while (*buf && (*buf == ' ')) /* Ignore leading spaces */
        buf++;

    /* Build the argv list */
    argc = 0;
    while ((delim = strchr(buf, ' '))) {
        argv[argc++] = buf;
        *delim = '\0';
        buf = delim + 1;
        while (*buf && (*buf == ' ')) /* Ignore spaces */
            buf++;
    }
    argv[argc] = NULL;

    if (argc == 0) /* Ignore blank line */
        return 1;

    /* Should the job run in the background? */
    if ((bg = (*argv[argc-1] == '&')) != 0)
        argv[--argc] = NULL;

    return bg;
}

void unix_error(char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

void sig_handler(int sig)
{
    printf("Receive signal: %d, %s\n", sig, strsignal(sig));
    if (fg_pgid <= 0) {
        return;
    }

    switch (sig) {
    case SIGINT:
        if (kill(-fg_pgid, SIGINT) < 0) {
            perror("kill error");
        }
        break;
    case SIGSTOP:
        if (kill(-fg_pgid, SIGSTOP) < 0) {
            perror("kill error");
        }
        break;
    }
}