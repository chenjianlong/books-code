#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAXARGS 128
#define MAXLINE 80

extern char **environ;

/* Function prototypes */
void eval(char *cmdline);
int parseline(char *buf, char **argv);
int builtin_command(char **argv);
void unix_error(char *msg);
void sig_handler(int sig);

static pid_t fg_pgid = -1;

int main()
{
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
        }
        else
            printf("%d %s", pid, cmdline);
    }
    return;
}

/* If first arg is a builtin command, run it and return true */
int builtin_command(char **argv)
{
    if (!strcmp(argv[0], "quit"))   /* quit command */
        exit(0);
    if (!strcmp(argv[0], "&"))      /* Ignore singleton & */
        return 1;
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

void handle_sigchld()
{
    int status = 0;
    while (1) {
        pid_t pid = waitpid(-1, &status, WNOHANG);
        if (pid <= 0) {
            break;
        }

        if (WIFEXITED(status)) {
            printf("child %d terminated normally with exit status=%d\n",
                    pid, WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            int signo = WTERMSIG(status);
            printf("child %d terminated by signal %d: %s\n",
                    pid, signo, strsignal(signo));
        } else {
            printf("child %d terminated abnormally\n", pid);
        }
    }
}

void sig_handler(int sig)
{
    printf("Receive signal: %d, %s\n", sig, strsignal(sig));
    switch (sig) {
    case SIGINT:
        if (fg_pgid <= 0) {
            return;
        }
        if (kill(-fg_pgid, SIGINT) < 0) {
            perror("kill error");
        }
        break;
    case SIGSTOP:
        if (fg_pgid <= 0) {
            return;
        }
        if (kill(-fg_pgid, SIGSTOP) < 0) {
            perror("kill error");
        }
        break;
    case SIGCHLD:
        handle_sigchld();
        break;
    }
}