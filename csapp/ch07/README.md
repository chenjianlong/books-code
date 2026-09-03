# 第7章 链接

## 练习题

### 练习题 7.1

这个题目是关于 图7-1b 中的 `swap.o` 模块。
对于每个在 `swap.o` 中定义或引用的符号,请指出它是否在模块 `swap.o` 中的 `.symtab` 节中有一个符号表条目。
如果是，请指出定义该符号的模块(`swap.o` 或者 `main.o`)、符号类型(本地、全局或者外部)和它在模块中占据的节(`.text`、`.data` 或者 `.bss`)。

|符号|`swap.o` `.symtab` 条目?|符号类型|在哪个模块中定义|节|
|-|-|-|-|-|
|buf|||||
|bufp0|||||
|bufp1|||||
|swap|||||
|temp|||||

附录：

```c
/* main.c */
void swap();

int buf[2] = {1, 2};

int main()
{
    swap();
    return 0;
}
```

```c
/* swap.c */
extern int buf[];

int *bufp0 = &buf[0];
int *bufp1;

void swap()
{
    int temp;

    bufp1 = &buf[1];
    temp = *bufp0;
    *bufp0 = *bufp1;
    *bufp1 = temp;
}
```

图 7.1

答：

|符号|`swap.o` `.symtab` 条目?|符号类型|在哪个模块中定义|节|
|-|-|-|-|-|
|buf|是|外部|`main.o`|`.data`|
|bufp0|是|全局|`swap.o`|`.data`|
|bufp1|是|全局|`swap.o`|`.bss`|
|swap|是|全局|`swap.o`|`.text`|
|temp|否|-|-|-|

### 练习题 7.2

在此题中，`REF(x.i)-->DEF(x.k)` 表示链接器将把模块 `i` 中对符号 `x` 的任意引用与模块 `k` 中 `x` 的定义联系起来。
对于下面的每个示例，用这种表示法来说明链接器将如何解析每个模块中对多重定义符号的引用。
如果有一个链接时错误(规则1)，写“ERROR”。
如果链接器从定义中任意选择一个(规则3)，则写“UNKNOWN”。

* A.

```c
/* Module 1 */
int main()
{
}

/* Module 2 */
int main;
int p2()
{
}
```


```
(a) REF(main.1) --> DEF(___.__)
(b) REF(main.2) --> DEF(___.__)
```

* B

```c
/* Module 1 */
void main()
{
}

/* Module 2 */
int main=1;
int p2()
{
}
```

```
(a) REF(main.1) --> DEF(___.__)
(b) REF(main.2) --> DEF(___.__)
```

* C.

```c
/* Module 1 */
int x;
void main()
{
}

/* Module 2 */
double x=1.0;
int p2()
{
}
```

```
(a) REF(x.1) --> DEF(___.__)
(b) REF(x.2) --> DEF(___.__)
```

答:

* A
    * (a) REF(main.1) --> DEF(main.1)
    * (b) REF(main.2) --> DEF(main.1)
* B ERROR
* C
    * (a) REF(x.1) --> DEF(x.2)
    * (b) REF(x.2) --> DEF(x.2)

### 练习题 7.3

`a` 和 `b` 表示当前目录中的目标模块或者静态库，而 `a → b` 表示 `a` 依赖于 `b`，也就是说 `b` 定义了一个被 `a` 引用的符号。
对于下面每种场景，请给出最小的命令行(也就是一个含有最少数量的
目标文件和库参数的命令)，使得静态链接器能解析所有的符号引用。

* A. `p.o → libx.a`
* B. `p.o → libx.a → liby.a`
* C. `p.o → libx.a → liby.a` 且 `liby.a → libx.a → p.o`

* A `gcc p.o libx.a`
* B `gcc p.o libx.a liby.a`
* C `gcc p.o libx.a liby.a libx.a`

### 练习题 7.4

本题是关于图 7-10 中的重定位程序的。

* A. 第 5 行中对 `swap` 的重定位引用的十六进制地址是多少?
* B. 第 5 行中对 `swap` 的重定位引用的十六进制值是多少?
* C. 假设因为某种原因，链接器决定将 `.text节` 放在 `0x80483b8` 处而不是 `0x80483b4` 处。
那么在这种情况下，第 5 行的重定位引用的十六进制值是多少?

附录：

```x86asm
# (a) Relocated .text section
# code/link/p-exe.d
1  080483b4 <main>:
2  80483b4: 55                   push %ebp
3  80483b5: 89 e5                mov %esp,%ebp
4  80483b7: 83 ec 08             sub $0x8,%esp
5  80483ba: e8 09 00 00 00       call 80483c8 <swap>           swap();
6  80483bf: 31 c0                xor %eax,%eax
7  80483c1: 89 ec                mov %ebp,%esp
8  80483c3: 5d                   pop %ebp
9  80483c4: c3                   ret
10 80483c5: 90                   nop
11 80483c6: 90                   nop
12 80483c7: 90                   nop
13 080483c8 <swap>:
14 80483c8: 55                   push %ebp
15 80483c9: 8b 15 5c 94 04 08    mov 0x804945c,%edx            Get *bufp0
16 80483cf: a1 58 94 04 08       mov 0x8049458,%eax            Get buf[1]
17 80483d4: 89 e5                mov %esp,%ebp
18 80483d6: c7 05 48 95 04 08 58 movl $0x8049458,0x8049548     bufp1 = &buf[1]
19 80483dd: 94 04 08
20 80483e0: 89 ec                mov %ebp,%esp
21 80483e2: 8b 0a                mov (%edx),%ecx
22 80483e4: 89 02                mov %eax,(%edx)
23 80483e6: a1 48 95 04 08       mov 0x8049548,%eax            Get *bufp1
24 80483eb: 89 08                mov %ecx,(%eax)
25 80483ed: 5d                   pop %ebp
26 80483ee: c3                   ret
# code/link/p-exe.d

# (b) Relocated .data section
# code/link/pdata-exe.d
1  08049454 <buf>:
2  8049454: 01 00 00 00 02 00 00 00

3  0804945c <bufp0>:
4  804945c: 54 94 04 08 Relocated!
# code/link/pdata-exe.d
```

**图 7-10 可执行文件 p 的已重定位的 `.text` 和 `.data节`。原始的 C 代码在图 7-1 中**

答：

* A 80483bb
* B 9
* C 不变，还是 9

### 练习题 7.5

* A. 为什么每个 C 程序都需要一个叫做 `main` 的函数?
* B. 你想过为什么 C 的 `main` 函数可以通过 `exit` 或者执行一条 `return` 语句来结束, 或者两者都不做, 而程序仍然可以正确终止吗?
请解释。

答：

* A. 因为启动代码会调用 `main` 函数，没有 `main` 函数，程序会编译失败
* B. 这三者都最终会通过 `_exit` 函数将控制权返回给操作系统。

## 家庭作业

### 7.6 \*

考虑下面的 `swap.c` 函数版本，它计算自己被调用的次数:

```c
extern int buf[];

int *bufp0 = &buf[0];
static int *bufp1;

static void incr()
{
    static int count=0;

    count++;
}

void swap()
{
    int temp;

    incr();
    bufp1 = &buf[1];
    temp = *bufp0;
    *bufp0 = *bufp1;
    *bufp1 = temp;
}
```

对于每个 `swap.o` 中定义和引用的符号，请指出它是否在模块 `swap.o` 的 `.symtab` 节中有符号表条目。
如果是这样，请指出定义该符号的模块(`swap.o` 或 `main.o`)、符号类型(本地、全局或外部)以及它在模块中所处的节(`.text`、`.data` 或 `.bss`)。

|符号|`swap.o` `.symtab` 条目?|符号类型|定义符号的模块|节|
|-|-|-|-|-|
|buf|||||
|bufp0|||||
|bufp1|||||
|swap|||||
|temp|||||
|incr|||||
|count|||||

答：

|符号|`swap.o` `.symtab` 条目?|符号类型|定义符号的模块|节|
|-|-|-|-|-|
|buf|是|外部|`main.o`|`.data`|
|bufp0|是|全局|`swap.o`|`.data`|
|bufp1|是|本地|`swap.o`|`.bss`|
|swap|是|全局|`swap.o`|`.text`|
|temp|否|-|-|-|
|incr|是|全局|`swap.o`|`.text`|
|count|是|本地|`swap.o`|`.bss`|

### 7.7 \*

不改变任何变量名字，修改 7.6.1 节中的 `bar5.c`, 使得 `foo5.c` 输出 x 和 y 的正确值（也就是整数 15213 和 15212 的十六进制表示）。

附录：

```c
/* foo5.c */
#include <stdio.h>
void f(void);

int x = 15213;
int y = 15212;

int main()
{
    f();
    printf("x = 0x%x y = 0x%x \n",
           x, y);
    return 0;
}
```

```c
/* bar5.c */
double x;

void f()
{
    x = -0.0;
}
```

答:

```c
/* bar5.c */
static double x;

void f()
{
    x = -0.0;
}
```

### 7.8 \*

在此题中，REF(x.i)-->DEF(x.k) 表示链接器将任意对模块 i 中符号 x 的引用与模块 k 中符号 x 的定义相关联。
在下面每个例子中，用这种符号来说明链接器是如何解析在每个模块中有多重定义的引用的。
如果出现链接时错误（规则 1），写 "ERROR"。
如果链接器从定义中任意选择一个（规则 3），那么写 “UNKNOWN”。

* A

```c
/* Module 1 */
int main()
{
}

/* Module 2 */
static int main=1;
int p2()
{
}
```

```
(a) REF(main.1) --> DEF(____.___)
(a) REF(main.2) --> DEF(____.___)
```

* B

```c
/* Module 1 */
int x;
void main()
{
}

/* Module 2 */
double x;
int p2()
{
}
```

```
(a) REF(x.1) --> DEF(____.___)
(a) REF(x.2) --> DEF(____.___)
```

* C

```c
/* Module 1 */
int x=1;
void main()
{
}

/* Module 2 */
double x=1.0;
int p2()
{
}
```

```
(a) REF(x.1) --> DEF(____.___)
(b) REF(x.2) --> DEF(____.___)
```

答：

* A

```
(a) REF(main.1) --> DEF(main.1)
(a) REF(main.2) --> DEF(main.2)
```

* B UNKNOWN
* C ERROR

### 7.9 \*

考虑下面的程序，它由两个目标模块组成:

```c
/* foo6.c */
void p2(void);

int main()
{
    p2();
    return 0;
}
```

```c
/* bar6.c */
#include <stdio.h>

char main;

void p2()
{
    printf("0x%x\n", main);
}
```

当在 Linux 系统中编译和执行这个程序时，即使p2不初始化变量 main，它也能打印字符串 “0x55\n” 并正常终止。
你能解释这一点吗?

答：

bar6.main 链接到 foo6.main 了，“0x55\n” 是 foo6.main 的内容。 

### 7.10 \*

a 和 b 表示当前路径中的目标模块或静态库，而 a→b 表示 a 依赖于 b，也就是说 a 引用了一个 b 定义的符号。
对于下面的每个场景，给出使得静态链接器能够解析所有符号引用的最小的命令行(含有最少数量的目标文件和库参数的命令):

* A. p.o → libx.a → p.o
* B. p.o → libx.a → liby.a 和 liby.a → libx.a
* C. p.o → libx.a → liby.a → libz.a 和 liby.a → libx.a → libz.a

答：

* A. gcc p.o -lx
* B. gcc p.o -lx -ly
* C. gcc p.o -lx -ly -lz

### 7.11 \*

图 7-12 中的段头部表明数据段占用了存储器中 0x104 个字节。
然而，只有开始的 0xe8 字节来自可执行文件的节。
引起这种差异的原因是什么?

答：

`.bss` 节需要占用内存空间

### 7.12 \*\*

图 7-10 中的 `swap` 程序包含 5 个重定位的引用。
对于每个重定位的引用，给出它在图 7-10 中的行号、运行时存储器地址和值。
`swap.o` 模块中的原始代码和重定位条目如图 7-19 所示。

```x86asm
1 00000000 <swap>:
2 0: 55                     push %ebp
3 1: 8b 15 00 00 00 00      mov 0x0,%edx Get *bufp0=&buf[0]
4                           3: R_386_32 bufp0 Relocation entry
5 7: a1 04 00 00 00         mov 0x4,%eax Get buf[1]
6                           8: R_386_32 buf Relocation entry
7 c: 89 e5                  mov %esp,%ebp
8 e: c7 05 00 00 00 00 04   movl $0x4,0x0 bufp1 = &buf[1];
9 15: 00 00 00
10                          10: R_386_32 bufp1 Relocation entry
11                          14: R_386_32 buf Relocation entry
12 18: 89 ec                mov %ebp,%esp
13 1a: 8b 0a                mov (%edx),%ecx temp = buf[0];
14 1c: 89 02                mov %eax,(%edx) buf[0]=buf[1];
15 1e: a1 00 00 00 00       mov 0x0,%eax Get *bufp1=&buf[1]
16                          1f: R_386_32 bufp1 Relocation entry
17 23: 89 08                mov %ecx,(%eax) buf[1]=temp;
18 25: 5d                   pop %ebp
19 26: c3                   ret
```

**图 7-19 练习题 7.12 的代码和重定位条目**

|图 7-10 中的行号|地址|值|
|-|-|-|
||||
||||
||||

附录 图 7-10

```x86asm
# (a) Relocated .text section
# code/link/p-exe.d
1   080483b4 <main>:
2   80483b4: 55                     push %ebp
3   80483b5: 89 e5                  mov %esp,%ebp
4   80483b7: 83 ec 08               sub $0x8,%esp
5   80483ba: e8 09 00 00 00         call 80483c8 <swap> swap();
6   80483bf: 31 c0                  xor %eax,%eax
7   80483c1: 89 ec                  mov %ebp,%esp
8   80483c3: 5d                     pop %ebp
9   80483c4: c3                     ret
10  80483c5: 90                     nop
11  80483c6: 90                     nop
12  80483c7: 90                     nop
13  080483c8 <swap>:
14  80483c8: 55                     push %ebp
15  80483c9: 8b 15 5c 94 04 08      mov 0x804945c,%edx Get *bufp0
16  80483cf: a1 58 94 04 08         mov 0x8049458,%eax Get buf[1]
17  80483d4: 89 e5                  mov %esp,%ebp
18  80483d6: c7 05 48 95 04 08 58   movl $0x8049458,0x8049548 bufp1 = &buf[1]
19  80483dd: 94 04 08
20  80483e0: 89 ec                  mov %ebp,%esp
21  80483e2: 8b 0a                  mov (%edx),%ecx
22  80483e4: 89 02                  mov %eax,(%edx)
23  80483e6: a1 48 95 04 08         mov 0x8049548,%eax Get *bufp1
24  80483eb: 89 08                  mov %ecx,(%eax)
25  80483ed: 5d                     pop %ebp
26  80483ee: c3                     ret
# code/link/p-exe.d

# (b) Relocated .data section
# code/link/pdata-exe.d
1   08049454 <buf>:
2   8049454: 01 00 00 00 02 00 00 00
3   0804945c <bufp0>:
4   804945c: 54 94 04 08 Relocated!
# code/link/pdata-exe.d
```

答:

|图 7-10 中的行号|地址|值|
|-|-|-|
|15|0x804945c|0x8049454|
|16|0x8049458|0x0000002|
|18|0x8049548|0x8049458|
|22|0x8049458|0x0000002|
|23|0x8049548|0x8049458|

### 7.13 \*\*\*

考虑图 7-20 中的 C 代码和相应的可重定位目标模块。

* A.确定当模块被重定位时，链接器将修改 `.text` 中的哪些指令。
对于每条这样的指令，列出它的重定位条目中的信息:节偏移、重定位类型和符号名字。
* B.确定当模块被重定位时，链接器将修改 `.data` 中的哪些数据目标。
对于每条这样的指令，列出它的重定位条目中的信息:节偏移、重定位类型和符号名字。

可以随意使用诸如 `OBJDUMP` 之类的工具来帮助你解答这个题目。


```c
extern int p3(void);
int x = 1;
int *xp = &x;

void p2(int y) {
}

void p1() {
    p2(*xp + p3());
}
```

(a) C 代码

```x86asm
1 00000000 <p2>:
2   0: 55               push %ebp
3   1: 89 e5            mov %esp,%ebp
4   3: 89 ec            mov %ebp,%esp
5   5: 5d               pop %ebp
6   6: c3               ret

7 00000008 <p1>:
8    8: 55              push %ebp
9    9: 89 e5           mov %esp,%ebp
10   b: 83 ec 08        sub $0x8,%esp
11   e: 83 c4 f4        add $0xfffffff4,%esp
12  11: e8 fc ff ff ff  call 12 <p1+0xa>
13  16: 89 c2           mov %eax,%edx
14  18: a1 00 00 00 00  mov 0x0,%eax
15  1d: 03 10           add (%eax),%edx
16  1f: 52              push %edx
17  20: e8 fc ff ff ff  call 21 <p1+0x19>
18  25: 89 ec           mov %ebp,%esp
19  27: 5d              pop %ebp
20  28: c3              ret
```

(b) 可重定位目标文件的 `.text` 节

```x86asm
1   00000000 <x>:
2       0: 01 00 00 00
3   00000004 <xp>:
4       4: 00 00 00 00
```

(c) 可重定位目标文件的 `.data` 节

**图 7-20 练习题 7.13 的示例代码**

### 7.14 \*\*\*

考虑图 7-21 中的 C 代码和相应的可重定位目标模块。

* A.确定当模块被重定位时，链接器将修改 `.text` 中的哪些指令。
对于每条这样的指令，列出它的重定位条目中的信息:节偏移、重定位类型和符号名字。
* B.确定当模块被重定位时，链接器将修改 `.data` 中的哪些数据目标。
对于每条这样的指令，列出它的重定位条目中的信息:节偏移、重定位类型和符号名字。

可以随意使用诸如 `OBJDUMP` 之类的工具来帮助你解答这个题目。

```c
int relo3(int val) {
    switch (val) {
    case 100:
        return(val);
    case 101:
        return(val+1);
    case 103: case 104:
        return(val+3);
    case 105:
        return(val+5);
    default:
        return(val+6);
    }
}
```

(a) C 代码

```x86asm
1 00000000 <relo3>:
2    0: 55                      push %ebp
3    1: 89 e5                   mov %esp,%ebp
4    3: 8b 45 08                mov 0x8(%ebp),%eax
5    6: 8d 50 9c                lea 0xffffff9c(%eax),%edx
6    9: 83 fa 05                cmp $0x5,%edx
7    c: 77 17                   ja 25 <relo3+0x25>
8    e: ff 24 95 00 00 00 00    jmp *0x0(,%edx,4)
9   15: 40                      inc %eax
10  16: eb 10                   jmp 28 <relo3+0x28>
11  18: 83 c0 03                add $0x3,%eax
12  1b: eb 0b                   jmp 28 <relo3+0x28>
13  1d: 8d 76 00                lea 0x0(%esi),%esi
14  20: 83 c0 05                add $0x5,%eax
15  23: eb 03                   jmp 28 <relo3+0x28>
16  25: 83 c0 06                add $0x6,%eax
17  28: 89 ec                   mov %ebp,%esp
18  2a: 5d                      pop %ebp
19  2b: c3                      ret
```

(b) 可重定位目标文件的 `.text` 节

```x86asm
This is the jump table for the switch statement
1 0000 28000000 15000000 25000000 18000000  4 words at offsets 0x0,0x4,0x8, and 0xc
2 0010 18000000 20000000                    2 words at offsets 0x10 and 0x14
```

(c) 可重定位目标文件的 `.rodata` 节

**图 7-21 练习题 7.14 示例代码**

### 7.15 \*\*\*

完成下面的任务将帮助你更熟悉处理目标文件的各种工具。

* A. 在你的系统上，`libc.a` 和 `libm.a` 的版本中包含多少目标文件?
* B. `gcc -O2` 产生的可执行代码与 `gcc -O2 -g` 产生的不同吗?
* C. 在你的系统上，GCC 驱动程序使用的是什么共享库?