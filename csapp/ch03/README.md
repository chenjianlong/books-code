# 第 3 章 程序的机器级表示

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

### 练习题 3.9 图 3-8a 中函数有以下变种，有些表达式用空格替代：

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

### 练习题 3.10 常常可以看见以下形式的汇编代码行：

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

* A. 我们可以看到，这个程序是在 64 位数据上进行多精度操作。还可以看到，64位乘法操作（第4行）使用的是无符号运算，因此我们可以确定 num_t 是 unsigned long long。（PS：不要被第 3 行的 imull 指令迷惑了，两个 32 位无符号乘法和补码乘法结果的低 32 位级表示是一样的,可以复习了第2章的整数乘法部分，或者查看：[整数运算](https://cs-cjl.com/2025/02_01_integer_operations#sideNavTitle4)）
* B. y = y<sub>h</sub> ∙ 2<sup>32</sup>+y<sub>l</sub>，这里 y<sub>h</sub> 和 y<sub>l</sub> 分别是高 32 位和低 32 位表示的值。因此我们可以计算 x ∙ y = x ∙ y<sub>h</sub> ∙ 2<sup>32</sup>+x ∙ y<sub>l</sub>。
乘积的完整表示是 96 位长，但是我们值需要低 64 位。
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

