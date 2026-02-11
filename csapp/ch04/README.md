# 第4章 处理器体系结构

## Y86 模拟器

### 编译

[sim](sim) 为官方提供了 Y86 模拟器源码，支持终端模式和 GUI 模式，默认只编译终端模式。
由于代码里面使用了 `matherr` 这个函数，这个函数在 Glibc 2.27 被删除了，因此只能使用 Glib 2.27 之前的版本进行编译。
这里用了 Ubuntu16.04 成功编译，编译后可以运行在 Ubuntu22.04 下。

我编译了 GUI 模式，除了 GCC 和 make 以外，还需要安装以下依赖库：

```sh
sudo apt install tk-dev
sudo apt install tcl-dev
sudo apt install bison
sudo apt install flex
```

然后修改 Makefile：

```diff
index 414b774..4a44fc4 100644
--- a/csapp/ch04/sim/Makefile
+++ b/csapp/ch04/sim/Makefile
@@ -1,6 +1,6 @@
 # Comment this out if you don't have Tcl/Tk on your system

-#GUIMODE=-DHAS_GUI
+GUIMODE=-DHAS_GUI

 # Modify the following line so that gcc can find the libtcl.so and
 # libtk.so libraries on your system. You may need to use the -L option
@@ -13,12 +13,15 @@ TKLIBS=-L/usr/lib -ltk -ltcl
 # header files on your system. Comment this out if you don't have
 # Tcl/Tk.

-TKINC=-isystem /usr/include
+TKINC=-isystem /usr/include/tcl8.6

 ##################################################
 # You shouldn't need to modify anything below here
 ##################################################

+CFLAGS +=-DUSE_INTERP_RESULT
+CPPFLAGS +=-DUSE_INTERP_RESULT
+
 # Use this rule (make all) to build the Y86 tools. The variables you've
 # assigned to GUIMODE, TKLIBS, and TKINC will override the values that
 # are currently assigned in seq/Makefile and pipe/Makefile.
```

pipe 和 seq 子目录的 Makefile 也需要做如上修改，然后编译即可。

### 工具介绍

编译后，有如下工具

#### misc/yas

Y86 汇编器，用于将 Y86 汇编代码编译成 Y86 对象代码，对象代码可以随后使用 Y86 模拟器（SEQ 或者 PIPE 实现）来运行。

```sh
$ ./misc/yas -h
Usage: ./misc/yas [-V[n]] file.ys
   -V[n]  Generate memory initialization in Verilog format (n-way blocking)
```

这里举个例子：

假设有 Y86 汇编代码 prog1.ys：

```x86asm
# prog1: Pad with 3 nop's
  irmovl $10,%edx
  irmovl  $3,%eax
  nop
  nop
  nop
  addl %edx,%eax
  halt
```

可以使用命令：

```sh
$ ./misc/yas ./prog1.ys
```

会在源码同一目录下生成 prog1.yo 内容如下：

```verilog
                      | # prog1: Pad with 3 nop's
  0x000: 30f20a000000 |   irmovl $10,%edx
  0x006: 30f003000000 |   irmovl  $3,%eax
  0x00c: 10           |   nop
  0x00d: 10           |   nop
  0x00e: 10           |   nop
  0x00f: 6020         |   addl %edx,%eax
  0x011: 00           |   halt
```

#### misc/yis

Y86 指令集模拟器，输入为 Y86 对象代码（object code）,然后输出运行结果，这里使用上面的 prog1.yo 举个例子：

```sh
$ ./misc/yis  ./prog1.yo
Stopped in 7 steps at PC = 0x11.  Status 'HLT', CC Z=0 S=0 O=0
Changes to registers:
%eax:	0x00000000	0x0000000d
%edx:	0x00000000	0x0000000a

Changes to memory:
```

#### misc/hcl2c

这个工具用于将 HCL 转成 C 代码，使用方法为：

```sh
$ ./misc/hcl2c  -h
Usage: ./misc/hcl2c [-h] < HCL_file  >C file
Output C file on stdout.
   -a     Add define/use annotations
   -h     Print this message
```

可以使用 misc/mux4.hcl 或者书中 4.2 节的 HCL 例子自行测试，这里不演示。

#### misc/hcl2v

这个工具用于将 HCL 转成 verilog，默认不会编译出来，如果需要这个工具，需要进 misc 目录然后：

```sh
$ make hcl2v
```

使用方法为：

```sh
$ ./hcl2v -h
Usage: ./hcl2v [-h] < HCL_file  >verilog file
Output verilog code on stdout.
   -h     Print this message
```

例如：

```sh
$ ./hcl2v < mux4.hcl > mux4.verilog
```

mux4.hcl 内容可以查看：[mux4.hcl](misc/mux4.hcl)

mux4.verilog 为：

```verilog
assign s1 =
    (code == 2 | code == 3);

assign s0 =
    (code == 1 | code == 3);

assign Out4 =
    ((~s1 & ~s0) ? A : ~s1 ? B : ~s0 ? C : D);
```

#### seq ssim/ssim+

这两个模拟器使用方法是一样的，通过 seq/Makefile 可知 ssim 使用 seq\-std.hcl 而 ssim\+ 使用 seq\+\-std.hcl

默认只编译 ssim，如果需要 ssim\+ 需要进 seq 目录然后：

```sh
$ make sseq+
```

#### pipe psim

这个是流水线化的  Y86 模拟器，默认使用 pipe-std.hcl，如果需要测试其他版本需要修改 pipe/Makefile 的 VERSION 变量。

## 练习题

### 练习题 4.1

确定下面的 Y86 指令序列的字节编码。“.pos 0x100”那一行表明这段目标代码的起始地址应该是 0x100。

```
.pos 0x100 # Start code at address 0x100
    irmovl  $15,%ebx        # Load 15 into %ebx
    rrmovl  %ebx,%ecx       # Copy 15 to %ecx
loop:                       # loop:
    rmmovl  %ecx,-3(%ebx)   # Save %ecx at address 15-3 = 12
    addl    %ebx,%ecx       # Increment %ecx by 15
    jmp     loop            # Goto loop
```

答案：

```
0x100:  30F30F000000
0x106:  2031
0x108:  4013FFFFFFFD
0x10E:  6031
0x110:  7008010000
```

### 练习题 4.2

确定下列每个字节序列所编码的 Y86 指令序列。
如果序列中有不合法的字节，指出指令序列中不合法值出现的位置。
每个序列都先给出了起始地址，冒号然后是字节序列。

* A. 0x100:30f3fcffffff40630008000000
* B. 0x200:a06f80080200000030f30a00000090
* C. 0x300:50540700000010f0b01f
* D. 0x400:6113730004000000
* E. 0x500:6362a0f0

答案：

* A.

```asm
0x100:  30f3fcffffff        |   irmovl  $-4, %ebx
0x106:  406300080000        |   rmmovl  %esi, 0x800(%ebx)
0x10c:  00                  |   halt
```

* B

```asm
0x200:  a06f                |   pushl   %esi
0x202:  8008200000          |   call    proc
0x207:  00                  |   halt
0x208:                      | proc:
0x208:  30f30a000000        |   irmovl  $10, %ebx
0x20e:  90                  |   ret
```

* C

```asm
0x300:  505407000000        |   mrmovl 7(%ebp), %esp
0x306:  10                  |   nop
0x307:  f0                  |   .byte 0xf0 # invalid instruction code
0x308:  b01f                |   popl %ecx
```

* D

```asm
0x400:                      | loop:
0x400:  6113                |   subl %ecx, %ebx
0x402:  7300040000          |   je loop
0x407:  00                  |   halt
```

* E

```asm
0x500:  6362                |   xorl %esi, %edx
0x502:  a0                  |   .byte 0xa0    # pushl instruction code
0x503:  f0                  |   .byte 0xf0    # Invalid register specifier byte
```

### 练习题 4.3

根据下面的 C 代码，用 Y86 代码来实现一个递归求和函数 rSum：

```c
int rSum(int *Start, int Count)
{
    if (Count <= 0)
        return 0;
    return *Start + rSum(Start+1, Count-1);
}
```

在一台 IA32 机器上编译这段 C 代码，然后再把那些指令翻译成 Y86 的指令，这样做可能会有帮助。

答案：

[ex4.3.ys](ex4.3.ys)

### 练习题 4.4

修改 Sum 函数的 Y86 代码（图 4-6），实现 AbsSum，计算一个数组的绝对值的和。
在内循环中使用条件跳转指令。

答案：

[ex4.4.ys](ex4.4.ys)

### 练习题 4.5

修改 Sum 函数的 Y86 代码（图 4-6），实现 AbsSum，计算一个数组的绝对值的和。
在内循环中使用条件传送指令。

答案：

[ex4.5.ys](ex4.5.ys)

### 练习题 4.6

确定 IA32 处理器上指令 `pushl %esp` 的行为。
我们可以通过阅读 Intel 关于这条指令的文档来了解它们的做法，但更简单的方法是在实际的机器上做个实验。
C 编译器正常情况下是不会产生这条指令的，所以我们必须用手工生成的汇编代码来完成这一任务。
下面是我们写的一个测试程序（网络旁注 ASM:EASM，描绘任何写 C 代码和手写汇编代码结合的程序）：

```asm
 1      .text
 2  .globl pushtest
 3  pushtest:
 4      pushl   %ebp
 5      movl    %esp, %ebp
 6      movl    %esp, %eax  Copy stack pointer
 7      pushl   %esp        Push stack pointer
 8      popl    %edx        Pop it back
 9      subl    %edx, %eax  Subtract new from old stack pointer
10      leave               Restore stack & frame pointers
11      ret
```

在实验中，我们发现函数 pushtest 总是返回 0，这表示在 IA32 中 `pushl %esp` 指令的行为是怎样的呢？

答：

`pushl %esp` 将 %esp 的当前值压入栈中，然后再修改 %esp 栈指针本身。

### 练习题 4.7

下面这个汇编函数让我们确定 IA32 上指令 `popl %esp` 的行为：

```asm
 1      .text
 2  .globl pushtest
 3  poptest:
 4      pushl   %ebp
 5      movl    %esp, %ebp
 6      pushl   0xabcd      Push test value
 7      popl    %esp        Pop to stack pointer
 8      movl    %esp, %eax  Set poped value as return value
 9      leave               Restore stack and frame pointers
10      ret
```

我们发现函数总是返回 0xabcd。
这表示 `popl %esp` 的行为是怎样的？
还有什么其他 Y86 指令也有相同的行为吗？

答案：

这表明 `popl %esp` 将 %esp 当前值指定的内存的值放到 %esp 寄存器中。

这条命令等价于 `mrmovl (%esp), %esp`。

### 练习题 4.8

写出信号 xor 的 HCL 表达式，xor 就是异或，输入为 a 和 b。
信号 xor 和上面定义的 eq 有什么关系？

答案：

```c
bool xor = (!a && b) || (a && !b);
```

eq 的输出取反等于 xor 的输出,也就是说 eq 和 xor 的输出互补。

### 练习题 4.9

假设你用练习题 4.8 中的异或电路而不是位级的相等电路来实现一个字级的相等电路。
设计一个 32 位字的相等电路需要 32 个字级的异或电路，另外还要两个逻辑门。

答案：

![](images/06_16_ex4.9.svg)

### 练习题 4.10

写一个电路的 HCL 代码，对于输入字 A、B 和 C，选择中间值。
也就是，输出等于三个输入中居于最小值和最大值中间的那个字。

答案：

```c
int Med3 = [
  A <= B && B <= C : B;
  C <= B && B <= A : B;
  B <= A && A <= C : A;
  C <= A && A <= B : A;
  1                : C;
];
```

### 练习题 4.11

填写下表的右边一栏，这个表描述的是图 4-17 中目标代码第 4 行上的 `irmovl` 指令的处理情况：

<table>
  <tr><th rowspan=2>阶段</th><th>通用</th><th>具体</th></tr>
  <tr><td>irmovl V, rB</td><td>irmovl $128, %esp</td></tr>
  <tr>
    <th>取指</th>
    <td>icode:ifun←M<sub>1</sub>[PC]</br>rA:rB←M<sub>1</sub>[PC+1]</br>valC←M<sub>4</sub>[PC+2]</br>valP←PC+6</td>
    <td></td>
  </tr>
  <tr><th>译码</th><td></td><td></td></tr>
  <tr><th>执行</th><td>valE←0+valC</td><td></td></tr>
  <tr><th>访存</th><td></td><td></td></tr>
  <tr><th>写回</th><td>R[rB]←valE</td><td></td></tr>
  <tr><th>更新PC</th><td>PC←valP</td><td></td></tr>
</table>

这条指令的执行会怎样改变寄存器和 PC 呢？

答案：

<table>
  <tr><th rowspan=2>阶段</th><th>通用</th><th>具体</th></tr>
  <tr><td>irmovl V, rB</td><td>irmovl $128, %esp</td></tr>
  <tr>
    <th>取指</th>
    <td>icode:ifun←M<sub>1</sub>[PC]</br>rA:rB←M<sub>1</sub>[PC+1]</br>valC←M<sub>4</sub>[PC+2]</br>valP←PC+6</td>
    <td>icode:ifun←M<sub>1</sub>[0x00e]=3:0</br>rA:rB←M<sub>1</sub>[0x00f]=0xF:4</br>valC←M<sub>4</sub>[0x010]=128</br>valP←PC+6=0x00e+6=0x14</td>
  </tr>
  <tr><th>译码</th><td></td><td></td></tr>
  <tr><th>执行</th><td>valE←0+valC</td><td>valE←0+valC=128</td></tr>
  <tr><th>访存</th><td></td><td></td></tr>
  <tr><th>写回</th><td>R[rB]←valE</td><td>R[%esp]←valE=128</td></tr>
  <tr><th>更新PC</th><td>PC←valP</td><td>PC←valP=0x014</td></tr>
</table>

### 练习题 4.12

填写下表的右边一栏，这个表描述的是图 4-17 中目标代码第 7 行上 popl 指令的处理情况：

<table>
  <tr><th rowspan=2>阶段</th><th>通用</th><th>具体</th></tr>
  <tr><td>popl rA</td><td>popl %eax</td></tr>
  <tr>
    <th>取指</th>
    <td>icode:ifun←M<sub>1</sub>[PC]</br>rA:rB←M<sub>1</sub>[PC+1]</br>valP←PC+2</td>
    <td></td>
  </tr>
  <tr><th>译码</th><td>valA←R[%esp]</br>valB←R[%esp]</td><td></td></tr>
  <tr><th>执行</th><td>valE←valB+4</td><td></td></tr>
  <tr><th>访存</th><td>valM←M<sub>4</sub>[valA]</td><td></td></tr>
  <tr><th>写回</th><td>R[%esp]←valE</br>R[rA]←valM</td><td></td></tr>
  <tr><th>更新PC</th><td>PC←valP</td><td></td></tr>
</table>

这条指令的执行会怎样改变寄存器和PC呢？

答案：

<table>
  <tr><th rowspan=2>阶段</th><th>通用</th><th>具体</th></tr>
  <tr><td>popl rA</td><td>popl %eax</td></tr>
  <tr>
    <th>取指</th>
    <td>icode:ifun←M<sub>1</sub>[PC]</br>rA:rB←M<sub>1</sub>[PC+1]</br>valP←PC+2</td>
    <td>icode:ifun←M<sub>1</sub>[0x01c]=0xB:0</br>rA:rB←M<sub>1</sub>[0x01d]=0:0xf</br>valP=0x01c+2=0x01e</td>
  </tr><tr>
    <th>译码</th>
    <td>valA←R[%esp]</br>valB←R[%esp]</td>
    <td>valA←R[%esp]=124</br>valB←R[%esp]=124</td>
  </tr><tr>
    <th>执行</th>
    <td>valE←valB+4</td>
    <td>valE←124+4=128</td>
  </tr><tr>
    <th>访存</th>
    <td>valM←M<sub>4</sub>[valA]</td>
    <td>valM←M<sub>4</sub>[124]=9</td>
  </tr><tr>
    <th>写回</th>
    <td>R[%esp]←valE</br>R[rA]←valM</td>
    <td>R[%esp]←valE=128</br>R[rA]=R[%eax]←valM=9</td>
  </tr><tr>
    <th>更新PC</th>
    <td>PC←valP</td>
    <td>PC←valP=0x01e</td>
  </tr>
</table>

这条指令会将 %eax 设置为 9，%esp 设置为 128，PC 增加2。

### 练习题 4.13

根据图 4-20 中列出的步骤，指令 `pushl %esp` 会有什么样的效果？
这与练习题 4.6 中确定的 Y86 期望的行为一致吗？

答案：

将 %esp 的旧值放到 %esp-4 指向的内存空间中，然后将 %esp 设置为 %esp-4。

一致。

### 练习题 4.14

假设 popl 在写回阶段中的两个寄存器写操作按照图 4-20 列出的顺序进行。
`popl %esp` 执行的效果会是怎样的？
这与练习题 4.7 中确定的 Y86 期望的行为一致吗？

答案：

将 %esp 设置为这条指令执行前 %esp 所指向的内存的值。

一致。

### 练习题 4.15

从指令编码（图 4-2 和图 4-3）我们可以看出，`rmmovl` 指令是一类更通用的、包括条件转移在内的指令的无条件版本。
请给出你要如何修改下面 `rrmovl` 指令的步骤，使之也能处理 6 个条件传送指令。
看看 jXX 指令的实现（图 4-21）是如何处理条件行为的，可能会有帮助。

|阶段|cmovXX rA, rB|
|-|-|
|取指|icode:ifun←M<sub>1</sub>[PC]</br>rA:rB←M<sub>1</sub>[PC+1]</br>valP←PC+2|
|译码|valA←R[rA]|
|执行|valE←0+valA|
|访存||
|写回|R[rB]←valE|
|更新PC|PC←valP|

答案：

|阶段|cmovXX rA, rB|
|-|-|
|取指|icode:ifun←M<sub>1</sub>[PC]</br>rA:rB←M<sub>1</sub>[PC+1]</br>valP←PC+2|
|译码|valA←R[rA]|
|执行|valE←0+valA</br>Cnd ← Cond(CC, ifun)|
|访存||
|写回|if (Cnd)</br>R[rB]←valE|
|更新PC|PC←valP|

### 练习题 4.16

填写下表右边一栏，这个表描述的是图 4-17 中目标代码第 9 行 call 指令的处理情况。
这条指令的执行会怎样改变寄存器、PC和存储器呢？

<table>
  <tr><th rowspan=2>阶段</th><th>通用</th><th>具体</th></tr>
  <tr><td>call Dest</td><td>call 0x209</td></tr>
  <tr>
    <th>取指</th>
    <td>icode:ifun←M<sub>1</sub>[PC]</br>valC←M<sub>4</sub>[PC+1]</br>valP←PC+5</td>
    <td></td>
  </tr>
  <tr><th>译码</th><td>valB←R[%esp]</td><td></td></tr>
  <tr><th>执行</th><td>valE←valB+(-4)</td><td></td></tr>
  <tr><th>访存</th><td>M<sub>4</sub>[valE]←valP</td><td></td></tr>
  <tr><th>写回</th><td>R[%esp]←valE</td><td></td></tr>
  <tr><th>更新PC</th><td>PC←valC</td><td></td></tr>
</table>

答案：

<table>
  <tr><th rowspan=2>阶段</th><th>通用</th><th>具体</th></tr>
  <tr><td>call Dest</td><td>call 0x209</td></tr>
  <tr>
    <th>取指</th>
    <td>icode:ifun←M<sub>1</sub>[PC]</br>valC←M<sub>4</sub>[PC+1]</br>valP←PC+5</td>
    <td>icode:ifun←M<sub>1</sub>[0x023]=8:0</br>valC←M<sub>4</sub>[0x024]=0x029</br>valP←PC+5=0x028</td>
  </tr><tr>
    <th>译码</th>
    <td>valB←R[%esp]</td>
    <td>valB←R[%esp]=128</td>
  </tr><tr>
    <th>执行</th>
    <td>valE←valB+(-4)</td>
    <td>valE←valB+(-4)=128-4=124</td>
  </tr><tr>
    <th>访存</th>
    <td>M<sub>4</sub>[valE]←valP</td>
    <td>M<sub>4</sub>[124]←valP=0x028</td>
  </tr><tr>
    <th>写回</th>
    <td>R[%esp]←valE</td>
    <td>R[%esp]←valE=124</td>
  </tr><tr>
    <th>更新PC</th>
    <td>PC←valC</td>
    <td>PC←valC=0x029</td>
  </tr>
</table>

### 练习题 4.17

写出 SEQ 实现中信号 need\_valC 的 HCL 代码。

答案：

```c
bool need_valC =
    icode in { IIRMOVL, IRMMOVL, IMRMOVL, IJXX, ICALL };
```

### 练习题 4.18

寄存器信号 srcB 表明应该读哪个寄存器以产生信号 valB。
所需要的值如图 4-18~图 4-21 中译码阶段第二步所示。
写出 srcB 的 HCL 代码。

答案：

```c
int srcB = [
    icode in { IRMMOVL, IMRMOVL, IOPL } : rB;
    icode in { IPUSHL, IPOPL, ICALL, IRET } : RESP;
    1 : RNONE; # Don’t need register
];
```

### 练习题 4.19

寄存器 ID dstM 表明写端口 M 的目的寄存器，从存储器中读出来的值 valM 将放在那里，如图 4-18~图 4-21 中写回阶段第二步所示。
写出 dstM 的 HCL 代码。

答案：

```c
int dstM = [
    icode in { IMRMOVL, IPOPL } : rA;
    1 : RNONE; # Don’t write any register
];
```

### 练习题 4.20

只有 `popl` 指令会同时用到寄存器文件的两个写端口。
对于指令 `popl %esp`，E 和 M 两个写端口会用到同一个地址，但是写入的数据不同。
为了解决这个冲突，必须对两个写端口都试图对一个寄存器进行写时，只有较高优先级端口上的写才会发生。
那么要实现练习题 4.7 中确定的行为，哪个端口该具有较高的优先级呢？

答案：

dstM 具有较高优先级。

### 练习题 4.21

根据图 4-18~图 4-21 中执行阶段第一步的第一个操作数，写出 SEQ 中信号 aluB 的 HCL 描述。

答案：

```c
int aluB = [
    icode in { IRMMOVL, IMRMOVL, IOPL, ICALL, IPUSHL, IRET, IPOPL } : valB;
    icode in { IRRMOVL, IIRMOVL } : 0;
    # Other instructions don’t need ALU
];
```

### 练习题 4.22

条件传送指令，简称 cmovXX，指令代码为 IRRMOVL。
如图 4-28 所示，我们可以用执行阶段中产生的 Cnd 信号实现这些指令。
修改 dstE 的 HCL 代码以实现这些指令。

答案：

```c
int dstE = [
    icode in { IRRMOVL } && Cnd : rB;
    icode in { IIRMOVL, IOPL} : rB;
    icode in { IPUSHL, IPOPL, ICALL, IRET } : RESP;
    1 : RNONE; # Don’t write any register
];
```

### 练习题 4.23

观察图 4-16~图 4-19 所示的不同指令的存储器操作，我们可以看到存储器写的数据总是 valA 或 valP。
写出 SEQ 中信号 mem\_data 的 HCL 代码。

答案：

```c
int mem_data = [
    # Value from register
    icode in { IRMMOVL, IPUSHL } : valA;
    # Return PC
    icode == ICALL : valP;
    # Default: Don’t write anything
];
```

### 练习题 4.24

我们希望只为向存储器写数据的指令设置控制信号 mem\_write。
写出 SEQ 中信号 mem\_write 的 HCL 代码。

答案：

```c
bool mem_write = icode in { IRMMOVL, IPUSHL, ICALL };
```

### 练习题 4.25

写出 Stat 的 HCL 代码，产生四个状态码 SAOK、SADR、SINS 和 SHLT（参见图 4-26）。

答案：

```c
## Determine instruction status
int Stat = [
      imem_error || dmem_error : SADR;
      !instr_valid: SINS;
      icode == IHALT : SHLT;
      1 : SAOK;
];
```

### 练习题 4.26

假设我们分析图 4-32 中的组合逻辑，认为它可以分成 6 个块，依次命名为 A\~F，延迟分别为 80、30、60、50、70 和 10ps，如下图所示：

![](images/06_17_ex4.26.svg)

在这些块之间插入流水线寄存器，就得到这一设计的流水线化的版本。
根据在哪里插入流水线寄存器，会出现不同的流水线深度（有多少个阶段）和最大吞吐量的组合。
假设每个流水线寄存器的延迟为 20ps。

* A. 只插入一个寄存器，得到一个二阶段的流水线。要使吞吐量最大化，应该在哪里插入寄存器呢？吞吐量和延迟是多少？
* B. 要使一个三阶段的流水线的吞吐量最大化，应该将两个寄存器插在哪里呢？吞吐量和延迟是多少？
* C. 要使一个四阶段的流水线的吞吐量最大化，应该将三个寄存器插在哪里呢？吞吐量和延迟是多少？
* D. 要得到一个吞吐量最大的设计，至少要有几个阶段？描述这个设计及其吞吐量和延迟。

* A. 在逻辑 C 和 D 之间插入寄存器，吞吐量是 5.26 GIPS，延迟是：380ps。
* B. 分别在逻辑 B 和 C 以及 D 和 E 之间插入寄存器，吞吐量是 7.69 GIPS，延迟是：390ps。
* C. 分别在逻辑 A 和 B，C 和 D 以及 D 和 E 之间插入寄存器，吞吐量是 9.09 GIPS，延迟是：440ps。
* B. 要使得吞吐量最大，至少需要 5 个阶段，在 (A,B)、(B,C)、(C,D)、(D,E) 之间插入寄存器，吞吐量是 10GIPS,延迟是 500ps。

### 练习题 4.27

让我们来看看图 4-32 中的系统，假设将它划分成任意数据的流水线阶段 k，每个阶段有相同的延迟 300/k，每个流水线寄存器的延迟为 20ps。

* A. 系统的延迟和吞吐量写成 k 的函数是什么？
* B. 吞吐量的上限等于多少？

答案：

* A 吞吐量为：1000/(300/k+20)=100/(30/k+2)=1000k/(300+20k) GIPS，延迟为：300+20k ps
* B 当 k 为无穷大时，吞吐量达到上限为：100/2=50 GIPS，此时延迟为无穷大

### 练习题 4.28

写出信号 f\_stat 的 HCL 代码，提供取出的指令的临时状态。

答案：

```c
## Determine status code for fetched instruction
int f_stat = [
      imem_error : SADR;
      !instr_valid: SINS;
      icode == IHALT : SHLT;
      1 : SAOK;
];
```

### 练习题 4.29

译码阶段中标号为 “dstE” 的块根据来自流水线寄存器 D 中取出的指令的各个阶段，产生寄存器文件 E 端口的寄存器 ID。
在 PIPE 的 HCL 描述中，得到的信号命名为 d\_dstE。
根据 SEQ 信号 dstE 的 HCL 描述，写出这个信号的 HCL 代码。（参考 4.3.4 节中的译码阶段。）
目前不用关心实现条件传送的逻辑。

答案：

```c
# WARNING: Conditional move not implemented correctly here
int d_dstE = [
    D_icode in { IRRMOVL, IIRMOVL, IOPL } : D_rB;
    D_icode in { IPUSHL, IPOPL, ICALL, IRET } : RESP;
    1 : RNONE; # Don’t write any register
];
```

### 练习题 4.30

假设 d\_valA 的 HCL 代码中第三和第四种情况（来自访存阶段的两个转发源）的顺序是反过来的。
请描述下列程序中 `rrmovl` 指令（第 5 行）导致的行为：

```x86asm
1   irmovl $5, %edx
2   irmovl $0x100,%esp
3   rmmovl %edx,0(%esp)
4   popl %esp
5   rrmovl %esp,%eax
```

答案：

由于 `popl` 指令（第 4 行）造成的加载/使用冒险，`rrmovl` 指令（第 5 行）会暂停一个周期。
当它进入译码阶段，`popl` 指令处于访存阶段，使 M\_dstE 和 M\_dstM 都等于 %esp。
如果两种情况反过来，那么来自 M\_valE 的写回优先级较高，导致增加了的栈指针被传送到 `rrmovl` 指令作为参数。
这与练习题 4.7 中确定的处理 `popl %esp` 的惯例不一样。

### 练习题 4.31

假设 d\_valA 的 HCL 代码中第五和第六种情况（来自写回阶段的两个转发源）的顺序是反过来的。
写一个会运行错误的 Y86 程序。
请描述错误是如何发生的，以及它对程序行为的影响。

答案：

```x86asm
```c
1   irmovl $5, %edx
2   irmovl $0x100,%esp
3   rmmovl %edx,0(%esp)
4   popl %esp
5   nop
6   nop
7   rrmovl %esp,%eax
```

两个 `nop` 指令会导致当 `rrmovl` 指令在译码阶段中时，`popl` 指令处于写回阶段。
如果给予处于写回阶段中的两个转发源错误的优先级，那么寄存器 %eax 会设置成增加了的栈指针（书中答案不一样，应该是书本有误：增加了的程序计数器），而不是从存储器中读出的值。

### 练习题 4.32

根据提供到流水线寄存器 E 的源操作数 valB 的值，写出信号 d\_valB 的 HCL 代码。

答案：

```c
int d_valB = [
    d_srcB == e_dstE : e_valE;           # Forward valE from execute
    d_srcB == M_dstM : m_valM;           # Forward valM from memory
    d_srcB == M_dstE : M_valE;           # Forward valE from memory
    d_srcB == W_dstM : W_valM;           # Forward valM from write back
    d_srcB == W_dstE : W_valE;           # Forward valE from write back
    1 : d_rvalB;                         # Use value read from register file
];
```

### 练习题 4.33

d\_valA 的 HCL 代码中的第二种情况使用了信号 e_dstE，判断是否要选择 ALU 的输出 e_valE 作为转发源。
假设我们用 E\_dstE，也就是流水线寄存器 E 中的目的寄存器 ID，作为这个选择。
写出一个采用这个修改过的转发逻辑就会产生错误结果的 Y86 程序。

答案：

```x86asm
1   irmovl $3, %eax
2   irmovl $1, %edx
3   irmovl $2, %ebx
4   subl %edx, %ebx         # CC = 000
5   cmove %ebx, %eax        # Not transfer Should be $3
6   halt
```

在未修改的代码中，由于 CC = 000，条件数据传送没有发生，%eax 的值为 3（第 5 行执行后）,在修改后的版本，条件传送发生了，%eax 的值为 1（第 5 行执行后）。

### 练习题 4.34

在这个阶段，通过检查数据存储器的非法地址情况，我们能够完成状态码 Stat 的计算。
写出信号 m\_stat 的 HCL 代码。

答案：

```c
int m_stat = [
        dmem_erorr : SADR;
        1 : M_stat;
];
```

### 练习题 4.35

写一个 Y86 汇编语言程序，它能导致出现组合 A 的情况，并判断控制逻辑是否处理正确。

答案：

[cjr.ys](y86-code/cjr.ys)

### 练习题 4.36

写一个 Y86 汇编语言程序，它能导致出现组合 B 的情况，如果流水线运行正确，以 halt 指令结束。

答案：

[ret-hazard.ys](y86-code/ret-hazard.ys)

### 练习题 4.37

写出 PIPE 实现中信号  D\_stall 的 HCL 代码。

答案：

```c
bool D_stall =
        # Conditions for a load/use hazard
        E_icode in { IMRMOVL, IPOPL } &&
        E_dstM in { d_srcA, d_srcB };
```

### 练习题 4.38

写出 PIPE 实现中信号 E\_bubble 的 HCL 代码。

答案：

```c
bool E_bubble =
        # Mispredicted branch
        (E_icode == IJXX && !e_Cnd) ||
        # Stalling at fetch while ret passes through pipeline
        # but not condition for a load/use hazard
        !(E_icode in { IMRMOVL, IPOPL }
          && E_dstM in { d_srcA, d_srcB });
```

### 练习题 4.39

写出 PIPE 实现中信号 set\_cc 的 HCL 代码。
该信号只对 OPl 指令出现，应该考虑程序异常的影响。

答案：

```c
bool set_cc =
        E_icode == IOPL &&
        !m_stat in { SADR, SINS, SHLT } && !W_stat in { SADR, SINS, SHLT };
```

### 练习题 4.40

写出 PIPE 实现中信号 M\_bubble 和 W\_stall 的 HCL 代码。
后者需要修改图 4-64 中列出的异常事件。

答案：

在下一个周期向访存阶段插入气泡需要检查当前周期中访存或者写回阶段中是否有异常。

```c
# Start injecting bubbles as soon as exception passes through memory stage
bool M_bubble = m_stat in { SADR, SINS, SHLT } || W_stat in { SADR, SINS, SHLT };
```

对于暂停写回阶段，只用检查这个阶段中的指令的状态。
如果当访存阶段中有异常指令时我们也暂停了，那么这条指令就不能进入写会阶段：

```c
bool W_stall = W_stat in { SADR, SINS, SHLT };
```

### 练习题 4.41

假设我们使用了一种成功率可以达到 65% 的分支预测策略，例如后向分支选择、前向分支就不选择，见 4.5.4 节。
那么对 CPI 有什么样的影响，假设其他所有频率都不变。

答案：

|原因|名称|指令频率|条件频率|气泡|乘积|
|-|-|-|-|-|-|
|加载/使用|_lp_|0.25|0.20|1|0.05|
|预测错误|_mp_|0.20|0.35|2|0.14|
|返回|_rp_|0.02|1.00|3|0.06|
|总处罚|||||0.25|

三种处罚的总和是 0.25，得到 CPI 为 1.25,比原来的 1.27 少了 0.02。

### 练习题 4.42

让我们来分析你为练习题 4.4 和 4.5 写的程序中使用条件传送和条件控制转移的相对性能。
假设用这些程序计算一个非常长的数据的绝对值的和，所以整体性能主要由内循环所需要的周期数决定。
假设跳转指令预测为选择分支，而大约 50% 的数组值为正。

* A. 平均来说，这两个程序的内循环中执行了多少条指令？
* B. 平均来说，这两个程序的内循环中插入了多少个气泡？
* C. 对着两个程序来说，每个数组元素平均需要多少个时钟周期？

答案：

* A
  * 平均来说，4.4 内循环中执行了 10.5 条指令。
  * 平均来说，4.5 内循环中执行了 10 条指令。
* B
  * 平均来说，4.4 内循环中插入了 1 个气泡。
  * 平均来说，4.5 内循环中插入了 0 个气泡。
* C
  * 4.4 每个数组元素平均需要 11.5 个时钟周期。
  * 4.5 每个数组元素平均需要 10 个时钟周期。

  ## 家庭作业

  ### 4.43 \*

  在 3.4.2 节中，IA32 `pushl` 指令被描述成要减少栈指针，然后将寄存器存储在栈指针的位置。
  因此，如果我们有一条指令形如对于某个寄存器 REG，pushl REG，它等价于下面的代码序列：

  ```x86asm
  subl $4, %esp       Decrement stack pointer
  movl REG,(%esp)     Store REG on stack
  ```

  * A. 借助于练习题 4.6 中所做的分析，这段代码序列正确描述了指令 `pushl %esp` 的行为吗？请解释。
  * B. 你该如何改写这段代码序列，使得它能够像对 REG 是其他寄存器时一样，正确地描述 REG 是 %esp 的情况。

答案：

* A 没正确描述 `pushl %esp`，这段代码将 %esp 修改后的值保存到栈中了
* B. 如下：

 ```x86asm
 movl REG,-4(%esp)     Store REG on stack
 subl $4, %esp       Decrement stack pointer
 ```

 ### 4.44 \*

 3.4.2 节中，IA32 `popl` 指令被描述为将来自栈顶的结果复制到目的寄存器，然后将栈指针减少。
 因此，如果我们有一条指令形如 `popl REG`，它等价于下面的代码序列：

 ```x86asm
movl (%esp),REG     Read REG from stack
addl $4,%esp        Increment stack pointer
```

* A.借助于练习题 4.7 中所做的分析，这段代码序列正确地描述了指令 `popl %esp` 的行为吗? 请解释。
* B.你该如何改写这段代码序列，使得它能够像对 REG 是其他寄存器时一样，正确地描述 REG 是 %esp 的情况?

答案：

* A. 没有，指令序列会将栈中的值赋值给 %esp 然后将 %esp 的值加 4
* B.

```x86asm
addl $4,%esp        Increment stack pointer
movl -4(%esp),REG     Read REG from stack
```

### 4.45 \*\*\*

你的作业是写一个执行冒泡排序的Y86程序。
下面这个 C 函数用数组引用实现冒泡排序，供你参考:

```c
/* Bubble sort: Array version */
void bubble_a(int *data, int count) {
  int i, last;
  for (last = count-1; last > 0; last--) {
    for (i = 0; i < last; i++)
      if (data[i+1] < data[i]) {
        /* Swap adjacent elements */
        int t = data[i+1];
        data[i+1] = data[i];
        data[i] = t;
      }
  }
}
```

* A. 书写并测试一个 C 版本，它用指针引用数组元素，而不是用数组索引。
* B. 书写并测试一个由这个函数和测试代码组成的 Y86 程序。
你会发现模仿编译你的 C 代码产生的 IA32 代码来做实现会很有帮助。
虽然指针比较通常是用无符号算术运算来实现的，但是在这个练习中，你可以使用有符号算术运算。

答案：

* A. [ex4.45a.c](ex4.45a.c)
* B. [ex4.45b.ys](ex4.45b.ys)

### 4.46 \*\*

修改对家庭作业 4.45 所写的代码，用条件传送来实现冒泡排序函数的内循环中的测试和交换。

答案： [ex4.46.ys](ex4.46.ys)

### 4.47 \*

如 3.7.2小节中讲述的那样，IA32的指令 leave 可以用来使栈为返回做准备。
它等价于下面这个 Y86 代码序列:

```x86asm
1 rrmovl %ebp, %esp     Set stack pointer to beginning of frame
2 popl %ebp             Restore saved %ebp and set stack ptr to end of caller’s frame
```

假设我们要往 Y86 指令集中加入一条指令，编码如下：

![](images/06_17_ex4.47.svg)

请描述实现这一指令所执行的计算。可以参考 `popl` 的计算(图4-20)。

答案：

|阶段|leave|
|-|-|
|取指|icode:ifun ← M<sub>1</sub>[PC]</br>valP ← PC+1|
|译码|valA ← R[%ebp]</br>valB ← R[%ebp]|
|执行|valE ← valB + 4|
|访存|valM ← M<sub>4</sub>[valA]|
|写回|R[%esp] ← valE</br>R[%ebp] ← valM|
|更新PC|PC ← valP|PC ← valP|PC ← valP|

### 4.48 \*

在 Y86 示例程序中，例如图 4-6 中的 Sum 函数，我们多次遇到想将一个常数加到寄存器的情况(例如第 12 和 13 行，以及第 14 和 15 行)。
这要求首先用 `irmovl` 指令将一个寄存器设置为这个常数然后用 `addl` 指令把这个值加到目的寄存器。
假设想添加一条新指令 `iaddl`，其格式如下：

![](images/06_17_ex4.48.svg)

这条指令将常数值 V 加到寄存器 rB。
请描述实现这一指令所执行的计算。可以参考 `irmovl` 和 `OPl` 的计算(图 4-18)。

答案：

|阶段|iaddl V, rB|
|-|-|
|取指|icode:ifun ← M<sub>1</sub>[PC]</br>rA:rB ← M<sub>1</sub>[PC+1]</br>valC ← M<sub>4</sub>[PC+2]</br>valP ← PC+6|
|译码|valB ← R[rB]|
|执行|valE ← valB + valC|
|访存||
|写回|R[rB] ← valE|
|更新PC|PC ← valP|

### 4.49 \*\*

文件 seq-full.hcl 还将常数 ILEAVE 声明为十六进制值 D，也就是 `leave` 的指令代码，同时将常数 REBP 声明为 7，即 %ebp 的寄存器。
修改实现 `leave` 指令的控制逻辑块的 HCL 描述，就像家庭作业 4.47 中描述的那样。
可以参考实验资料获得如何为你的解答生成模拟器以及如何测试模拟器的指导。

答案：

* HCL 文件：[ex4.49.hcl](ex4.49.hcl)，具体修改点可以和 sim/y86-code/seq-full.hcl 对比
* 测试代码：[ex4.49.ys](ex4.49.ys)

### 4.50 \*\*

文件 seq-full.hcl 包括 SEQ 的 HCL 描述，并将常数 IIADDL 声明为十六进制值 C，也就是 `iaddl` 的指令代码。
修改实现 `iaddl` 指令的控制逻辑块的 HCL 描述，就像家庭作业 4.48 中描述的那样。
可以参考实验资料获得如何为你的解答生成模拟器以及如何测试模拟器的指导。

答案：

* HCL 文件：[ex4.50.hcl](ex4.50.hcl)，具体修改点可以和 sim/seq/seq-full.hcl 对比
* 测试代码：[ex4.50.ys](ex4.50.ys)

### 4.51 \*\*\*

假设要创建一个较低成本的、基于我们为PIPE-设计的结构(图4-41)的流水线化的处理器，不使用旁路技术。
这个设计用暂停来处理所有的数据相关，直到产生所需值的指令已经通过了写回阶段。
文件 pipe-stall.hcl 包含一个对 PIPE 的HCL 代码的修改版，其中禁止了旁路逻辑。
也就是信号 d\_valA 和 d\_valB 只是简单地声明如下：

```x86asm
## DO NOT MODIFY THE FOLLOWING CODE.
## No forwarding. valA is either valP or value from register file
int d_valA = [
    D_icode in { ICALL, IJXX } : D_valP; # Use incremented PC
    1 : d_rvalA; # Use value read from register file
];

## No forwarding. valB is value from register file
int d_valB = d_rvalB;
```

修改文件结尾处的流水线控制逻辑，使之能正确处理所有可能的控制和数据冒险。
作为设计工作的一部分，你应该分析各种控制情况的组合，就像我们在 PIPE 的流水线控制逻辑设计中做的那样。
你会发现有许多不同的组合，因为有更多的情况需要流水线暂停。
要确保你的控制逻辑能正确处理每种组合情况。
可以参考实验资料指导你如何为解答生成模拟器以及如何测试。

答案：

* HCL 文件：[ex4.51.hcl](ex4.51.hcl)，具体修改点可以和 sim/pipe/sim/pipe/pipe-nobypass.hcl 对比
* 测试代码：使用上述 HCL 文件编译 psim 后，进 sim/y86-code 运行 `make testpsim`

### 4.52 \*\*\*

文件 pipe-full.hcl 还包含常数 ILEAVE 和 REBP 的声明。
修改该文件以实现指令 `leave`，就像家庭作业 4.47 中描述的那样。
可以参考实验资料获得如何为你的解答生成模拟器以及如何测试模拟器的指导。

答案：

* HCL 文件：[ex4.52.hcl](ex4.52.hcl)，具体修改点可以和 sim/pipe/sim/pipe/pipe-full.hcl 对比
* 测试代码：
  * 使用上述 HCL 文件编译 psim 后，进 sim/y86-code 运行 `make testpsim`
  * [ex4.49.ys](ex4.49.ys)

### 4.53 \*\*

文件 pipe-full.hcl 包含一份 PIPE 的 HCL 描述，以及常数值 `IIADDL` 的声明。
修改该文件以实现指令 `iaddl`，就像家庭作业 4.48 中描述的那样。
可以参考实验资料获得如何为你的解答生成模拟器以及如何测试模拟器的指导。

答案：

* HCL 文件：[ex4.53.hcl](ex4.53.hcl)，具体修改点可以和 sim/pipe/sim/pipe/pipe-full.hcl 对比
* 测试代码：
  * 使用上述 HCL 文件编译 psim 后，进 sim/y86-code 运行 `make testpsim`
  * [ex4.50.ys](ex4.50.ys)

### 4.54 \*\*\*

文件 pipe-nt.hcl 包含一份 PIPE 的 HCL 描述，并将常数 J\_YES 声明为值 0，即无条件转移指令的功能码。
修改分支预测逻辑，使之对条件转移预测为不选择分支，而对无条件转移和 `call` 预测为选择分支。
你需要设计一种方法来得到跳转目标地址 valC，并送到流水线寄存器 M，以便从错误的分支预测中恢复。
可以参考实验资料获得如何为你的解答生成模拟器以及如何测试模拟器的指导。

答案：

* HCL 文件：[ex4.54.hcl](ex4.54.hcl)，具体修改点可以和 sim/pipe/sim/pipe/pipe-nt.hcl 对比
* 测试代码：使用上述 HCL 文件编译 psim 后，进 sim/y86-code 运行 `make testpsim`

### 4.55 \*\*

文件 pipe-btfnt.hcl 包含一份PIPE的 HCL 描述，并将常数 J\_YES 声明为值 0，即无条件转移指令的功能码。
修改分支预测逻辑，使得当 valC &lt; valP 时(后向分支)，就预测条件转移为选择分支，当 valC &gt; valP 时(前向分支)，就预测为不择分支。
(由于 Y86 不支持无符号运算，你应该使用有符号比较来实现这个测试。)
并且将无条件转移和 `call` 预测为选择分支。
你需要设计一种方法来得到 valC 和 valP，并送到流水线寄存器 M，以便从错误的分支预测中恢复。
可以参考实验资料获得如何为你的解答生成模拟器以及如何测试模拟器的指导。

答案：

* HCL 文件：[ex4.55.hcl](ex4.55.hcl)，具体修改点可以和 sim/pipe/sim/pipe/pipe-btfnt.hcl 对比
* 测试代码：使用上述 HCL 文件编译 psim 后，进 sim/y86-code 运行 `make testpsim`

### 4.56 \*\*\*

我们的流水线化的设计有点不太现实，因为寄存器文件有两个写端口，
然而只有 `popl` 指令需要对寄存器文件同时进行两个写操作。
因为，其他指令只使用一个写端口，共享这个端口来写 valE 和 valM。
下面这个图是一个对写回逻辑的修改版，其中，将写回寄存器 ID（W\_dstE 和 W\_dstM）合并成一个信号 w\_dstE，
同时也将写回值（W\_valE 和 W\_valM）合并成一个信号 w\_valE：

![](images/07_17_ex4.56.svg)

用 HCL 写的执行这些合并的逻辑，如下所示：

```c
## Set E port register ID
int w_dstE = [
    ## writing from valM
    W_dstM != RNONE : W_dstM;
    1: W_dstE;
];

## Set E port value
int w_valE = [
    W_dstM != RNONE : W_valM;
    1: W_valE;
];
```

对这些多路复用器的控制由 dstE 确定——当它表明有某个寄存器时，就选择端口 E 的值，否则就选择端口 M 的值。

在模拟模型中，我们可以禁止寄存器端口 M，如下面这段 HCL 代码所示：

```c
## Disable register port M
## Set M port register ID
int w_dstM = RNONE;

## Set M port value
int w_valM = 0;
```

接下来的问题就是要设计处理 `popl` 的方法。
一种方法是用控制逻辑动态地处理指令 `popl rA`，使之与下面两条指令序列有一样的效果：

```x86asm
iaddl $4, %esp
mrmovl -4(%esp), rA
```

（关于指令 `iaddl` 的描述，请参考家庭作业 4.48）要注意两条指令的顺序，以保证 `popl %esp` 能正常工作。
要达到这个目的，可以让译码阶段的逻辑对上面列出的 `popl` 指令和 `addl` 指令一视同仁，除了它会预测下一个 PC 与当前 PC 相等以外。
在下一个周期，再次取出 `popl` 指令，但是指令代码变成了特殊的值 IPOP2。
它会被当做一条特殊的指令来处理，行为与上面列出的 `mrmovl` 指令一样。

文件 pipe-1w.hcl 包含上面将的修改过的写端口逻辑。
它将常数 IPOP2 声明为十六进制值 E。
还包括信号 f\_icode 的定义，它产生流水线寄存器 D 的 icode 字段。
可以修改这个定义，使得当第二次取出 `popl` 指令时，插入指令代码 IPOP2。
这个 HCL 文件还包含信号 f\_pc 的声明，也就是标号为 “Select PC” 的块（见图 4-55）在取值阶段产生的程序计数器的值。

修改该文件中的控制逻辑，使之按照我们描述的方式来处理 `popl` 指令。
可以参考实验资料获得如何为你的解答生成模拟器以及如何测试模拟器的指导。

答案：

* HCL 文件：[ex4.56.hcl](ex4.56.hcl)，具体修改点可以和 sim/pipe/sim/pipe/pipe-1w.hcl 对比
* 测试代码：使用上述 HCL 文件编译 psim 后，进 sim/y86-code 运行 `make testpsim`

### 4.57 \*\*\*

 在我们的 PIPE 的设计中，只要一条指令执行了 load 操作，从存储器中读一个值到寄存器，并且下一条指令要用这个寄存器作为源操作数，就会产生一个暂停。
 如果要在执行阶段中使用这个源操作数，暂停是避免冒险的唯一方法。

 对于第二条指令将源操作数存储到存储器的情况，例如 `rmmovl` 或 `pushl` 指令，是不需要这样的暂停的。
 考虑下面这段代码示例：

 ```x86asm
 1    mrmovl 0(%ecx), %edx      # Load 1
 2    pushl %edx                # Store 1
 3    nop
 4    popl %edx                 # Load 2
 5    rmmovl %eax, 0(%edx)      # Store 2
 ```

 在第 1 行和第 2 行，`mrmovl` 指令从存储器读一个值到 %edx，然后 `pushl` 指令将这个值压入栈中。
 我们的 PIPE 设计会让 `pushl` 指令暂停，以避免状态/使用冒险。
 不过，可以看到，`pushl` 指令要到访存阶段才会需要 %edx 的值。
 我们可以再添加一条旁路通路，如下图 4-69 所示，将存储器输出（信号 m\_valM）转发到流水线寄存器 M 中的 valA 字段。
 在下一个时钟周期，被传送的值就能吸入存储器了。
 这种技术被称为加载转发（load forwarding）。

 TODO

 注意，上述代码序列中的第二个例子（第 4 行和第 5 行）不能利用加载转发。
 `popl` 指令加载的值是作为下一条指令地址计算的一部分的，而在执行阶段而非访存阶段就需要这个值了。

 * A 写出描述发现加载/使用冒险条件的逻辑公式，类似于图 4-64 所示，除了能用加载转发时不会导致暂停以外。
 * B 文件 pipe-lf.hcl 包含一个 PIPE 控制逻辑的修改版。
 它含有信号 e\_valA 的定义，用来实现图 4-69 中标号为 “Fwd A” 的块。
 它还将流水线控制逻辑中的加载/使用冒险的条件设置为 0，因此流水线控制逻辑将不会发现任何形式的加载/使用冒险。
 修改这个 HCL 描述以实现加载转发。
 可以参考实验资料获得如何为你的解答生成模拟器以及如何测试模拟器的指导。

A:

|条件|触发条件|
|-|-|
|加载转发|E_icode ∈ {IRMMOVL, IPUSHL}|

 TODO
 
 ### 4.58 \*\*

 比较两个版本的冒泡排序的性能（家庭作业 4.45 和 4.46）。
 解释为什么一个版本的性能比另一个的好。

 TODO