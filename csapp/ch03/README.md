# 第 3 章 程序的机器级表示

## 要点

### 3.4.2 数据传送指令

|指令|效果|描述|
|-|-|-|
|MOV S,D|D ← S|传送|
|movb</br>movw</br>movl|传送字节</br>传送字</br>传送双字||
|MOVS S, D|D ← 符号扩展（S）|传送符号扩展的字节|

## 练习题

### 练习题 3.1 假设下面的值存放在指明的存储器地址和寄存器中：

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

### 练习题 3.2 对于下面汇编代码的每一行，根据操作数，确定适当的指令后缀。（例如，move 可以被重写成 movb、movw 或者 movl。）

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

### 练习题 3.3 当我们调用汇编器的时候，下面代码的每一行都会产生一个错误消息。解释每一行都是哪里出了错。

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

### 练习题 3.4 假设变了 v 和 p 被声明为类型

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

### 练习题 3.5 已知信息如下。将一个原型为

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

### 练习题 3.6 假设寄存器 %eax 的值为 x，%ecx 的值为 y。填写下表，指明下面每条汇编代码指令存储在寄存器 %edx 中的值：

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

### 练习题 3.8 假设我们想生成以下 C 函数的汇编代码：

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

