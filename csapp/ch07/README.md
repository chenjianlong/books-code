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
