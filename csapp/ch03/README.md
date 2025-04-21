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
