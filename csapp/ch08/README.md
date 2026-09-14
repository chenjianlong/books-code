# 第8章 异常控制流

## 练习题

### 练习题 8.1

考虑三个具有下述起始时间和结束时间的进程：

|进程|起始时间|结束时间|
|-|-|-|
|A|0|2|
|B|1|4|
|C|3|5|

对于每对进程，指出它们是否是并发地运行的：

|进程对|并发的？|
|-|-|
|AB||
|AC||
|BC||

答：

|进程对|并发的？|
|-|-|
|AB|是|
|AC|否|
|BC|是|

### 练习题 8.2

考虑下面的程序：

```c
/* code/ecf/forkprob0.c */
#include "csapp.h"

int main()
{
    int x = 1;

    if (Fork() == 0)
        printf("printf1: x=%d\n", ++x);
    printf("printf2: x=%d\n", --x);
    exit(0);
}
/* code/ecf/forkprob0.c */
```

* A. 子进程的输出是什么？
* B. 父进程的输出是什么？

答：

* A. 2
* B. 0

### 练习题 8.3

列出下面程序所有可能的输出序列：

```c
/* code/ecf/waitprob0.c */
int main()
{
    if (Fork() == 0) {
        printf("a");
    }
    else {
        printf("b");
        waitpid(-1, NULL, 0);
    }
    printf("c");
    exit(0);
}
/* code/ecf/waitprob0.c */
```

答：

```
abc
bac
```

### 练习题 8.4

考虑下面的程序：

```c
/* code/ecf/waitprob1.c */
int main()
{
    int status;
    pid_t pid;

    printf("Hello\n");
    pid = Fork();
    printf("%d\n", !pid);
    if (pid != 0) {
        if (waitpid(-1, &status, 0) > 0) {
            if (WIFEXITED(status) != 0)
                printf("%d\n", WEXITSTATUS(status));
        }
    }
    printf("Bye\n");
    exit(2);
}
/* code/ecf/waitprob1.c */
```

* A. 这个程序会产生多少输出行？
* B. 这些输出行的一种可能的顺序是什么？

答：

* A. 6 行
* B.

```
Hello
0
1
Bye
2
Bye
```

```
Hello
1
0
Bye
2
Bye
```

```
Hello
1
Bye
0
2
Bye
```



### 练习题 8.5

编写一个 `sleep` 的包装函数，叫做 `snooze`，带有下面的接口：

```c
unsigned int snooze(unsigned int secs);
```

除了 `snooze` 函数会打印一条信息来描述进程实际休眠了多长时间外，它和 `sleep` 函数的行为完全一样:

```
Slept for 4 of 5 secs.
```

答：

[ex8.05.c](ex8.05.c)

### 练习题 8.6

编写一个叫做 `myecho` 的程序，它打印出它的命令行参数和环境变量。
例如:

```sh
unix> ./myecho arg1 arg2
Command line arguments:
argv[ 0]: myecho
argv[ 1]: arg1
argv[ 2]: arg2
Environment variables:
envp[ 0]: PWD=/usr0/droh/ics/code/ecf
envp[ 1]: TERM=emacs
...
envp[25]: USER=droh
envp[26]: SHELL=/usr/local/bin/tcsh
envp[27]: HOME=/usr0/droh
```

### 练习题 8.8

下面这个程序的输出是什么？

```c
/* code/ecf/signalprob0.c */
pid_t pid;
int counter = 2;

void handler1(int sig) {
    counter = counter - 1;
    printf("%d", counter);
    fflush(stdout);
    exit(0);
}

int main() {
    signal(SIGUSR1, handler1);

    printf("%d", counter);
    fflush(stdout);

    if ((pid = fork()) == 0) {
        while(1) {};
    }
    kill(pid, SIGUSR1);
    waitpid(-1, NULL, 0);
    counter = counter + 1;
    printf("%d", counter);
    exit(0);
}
/* code/ecf/signalprob0.c */
```

答：

```
213
```

## 家庭作业

### 8.9 \*

考虑四个具有如下开始和结束时间的进程：

|进程|开始时间|结束时间|
|-|-|-|
|A|5|7|
|B|2|4|
|C|3|6|
|D|1|8|

对于每对进程，指明它们是否是并发地运行的：

|进程对|并发地？|
|-|-|
|AB||
|AC||
|AD||
|BC||
|BD||
|CD||

答：

|进程对|并发地？|
|-|-|
|AB|否|
|AC|是|
|AD|是|
|BC|是|
|BD|是|
|CD|是|

### 8.10 \*

在这一章里，我们介绍了一些具有不寻常的调用和返回行为的函数: `setjmp`、`longjmp`、`execve` 和 `fork`。
找到下列行为中和每个函数相匹配的一种:

* A. 调用一次，返回两次。
* B. 调用一次，从不返回。
* C. 调用一次，返回一次或者多次。

答：

* A. `fork`
* B. `longjmp`、`execve`
* C. `setjmp`

### 8.11 \*

这个程序会输出多少个 "hello" 输出行？

```c
/* code/ecf/forkprob1.c */
#include "csapp.h"

int main()
{
    int i;

    for (i = 0; i < 2; i++)
        Fork();
    printf("hello\n");
    exit(0);
}
/* code/ecf/forkprob1.c */
```

答：4

### 8.12 \*

这个程序会输出多少个 "hello" 输出行？

```c
/* code/ecf/forkprob4.c */
#include "csapp.h"

void doit()
{
    Fork();
    Fork();
    printf("hello\n");
    return;
}

int main()
{
    doit();
    printf("hello\n");
    exit(0);
}
/* code/ecf/forkprob4.c */
```

答：8

### 8.13 \*

下面程序的一种可能的输出是什么？

```c
/* code/ecf/forkprob3.c */
#include "csapp.h"

int main()
{
    int x = 3;

    if (Fork() != 0)
        printf("x=%d\n", ++x);

    printf("x=%d\n", --x);
    exit(0);
}
/* code/ecf/forkprob3.c */
```

答：433

### 8.14 \*

下面这个程序会输出多少个 "hello" 输出行？

```c
/* code/ecf/forkprob5.c */
#include "csapp.h"

void doit()
{
    if (Fork() == 0) {
        Fork();
        printf("hello\n");
        exit(0);
    }
    return;
}

int main()
{
    doit();
    printf("hello\n");
    exit(0);
}
/* code/ecf/forkprob5.c */
```

答：3

### 8.15 \*

下面这个程序会输出多少个 "hello" 输出行？

```c
/* code/ecf/forkprob6.c */
#include "csapp.h"

void doit()
{
    if (Fork() == 0) {
        Fork();
        printf("hello\n");
        return;
    }
    return;
}

int main()
{
    doit();
    printf("hello\n");
    exit(0);
}
/* code/ecf/forkprob6.c */
```

答：6

### 8.16 \*

下面这个程序的输出是什么？

```c
/* code/ecf/forkprob7.c */
#include "csapp.h"
int counter = 1;

int main()
{
    if (fork() == 0) {
        counter--;
        exit(0);
    }
    else {
        Wait(NULL);
        printf("counter = %d\n", ++counter);
    }
    exit(0);
}
/* code/ecf/forkprob7.c */
```

答：2

### 8.17 \*

列举练习题 8.4 中程序所有可能的输出。

答：

```
Hello
0
1
Bye
2
Bye
```

```
Hello
1
0
Bye
2
Bye
```

```
Hello
1
Bye
0
2
Bye
```

### 8.18 \*\*

考虑下面的程序：

```c
/* code/ecf/forkprob2.c */
#include "csapp.h"

void end(void)
{
    printf("2");
}

int main()
{
    if (Fork() == 0)
        atexit(end);
    if (Fork() == 0)
        printf("0");
    else
        printf("1");
    exit(0);
}
/* code/ecf/forkprob2.c */
```

判断下面哪个输出是可能的。

> 注意: `atexit` 函数以一个指向函数的指针为输入，并将它添加到函数列表中(初始为空)，当exit函数被调用时，会调用该列表中的函数。

* A. 112002
* B. 211020
* C. 102120
* D. 122001
* E. 100212

答：

下面是进程和它们的输出关系：

```
main
    Fork1
        Fork2 -> 0
              -> 2
        -> 1
        -> 2
    Fork2 -> 0
-> 1
```

明显 B 和 D 都是不可能的，ACE 都可能

### 8.19 \*\*

下面的函数打印多少行输出?
给出一个答案为 n 的表达式。
假设 n ≥ 1。

```c
/* code/ecf/forkprob8.c */
void foo(int n)
{
    int i;

    for (i = 0; i < n; i++)
        Fork();
    printf("hello\n");
    exit(0);
}
/* code/ecf/forkprob8.c */
```

答: 2<sup>n</sup>

### 8.20 \*\*

使用 `execve` 编写一个叫做 `myls` 的程序，该程序的行为和 `/bin/ls` 程序的一样。
你的程序应该接受相同的命令行参数，解释同样的环境变量，并产生相同的输出。
`ls` 程序从 `COLUMNS` 环境变量中获得屏幕的宽度。
如果没有设置 `COLUMNS`，那么 `ls` 会假设屏幕宽 80 列。
因此，你可以通过把 `COLUMNS` 环境设置得小于 80，来检查你对环境变量的处理:

```sh
unix> setenv COLUMNS 40
unix> ./myls
...output is 40 columns wide
unix> unsetenv COLUMNS
unix> ./myls
...output is now 80 columns wide
```

TODO

### 8.21 \*\*

下面程序的可能的输出序列是什么?

```c
/* code/ecf/waitprob3.c */
int main()
{
    if (fork() == 0) {
        printf("a");
        exit(0);
    }
    else {
        printf("b");
        waitpid(-1, NULL, 0);
    }
    printf("c");
    exit(0);
}
/* code/ecf/waitprob3.c */
```

答：

```
abc
```

或者

```
bac
```

### 8.22 \*\*\*

编写 Unix system 函数的你自己的版本

```c
int mysystem(char *command);
```

`mysystem` 函数通过调用 “/bin/sh-c command” 来执行 command, 然后在 command 完成后返回。
如果 command(通过调用 `exit` 函数或者执行一条 `return` 语句)正常退出，那么 `mysystem` 返回 command 退出状态。
例如，如果 command 通过调用exit(8)终止，那么 `mysystem` 返回值 8。
否则，如果 command 是异常终止的，那么 `mysystem` 就返回外壳返回的状态。

TODO

### 8.23 \*\*

你的一个同事想要使用信号来让一个父进和程对发生在一个子进程中的事件计数。
其思想是每次发生一个事件时，通过向父进程发送一个信号来通知它，并且让父进程的信号处理程序对一个全局变量`counter`加一，在子进程终止之后，父
进程就可以检查这个变量。
然而，当他在系统上运行图 8-41 中的测试程序时，发现当父进程调用 `printf` 时，`counter`的值总是2，即使子进程向父进程发送了5个信号。
他很困惑，向你寻求帮助。
你能解释这个程序有什么错误吗?

```c
/* code/ecf/counterprob.c */
#include "csapp.h"

int counter = 0;

void handler(int sig)
{
    counter++;
    sleep(1); /* Do some work in the handler */
    return;
}

int main()
{
    int i;

    Signal(SIGUSR2, handler);

    if (Fork() == 0) { /* Child */
        for (i = 0; i < 5; i++) {
            Kill(getppid(), SIGUSR2);
            printf("sent SIGUSR2 to parent\n");
        }
        exit(0);
    }

    Wait(NULL);
    printf("counter=%d\n", counter);
    exit(0);
}
/* code/ecf/counterprob.c */
```

**图 8-41 家庭作业 8.23 中引用的计数器程序**

答：

当子进程连续发送多个 SIGUSR2 给父进程时，如果父进程已经有未处理的 SIGUSR2 信号，系统会直接丢弃后面发送的 SIGUSR2 信号。

### 8.24 \*\*\*

修改图 8-17 中的程序，以满足下面两个条件:

1. 每个子进程在试图写一个只读文本段中的位置时会异常终止。
2. 父进程打印和下面所示相同(除了PID)的输出:

```
child 12255 terminated by signal 11: Segmentation fault
child 12254 terminated by signal 11: Segmentation fault
```

> 提示: 请参考psignal(3)的 man 页。

附录：

```c
/* code/ecf/waitpid1.c */
#include "csapp.h"
#define N 2

int main()
{
    int status, i;
    pid_t pid;

    /* Parent creates N children */
    for (i = 0; i < N; i++)
        if ((pid = Fork()) == 0) /* Child */
            exit(100+i);

    /* Parent reaps N children in no particular order */
    while ((pid = waitpid(-1, &status, 0)) > 0) {
        if (WIFEXITED(status))
            printf("child %d terminated normally with exit status=%d\n",
                    pid, WEXITSTATUS(status));
        else
            printf("child %d terminated abnormally\n", pid);
    }

    /* The only normal termination is if there are no more children */
    if (errno != ECHILD)
        unix_error("waitpid error");

    exit(0);
}
/* code/ecf/waitpid1.c */
```

**图8-17 使用 waitpid 函数不按照特定的顺序回收僵死子进程**

TODO
