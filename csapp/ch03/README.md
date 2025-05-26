# 第3章 程序的机器级表示

## 常见操作命令

* 将 c 文件编译成汇编语言，指定为 32 位，i386 兼容

```sh
gcc -m32 -mtune=i386 -S code.c
```

* 将汇编语言编译成机器码，同样是 32 位，i386 兼容

```sh
as --32 -march=i386 code.s -o code.o
```

* 将 object 文件反汇编成机器码和汇编语言

```sh
objdump -d code.o
```

### 3.4.2 数据传送指令

|指令|效果|描述|
|-|-|-|
|MOV S,D|D ← S|传送|
|movb</br>movw</br>movl|传送字节</br>传送字</br>传送双字||
|MOVS S, D|D ← 符号扩展（S）|传送符号扩展的字节|

## 练习题

### 练习题 3.1

假设下面的值存放在指明的存储器地址和寄存器中：

|地址|值|
|-|-|
|0x100|0xFF|
|0x104|0xAB|
|0x108|0x13|
|0x10C|0x11|

|寄存器|值|
|-|-|
|%eax|0x100|
|%ecx|0x1|
|%edx|0x3|

填写下面，给出所示操作数的值。

|操作数|值|
|-|-|
|%eax||
|0x104||
|$0x108||
|(%eax)||
|4(%eax)||
|9(%eax,%edx)||
|260(%ecx,%edx)||
|0xFC(,%ecx,4)||
|(%eax,%edx,4)||

答案：

|操作数|值|注释|
|-|-|-|
|%eax|0x100|寄存器|
|0x104|0xAB|绝对地址|
|$0x108|0x108|立即数|
|(%eax)|0xFF|地址 0x100|
|4(%eax)|0xAB|地址 0x104|
|9(%eax,%edx)|0x11|地址 0x10C|
|260(%ecx,%edx)|0x13|地址 0x108|
|0xFC(,%ecx,4)|0xFF|地址 0x100|
|(%eax,%edx,4)|0x11|地址 0x10C|

### 练习题 3.2

对于下面汇编代码的每一行，根据操作数，确定适当的指令后缀。（例如，move 可以被重写成 movb、movw 或者 movl。）

```asm
1   mov %eax, (%esp)
2   mov (%eax), %dx
3   mov $0xFF, %bl
4   mov (%esp,%edx,4), %dh
5   push $0xFF
6   mov %dx, (%eax)
7   pop %edi
```

答案：

```asm
1   movl %eax, (%esp)
2   movw (%eax), %dx
3   movb $0xFF, %bl
4   movb (%esp,%edx,4), %dh
5   pushl $0xFF
6   movw %dx, (%eax)
7   popl %edi
```

### 练习题 3.3

当我们调用汇编器的时候，下面代码的每一行都会产生一个错误消息。解释每一行都是哪里出了错。

```asm
1   movb $0xF, (%bl)
2   movl %ax, (%esp)
3   movw (%eax),4(%esp)
4   movb %ah,%sh
5   movl %eax,$0x123
6   movl %eax,%dx
7   movb %si, 8(%ebp)
```

答案：

```asm
1   movb $0xF, (%bl)   // 寻址不能用 bl 寄存器，改成 ebx
2   movl %ax,(%esp)    // movl 表示操作数为双字，而 ax 为字寄存器，改为 eax
3   movw (%eax),4(%esp) // 不支持端跟目标操作数均为内存寻址
4   movb %ah,%sh // 没有 sh 寄存器
5   movl %eax,$0x123 // 目的为立即数
6   movl %eax,%dx // 无法将双字寄存器赋值给字寄存器
7   movb %si,8(%ebp) // si 为字寄存器,指令需要改为 movw
```

### 练习题 3.4

假设变了 v 和 p 被声明为类型

```c
src_t v;
dest_t *p;
```

这里 src_t 和 dest_t 是用 typedef 声明的数据类型。
我们想使用适当的数据传送指令来实现下面的操作

```c
*p = (dest_t) v;
```

此处，v 存储在寄存器 %eax 适当命名的部分中（也就是 %eax、%ax 或 %al），而指针 p 存储在寄存器 %edx 中。

对于下列 src_t 和 dest_t 的组合，写一行汇编代码进行适当的数据传送。
记住，在 C 语言中，对执行既涉及大小变化又涉及符号改变的强制类型转换时，操作应该先改变符号（参见 2.2.6 节）。

|src_t|dest_t|指令|
|-|-|-|
|int|int|movl %eax, (%edx)|
|char|int||
|char|unsigned||
|unsigned char|int||
|int|char||
|unsigned|unsigned char|
|unsigned|int||

答案:

|src_t|dest_t|指令|
|-|-|-|
|int|int|movl %eax, (%edx)|
|char|int|movsbl %al, (%edx)|
|char|unsigned|movsbl %al, (%edx)|
|unsigned char|int|movzbl %al, (%edx)|
|int|char|movb %al, (%edx)|
|unsigned|unsigned char|movb %al, (%edx)|
|unsigned|int|movl %eax, (%edx)|

### 练习题 3.5

已知信息如下。将一个原型为

```c
void decode1(int *xp, int *yp, int *zp);
```

的函数编译成汇编代码。代码体如下：

```asm
    xp at %ebp+8, yp at %ebp+12, zp at %ebp+16
1   movl    8(%ebp), %edi
2   movl    12(%ebp), %edx
3   movl    16(%ebp), %ecx
4   movl    (%edx), %ebx
5   movl    (%ecx), %esi
6   movl    (%edi), %eax
7   movl    %eax, (%edx)
8   movl    %ebx, (%ecx)
9   movl    %esi, (%edi)
```

参数 xp、yp 和 zp 分别存储在相对于寄存器 %ebp 中地址值的偏移 8、12 和 16 的地方。
请写出以上汇编代码的 decode1 等效的 C 代码。

答案：

```asm
    xp at %ebp+8, yp at %ebp+12, zp at %ebp+16
1   movl    8(%ebp), %edi # xp
2   movl    12(%ebp), %edx # yp
3   movl    16(%ebp), %ecx # zp
4   movl    (%edx), %ebx # ebx = *yp
5   movl    (%ecx), %esi # esi = *zp
6   movl    (%edi), %eax # eax = *xp
7   movl    %eax, (%edx) # *yp = *xp
8   movl    %ebx, (%ecx) # *zp = *yp
9   movl    %esi, (%edi) # *xp = *zp
```

```c
void decode1(int *xp, int *yp, int *zp)
{
    int t = *yp;
    *yp = *xp;
    *xp = *zp;
    *zp = t;
}
```

### 练习题 3.6

假设寄存器 %eax 的值为 x，%ecx 的值为 y。填写下表，指明下面每条汇编代码指令存储在寄存器 %edx 中的值：

|指令|结果|
|-|-|
|leal 6(%eax),%edx||
|leal (%eax,%ecx),%edx||
|leal (%eax,%ecx,4),%edx||
|leal 7(%eax,%eax,8),%edx||
|leal 0xA(,%eax,4),%edx||
|leal 9(%eax,%ecx,2),%edx||

答案：

|指令|结果|
|-|-|
|leal 6(%eax),%edx|x+6|
|leal (%eax,%ecx),%edx|2x|
|leal (%eax,%ecx,4),%edx|5x|
|leal 7(%eax,%eax,8),%edx|9x+7|
|leal 0xA(,%eax,4),%edx|4x+0xA|
|leal 9(%eax,%ecx,2),%edx|3x+9|

### 练习题 3.7

假设下面的值存放在指定的存储器地址和寄存器中：

|地址|值|
|-|-|
|0x100|0xFF|
|0x104|0xAB|
|0x108|0x13|
|0x10C|0x11|

|寄存器|值|
|-|-|
|%eax|0x100|
|%ecx|0x1|
|%edx|0x3|

填写下表，给出下面指令的效果，说明将被更新的寄存器或存储器的位置，以及得到的值。

|指令|目的|值|
|-|-|-|
|addl %ecx,(%eax)|||
|subl %edx,4(%eax)|||
|imull $16,(%eax,%edx,4)|||
|incl 8(%eax)|||
|decl %ecx|||
|subl %edx,%eax|||

答案：

|指令|目的|值|
|-|-|-|
|addl %ecx,(%eax)|0x100|0x100|
|subl %edx,4(%eax)|0x104|0xA8|
|imull $16,(%eax,%edx,4)|0x10C|0x110|
|incl 8(%eax)|0x108|0x14|
|decl %ecx|%ecx|0x0|
|subl %edx,%eax|%eax|0xFD|

### 练习题 3.8

假设我们想生成以下 C 函数的汇编代码：

```c
int shift_left2_rightn(int x, int n)
{
    x <<= 2;
    x >>= n;
    return x;
}
```

下面这段汇编代码执行实际的移位，并将最后的结果放在寄存器 %eax 中。
此处省略了两条关键的指令。
参数 x 和 n 分别存放在存储器中相对于寄存器 %ebp 中地址偏移 8 和 12 的地方。

```asm
1   movl 8(%ebp), %eax      Get x
2   __________________      x <<= 2
3   movl 12(%ebp), %ecx     Get n
4   __________________      x >>= n
```

答案：

```asm
1   movl 8(%ebp), %eax      Get x
2   sall 2, %eax            x <<= 2
3   movl 12(%ebp), %ecx     Get n
4   sarl %ecx, %eax         x >>= n
```

### 练习题 3.9

图 3-8a 中函数有以下变种，有些表达式用空格替代：

```c
1   int arith(int x,
2             int y,
3             int z)
4   {
5       int t1 = ___________;
6       int t2 = ___________;
7       int t3 = ___________;
8       int t4 = ___________;
9       return t4;
10  }
```

实现这些表达式对应的汇编代码如下：

```asm
    x at %ebp+8, y at %ebp+12, z at %ebp+16
1   movl 12(%ebp), %eax
2   xorl 8(%ebp), %eax
3   sarl $3, %eax
4   notl %eax
5   subl 16(%ebp), %eax
```

基于这些汇编代码，填写 C 语言代码中缺失的部分。

答案：

```c
1   int arith(int x,
2             int y,
3             int z)
4   {
5       int t1 = x ^ y;
6       int t2 = t1 << 3;
7       int t3 = ~t2;
8       int t4 = t3 - z;
9       return t4;
10  }
```

### 练习题 3.10

常常可以看见以下形式的汇编代码行：

```asm
xorl %edx,%edx
```

但是在产生这段汇编代码的 C 代码中，并没有出现 EXCLUSIVE-OR 操作。

* A 解释这条特殊的 EXCLUSIVE-OR 指令的效果，它实现了什么有用的操作。
* B 更直接表达这个操作的汇编代码是什么？
* C 比较一下同样一个操作的两种不同实现的编码字节长度。

答案：

* A 将 %edx 置为 0
* B movl 0, %edx
* C 通过反汇编可知：

xor 占用两个字节

```
0:   31 d2                   xor    %edx,%edx
```

movl 0, %edx 占用 5 个字节

```
0:   8b 15 00 00 00 00       mov    0x0,%edx
```

### 练习题 3.11

修改有符号除法的汇编代码，使它计算数 x 和 y 的无符号商和余数，并将结果存放在栈上。

```asm
; x at %ebp+8, y at %ebp+12
movl    8(%ebp),%edx    Put x in %edx
cltd                    Sign extend into %edx
idivl   12(%ebp)        Divide by y
movl    %eax, 4(%esp)   Store x/y
movl    %edx, (%esp)    Store x%y
```

答案：

```asm
; x at %ebp+8, y at %ebp+12
movl    8(%ebp),%edx    Put x in %edx
xorl    %edx,%edx       Set %edx to 0
divl    12(%ebp)        Divide by y
movl    %eax, 4(%esp)   Store x/y
movl    %edx, (%esp)    Store x%y
```

### 练习题 3.12

考虑下面的 C 函数原型，其中，num_t 是用 typedef 声明的数据类型。

```c
void store_prod(num_t *dest, unsigned x, num_t y) {
    *dest = x*y;
}
```

GCC 产生以下汇编代码来实现计算的主体：

```asm
dest at %ebp+8, x at %ebp+12, y at %ebp+16
1   movl    12(%ebp),%eax
2   movl    20(%ebp),%ecx
3   imull   %eax,%ecx
4   mull    16(%ebp)
5   leal    (%ecx,%edx),%edx
6   movl    8(%ebp),%ecx
7   movl    %eax,(%ecx)
8   movl    %edx,4(%ecx)
```

可以看到，这段代码需要读两次内存来取参数 y（第2行和第4行），两个乘法（第3行和第4行），
以及两次内存写来存储结果（第7行和第8行）。

* A. num_t 是什么数据类型的。
* B. 描述用来计算乘积的算法，并证明它是正确的。

答案：

* A. 我们可以看到，这个程序是在 64 位数据上进行多精度操作。还可以看到，64位乘法操作（第4行）使用的是无符号运算，因此我们可以确定 num_t 是 unsigned long long。（PS：不要被第 3 行的 imull 指令迷惑了，两个 32 位无符号乘法和补码乘法结果的低 32 位级表示是一样的,可以复习下第2章的整数乘法部分，或者查看：[整数运算](https://cs-cjl.com/2025/02_01_integer_operations#sideNavTitle4)）
* B. y = y<sub>h</sub> ∙ 2<sup>32</sup>+y<sub>l</sub>，这里 y<sub>h</sub> 和 y<sub>l</sub> 分别是高 32 位和低 32 位表示的值。因此我们可以计算 x ∙ y = x ∙ y<sub>h</sub> ∙ 2<sup>32</sup>+x ∙ y<sub>l</sub>。
乘积的完整表示是 96 位长，但是我们只需要低 64 位。
因此可以设 s 为 x ∙ y<sub>h</sub> 的低 32 位，而 t 为 x ∙ y<sub>l</sub> 的完整的 64 位乘积，可以将之划分为高位部分 t<sub>h</sub> 和低位部分 t<sub>l</sub>。
最终的结果是 t<sub>l</sub> 是低位部分，而 s + t<sub>h</sub> 是高位部分。

这里是添加了注释的汇编代码：

```asm
dest at %ebp+8, x at %ebp+12, y at %ebp+16
1   movl    12(%ebp),%eax           Get x
2   movl    20(%ebp),%ecx           Get y_h
3   imull   %eax,%ecx               Compute s = x*y_h
4   mull    16(%ebp)                Compute t = x*y_h
5   leal    (%ecx,%edx),%edx        Add s to t_h
6   movl    8(%ebp),%ecx            Get dest
7   movl    %eax,(%ecx)             Store t_l
8   movl    %edx,4(%ecx)            Store s+t_h
```

### 练习题 3.13

考虑以下 C 语言代码：

```c
int comp(data_t a, data_t b) {
    return a COMP b;
}
```

它给出了参数 a 和 b 之间比较的一般形式。
这里，我们可以用 typedef 来声明 data_t，从而设置参数的数据类型：用一条 #define 声明来定义 COMP，从而设置比较。

假设 a 在 %edx 中，b 在 %eax 中。对于下面每个指令序列，确定哪种数据类型 data_t 和比较 COMP 会导致编译器产生这样的代码。（可能有多个正确答案，请列出所有的正确答案。）

* A.
```asm
cmpl    %eax,%edx
setl    %al
```
* B.
```asm
cmpw    %ax,%dx
setge   %al
```
* C.
```asm
cmpb    %al,%dl
setb    %al
```
* D.
```asm
cmpl    %eax,%edx
setne   %al
```

答案：

* A data_t 为 int COMP 为 &lt;
* B data_t 为 short COMP 为 &gt;=
* C data_t 为 unsigned char COMP 为 &lt;
* D data_t 为 int 或者 unsigned 或者指针 COMP 为 !=

### 练习题 3.14

考虑以下 C 语言代码：

```c
int test(data_t a) {
    return a TEST 0;
}
```

它给出了参数 a 和 0 之间比较的一般形式。
这里，我们可以用 typedef 来声明 data_t，从而设置参数的数据类型；通过用 #define 来声明 TEST，从而设置比较的类型。
对于下面每个指令序列，确定哪种数据类型 data_t 和比较 TEST 会导致编译器产生这样的代码。
（可能有多个正确答案，请列出所有正确答案。）

* A.
```asm
testl   %eax,%eax
setne   %al
```
* B.
```asm
testw   %ax,%ax
sete    %al
```
* C.
```asm
testb   %al,%al
setg    %al
```
* D.
```asm
testw   %ax,%ax
seta    %al
```

答案：

* A. data_t 为 unsigned或int TEST 为 !=
* B. data_t 为 unsigned short或short TEST 为 =
* C. data_t 为 char TEST 为 &gt;
* D. data_t 为 unsigned short，TEST 为 &gt;

### 练习题 3.15

在下面这些反汇编二进制代码节选中，有些信息被 X 代替了。
回答下列关于这些指令的问题。

A. 下面 je 指令的目标是什么？（在此，你不需要知道任何有关 call 指令的信息。）

```
804828f:    74 05                   je      XXXXXXX
8048291:    e8 1e 00 00 00          call    80482b4
```

B. 下面 jb 指令的目标是什么？

```
8048357:    72 e7                   jb      XXXXXXX
8048359:    c6 05 10 a0 04 08 01    movb    0x1,0x804a010
```

C. mov 指令的地址是多少？

```
XXXXXXX:    74 12                   je      8048391
XXXXXXX:    b8 00 00 00 00          mov     $0x0,%eax
```

D. 在下面的代码中，跳转目标的编码是 PC 相关的，且是一个 4 字节的补码数。
字节按照从最低位到最高位的顺序列出，反映在 IA32 的小端法字节顺序。
跳转目标的地址是什么？

```
80482bf:    e9 e0 ff ff ff          jmp     XXXXXXX
80482c4:    90                      nop
```

E. 请解释右边的注释与左边的字节代码之间的关系。

```
80482aa:    ff 25 fc 9f 04 08       jmp     *0x8049ffc
```

答案：

A. 下面 je 指令的目标是什么？（在此，你不需要知道任何有关 call 指令的信息。）

```
804828f:    74 05                   je      8048296
8048291:    e8 1e 00 00 00          call    80482b4
```

B. 下面 jb 指令的目标是什么？

```
8048357:    72 e7                   jb      8048340
8048359:    c6 05 10 a0 04 08 01    movb    0x1,0x804a010
```

C. mov 指令的地址是多少？

```
804837d:    74 12                   je      8048391
804837f:    b8 00 00 00 00          mov     $0x0,%eax
```

D. 在下面的代码中，跳转目标的编码是 PC 相关的，且是一个 4 字节的补码数。
字节按照从最低位到最高位的顺序列出，反映在 IA32 的小端法字节顺序。
跳转目标的地址是什么？

```
80482bf:    e9 e0 ff ff ff          jmp     00000020
80482c4:    90                      nop
```

E. 请解释右边的注释与左边的字节代码之间的关系。

```
80482aa:    ff 25 fc 9f 04 08       jmp     *0x8049ffc
```

jmp 星号表示进行绝对地址跳转,对应字码中前两位 ff 25，地址为：0x8049ffc，对应字节代码中的 fc 9f 04 08，字节码中的地址是以小端形式给出的。

参考：[AT&T x86 Assembly](https://daksh.github.io/ATT-Assembly/)

### 练习题 3.16

已知下列 C 代码：

```c
void cond(int a, int *p)
{
    if (p && a > 0)
        *p += a;
}
```

GCC 对函数体产生的汇编代码如下：

```asm
a %ebp+8，p at %ebp+12

    movl        8(%ebp),%edx
    movl        12(%ebp),%eax
    testl       %eax,%eax
    je          .L3
    testl       %edx,%edx
    jle         .L3
    addl        %edx,(%eax)
.L3:
```

A. 按照图 3-13 b 中所示的风格，用 C 语言写一个 goto 版本，执行同样的计算，并模拟汇编代码的控制流。
像示例中那样给汇编代码加上注解可能会有帮助。

B. 请说明为什么 C 语言代码中只有一个 if 语句，而汇编代码包含两个条件分支。

答案：

A.

汇编加注释：

```asm
a %ebp+8，p at %ebp+12

    movl        8(%ebp),%edx        Get a
    movl        12(%ebp),%eax       Get p
    testl       %eax,%eax           test p
    je          .L3                 if p == 0 goto L3
    testl       %edx,%edx           test a
    jle         .L3                 if a <= 0 goto L3
    addl        %edx,(%eax)         *p += a
.L3:
```

等效 C 语言：

```c
void cond(int a, int *p)
{
    if (!p) goto L3;
    if (a<=0) goto L3;

    *p += a;
L3:
}
```

B. C 代码中的 if 语句有两个条件判断并将这两个条件判断的结果做了与操作，对应到汇编语言至少需要两次条件判断

### 练习题 3.17

将 if 语句翻译成 goto 代码的另一种可行的规则如下：

```
    t = test-expr;
    if (t)
        goto true;
    else-statement
    goto done;
true:
    then-statement
done:
```

* A. 基于这种规则，重写 absdiff 的 goto 版本。
* B. 你能想出选用一种规则而不选用另一种规则的理由吗？

答案：

A.

```c
int yagotodiff(int x, int y)
{
    int result;
    if (x < y)
        goto x_lt_y;
    result = x - y;
    goto done;
x_lt_y:
    result = y - x;
done:
    return result;
}
```

B. 大多数情况下，可在这两种方式中任意选择。
但是原来的方法对常见的没有 else 语句的情况更好一些。
对于这种情况，我们只简单地将翻译规则修改如下：

```
    t = test-expr;
    if (!t)
        goto done;
    then-statement
done:
```

基于替代规则的翻译更麻烦一些。

### 练习题 3.18

从如下形式的 C 语言代码开始：

```c
int test(int x, int y) {
    int val = ___________;
    if (___________) {
        if (___________)
            val = ___________;
        else
            val = ___________;
    } else if (___________)
        val = ___________;
    return val;
}
```

GCC 产生如下汇编代码：

```asm
x at %ebp+8, y at %ebp+12

    movl    8(%ebp), %eax
    movl    12(%ebp), %edx
    cmpl    $-3, %eax
    jge     .L2
    cmpl    %edx, %eax
    jle     .L3
    imull   %edx, %eax
    jmp     .L4
.L3:
    leal    (%edx,%eax), %eax
    jmp     .L4
.L2:
    cmpl    $2, %eax
    jg      .L5
    xorl    %edx, %eax
    jmp     .L4
.L5:
    subl    %edx, %eax
.L4:
```

填写 C 代码中缺失的表达式。为了让代码能够符合 C 语言代码模板，你需要还原 GCC 对计算所做的某些重排序。

答案：

```asm
x at %ebp+8, y at %ebp+12

    movl    8(%ebp), %eax           Load x to %eax
    movl    12(%ebp), %edx          Load y to %edx
    cmpl    $-3, %eax
    jge     .L2                     if x >= -3 goto .L2
    cmpl    %edx, %eax
    jle     .L3                     if x <= y goto .L3
    imull   %edx, %eax              val = x * y
    jmp     .L4
.L3:
    leal    (%edx,%eax), %eax       val = x + y
    jmp     .L4
.L2:
    cmpl    $2, %eax
    jg      .L5                     if x > 2 goto .L5
    xorl    %edx, %eax              val = x ^ y
    jmp     .L4
.L5:
    subl    %edx, %eax              val = x - y
.L4:
```

对应的 C 代码为：

```c
int test(int x, int y) {
    int val = x - y;
    if (x < -3) {
        if (x > y)
            val = x * y;
        else
            val = x + y;
    } else if (x <= 2)
        val = x - y;
    return val;
}
```

### 练习题 3.19

* A. 用一个 32 位 int 表示 n!，最大的 n 的值是多少？
* B. 如果用一个 64 位 long long int 表示，最大的 n 的值是多少？

答案：

参考代码：[ex3.19.c](ex3.19.c)

* A. 13
* B. 20

### 练习题 3.20

已知 C 代码如下：

```c
1 int dw_loop(int x, int y, int n) {
2     do {
3        x += n;
4        y *= n;
5        n--;
6     } while ((n > 0) && (y < n>));
7     return x;
8 }
```

GCC 产生的汇编代码如下：

```asm
x at %ebp+8, y at %ebp+12, n at %ebp+16

1       movl    8(%ebp), %eax
2       movl    12(%ebp), %ecx
3       movl    16(%ebp), %edx
4   .L2:
5       addl    %edx, %eax
6       imull   %edx, %ecx
7       subl    $1, %edx
8       testl   %edx, %edx
9       jle     .L5
10      cmpl    %edx, %ecx
11      jl      .L2
12  .L5:
```

* A. 创建一个寄存器使用表，参考图 3-14b。
* B. 指出 C 代码中的 test-expr 和 body-statement，以及汇编代码中相应的行。
* C. 给汇编代码添加一些注释，描述程序的操作，参考图 3-14c。

答案：

A.

|寄存器|变量|初始值|
|-|-|-|
|%eax|x|x|
|%ecx|y|y|
|%edx|n|n|

B.

C 代码中的 test-expr 为第 6 行中的 `(n > 0) && (y < n)` 对应汇编代码中的 8-11 行。
C 代码中的 body-statement 为 3-5 行，对应汇编代码中的 5-7 行。

C.

```asm
Argument x at %ebp+8, y at %ebp+12, n at %ebp+16
Registers: x at %eax y at %ecx n at %edx, result in %eax

1       movl    8(%ebp), %eax           Get x
2       movl    12(%ebp), %ecx          Get y
3       movl    16(%ebp), %edx          Get n
4   .L2:                            loop:
5       addl    %edx, %eax              Compute x += n
6       imull   %edx, %ecx              Compute y *= n
7       subl    $1, %edx                Compute n--
8       testl   %edx, %edx              test n
9       jle     .L5                     if n <= 0 exit loop
10      cmpl    %edx, %ecx              compare y:n
11      jl      .L2                     if y<n goto loop
12  .L5:
```

### 练习题 3.21

对于下面的 C 代码：

```c
1   int loop_while(int a, int b)
2   {
3       int result = 1;
4       while (a < b) {
5           result *= (a+b);
6           a++;
7       }
8       return result;
9   }
```

GCC产生如下汇编代码：

```asm
a at %ebp+8, b at %ebp+12

1       movl    8(%ebp), %ecx
2       movl    12(%ebp), %ebx
3       movl    $1, %eax
4       cmpl    %ebx, %ecx
5       jge     .L11
6       leal    (%ebx,%ecx), %edx
7       movl    $1, %eax
8   .L12:
9       imull   %edx, %eax
10      addl    $1, %ecx
11      addl    $1, %edx
12      cmpl    %ecx, %ebx
13      jg      .L12
14  .L11:
```

在产生这段代码的过程中，GCC 做了一个有趣的转换，实际上是引入了一个新的程序变量。

* A. 在第 6 行初始化寄存器 %edx，在第 11 行循环体内更新它的值。
让我们认为这是一个新的程序变量。请描述它与 C 代码中的变量之间的关系。
* B. 创建该函数的寄存器使用表。
* C. 给汇编代码添加一些注释，描述它的操作。
* D. (用C语言)写一个该函数的 goto 版本，用它模仿汇编代码程序如何运行。

答案：

A. %edx 对应 a+b

B.

|寄存器|变量|初始值|
|-|-|-|
|%eax|result|1|
|%ebx|b|b|
|%ecx|a|a|
|%edx|a+b|a+b|

C.

```asm
a at %ebp+8, b at %ebp+12

1       movl    8(%ebp), %ecx           Get a
2       movl    12(%ebp), %ebx          Get b
3       movl    $1, %eax                Set result = 1
4       cmpl    %ebx, %ecx              Compare a:b
5       jge     .L11                    if a >= b goto end
6       leal    (%ebx,%ecx), %edx       tmp = a + b
7       movl    $1, %eax                result = 1
8   .L12:                               loop:
9       imull   %edx, %eax              result *= tmp
10      addl    $1, %ecx                tmp++;
11      addl    $1, %edx                a++;
12      cmpl    %ecx, %ebx              Compare b:a
13      jg      .L12                    if b > a goto loop
14  .L11:                               end:
```

D.

```c
int loop_goto(int a, int b)
{
    int result = 1;
    if (a >= b) goto end;
loop:
    result *= (a+b);
    a++;
    if (b > a) goto loop;
end:
    return result
}
```

### 练习题 3.22

函数 fun_a 有如下整体结果：

```c
int fun_a(unsigned x) {
    int val = 0;
    while (________) {
        ________;
    }
    return ________;
}
```

GCC C编译器产生如下汇编代码：

```asm
    x at %ebp+8

1       movl    8(%ebp), %edx
2       movl    $0, %eax
3       testl   %edx, %edx
4       je      .L7
5   .L10:
6       xorl    %edx, %eax
7       shrl    %edx                Shift right by 1
8       jne     .L10
9   .L7:
10      andl    $1, %eax
```

逆向工程这段代码的操作，然后完成下面的作业：

* A. 更好汇编代码版本填写 C 代码中缺失的部分。
* B. 用自然语言描述这个函数是计算什么的。

答案：

* A.

汇编注释版：
```asm
    x at %ebp+8

1       movl    8(%ebp), %edx       Get x
2       movl    $0, %eax            Set val = 0
3       testl   %edx, %edx
4       je      .L7                 if x == 0 goto end
5   .L10:                           loop:
6       xorl    %edx, %eax          val ^= x
7       shrl    %edx                Shift right by 1（x >>= 1）
8       jne     .L10                if x != 0 goto loop
9   .L7:                            end:
10      andl    $1, %eax            val &= 1
```

对应 C 语言：

```c
int fun_a(unsigned x) {
    int val = 0;
    while (x) {
        val ^= x;
        x >>= 1;
    }
    return val & 0x1;
}
```

B. 判断 x 的二进制表示形式中 1 的个数的奇偶性，如果是奇数个 1 返回 1，如果是偶数个 1 返回 0。

### 练习题 3.23

函数 fun_b 有如下整体结构：

```c
int fun_b(unsigned x) {
    int val = 0;
    int i;
    for (________;________;________) {
        ________
    }
    return val;
}
```

GCC C编译器产生如下汇编代码：

```asm
    x at %ebp+8
1       movl    8(%ebp), %ebx
2       movl    $0, %eax
3       movl    $0, %ecx
4   .L13:
5       leal    (%eax,%eax), %edx
6       movl    %ebx, %eax
7       andl    $1, %eax
8       orl     %edx, %eax
9       shrl    %ebx                Shift right by 1
10      addl    $1, %ecx
11      cmpl    $32, %ecx
12      jne     .L13
```

逆向工程这段代码的操作，然后完成下面的作业：

* A. 根据汇编代码版本填写 C 代码中缺失的部分。
* B. 用自然语言描述这个函数是计算什么的。

答案：

A.


汇编加注释

```asm
    x at %ebp+8
1       movl    8(%ebp), %ebx       Get x
2       movl    $0, %eax            val = 0
3       movl    $0, %ecx            i = 0
4   .L13:                           loop:
5       leal    (%eax,%eax), %edx   tmp=2*val
6       movl    %ebx, %eax          val = x
7       andl    $1, %eax            val &= 0x1
8       orl     %edx, %eax          val |= tmp
9       shrl    %ebx                x >>= 1
10      addl    $1, %ecx            i++
11      cmpl    $32, %ecx           Compare i:32
12      jne     .L13                if i != 32 goto loop
```

C语言版：

```c
int fun_b(unsigned x) {
    int val = 0;
    int i;
    for (i=0; i != 32; i++) {
        int tmp = val << 1;
        val = x & 0x1;
        val |= tmp;
        x >>= 1;
    }
    return val;
}
```

B. 二进制比特翻转

### 练习题 3.24

在 C 语言中执行 continue 语句会导致程序跳到当前循环迭代的结尾。
当处理 continue 语句时，将 for 循环翻译成 while 循环的描述规则需要一些改进。
例如，考虑下面的代码：

```c
/* Example of for loop using a continue statement */
/* Sum even numbers between 0 and 9 */
int sum = 0;
int i;
for (int i = 0; i < 10; i++) {
    if (i & 1)
        continue;
    sum += i;
}
```

* A. 如果我们天真地直接应用将 for 循环翻译到 while 循环的规则，会得到什么呢？产生的代码会有什么错误呢？
* B. 如何用 goto 语句来替代 continue 语句，保证 while 循环的行为同 for 循环的行为完全一样。

答案：

* A

如果我们直接应用 将 for 循环翻译到 while 循环的规则，会得到如下代码：

```c
int sum = 0;
int i = 0
while (i < 10) {
    if (i & 1)
        continue;

    sum += i;
    i++;
}
```

产生的代码会是个无限循环。

* B

```c
int sum = 0;
int i = 0
while (i < 10) {
    if (i & 1)
        goto update_expr;

    sum += i;

update_expr:
    i++;
}
```

### 练习题 3.25

在 Pentium 4 上运行，当分支行为模式非常容易预测时，我们的代码需要大约 16 个时钟周期，而当模式是随机时，需要大约 31 个时钟周期。

* A. 预测错误处罚大约是多久？
* B. 当分支预测错误时，这个函数需要多少个时钟周期？

答案：

* A.

T<sub>OK</sub>=16
T<sub>OK</sub>+0.5*T<sub>MP</sub>=31

得到：

T<sub>MP</sub>=30

* B 46个周期

### 练习题 3.26

在下面的 C 函数中，我们对 OP 操作的定义是不完整的：

```c
#define OP ________ /* Unknown operator */

int arith(int x) {
    return x OP 4;
}
```

当编译时，GCC 会产生如下汇编代码：

```asm
    Register x in %edx

1   leal    3(%edx), %eax
2   testl   %edx, %edx
3   cmovns  %edx, %eax
4   sarl    $2, %eax            Return value in %eax
```

* A. OP 进行的是什么操作？
* B. 给代码添加注释，解释它是如何工作的。

答案：

* A. 运算符是 '/'。我们看到这个例子是通过右移来实现除以 2 的幂，参见 [除以 2 的幂](https://cs-cjl.com/2025/02_01_integer_operations#sideNavTitle7)

* B

```asm
    Register x in %edx

1   leal    3(%edx), %eax       tmp = x+3
2   testl   %edx, %edx          Test x
3   cmovns  %edx, %eax          if x >= 0, x = tmp
4   sarl    $2, %eax            Return temp >> 2 (=x/4)
```

### 练习题 3.27

C 代码开始的形式如下：

```c
1   int test(int x, int y) {
2       int val = ________;
3       if (________) {
4           if (________)
5               val = ________;
6           else
7               val = ________;
8       } else if (________)
9           val = ________;
10      return val;
11  }
```

GCC 带命令行设置 '-march=i686'，产生如下汇编代码：

```asm
    x at %ebp+8, y at %ebp+12

1       movl    8(%ebp), %ebx
2       movl    12(%ebp), %ecx
3       testl   %ecx, %ecx
4       jle     .L2
5       movl    %ebx, %ecx
6       subl    %ecx, %edx
7       movl    %ecx, %eax
8       xorl    %ebx, %eax
9       cmpl    %ecx, %ebx
10      comvl   %edx, %eax
11      jmp     .L4
12  .L2:
13      leal    0(,%ebx,4), %edx
14      leal    (%ecx, %ebx), %eax
15      cmpl    $-2, %ecx
16      cmovge  %edx, %eax
17  .L4:
```

填补C 代码中缺失的表达式。

答案：

```asm
    x at %ebp+8, y at %ebp+12

1       movl    8(%ebp), %ebx           Get x
2       movl    12(%ebp), %ecx          Get y
3       testl   %ecx, %ecx              Test y
4       jle     .L2                     if y <= 0 goto .L2
5       movl    %ebx, %edx              tmp = x;
6       subl    %ecx, %edx              tmp -= y
7       movl    %ecx, %eax              result = y
8       xorl    %ebx, %eax              result ^= x
9       cmpl    %ecx, %ebx              Compare x:y
10      comvl   %edx, %eax              if x < y, result = tmp
11      jmp     .L4                     Goto end
12  .L2:
13      leal    0(,%ebx,4), %edx        tmp = 4 * x
14      leal    (%ecx, %ebx), %eax      result = x + y
15      cmpl    $-2, %ecx               Compare y:-2
16      cmovge  %edx, %eax              if y >= -2, result = tmp
17  .L4:                                end:
```

C 代码补全：

```c
1   int test(int x, int y) {
2       int val = 4 * x;
3       if (y > 0) {
4           if (x >= y)
5               val = x - y;
6           else
7               val = x ^ y;
8       } else if (y < -2)
9           val = x + y;
10      return val;
11  }
```

### 练习题 3.28

下面 C 函数省略了 switch 语句的主体。
在 C 代码中，情况标号是不连续的，并且有些情况还有多个标号。

```c
int switch2(int x) {
    int result = 0;
    switch (x) {
        /* Body of switch statement omitted */
    }
    return result;
}
```

在编译函数时，GCC 为程序的初始部分以及跳转表生成了以下汇编代码。
变量 x 开始时位于相对于寄存器 %ebp 偏移量为 8 的地方。

```asm
    x at %ebp+8

1   movl    8(%ebp), %eax
    Setup jump table access
2   addl    $2, %eax
3   cmpl    $6, %eax
4   ja      .L2
5   jmp     *.L8(,%eax,4)
```

跳转表

```asm
    Jump table for switch2

1   .L8:
2       .long   .L3
3       .long   .L2
4       .long   .L4
5       .long   .L5
6       .long   .L6
7       .long   .L6
8       .long   .L7
```

根据上述信息回答下列问题：

* A. switch 语句体内情况标号的值是多少？
* B. C 代码中哪些情况有多个标号？

答案：

* A 对应跳转表，标号值分别为：-2、0、1、2、3、4、5、default
* B 2、3

### 练习题 3.29

已知一个通用结构的 C 函数 switcher:

```c
1   int switcher(int a, int b, int c)
2   {
3       int answer;
4       switch (a) {
5       case ________:          /* Case A */
6           c = ________;
7           /* Fall through */
8       case ________:          /* Case B */
9           answer = ________;
10          break;
11      case ________:          /* Case C */
12      case ________:          /* Case D */
13          answer = ________;
14          break;
15      case ________:          /* Case E */
16          answer = ________;
17          break;
18      default:
19          answer = ________;
20      }
21      return answer;
22  }
```

GCC 产生如下所示的汇编代码和跳转表。

填写 C 代码中缺失的部分。
除了情况标号 C 和 D 的顺序之外，将不同情况填入这个模板的方式是唯一的。

```asm
    a at %ebp+8, b at %ebp+12, c at %ebp+16

1       movl    8(%ebp), %eax       1   .L7:
2       cmpl    $7, %eax            2       .long   .L3
3       ja      .L2                 3       .long   .L2
4       jmp     *.L7(,%eax,4)       4       .long   .L4
5   .L2:                            5       .long   .L2
6       movl    12(%ebp), %eax      6       .long   .L5
7       jmp     .L8                 7       .long   .L6
8   .L5:                            8       .long   .L2
9       movl    $4, $eax            9       .long   .L4
10      jmp     .L8
11  .L6:
12      movl    12(%ebp), %eax
13      xorl    $15, %eax
14      movl    %eax, 16(%ebp)
15  .L3:
16      movl    16(%ebp), %eax
17      addl    $112, %eax
18      jmp     .L8
19  .L4:
20      movl    16(%ebp), %eax
21      addl    12(%ebp), %eax
22      sall    $2, %eax
23  .L8:
```

答案：

只有 .L6 没有 jmp 语句，因此 .L6 对应 Case A，.L3 对应 Case B。
只有 .L4 是有两种情况下都跳转到此分支，因此对应了 Case C和D。

```c
1   int switcher(int a, int b, int c)
2   {
3       int answer;
4       switch (a) {
5       case 5:                     /* Case A */
6           c = b ^ 15;
7           /* Fall through */
8       case 0:                     /* Case B */
9           answer = c + 112;
10          break;
11      case 2:                     /* Case C */
12      case 7:                     /* Case D */
13          answer = (c + b) << 2;
14          break;
15      case 4:                     /* Case E */
16          answer = 4;             /* 或者是 answer = a */
17          break;
18      default:
19          answer = b;
20      }
21      return answer;
22  }
```

### 练习题 3.30

下面的代码片段常常出现在库函数的编译版本中：

```asm
1       call next
2   next:
3       popl %eax
```

* A. 寄存器 %eax 被设置成了什么值？
* B. 解释为什么这个调用没有与之匹配的 ret 指令。
* C. 这段代码完成了什么功能？

答案：

* A. popl %eax 在内存中的地址
* B. 这个代码片段的目的是为了获取指令所在的内存地址，而不是为了进行过程调用
* B. 获取指令所在的内存地址 ,这是 IA32 中将程序计数器的值放到整数寄存器中的唯一方法。

### 练习题 3.31

在 GCC 为一个 C 过程产生的汇编代码的前部有下面这段代码：

```asm
1   subl    $12, %esp
2   movl    %ebx, (%esp)
3   movl    %esi, 4(%esp)
4   movl    %edi, 8(%esp)
5   movl    8(%ebp), %ebx
6   movl    12(%ebp), %edi
7   movl    (%ebx), %esi
8   movl    (%edi), %eax
9   movl    16(%ebp), %edx
10  movl    (%edx), %ecx
```

我们看到，将三个寄存器（%ebx、%esi 和 %edi）保存到了栈中（第2~4行）。
程序会修改它们，以及另外三个寄存器（%eax、%ecx和%edx）。
在过程结尾，寄存器 %edi、%esi和%ebx的值被恢复（没有显示出来），而其他三个寄存器就保持修改后的状态。

请解释在保存和恢复寄存器状态时表现出来的明显的矛盾。

答案：

这个练习是对寄存器使用规则的具体化讨论。
寄存器 %edi、%esi和%ebx 是被调用者保存的。
改变它们的值之前，过程必须将它们保存在栈中，在返回之前，要恢复它们。
其他三个寄存器是调用者保存的，改变它们不会影响调用者的行为。

### 练习题 3.32

一个 C 函数 fun 具有如下代码体：

```c
*p = d;
return x-c;
```

执行这个函数体的 IA32 代码如下：

```asm
1   movsbl  12(%ebp), %edx
2   movl    16(%ebp), %eax
3   movl    %edx, (%eax)
4   movswl  8(%ebp), %eax
5   movl    20(%ebp), %edx
6   subl    %eax, %edx
7   movl    %edx, %eax
```

写出函数 fun 的原型，给出参数 p、d、x 和 c 的类型和顺序。

答案：

汇编代码注释：

```asm
1   movsbl  12(%ebp), %edx      Get d
2   movl    16(%ebp), %eax      Get p
3   movl    %edx, (%eax)        *p = d
4   movswl  8(%ebp), %eax       Get c
5   movl    20(%ebp), %edx      Get x
6   subl    %eax, %edx          x-c
7   movl    %edx, %eax          return x-c
```

函数 fun 的原型为：

```c
int fun(short c, char d, int *p, int x);
```

### 练习题 3.33

给定 C 函数如下：

```c
1   int proc(void)
2   {
3       int x, y;
4       scanf("%x %x", &y, &x);
5       return x-y;
6   }
```

GCC 产生以下汇编代码：

```asm
1   proc:
2       pushl   %ebp
3       movl    %esp, %ebp
4       subl    $40, %esp
5       leal    -4(%ebp), %eax
6       movl    %eax, 8(%esp)
7       leal    -8(%ebp), %eax
8       movl    %eax, 4(%esp)
9       movl    $.LC0, (%esp)               Pointer to string "%x %x"
10      call    scanf
        Diagram stack fram at this point
11      movl    -4(%ebp), %eax
12      subl    -8(%ebp), %eax
13      leave
14      ret
```

假设过程 proc 开始执行时，寄存器的值如下：

|寄存器|值|
|-|-|
|%esp|0x800040|
|%ebp|0x800060|

如果 proc 调用 scanf（第10行），而 scanf 从标准输入读入值 0x46 和 0x53。
假设字符串 "%x %x" 存放在存储器位置 0x300070 处。

* A. 第 3 行 %ebp 的值被设置成了多少？
* B. 第 4 行 %esp 的值被设置成了多少？
* C. 局部变量 x  和 y 的存放地址是什么？
* D. 画出就在 scanf 返回后 proc 的栈帧图。请包括尽可能多的关于栈帧元素的地址和内容的信息。
* E. 指出 proc 未使用的栈帧区域。

答案：

* A 0x80003C
* B 0x800014
* C y 的存放地址是 0x800034，x的存放地址是 0x800038
* D 

```
地址            内容            寄存器
0x800014    "%x %x" 地址        %esp 新值
0x800018    0x800034
0x80001C    0x800038
...
0x800034    0x46
0x800038    0x53
0x80003C    0x800060            %ebp
0x800040                        %esp 旧值
```

* E 0x800020~0x800033 的字节地址没有使用

### 练习题 3.34

一个具有通用结构的 C 函数如下：

```c
int rfun(unsigned x) {
    if (________)
        return ________;
    unsigned nx = ________;
    int rv = rfun(nx);
    return ________;
}
```

GCC 产生如下汇编代码（省略了建立和完成代码）：

```asm
1       movl    8(%ebp), %ebx
2       movl    $0, %eax
3       testl   %ebx, %ebx
4       je      .L3
5       movl    %ebx, %eax
6       shrl    %eax                Shift right by 1
7       movl    %eax, (%esp)
8       call    rfun
9       movl    %ebx, %edx
10      andl    $1, %edx
11      leal    (%edx, %eax), %eax
12  .L3:
```

* A. rfun 存储在被调用者保存寄存器 %ebx 中的值是什么？
* B. 填写上述 C 代码中缺失的表达式。
* C. 用自然语言描述这段代码计算的功能。

答案：

* A 入参 x
* B

```c
int rfun(unsigned x) {
    if (!x)
        return 0;
    unsigned nx = x >> 1;
    int rv = rfun(nx);
    return (nx & 1) + rv;
}
```

* C 计算 x 二进制 1 的个数

### 练习题 3.35

考虑下面的声明：

```c
short           S[7];
short          *T[3];
short         **U[6];
long double     V[8];
long double    *W[4];
```

填写下表，描述每个数组的元素大小、整个数组的大小以及元素 i 的地址：

|数组|元素大小|整个数组的大小|起始地址|元素 i|
|-|-|-|-|-|
|S|||x<sub>S</sub>||
|T|||x<sub>T</sub>||
|U|||x<sub>U</sub>||
|V|||x<sub>V</sub>||
|W|||x<sub>W</sub>||

答案：

|数组|元素大小|整个数组的大小|起始地址|元素 i|
|-|-|-|-|-|
|S|2|14|x<sub>S</sub>|x<sub>S</sub>+2\*i|
|T|4|12|x<sub>T</sub>|x<sub>T</sub>+4\*i|
|U|4|24|x<sub>U</sub>|x<sub>U</sub>+4\*i|
|V|12|96|x<sub>V</sub>|x<sub>V</sub>+12\*i|
|W|4|16|x<sub>W</sub>|x<sub>W</sub>+4\*i|

### 练习题 3.36

假设 short 短整型数组 S 的地址和整数索引 i 分别存放在寄存器 %edx 和 %ecx 中。
对下面每个表达式，给出它的类型、值表达式和汇编代码实现。
如果结果是指针的话，要保存在寄存器 %eax 中，如果是短整数，就保存在寄存器元素 %ax 中。

|表达式|类型|值|汇编代码|
|-|-|-|-|
|S+1||||
|S[3]||||
|&S[i]||||
|S[4*i+1]||||
|S+i-5||||

答案：

|表达式|类型|值|汇编代码|
|-|-|-|-|
|S+1|short*|x<sub>S</sub>+2|leal 2(%edx),%eax|
|S[3]|short|M[x<sub>S</sub>+6]|movw 6(%edx),%ax|
|&S[i]|short*|x<sub>S</sub>+2\*i|leal (%edx,%ecx,2), %eax|
|S[4*i+1]|short|M[x<sub>S</sub>+i\*i+2]|movw 2(%edx,%ecx,8), %ax|
|S+i-5|short*|x<sub>S</sub>+2\*i-10|leal -10(%edx,%ecx,2), %eax|

### 练习题 3.37

考虑下面的源代码，其中 M 和 N 是用 #define 声明的常数：

```c
1   int mat1[M][N];
2   int mat2[N][M];
3
4   int sum_element(int i, int j) {
5       return mat1[i][j] + mat2[j][i];
6   }
```

在编译这个程序中，GCC 产生如下汇编代码：

```asm
    i at %ebp+8, j at %ebp+12
1       movl        8(%ebp), %ecx
2       movl        12(%ebp), %edx
3       leal        0(,%ecx,8), %eax
4       subl        %ecx, %eax
5       addl        %edx, %eax
6       leal        (%edx,%edx,4), %edx
7       addl        %ecx, %edx
8       movl        mat1(,%eax,4), %eax
9       addl        mat2(,%edx,4), %eax
```

运用你的逆向工程技能，根据这段汇编代码，确定 M 和 N 的值。

答案：

给汇编代码添加注释：

```asm
    i at %ebp+8, j at %ebp+12
1       movl        8(%ebp), %ecx           Get i
2       movl        12(%ebp), %edx          Get j
3       leal        0(,%ecx,8), %eax        t1 = 8 * i
4       subl        %ecx, %eax              t1 = t1 - i = 7 * i
5       addl        %edx, %eax              t1 = 7 * i + j
6       leal        (%edx,%edx,4), %edx     t2 = 5 * j
7       addl        %ecx, %edx              t2 = 5 * j + i
8       movl        mat1(,%eax,4), %eax     result = mat1 + t1 * 4
9       addl        mat2(,%edx,4), %eax     result += mat2 + t2 * 4
```

mat1[i][j] = mat1 + L(C<sub>1</sub> \* i + j) = mat1 + (7 * i + j) \* 4

根据公式 3-1 可知 N = 7

mat2[j][i] = mat2 + L(C<sub>2</sub> \* j + i) = mat1 + (5 * j + i) \* 4

根据公式 3-1 可知 M = 5

### 练习题 3.38

下面的 C 代码将定长数组的对角线上的元素设置为 val：

```c
1   /* Set all diagonal elements to val */
2   void fix_set_diag(fix_matrix A, int val) {
3       int i;
4       for (i = 0; i < N; i++)
5           A[i][i] = val;
6   }
```

当编译时，GCC 产生如下汇编代码：

```asm
    A at %ebp+8, val at %ebp+12
1       movl    8(%ebp), %ecx
2       movl    12(%ebp), %edx
3       movl    $0, %eax
4   .L14:
5       movl    %edx, (%ecx, %eax)
6       addl    $68, %eax
7       cmpl    $1088, %eax
8       jne     .L14
```

创建一个 C 代码程序 fix-set-diag-opt，参考这段汇编代码中所使用的优化，风格与图 3-28b 中的代码一致。
使用含有参数 N 的表达式，而不是整数常量，使得如果重新定义了 N，你的代码仍能够正确地工作。

答案：

```c
1   /* Set all diagonal elements to val */
2   void fix_set_diag_opt(fix_matrix A, int val) {
        int *Aptr = &A[0][0];
3       int i;
4       for (i = 0; i < N; i++) {
5           *Aptr = val;
6           Aptr += (N + 1);
7       }
8   }
```

### 练习题 3.39

考虑下面的结构声明：

```c
struct prob {
    int *p;
    struct {
        int x;
        int y;
    } s;
    struct prob *next;
}
```

这个声明说明一个结构可以嵌套在另一个结构中，就像数组可以嵌套在结构中、数组可以嵌套在数组中一样。

下面的过程（省略了某些表达式）对这个结构进行操作：

```c
void sp_init(struct prob *sp)
{
    sp->s.x     = ________;
    sp->p       = ________;
    sp->next    = ________;
}
```

A. 下列字段的偏移量是多少（以字节为单位）？

```
   p: ________;
 s.x: ________;
 s.y: ________;
next: ________;
```

B. 这个结构总共需要多少字节？

C. 编译器为 sp\_init 的主体产生的汇编代码如下：

```
    sp at %ebp+8
1       movl    8(%ebp), %eax
2       movl    8(%eax), %edx
3       movl    %edx, 4(%eax)
4       leal    4(%eax), %edx
5       movl    %edx, (%eax)
6       movl    %eax, 12(%eax)
```

根据这些信息，填写 sp\_init 代码中缺失的表达式。

答案：

A.

```
   p: 0;
 s.x: 4;
 s.y: 8;
next: 12;
```

B. 16个字节

C.

给汇编代码添加注释：

```
    sp at %ebp+8
1       movl    8(%ebp), %eax       Get sp
2       movl    8(%eax), %edx       Get s.y
3       movl    %edx, 4(%eax)       s.x = s.y
4       leal    4(%eax), %edx       Get s.x
5       movl    %edx, (%eax)        sp.p = &s.x
6       movl    %eax, 12(%eax)      sp.next = sp
```

填写 sp\_init 代码中缺失的表达式：

```c
void sp_init(struct prob *sp)
{
    sp->s.x     = sp->s.y;
    sp->p       = &(sp->s.x);
    sp->next    = sp;
}
```

### 练习题 3.40

假设给你个任务，检查一下 C 编译器为结构和联合的访问产生正确的代码。
你写了下面的结构声明：

```c
typedef union {
    struct {
        short v;
        short d;
        int   s;
    } t1;
    struct {
        int a[2];
        char *p;
    } t2;
} u_type;
```

你写了一组具有下面这种形式的函数：

```c
void get(u_type *up, TYPE *dest) {
    *dest = EXPR;
}
```

这组函数有不一样的访问表达式 EXPR，而且根据 EXPR 的类型来设置目的数据类型 TYPE。
然后再检查编译这些函数时产生的代码，看看它们是否与你预期的一样。

假设在这些函数中，up 和 dest 分别被加载到寄存器 %eax 和 %edx 中。
填写下表中的数据类型 TYPE，并用 1\~3 条指令序列在计算表达式，将结构存储到 dest 中。
试着只用寄存器 %eax 和 %edx，不够用的时候，再用寄存器 %ecx

|EXPR|TYPE|Code|
|-|-|-|
|up-&gt;t1\.s|int|movl 4(%eax), %eax</br>movl %eax, (%edx)|
|up-&gt;t1\.v|||
|up-&gt;t1\.d|||
|up-&gt;t2\.a|||
|up-&gt;t2\.a[up-&gt;t1\.s]|||
|*up-&gt;t1\.p|||

答案：

|EXPR|TYPE|Code|
|-|-|-|
|up-&gt;t1\.s|int|movl 4(%eax), %eax</br>movl %eax, (%edx)|
|up-&gt;t1\.v|short|movw (%eax), %ax</br>movw %ax, (%edx)|
|&up-&gt;t1\.d|short*|leal 2(%eax), %eax</br>movl %eax, (%edx)|
|up-&gt;t2\.a|int*|movl %eax, (%edx)|
|up-&gt;t2\.a[up-&gt;t1\.s]|int|movl 4(%eax), %ecx</br>movl (%eax,%ecx,4), %eax</br>movl %eax, (%edx)|
|*up-&gt;t1\.p|char|movl 8(%eax), %eax</br>movb (%eax), %al</br>movb %al, (%edx)|

### 练习题 3.41

对下面每个结构声明，确定每个字段的偏移量、结构总的大小，以及在 Linux/IA32 下它的对齐要求。

* A. struct P1 { int i; char c; int j; char d; };
* B. struct P2 { int i; char c; char d; int j; };
* C. struct P3 { short w[3]; char c[3] };
* D. struct P4 { short w[3]; char *c[3] };
* E. struct P3 { struct P1 a[2]; struct P2 *p };

答案：

* A. 总大小为：16字节，i的偏移是：0，c的偏移是4，j的偏移是 8，d的偏移是 12，对齐 4
* B. 总大小位：12字节，i的偏移是：0，c的偏移是4，d的偏移是 5，j的偏移是 8，对齐 4
* C. 总大小是：10字节，w的偏移是：0，c的偏移是：6，对齐 2
* D. 总大小是：20字节，w的偏移是：0，c的偏移是：8，对齐 4
* E. 总大小是：36字节，a的偏移是：0，p的偏移是：32，对齐 4

### 练习题 3.42

对于结构声明

```c
struct {
    char *a;
    short b;
    double c;
    char d;
    float e;
    char f;
    long long g;
    void *h;
} foo;
```

假设在 Windows 机器上编译它，这里每个 K 字节的基本数据类型的偏移量必须是 K 的倍数。

* A. 这个结构中所有字段的字节偏移量是多少？
* B. 这个结构总的大小是多少？
* C. 重新排列这个结构中的字段，以最小化浪费的空间，然后再给出重新排过的结构的字节偏移量和总的大小。

答案：

* A. 如下：

```c
struct {
    char *a;            // 0
    short b;            // 4
    double c;           // 8
    char d;             // 16
    float e;            // 20
    char f;             // 24
    long long g;        // 32
    void *h;            // 40
} foo;
```

* B. 总大小为 48 字节，结构的结尾必须填充 4 个字节以满足 8 字节的对齐要求。

* C. 如下，总大小为 32 字节

```c
struct {
    char d;             // 0
    char f;             // 1
    short b;            // 2
    char *a;            // 4
    void *h;            // 8
    float e;            // 12
    double c;           // 16
    long long g;        // 24
} foo;
```

### 练习题 3.43

```c
1   /* This is very low-quality code.
2      It is intended to illustrate bad programming practices.
3      See Problem 3.43. */
4   char *getline()
5   {
6       char buf[8];
7       char *result;
8       gets(buf);
9       result = malloc(strlen(buf));
10      strcpy(result, buf);
11      return result;
12  }
```

**a) C语言代码**

```asm
1   080485c0 <getline>:
2    80485c0: 55                    push %ebp
3    80485c1: 89 e5                 mov %esp,%ebp
4    80485c3: 83 ec 28              sub $0x28,%esp
5    80485c6: 89 5d f4              mov %ebx,-0xc(%ebp)
6    80485c9: 89 75 f8              mov %esi,-0x8(%ebp)
7    80485cc: 89 7d fc              mov %edi,-0x4(%ebp)
    Diagram stack at this point
8    80485cf: 8d 75 ec              lea -0x14(%ebp),%esi
9    80485d2: 89 34 24              mov %esi,(%esp)
10   80485d5: e8 a3 ff ff ff        call 804857d <gets>
    Modify diagram to show stack contents at this point
```

**b) 对 gets 调用的反汇编**

以上代码是一个函数（不太好的）实现，这个函数从标准输入读入一行，
将字符串复制到新分配的存储中，并返回一个执行结果的指针。

考虑下面这样的场景。调用过程 getline，返回地址等于 0x8048643，寄存器 %ebp 等于 0xbffffc94，
寄存器 %ebx 等于 0x1，寄存器 %edi 等于 0x2，而寄存器 %esi 等于 0x3。
输入字符串为“012345678901234567890123”，程序会因为段错误（segmentation fault）而中止。
运行 GDB，确定错误是在执行 getline 的 ret 指令时发生的。

* A. 填写下图，尽可能多地说明在执行完反汇编代码中第 7 行指令后栈的相关信息。
在右边标准出存储在栈中数字的含义（例如“返回地址”）。在方框中写出它们的十六进制值（如果知道的话）。
每个方框都代表 4 个字节。指出 %ebp 的位置。

![](images/05_19_ex3.43.svg)

* B. 修改你的图，展现调用 gets 的影响（第 10 行）。
* C. 程序应该试图返回到什么地址？
* D. 当 getline 返回时，哪个（些）寄存器的值被破坏了？
* E. 除了可能会缓冲区溢出以外，getline 的代码还有哪两个错误？

答案：

A. 第7行后的栈：

![](images/05_19_ex3.43A.svg)

B. 第10行后的栈：

![](images/05_19_ex3.43B.svg)

C. 这个程序试图返回到地址 0x8048600。低位字节被结尾的空（null）字符覆盖了。

D. 下列寄存器的保存值被改变了：

|寄存器|值|
|-|-|
|%ebp|33323130|
|%edi|39383736|
|%esi|35343332|
|%ebx|31303938|

在 getline 返回之前，这些值将被加载到寄存器中

E. 对 malloc 的调用应该以 strlen(buf)+1 作为它的参数，而且代码还应该检查返回值是否位 NULL。

### 练习题 3.44

在运行 Linux 版本 2.6.16 的机器上运行栈检查代码 10 000 次，我们获取地址的范围从最小的 0xffffb754 到最大的 0xffffd754。

* A. 地址的大概范围是多大？
* B. 如果我们尝试一个有 128 字节 nop sled 的缓冲区溢出，想穷尽所有的起始地址，需要尝试多少次？

答案：

* A. 8192 字节，即 2^13 字节。
* B. 64次

### 练习题 3.45

函数 intlen，和函数 len 和 iptoa 一起，提供了一种很纠结的方式，来计算表示一个整数所需要的十进制数字的个数。
我们利用它来研究 GCC 栈保护者措施的一些情况。

```c
int len(char *s) {
    return strlen(s);
}

void iptoa(char *s, int *p) {
    int val = *p;
    sprintf(s, "%d", val);
}

int intlen(int x) {
    int v;
    char buf[12];
    v = x;
    iptoa(buf, &v);
    return len(buf);
}
```

下面是 intlen 的部分代码，分别由带和不带栈保护者编译：

不带保护者

```asm
1       subl        $36, %esp
2       movl        8(%ebp), %eax
3       movl        %eax, -8(%ebp)
4       leal        -8(%ebp), %eax
5       movl        %eax, 4(%esp)
6       leal        -20(%ebp), %ebx
7       movl        %ebx, (%esp)
8       call        iptoa
```

带保护者

```asm
1       subl        $52, %esp
2       movl        %gs:20, %eax
3       movl        %eax, -8(%ebp)
4       xorl        %eax, %eax
5       movl        8(%ebp), %eax
6       movl        %eax, -24(%ebp)
7       leal        -24(%ebp), %eax
8       movl        %eax, 4(%esp)
9       leal        -20(%ebp), %ebx
10      movl        %ebx, (%esp)
11      call        iptoa
```

* A. 对于两个版本：buf、v和金丝雀值（如果有的话）分别在栈帧中的什么位置？
* B. 在有保护的代码中，对局部变量重新排列如何提供更好的安全性，以对抗缓冲区越界攻击。

答案：

A. 

* 对于不带保护者版本：buf、v分别位于 %ebp-20 和 %ebp-8 的位置
* 对于带保护者版本：buf、v分别位于 %ebp-20和%ebp-24 的位置，金丝雀值位于 %ebp-8 的位置

B. 在有保护的代码中，局部变量 v 比 buf 更靠近栈顶，因此 buf 溢出就不会破坏 v 的值。
实际上，这样放置 buf 目的是一旦有缓冲区溢出，就会破坏金丝雀的值。

### 练习题 3.46

DRAM 是实现微处理器的主存储器的存储器技术，如图 6-17b 所示，DRAM 的开销从 1980 年的每 MB 8000 美元
下降到了 2010 年的大约 0.06 美元，每年大约下降 1.48倍，或者每 10 年大约下降 51 倍。
假设这种趋势无限地持续下去（这可能不太现实），而我们对机器存储器的预算大约是 1000 美元，
这样在 1980 年我们能为机器配置 128KB 的内存，而在 2010 年，可以配置 16.3GB。

* A. 估计到什么时候用 1000 美元的预算我们能买到 256TB 的内存。
* B. 估计到什么时候用 1000 美元的预算我们能买到 16EB 的内存。
* C. 如果我们把 DRAM 的预算提高到 10 000 美元，上述这两个时间点能提前多久到来？

答案：

* A. 假设  2010 年的 16.3GB 是基准线，256TB 表示增加了 1.608×10<sup>4</sup> 倍，需要大约 25 年，也就是到 2035 年。
* B. 16EB 比起 16.3GB 是增加了 1.054×10<sup>9</sup> 倍。这需要大约 53 年，也就是到 2063 年。
* C. 将预算增加 10 倍，会比预期缩短 6 年，使得分别可以在 2029 年和 2057 年达到两个存储器大小的目标。

### 练习题 3.47

下面的 C 函数将类型为 src\_t 的参数转换成类型 dst\_t 并返回，这里两种类型用 typedef 定义：

```c
dest_t cvt(src_t x)
{
    dest_t y = (dest_t) x;
    return y;
}
```

假设参数 x 存放在寄存器 %rdi 的某个适当命令的部分（即 %rdi、%edi、%di或者 %dil），
假设使用某种形式的数据传送指令来执行这个类型转换，并将这个值复制到寄存器 %rax 的某个释放命名部分。
填写下表，指明为下面的源类型和目的类型组合，使用的指令、源寄存器和目的寄存器。

|src\_t|dest\_t|指令|S|D|
|-|-|-|-|-|
|long|long|movq|%rdi|%rax|
|int|long||||
|char|long||||
|unsigned int|unsigned long||||
|unsigned char|unsigned long||||
|long|int||||
|unsigned long|unsigned||||

答案：

|src\_t|dest\_t|指令|S|D|
|-|-|-|-|-|
|long|long|movq|%rdi|%rax|
|int|long|mvoslq|%edi|%rax|
|char|long|movsbq|%dil|%rax|
|unsigned int|unsigned long|movl|%edi|%eax|
|unsigned char|unsigned long|movzbq|%eil|%rax|
|long|int|movl|%edi|%eax|
|unsigned long|unsigned|movl|%edi|%eax|

### 练习题 3.48

C 函数 arithprob 有参数 a、b、c 和 d，主体如下：

```c
return a*b + c*d;
```

编译得到如下 x86-64 代码：

```asm
1   arithprob:
2       movslq      %ecx,%rcx
3       imulq       %rdx,%rcx
4       movsbl      %sil,%esi
5       imull       %edi,%esi
6       movslq      %esi,%rsi
7       leaq        (%rcx,%rsi), %rax
8       ret
```

参数和返回值都是长度不同的有符号整数。
参数 a、b、c 和 d 分别在寄存器 %rdi、%rsi、%rdx 和 %rcx 中的适当的区域内传递。
根据这个汇编代码，写出一个函数原型，描述 arithprob 的返回值类型和参数类型。

答案：

```c
long arithprob(int a, char b, long c, int d) {
	return a*b + c*d;
}
```

### 练习题 3.49

C 函数 fun\_c 有如下总体结构：

```c
long fun_c(unsigned long x) {
    long val = 0;
    int i;
    for (________; ________; ________) {
        ________;
    }
    ________;
    return ________;
}
```

GCC编译器产生如下汇编代码：

```asm
1   fun_c:
  x in %rdi
2       movl        $0, %ecx
3       movl        $0, %edx
4       movabsq     $72340172838076673, %rsi
5   .L2:
6       movq        %rdi, %rax
7       andq        %rsi, %rax
8       addq        %rax, %rcx
9       shrq        %rdi            Shift right by 1
10      addl        $1, %edx
11      cmpl        $8, %edx
12      jne         .L2
13      movq        %rcx, %rax
14      sarq        $32, %rax
15      addq        %rcx, %rax
16      movq        %rax, %rdx
17      sarq        $16, %rdx
18      addq        %rax, %rdx
19      movq        %rdx, %rax
20      sarq        $8, %rax
21      addq        %rdx, %rax
22      andl        $255, %eax
23      ret
```

对这段代码做逆向工程，你会发现这对第4行的十进制常数转换为十六进制会有所帮助。

* A. 根据汇编代码版本填写 C 代码中缺失的部分。
* B. 用自然语言描述这段代码计算的是什么。

答案：

A.

```asm
1   fun_c:
  x in %rdi
2       movl        $0, %ecx        val = 0
3       movl        $0, %edx        i = 0
4       movabsq     $72340172838076673, %rsi
5   .L2:                            loop:
6       movq        %rdi, %rax      tmp = x
7       andq        %rsi, %rax      tmp &= 0x0101 0101 0101 0101
8       addq        %rax, %rcx      val &= tmp
9       shrq        %rdi            x >>= 1
10      addl        $1, %edx        ++i
11      cmpl        $8, %edx        Compare i:8
12      jne         .L2             if != goto loop
13      movq        %rcx, %rax      tmp = val
14      sarq        $32, %rax       tmp >>= 32
15      addq        %rcx, %rax      tmp += val
16      movq        %rax, %rdx      tmp2 = tmp
17      sarq        $16, %rdx       tmp2 >>= 16
18      addq        %rax, %rdx      tmp2 += tmp
19      movq        %rdx, %rax      tmp = tmp2
20      sarq        $8, %rax        tmp >>= 8
21      addq        %rdx, %rax      tmp += tmp2
22      andl        $255, %eax      tmp &= 0xFF
23      ret
```

```c
long fun_c(unsigned long x) {
    long val = 0;
    int i;
    for (i = 0; i != 8; x >>= 1, ++i) {
        val += (x & 0x0101010101010101);
    }
    val = (val >> 32) + val;
    val = (val >> 16) + val;
    val = (val >> 8) + val;
    return val & 0xFF;
}
```

B. 计算参数 x 二进制表示格式位为 1 的个数

### 练习题 3.50

C 函数 incrprob 有不同大小的参数 q、t 和 x，每个都可能是有符号的，也可能是无符号的。
该函数有如下主体：

```c
*t += x;
*q += *t;
```

编译得到下面的 x86-64 代码：

```asm
1   incrprob:
2       addl        (%rdx), %edi
3       movl        %edi, (%rdx)
4       movslq      %edi, %rdi
5       addq        %rdi, (%rsi)
6       ret
```

通过确定 3 个参数的顺序和可能的类型，确定 incrprob 的全部 4 种合理的函数原型。

答案：

根据使用的参数寄存器，易知参数顺序为：

```c
void incrprob(x,*q,*t);
```

四种合法的原型分别为：

```c
void incrprob(int x, long *q, int *t);
void incrprob_u(unsigned x, long *q, int *t);
void incrprob_sl(long x, long *q, int *t);
void incrprob_ul(unsigned long x, long *q, int *t);
```

### 练习题 3.51

对于 C 程序

```c
long int local_array(int i)
{
    long int a[4] = {2L, 3L, 5L, 7L};
    int idx = i & 3;
    return a[idx];
}
```

GCC 产生如下代码：

```asm
  x86-64 implementation of local_array
  Argument: i in %edi
1   local_array:
2       movq        $2, -40(%rsp)
3       movq        $3, -32(%rsp)
4       movq        $5, -24(%rsp)
5       movq        $7, -16(%rsp)
6       andl        $3, %edi
7       movq        -40(%rsp,%rdi,8), %rax
8       ret
```

* A. 画图说明这个函数使用的栈位置，以及它们相对于栈指针的偏移量。
* B. 为汇编代码添加注释，描述每条指令的效果。
* C. 这个示例说明关于 x86-64 栈规则的什么有趣特性？

答案：

A.

![](images/05_20_ex3.51.svg)

B.

```asm
  x86-64 implementation of local_array
  Argument: i in %edi
1   local_array:
2       movq        $2, -40(%rsp)               a[0] = 2
3       movq        $3, -32(%rsp)               a[1] = 3
4       movq        $5, -24(%rsp)               a[2] = 5
5       movq        $7, -16(%rsp)               a[3] = 7
6       andl        $3, %edi                    idx = i & 3
7       movq        -40(%rsp,%rdi,8), %rax      set %rax=a[idx]
8       ret                                     Return
```

C. 这个函数从来不改变栈指针。它将它的所有局部变量都存放在栈指针外的区域中。

### 练习题 3.52

对于递归阶乘函数

```c
long int rfact(long int x)
{
    if (x <= 0)
        return 1;
    else {
        long int xm1 = x-1;
        return x * rfact(xm1);
    }
}
```

GCC 产生下面的代码：

```asm
  x86-64 implementation of recursive factorial function rfact
  Argument x in %rdi
1   rfact:
2       pushq   %rbx
3       movq    %rdi, %rbx
4       movl    $1, %eax
5       testq   %rdi, %rdi
6       jle     .L11
7       leaq    -1(%rdi), %rdi
8       call    rfact
9       imulq   %rbx, %rax
10  .L11:
11      popq    %rbx
12      ret
```

* A. 函数存储在 %rbx 中的是什么值？
* B. pushq（第2行）和 popq（第11行）指令是干什么用的？
* C. 为汇编代码添加注释，描述每条指令的效果。
* D. 这个函数管理栈帧的方式与我们见过的其他方式有什么不同？

答案：

* A. 入参 x
* B. 保存 %rbx 的原始值到栈中以及返回前恢复 %rbx 的原始值
* C 如下：

```asm
  x86-64 implementation of recursive factorial function rfact
  Argument x in %rdi
1   rfact:
2       pushq   %rbx                Save %rbx to stack
3       movq    %rdi, %rbx          %rbx = x
4       movl    $1, %eax            Set return value to 1
5       testq   %rdi, %rdi          test x
6       jle     .L11                If x <= 0 goto end
7       leaq    -1(%rdi), %rdi      xm = x -1
8       call    rfact               call rfact(xm)
9       imulq   %rbx, %rax          return value = x * rfact(x - 1)
10  .L11:                       end:
11      popq    %rbx                Restore %rbx
12      ret                         Ret
```

* D. 不显式地减少或者增加栈指针，相反，代码可以用 pushq 和 popq 来修改栈指针以及保存和恢复寄存器状态。

### 练习题 3.53

对于下列结构声明，确定每个字段的偏移量，结构的整个大小，以及在 x86-64 下它的对齐要求。

* A. struct P1 { int i; char c; long j; char d; };
* B. struct P2 { long i; char c; char d; int j; };
* C. struct P3 { short w[3]; char c[3] };
* D. struct P4 { short w[3]; char *c[3] };
* E. struct P5 { struct P1 a[2]; struct P2 *p };

答案：

![](images/05_20_ex3.53.svg)

## 家庭作业

### 3.54 \*

一个函数的原型为：

```c
int decode2(int x, int y, int z);
```

将这个函数编译成 IA32 汇编代码。代码体如下：

```asm
  x at %ebp+8, y at %ebp+12, z at %ebp+16
1   movl    12(%ebp), %edx
2   subl    16(%ebp), %edx
3   movl    %edx, %eax
4   sall    $15, %eax
5   sarl    $15, %eax
6   imull   8(%ebp), %edx
7   xorl    %edx, %eax
```

参数 x、y 和  z 存放在存储器中相对于寄存器 %ebp 中地址偏移量为 8、12 和 16 的地方。
代码将返回值存放在寄存器 %eax 中。

写出等价于我们汇编代码的 decode2 的 C 代码。

答案：

```asm
  x at %ebp+8, y at %ebp+12, z at %ebp+16
1   movl    12(%ebp), %edx          Get y
2   subl    16(%ebp), %edx          y -= z
3   movl    %edx, %eax              ret = y
4   sall    $15, %eax               ret <<= 15
5   sarl    $15, %eax               ret >>= 15
6   imull   8(%ebp), %edx           y *= x
7   xorl    %edx, %eax              ret ^= y
```

```c
int decode2(int x, int y, int z) {
    int tmp = y - z;
    return (tmp * x) ^ (tmp << 15 >> 15);
}
```

### 3.55 \*

下面的代码计算 x 和 y 的乘积，并将结果存放在存储器中。
数据类型 ll\_t 被定义为等价于 long long。

```c
typedef long long ll_t;

void store_prod(ll_t *dest, ll_t x, int y) {
    *dest = x*y;
}
```

GCC 生成下面的汇编代码实现计算：

```asm
  dest at %ebp+8, x at %ebp+12, y at %ebp+20
1   movl    12(%ebp), %esi
2   movl    20(%ebp), %eax
3   movl    %eax, %edx
4   sarl    $31, %edx
5   movl    %edx, %ecx
6   imull   %esi, %ecx
7   movl    16(%ebp), %ebx
8   imull   %eax, %ebx
9   addl    %ebx, %ecx
10  mull    %esi
11  leal    (%ecx, %edx), %edx
12  movl    8(%ebp), %ecx
13  movl    %eax, (%ecx)
14  movl    %edx, 4(%ecx)
```

这段代码用了三个乘法实现多精度运算，这个多精度运算是在 32 位机器上实现 64 位运算所需要的。
描述用来计算这个乘积的算法，并对汇编代码添加注释，说明它是如何实现你的算法的。

**提示：** 参考练习题 3.12 及其答案。

答案：

ux = x + x<sub>63</sub>2<sup>64</sup>

uy = y + y<sub>31</sub>2<sup>32</up>

ux \* uy = (x + x<sub>63</sub>2<sup>64</sup>) \* (y + y<sub>31</sub>2<sup>32</sup>)

ux \* uy = x\*y + x \* y<sub>31</sub>2<sup>32</sup> + y \* x<sub>63</sub>2<sup>64</sup> + x<sub>63</sub>y<sub>31</sub>2<sup>96</sup>

我们只需要低 64 位，因此：

x \* y = ux \* uy - x \* y<sub>31</sub>2<sup>32</sup>

= (ux_h + ux_l) \* uy - x \* y<sub>31</sub>2<sup>32</sup>

(ux_h + ux_l) \* uy 的结果由练习题 3.12 可知 

(ux_h + ux_l) \* uy = (t_h + s) + t_l

另外：

-x \* y<sub>31</sub>2<sup>32</sup> = - (x_h + x_l) \* y<sub>31</sub>2<sup>32</sup>

由于我们只需要低 64 位，因此

= -x_l \* y<sub>31</sub>2<sup>32</sup>

当 y<sub>31</sub> 为 0 时乘积为 0，为 1 时乘积为 -x_l\*2<sup>32</sup>，因此：

当 y<sub>31</sub> 为 0

x \* y 的低 32 位为：t_l
高 32 位为：t_h + s

当 y<sub>31</sub> 为 1 时

x \* y 的低 32 位为：t_l
高 32 位为：t_h + s - x_l

```asm
  dest at %ebp+8, x at %ebp+12, y at %ebp+20
1   movl    12(%ebp), %esi              Load x_l
2   movl    20(%ebp), %eax              Load y
3   movl    %eax, %edx                  
4   sarl    $31, %edx
5   movl    %edx, %ecx
6   imull   %esi, %ecx                  If y_31 is 1 ecx = -x_l else ecx = 0
7   movl    16(%ebp), %ebx              Load x_h
8   imull   %eax, %ebx                  ebx = s
9   addl    %ebx, %ecx                  s += ecx
10  mull    %esi                        t = x_l * y
11  leal    (%ecx, %edx), %edx          t_h + s
12  movl    8(%ebp), %ecx               Load dest
13  movl    %eax, (%ecx)                save t_l to dest_l
14  movl    %edx, 4(%ecx)               save t_h + s to dest_h
```

### 3.56 \*\*

考虑下面的汇编代码：

```asm
  x at %ebp+8, n at %ebp+12
1       movl    8(%ebp), %esi
2       movl    12(%ebp), %ebx
3       movl    $1431655765, %edi
4       movl    $-2147483648, %edx
5   .L2:
6       movl    %edx, %eax
7       andl    %esi, %eax
8       xorl    %eax, %edi
9       movl    %ebx, %ecx
10      sall    %cl, %edx
11      testl   %edx, %edx
12      jne     .L2
13      movl    %edi, %eax
```

以上代码是以下整体形式的 C 代码编译产生的：

```c
1   int loop(int x, int n)
2   {
3       int result = ________;
4       int mask;
5       for (mask = ________; mask ________; mask = ________) {
6           result ^= ________;
7       }
8       return result;
9   }
```

你的任务是填写这个 C 代码中缺失的部分，得到一个程序等价于产生的汇编代码。
回想一下，这个函数的结果是在寄存器 %eax 中返回的。
你会发现以下工作很有帮助：检查循环之前、之中和之后的汇编代码，形成一个寄存器和程序变量之间一致的映射。

* A. 哪个寄存器保存着程序值 x、n、result 和 mask？
* B. result 和 mask 的初始值是什么？
* C. mask 的测试条件是什么？
* D. mask 是如何被修改的？
* E. result 是如何被修改的？
* F. 填写这段 C 代码中所有缺失的部分。

答案：

* A. 哪个寄存器保存着程序值 esi 保存 x、ebx 保存 n、edi 保存 result,edx 保存 mask？
* B. result的初始值是 0x5555 5555 和 mask 的初始值是 0xFFFF FFFF
* C. mask 的测试条件是是否为 0
* D. mask 是如何被修改的？每次逻辑右移 n 位
* E. result 是如何被修改的？result ^= (mask & x)
* F. 填写这段 C 代码中所有缺失的部分。

```asm
  x at %ebp+8, n at %ebp+12
1       movl    8(%ebp), %esi           Load x
2       movl    12(%ebp), %ebx          Load n
3       movl    $1431655765, %edi       result = 0x5555 5555
4       movl    $-2147483648, %edx      mask = 0xFFFF FFFF
5   .L2:                            loop:
6       movl    %edx, %eax              tmp = mask
7       andl    %esi, %eax              tmp &= x
8       xorl    %eax, %edi              result ^= tmp
9       movl    %ebx, %ecx              ecx = n
10      shrl    %cl, %edx               mask >>= (n & 0xFF)
11      testl   %edx, %edx              test mask
12      jne     .L2                     If != 0, goto loop 
13      movl    %edi, %eax              retval = result
```

C代码如下：

```c
1   int loop(int x, int n)
2   {
3       int result = 0x55555555;
4       int mask;
5       for (mask = 0xFFFFFFFF; mask; mask = mask >> (n & 0xFF)) {
6           result ^= (mask & x);
7       }
8       return result;
9   }
```

### 3.57 \*\*

在 3.6.6 节，我们查看了下面的代码，作为使用条件数据传输的一种选择：

```c
int cread(int *xp) {
    return (xp ? *xp : 0);
}
```

我们给出了使用条件传送指令的一个尝试实现，但是认为它是不合法的，因为它试图从一个空地址读数据。

写一个 C 函数 cread\_alt，它与 cread 有一样的行为，除了它可以被编译成使用条件数据传送。
当用命令行选项 '-march=i686' 来编译时，产生的代码应该使用条件传送指令而不是某种跳转指令。

答案：

在我的测试环境要用 64 位编译才会使用条件传送指令

```c
int cread_alt(int *xp) {
    int zero = 0;
    return *(xp ? xp : &zero);
}
```

### 3.58 \*\*

下面的代码是在一个开关语句中根据枚举类型值进行分支选择的例子。
回忆一下，C 语言中枚举类型只是一种引入一组与整数值相对应的名字的方法。
默认情况下，值是从 0 向上依次赋给名字的。
在我们的代码中，省略了与各种情况标号相对应的动作。

```c
/* Enumerated type creates set of constants numbered 0 and upward */

int switch3(int *p1, int *p2, mode_t action)
{
    int result = 0;
    switch (action) {
    case MODE_A:

    case MODE_B:

    case MODE_C:

    case MODE_D:

    case MODE_E:

    default:

    }
    return result;
}
```

产生的实现各个动作的汇编代码部分如下所示。
注释指明了参数位置，寄存器值，以及各个跳转目的的情况标号。
寄存器 %edx 对应于程序变量 result，并被初始化为 -1。
填写 C 代码中缺失的部分。注意那些会落入其他情况中的情况。

```asm
  Arguments: p1 at %ebp+8, p2 at %ebp+12, action at %ebp+16
  Registers: result in %edx (initialized to -1)
  The jump targets:
1   .L17:                               MODE_E
2       movl        $17, %edx
3       jmp         .L19
4   .L13:                               MODE_A
5       movl        8(%ebp), %eax
6       movl        (%eax), %edx
7       movl        12(%ebp), %ecx
8       movl        (%ecx), %eax
9       movl        8(%ebp), %ecx
10      movl        %eax, (%ecx)
11      jmp         .L19
12  .L14:                               MODE_B
13      movl        12(%ebp), %edx
14      movl        (%edx), %eax
15      movl        %eax, %edx
16      movl        8(%ebp), %ecx
17      addl        (%ecx), %edx
18      movl        12(%ebp), %eax
19      movl        %edx, (%eax)
20      jmp         .L19
21  .L15:                               MODE_C
22      movl        12(%ebp), %edx
23      movl        $15, (%edx)
24      movl        8(%ebp), %ecx
25      movl        (%ecx), %edx
26      jmp         .L19
27  .L16:                               MODE_D
28      movl        8(%ebp), %edx
29      movl        (%edx), %eax
30      movl        12(%ebp), %ecx
31      movl        %eax, (%ecx)
32      movl        $17, %edx
33  .L19:                               default
34      movl        %edx, %eax          Set return value
```

答案：

```c
/* Enumerated type creates set of constants numbered 0 and upward */

int switch3(int *p1, int *p2, mode_t action)
{
    int result = 0;
    switch (action) {
    case MODE_A:
        result = *p1;
        *p1 = *p2;
        break;
    case MODE_B:
        result = *p1 + *p2;
        *p2 = result;
        break;
    case MODE_C:
        *p2 = 15;
        result = *p1;
        break;
    case MODE_D:
        *p2 = *p1;
    case MODE_E:
        result = 17;
    default:
        break;
    }
    return result;
}
```

### 3.59 \*\*

这个程序给你一个机会，逆向工程一个 switch 语句。
在下面这个过程中，去掉了 switch 语句的主题：

```c
1   int switch_prob(int x, int n)
2   {
3       int result = x;
4
5       switch(n) {
6
7           /* Fill in code here */
8       }
9
10      return result;
11  }
```

下图给出了这个过程的反汇编机器代码。我们可以可看到，在第 4 行，参数 n 被加载到寄存器 %eax 中.

```asm
1  08048420 <switch_prob>:
2   8048420: 55                     push    %ebp
3   8048421: 89 e5                  mov     %esp,%ebp
4   8048423: 8b 45 0c               mov     0xc(%ebp),%eax
5   8048426: 83 e8 28               sub     $0x28,%eax
6   8048429: 83 f8 05               cmp     $0x5,%eax
7   804842c: 77 07                  ja      8048435 <switch_prob+0x15>
8   804842e: ff 24 85 f0 85 04 08   jmp     *0x80485f0(,%eax,4)
9   8048435: 8b 45 08               mov     0x8(%ebp),%eax
10  8048438: eb 24                  jmp     804845e <switch_prob+0x3e>
11  804843a: 8b 45 08               mov     0x8(%ebp),%eax
12  804843d: 8d 76 00               lea     0x0(%esi),%esi
13  8048440: eb 19                  jmp     804845b <switch_prob+0x3b>
14  8048442: 8b 45 08               mov     0x8(%ebp),%eax
15  8048445: c1 e0 03               shl     $0x3,%eax
16  8048448: eb 17                  jmp     8048461 <switch_prob+0x41>
17  804844a: 8b 45 08               mov     0x8(%ebp),%eax
18  804844d: c1 f8 03               sar     $0x3,%eax
19  8048450: eb 0f                  jmp     8048461 <switch_prob+0x41>
20  8048452: 8b 45 08               mov     0x8(%ebp),%eax
21  8048455: c1 e0 03               shl     $0x3,%eax
22  8048458: 2b 45 08               sub     0x8(%ebp),%eax
23  804845b: 0f af c0               imul    %eax,%eax
24  804845e: 83 c0 11               add     $0x11,%eax
25  8048461: 5d                     pop     %ebp
26  8048462: c3                     ret
```

跳转表驻留在另一个存储器区域中。
可以从第 8 行的间接跳转看出来，跳转表的起始地址为 0x80485f0。
用调试器 GDB，我们可以用命令 x/6w 0x80485f0 来检查存储器中的6个4字节的字。
GDB 打印出下面的内容：

```
(gdb) x/6w 0x80485f0
0x80485f0: 0x8048442 0x8048435 0x8048442 0x804844a
0x8048600: 0x8048452 0x804843a
```

用 C 代码填写开关语句的主体，使它的行为与机器代码一致。

答案：


```asm
1  08048420 <switch_prob>:
2   8048420: 55                     push    %ebp                            Save %ebp
3   8048421: 89 e5                  mov     %esp,%ebp                       Set stack frame
4   8048423: 8b 45 0c               mov     0xc(%ebp),%eax                  Get n
5   8048426: 83 e8 28               sub     $0x28,%eax                      n -= 40
6   8048429: 83 f8 05               cmp     $0x5,%eax                       Compare n:5
7   804842c: 77 07                  ja      8048435 <switch_prob+0x15>      If > goto case 1
8   804842e: ff 24 85 f0 85 04 08   jmp     *0x80485f0(,%eax,4)             do switch jmp
9   8048435: 8b 45 08               mov     0x8(%ebp),%eax                case1: result = x
10  8048438: eb 24                  jmp     804845e <switch_prob+0x3e>      goto case7
11  804843a: 8b 45 08               mov     0x8(%ebp),%eax                case2: result = x
12  804843d: 8d 76 00               lea     0x0(%esi),%esi                  esi=esi do nothing
13  8048440: eb 19                  jmp     804845b <switch_prob+0x3b>      goto case6
14  8048442: 8b 45 08               mov     0x8(%ebp),%eax                case3: result = x
15  8048445: c1 e0 03               shl     $0x3,%eax                       result <<= 3
16  8048448: eb 17                  jmp     8048461 <switch_prob+0x41>      goto end
17  804844a: 8b 45 08               mov     0x8(%ebp),%eax                case4: result = x
18  804844d: c1 f8 03               sar     $0x3,%eax                       result >>= 3
19  8048450: eb 0f                  jmp     8048461 <switch_prob+0x41>      goto end
20  8048452: 8b 45 08               mov     0x8(%ebp),%eax                case5: result = x
21  8048455: c1 e0 03               shl     $0x3,%eax                       result <<= 3
22  8048458: 2b 45 08               sub     0x8(%ebp),%eax                case6:  result -= x
23  804845b: 0f af c0               imul    %eax,%eax                       result *= result
24  804845e: 83 c0 11               add     $0x11,%eax                    case7: result += 17
25  8048461: 5d                     pop     %ebp                         end:
26  8048462: c3                     ret
```

对应C代码：

```c
int switch_prob(int x, int n)
{
    int result = x;
    switch(n) {
    case 40:
    case 42:
        result << = 3;
        break;
    case 43:
        result >>= 3;
        break;
    case 44:
        result <<= 3;
    case 45:
        result -= x;
        result *= result;
    case 41:
    default:
        result += 17;
        break;
    }

    return result;
}
```

### 3.60 \*\*\*

考虑下面的源代码，这里 R、S 和 T 都是用 #define 声明的常数：

```c
int A[R][S][T];

int store_ele(int i, int j, int k, int *dest)
{
    *dest = A[i][j][k];
    return sizeof(A);
}
```

编译这个程序，GCC 产生下面的汇编代码：

```
  i at %ebp+8, j at %ebp+12, k at %ebp+16, dest at %ebp+20
1   movl    8(%ebp), %ecx
2   movl    12(%ebp), %eax
3   leal    (%eax, %eax, 8), %eax
4   movl    %ecx, %edx
5   sall    $6, %edx
6   subl    %ecx, %edx
7   addl    %edx, %eax
8   addl    16(%ebp), %eax
9   movl    A(,%eax,4), %edx
10  movl    20(%ebp), %eax
11  movl    %edx, (%eax)
12  movl    $2772, %eax
```

* A. 将等式（3-1）从二维扩展到三维，提供数组元素 A[i][j][k] 的位置公式。
* B. 运用你的逆向工程技术，根据汇编代码，确定 R、S 和 T 的值。

* A

```
int A[R][S][T];

&A[i][j][k] = xA+L(T·S·i+S·j+k) = xA+L((T·i+j)·S·+k)
```

其中 L为int的大小，这里为4

* B

给汇编代码添加注解

```
  i at %ebp+8, j at %ebp+12, k at %ebp+16, dest at %ebp+20
1   movl    8(%ebp), %ecx               Load i
2   movl    12(%ebp), %eax              Load j
3   leal    (%eax, %eax, 8), %eax       x = 9 * j
4   movl    %ecx, %edx                  tmp = i
5   sall    $6, %edx                    tmp <<= 6
6   subl    %ecx, %edx                  tmp -= i  // tmp=63*i=T*S*i
7   addl    %edx, %eax                  x += tmp=63i+9j // x=T*S*i+S*j=63*i+9*j
8   addl    16(%ebp), %eax              x += k // x=(T·i+S)·j+k
9   movl    A(,%eax,4), %edx            Calc xA+L((T·i+S)·j+k)
10  movl    20(%ebp), %eax              Load dest
11  movl    %edx, (%eax)                *dest = A[i][j][k];
12  movl    $2772, %eax                 sizeof(A)=2772
```

由第12行代码得知 R\*S\*T=2772/4=693，通过上述代码注解得知：

63i=T\*S\*i

9j=S\*j

得到：

S=9

T=7

R=11

### 3.61 \*\*

C 编译器为 var\_prod\_ele 产生的代码（图3-29，我在下面重复了一份）不能将它在循环中使用的所有值都放进寄存器中，
因此它必须在每次循环时都从存储器中读出 n 的值。
写出这个函数的 C 代码，使用类似于 GCC 执行的那些优化，但是它的编译代码不会让循环值溢出到存储器中。

```c
/* Compute i,k of variable matrix.product */
int var_prod_ele(int n, int A[n][n], int B[n][n], int i, int k) {
    int j;
    int result = 0;

    for(j=0;j<n;j++)
        result += A[i][j] * B[j][k];

    return result;
}
```

回忆一下，处理器只有 6 个寄存器可以用来保存临时数据，因为寄存器 %ebp 和 %esp 不能用于此目的。
其中一个寄存器还必须用来保存乘法指令的结果。
因此，你必须把循环中的值的数量从 6 个（result、Arow、Bcol、j、n 和 4\*n）减少到 5 个。

需要找到一个对你那种编译器行之有效的策略。不断尝试各种不同的策略，直到有一种能工作。

答案：

在我的测试环境中，即使原来的版本也不需要每次循环从内存里面读取 n 值。

里面用了 %ebp, 现在版本的 GCC 即使是为 i386 生成代码也不会适用 %ebp 作为栈帧指针，和书中描述有所差异。

```c
/* Compute i,k of variable matrix.product */
int var_prod_ele(int n, int A[n][n], int B[n][n], int i, int k) {
    int j;
    int result = 0;

    int* Arow = &(A[i][0]);
    int* BCol = &(B[0][k]);
    for(j=0;j<n;j++)
        result += Arow[j] * (*(BCol + (j * n)));

    return result;
}
```

### 3.62 \*\*

下面的代码转置一个 M×M 矩阵的元素，这里 M 是一个用 #define 定义的常数：

```c
void transpose(int A[M][M]) {
    int i, j;
    for (i = 0; i < M; i++)
        for (j = 0; j < i; j++) {
            int t = A[i][j];
            A[i][j] = A[j][i];
            A[j][i] = t;
        }
}
```

当用优化等级 -O2 编译时，GCC 为这个函数的内循环产生下面的代码：

```asm
1   .L3:
2       movl    (%ebx), %eax
3       movl    (%esi,%ecx,4), %edx
4       movl    %eax, (%esi,%ecx,4)
5       addl    $1, %ecx
6       movl    %edx, (%ebx)
7       addl    $76, %ebx
8       cmpl    %edi, %ecx
9       jl      .L3
```

* A. M 的值是多少？
* B. 哪个寄存器保存着程序值 i 和 j?
* C. 写 transpose 的一个 C 代码版本，使用在这个循环中出现的优化。在你的代码中，使用参数 M，而不要用常数值。

```asm
1   .L3:                              loop:
2       movl    (%ebx), %eax            Get A[j][i]
3       movl    (%esi,%ecx,4), %edx     t = A[i][j]
4       movl    %eax, (%esi,%ecx,4)     A[i][j] = A[j][i]
5       addl    $1, %ecx                j++; // Arow++
6       movl    %edx, (%ebx)            A[j][i] = t
7       addl    $76, %ebx               ACol++
8       cmpl    %edi, %ecx              Compare j:M
9       jl      .L3                     If < goto loop
```

* A. M 的值为 76/4=19
* B. %ecx 保存着 j，%esi保存着 &(A[i][0])
* C 如下：

```c
void transpose(int A[M][M]) {
    int i, j;
    for (i = 0; i < M; i++) {
        int* Arow = &(A[i][0]);
        int* ACol = &(A[0][i]);
        for (j = 0; j < i; j++) {
            int t = Arow[j];
            Arow[j] = *(ACol + M * j);
            *(ACol + M * j) = t;
        }
    }
}
```

### 3.63 \*\*

考虑下面的源代码，这里 E1 和 E2 是用 #define 声明的宏表达式，计算用参数 n 表示的矩阵 A 的维度。
这段代码计算矩阵的第 j 列的元素之和。

```c
1   int sum_col(int n, int A[E1(n)][E2(n)], int j) {
2       int i;
3       int result = 0;
4       for (i = 0; i < E1(n); i++)
5           result += A[i][j];
6       return result;
7   }
```

编译这个程序，GCC 产生下面的汇编代码：

```asm
  n at %ebp+8, A at %ebp+12, j at %ebp+16
1       movl    8(%ebp), %edx
2       leal    (%edx, %edx), %eax
3       leal    -1(%eax), %ecx
4       leal    (%eax,%edx), %esi
5       movl    $0, %eax
6       testl   %esi, %esi
7       jle     .L3
8       leal    0(,%ecx,4), %ebx
9       movl    16(%ebp), %eax
10      movl    12(%ebp), %edx
11      leal    (%edx,%eax,4), %ecx
12      movl    $0, %edx
13      movl    $0, %eax
14  .L4:
15      addl    (%ecx), %eax
16      addl    $1, %edx
17      addl    %ebx, %ecx
18      cmpl    %esi, %edx
19      jl      .L4
20  .L3:
```

运用你的逆向工程技术，确定 E1 和 E2 的定义。

答案：

为汇编代码添加注解：

```asm
  n at %ebp+8, A at %ebp+12, j at %ebp+16
1       movl    8(%ebp), %edx           Get n   
2       leal    (%edx, %edx), %eax      2n
3       leal    -1(%eax), %ecx          2n-1
4       leal    (%eax,%edx), %esi       3n
5       movl    $0, %eax
6       testl   %esi, %esi              test 0
7       jle     .L3                     if <= 0 goto end
8       leal    0(,%ecx,4), %ebx        8n-4
9       movl    16(%ebp), %eax          Get j
10      movl    12(%ebp), %edx          Get A
11      leal    (%edx,%eax,4), %ecx     addr=A + 4j
12      movl    $0, %edx                i = 0
13      movl    $0, %eax                result = 0
14  .L4:                              loop:
15      addl    (%ecx), %eax            result += *(addr)
16      addl    $1, %edx                i++
17      addl    %ebx, %ecx              addr+=(8n-4)
18      cmpl    %esi, %edx              Compare i:3n
19      jl      .L4                     if < goto loop
20  .L3:                              end:
```

根据等式 3-1 可知:

```c
#define E1(n) 3*n
#define E2(n) 2*n-1
```

完整 C 代码为：

```c
#define E1(n) 3*n
#define E2(n) 2*n-1

int sum_col(int n, int A[E1(n)][E2(n)], int j) {
    int i;
    int result = 0;
    for (i = 0; i < E1(n); i++)
        result += A[i][j];
    return result;
}
```

### 3.64 \*\*

这个作业要查看 GCC 为参数和返回值中有结构的函数产生的代码，由此可以看到通常这些语言特性是如何实现的。

下面的 C 代码是函数 word\_sum，它用结构作为参数和返回值，还有一个函数 diff 调用 word\_sum：

```c
typedef struct {
    int *p;
    int v;
} str1;

typedef struct {
    int prod;
    int sum;
} str2;

str2 word_sum(str1 s1) {
    str2 result;
    result.prod = *s1.p * s1.v;
    result.sum = *s1.p + s1.v;
    return result;
}

int diff(int x, int y)
{
    str1 s1;
    str2 s2;
    s1.p = &x;
    s1.v = y;
    s2 = word_sum(s1);
    return s2.prod - s2.sum;
}
```

GCC 为这两个函数产生下面的代码：

```asm
1   word_sum:
2       pushl   %ebp
3       movl    %esp, %ebp
4       pushl   %ebx
5       movl    8(%ebp), %eax
6       movl    16(%ebp), %ebx
7       movl    12(%ebp), %edx
8       movl    (%edx), %edx
9       leal    (%edx,%ebx), %ecx
10      movl    %ecx, 4(%eax)
11      imull   %ebx, %edx
12      movl    %edx, (%eax)
13      popl    %ebx
14      popl    %ebp
15      ret     $4


1   diff:
2       pushl   %ebp
3       movl    %esp, %ebp
4       subl    $20, %esp
5       leal    -8(%ebp), %edx
6       leal    8(%ebp), %eax
7       movl    %eax, 4(%esp)
8       movl    12(%ebp), %eax
9       movl    %eax, 8(%esp)
10      movl    %edx, (%esp)
11      call    word_sum
12      subl    $4, %esp
13      movl    -8(%ebp), %eax
14      subl    -4(%ebp), %eax
15      leave
16      ret
```

指令 ret $4 很像普通的返回指令，但是它将栈指针增加了 8（4个是为了返回地址，加上4的加法），而不是 4。

* A. 从 word\_sum 代码的第 5~7 行我们可以看到，虽然函数只有一个参数，但是看上去好像从栈中取出了 3 个值。描述这三个值分别是什么。
* B. 从 diff 代码的第 4 行我们可以看到，栈帧中分配了 20 个字节。把它们当做 5 个字段来使用，每个字段 4 个字节。描述每个字段都是怎么用的。
* C. 你要如何描述向函数传递结构参数的通用策略？
* D. 你要如何描述处理从函数返回结构值的通用策略？

答案：

首先为汇编代码添加注解：

```asm
1   word_sum:
2       pushl   %ebp                    Save %ebp
3       movl    %esp, %ebp              Set stack frame
4       pushl   %ebx                    Save %ebx
5       movl    8(%ebp), %eax           Get &result
6       movl    16(%ebp), %ebx          Get s1.v
7       movl    12(%ebp), %edx          Get s1.p
8       movl    (%edx), %edx            Get *(s1.p)
9       leal    (%edx,%ebx), %ecx       sum = s1.p+sp.v
10      movl    %ecx, 4(%eax)           result.sum = sum
11      imull   %ebx, %edx              prod = *(s1.p) * s1.v
12      movl    %edx, (%eax)            result.prod = prod
13      popl    %ebx                    Restore %ebx
14      popl    %ebp                    Restore %ebp
15      ret     $4


1   diff:
2       pushl   %ebp                    Save %ebp
3       movl    %esp, %ebp              Set stack frame
4       subl    $20, %esp               Allocate 20byte on stack
5       leal    -8(%ebp), %edx          Get &s2  
6       leal    8(%ebp), %eax           Get &x
7       movl    %eax, 4(%esp)           s1.p = &x
8       movl    12(%ebp), %eax          Get y
9       movl    %eax, 8(%esp)           s1.v = y
10      movl    %edx, (%esp)            Set &s2 to stack
11      call    word_sum                Call word_sum
12      subl    $4, %esp                Restore %esp pointer same as before word_sum
13      movl    -8(%ebp), %eax          Get s2.prod
14      subl    -4(%ebp), %eax          s2.prod - s2.sum
15      leave                           恢复栈帧，等价于 movl %ebp,%esp; popl %ebp
16      ret                             返回
```

* A. 从 word\_sum 代码的第 5~7 行我们可以看到，虽然函数只有一个参数，但是看上去好像从栈中取出了 3 个值。描述这三个值分别是什么。

执行完第12行汇编代码的栈为：

![](images/05_22_ex3.64A.svg)

分别是 result 的地址，s1.v 和 s1.p

* B. 从 diff 代码的第 4 行我们可以看到，栈帧中分配了 20 个字节。把它们当做 5 个字段来使用，每个字段 4 个字节。描述每个字段都是怎么用的。

如下图所示，展示了执行完第 10 行代码的栈示意图：

![](images/05_22_ex3.64B.svg)

* C. 你要如何描述向函数传递结构参数的通用策略？

向函数传递结构的时候会将结构的每个字段都放在栈中传递，结构中前面的变量放在栈的低地址，靠后的放高地址。

* D. 你要如何描述处理从函数返回结构值的通用策略？

如果函数返回的是结构体，调用函数会先在栈中为返回结构分配好地址，然后将返回结构体的地址放在最靠近栈顶的地方（比第一个参数更靠近栈顶）

### 3.65 \*\*\*

在下面的代码中，A 和 B 是用 #define 定义的常数：

```c
typedef struct {
    short x[A][B]; /* Unknown constants A and B */
    int y;
} str1;

typedef struct {
    char array[B];
    int t;
    short s[B];
    int u;
} str2;

void setVal(str1 *p, str2 *q) {
    int v1 = q->t;
    int v2 = q->u;
    p->y = v1+v2;
}
```

GCC 为 setVal 的主体产生下面的代码：

```asm
1   movl    12(%ebp), %eax
2   movl    28(%eax), %edx
3   addl    8(%eax), %edx
4   movl    8(%ebp), %eax
5   movl    %edx, 44(%eax)
```

A 和 B 的值是多少？（答案是唯一的。）

答案：

首先给汇编代码添加注解：

```asm
1   movl    12(%ebp), %eax      Get q
2   movl    28(%eax), %edx      v2 = q->u
3   addl    8(%eax), %edx      t = q->t+v2
4   movl    8(%ebp), %eax       Get p
5   movl    %edx, 44(%eax)      p->y = t;
```

可知：char array[B] + padding 为 8 字节大小，short s[B]+padding2 为 28-8-4=16字节，padding和padding2的范围是0~3，B的合法值为8或者7

str1 中的 short x[A][B]+padding 占用了44字节大小，也就是 A\*B\*2+padding=44，padding3 为 0~3

padding3 等于 0 时，A\*B=22，显然无法得到解为正整数的 A

padding3 为 1或者3时，显然也无法得到解为正整数的 A

当 padding3 为 2 时，A\*B=21，当B等于7时，得到A为3,当 B 为 8时，A无正整数解

综上，唯一解是：

* A 等于 3，B 等于 7

### 3.66 \*\*\*

你负责维护一个大型 C 程序时，遇到下面这样的代码：

```c
1   typedef struct {
2       int left;
3       a_struct a[CNT];
4       int right;
5   } b_struct;
6
7   void test(int i, b_struct *bp)
8   {
9       int n = bp->left + bp->right;
10      a_struct *ap = &bp->a[i];
11      ap->x[ap->idx] = n;
12  }
```

编译时常数 CNT 和结构 a\_struct 的声明在一个你没有访问权限的文件中。
幸好，你有代码的 '.o' 版本，可以用 OBJDUMP 程序来反汇编这些文件，得到下面的汇编代码：

```
1   00000000 <test>:
2       0:  55                      push    %ebp
3       1:  89 e5                   mov     %esp,%ebp
4       3:  53                      push    %ebx
5       4:  8b 45 08                mov     0x8(%ebp),%eax
6       7:  8b 4d 0c                mov     0xc(%ebp),%ecx
7       a:  6b d8 1c                imul    $0x1c,%eax,%ebx
8       d:  8d 14 c5 00 00 00 00    lea     0x0(,%eax,8),%edx
9      14:  29 c2                   sub     %eax,%edx
10     16:  03 54 19 04             add     0x4(%ecx,%ebx,1), %edx
11     1a:  8b 81 c8 00 00 00       mov     0xc8(%ecx), %eax
12     20:  03 01                   add     (%ecx), %eax
13     22:  89 44 91 08             mov     %eax,0x8(%ecx,%edx,4)
14     26:  5b                      pop     %ebx
15     27:  5d                      pop     %ebp
16     28:  c3                      ret
```

运用你的逆向工程技术，推断出下列内容：

* A. CNT 的值。
* B. 结构 a\_struct 的完整声明。假设这个结构只有字段 idx 和 x。

答案：

```
1   00000000 <test>:
2       0:  55                      push    %ebp                        Save %ebp
3       1:  89 e5                   mov     %esp,%ebp                   Set stack frame
4       3:  53                      push    %ebx                        Save %ebx
5       4:  8b 45 08                mov     0x8(%ebp),%eax              Get i
6       7:  8b 4d 0c                mov     0xc(%ebp),%ecx              Get bp
7       a:  6b d8 1c                imul    $0x1c,%eax,%ebx             i*28
8       d:  8d 14 c5 00 00 00 00    lea     0x0(,%eax,8),%edx           8*i
9      14:  29 c2                   sub     %eax,%edx                   7*i
10     16:  03 54 19 04             add     0x4(%ecx,%ebx,1), %edx      Get xx 7i+*(28*i+bp+4) // bp->a[i].idx+7i
11     1a:  8b 81 c8 00 00 00       mov     0xc8(%ecx), %eax            Get bp->right(offset 200)
12     20:  03 01                   add     (%ecx), %eax                n = bp->left+bp->right
13     22:  89 44 91 08             mov     %eax,0x8(%ecx,%edx,4)       ap->x[ap->idx] = n //*(bp+4xx+8)=n // *(bp+28i+4idx+8) = n
14     26:  5b                      pop     %ebx
15     27:  5d                      pop     %ebp
16     28:  c3                      ret
```

* A. CNT 的值。

6

* B. 结构 a\_struct 的完整声明。假设这个结构只有字段 idx 和 x。

```c
struct a_struct {
    int idx;
    int x[6];
};
```

### 3.67 \*\*\*

考虑下面的联合声明：

```c
union ele {
    struct {
        int *p;
        int y;
    } e1;
    struct {
        int x;
        union ele *next;
    } e2;
};
```

这个声明说明联合中可以嵌套结构。

下面的过程（省略了一些表达式）对一个链表进行操作，链表是以上联合作为元素的：

```c
void proc(union ele *up)
{
    up->________ = *(up->________) - up->________;
}
```

* A. 下列字段的偏移量是多少（以字节为单位）：

```
e1.p: ________
e1.x: ________
e2.y: ________
e2.next: ________
```

* B. 这个结构总共需要多少个字节？
* C. 编译器为 proc 的主体产生下面的汇编代码：

```asm
  up at %ebp+8
1   movl    8(%ebp), %edx
2   movl    4(%edx), %ecx
3   movl    (%ecx), %eax
4   movl    (%eax), %eax
5   subl    (%edx), %eax
6   movl    %eax, 4(%ecx)
```

在这些信息的基础上，填写 proc 代码中缺失的表达式。**提示：** 有些联合引用的解释可以有歧义。

当你清楚引用指引到哪里的时候，就能够澄清这些歧义。
只有一个答案，不需要进行强制类型转换，且不违反任何类型限制。

TODO

* A. 下列字段的偏移量是多少（以字节为单位）：

```
e1.p: 0
e1.x: 4
e2.y: 0
e2.next: 4
```

* B. 这个结构总共需要多少个字节？

8 个字节

* C. 给汇编代码添加注解

```asm
  up at %ebp+8
1   movl    8(%ebp), %edx       Get up
2   movl    4(%edx), %ecx       Get up->e2.next
3   movl    (%ecx), %eax        Get up->e2.next->e1.p
4   movl    (%eax), %eax        Get *(up->e2.next->e1.p)
5   subl    (%edx), %eax        *(up->e2.next->e1.p) - up->e2.y
6   movl    %eax, 4(%ecx)       up->e2.next->e1.x = *(up->e2.next->e1.p) - up->e2.y
```

因此：

```c
void proc(union ele *up)
{
    up->e2.next->e1.x = *(up->e2.next->e1.p) - up->e2.y;
}
```

### 3.68 \*

写一个函数 good\_echo，它从标准输入读取一行，再把它写到标准输出。
你的实现应该对任意长度的输入行都能工作。
可以使用库函数 fgets，但是你必须确保即使当输入行要求比你已经为缓冲区分配的更多的空间时，你的函数也能正确工作。
你的代码还应该检查错误条件，要在遇到 1 时返回。
参考标准 I/O 函数的定义文档。

答案： [ex3.68.c](ex3.68.c)

### 3.69 \*

下面的声明定义了一类结构，用来构建二叉树：

```c
1   typedef struct ELE *tree_ptr;
2
3   struct ELE {
4       long val;
5       tree_ptr left;
6       tree_ptr right;
7   };
```

对于具有如下原型的函数：

```c
long trace(tree_ptr tp);
```

GCC 产生下面的 x86-64 代码：

```asm
1   trace:
  tp in %rdi
2       movl    $0, %eax
3       testq   %rdi, %rdi
4       je      .L3
5   .L5:
6       movq    (%rdi), %rax
7       movq    16(%rdi), %rdi
8       testq   %rdi, %rdi
9       jne     .L5
10  .L3:
11      rep
12      ret
```

* A. 给出一个该函数的 C 版本，使用 while 循环。
* B. 用自然语言解释这个函数计算的是什么。

给汇编代码添加注释：

```asm
1   trace:
  tp in %rdi
2       movl    $0, %eax            Set 0
3       testq   %rdi, %rdi          Check tp
4       je      .L3                 If tp == NULL goto end
5   .L5:                          loop:
6       movq    (%rdi), %rax        ret = tp->val
7       movq    16(%rdi), %rdi      tp = t->right
8       testq   %rdi, %rdi          Check tp
9       jne     .L5                 If tp != NULL goto loop
10  .L3:                          end:
11      rep
12      ret
```

* A. 给出一个该函数的 C 版本，使用 while 循环。

```c
long trace(tree_ptr tp)
{
    long result = 0
    while (tp) {
        result = tp->val;
        tp = tp->right
    }
    return result;
}
```

* B. 用自然语言解释这个函数计算的是什么。

返回二叉树最右侧叶子节点的值

### 3.70 \*\*

用家庭作业 3.69 中的树结构，以及一个具有以下原型的函数

```c
long traverse(tree_ptr tp);
```

GCC 产生下面的 x86-64 代码：

```asm
1   traverse:
  tp in %rdi
2       movq    %rbx, -24(%rsp)
3       movq    %rbp, -16(%rsp)
4       movq    %r12, -8(%rsp)
5       subq    $24, %rsp
6       movq    %rdi, %rbp
7       movabsq $-9223372036854775808, %rax
8       testq   %rdi, %rdi
9       je      .L9
10      movq    (%rdi), %rbx
11      movq    8(%rdi), %rdi
12      call    traverse
13      movq    %rax, %r12
14      movq    16(%rbp), %rdi
15      call    traverse
16      cmpq    %rax, %r12
17      cmovge  %r12, %rax
18      cmpq    %rbx, %rax
19      cmovl   %rbx, %rax
20  .L9:
21      movq    (%rsp), %rbx
22      movq    8(%rsp), %rbp
23      movq    16(%rsp), %r12
24      addq    $24, %rsp
25      ret
```

* A. 生成这个函数的 C 版本。
* B. 用自然语言解释这个函数计算的是什么。


答案：

给汇编代码添加注释：

```asm
1   traverse:
  tp in %rdi
2       movq    %rbx, -24(%rsp)                 Save %rbx
3       movq    %rbp, -16(%rsp)                 Save %rbp
4       movq    %r12, -8(%rsp)                  Save %412
5       subq    $24, %rsp                       Allocate 24byte on stack
6       movq    %rdi, %rbp                      Get tp
7       movabsq $-9223372036854775808, %rax     0x8000,0000,0000,0000
8       testq   %rdi, %rdi                      Check tp
9       je      .L9                             If tp == NULL goto end
10      movq    (%rdi), %rbx                    Get tp->val
11      movq    8(%rdi), %rdi                   Get tp->left
12      call    traverse                        Call traverse
13      movq    %rax, %r12                      Save result to %r12
14      movq    16(%rbp), %rdi                  tp->right
15      call    traverse                        Call traverse
16      cmpq    %rax, %r12                      Compare traverse(tp->left):%rax
17      cmovge  %r12, %rax                      If >= %rax=traverse(tp->left)
18      cmpq    %rbx, %rax                      Compare %rax:tp->right
19      cmovl   %rbx, %rax                      If < %rax=tp->val
20  .L9:
21      movq    (%rsp), %rbx                    Restore reg
22      movq    8(%rsp), %rbp
23      movq    16(%rsp), %r12
24      addq    $24, %rsp                       Restore stack
25      ret
```

* A. 生成这个函数的 C 版本。

```c
long traverse(tree_ptr tp)
{
    if (!tp) return 0x8000000000000000;

    long r1 = traverse(tp->left);
    long result = traverse(tp->right);
    if (r1 >= result) {
        result = r1;
    }

    if (result < tp->val) {
        result = tp->val;
    }

    return result;
}
```

* B. 用自然语言解释这个函数计算的是什么。

计算二叉树所有节点的最大值