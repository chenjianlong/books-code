# 第4章 处理器体系结构

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

TODO

### 练习题 4.4

修改 Sum 函数的 Y86 代码（图 4-6），实现 AbsSum，计算一个数组的绝对值的和。
在内循环中使用条件跳转指令。

TODO

### 练习题 4.5

修改 Sum 函数的 Y86 代码（图 4-6），实现 AbsSum，计算一个数组的绝对值的和。
在内循环中使用条件传送指令。

TODO

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

TODO

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

这表明 `popl %esp` 会弹出这条指令执行前 %esp 指定的内存的值到 %esp 寄存器中。

这条命令等价于 `mrmovl (%esp), %esp`。

### 练习题 4.8

写出信号 xor 的 HCL 表达式，xor 就是异或，输入为 a 和 b。
信号 xor 和上面定义的 eq 有什么关系？

TODO

### 练习题 4.9

假设你用练习题 4.8 中的异或电路而不是位级的相等电路来实现一个字级的相等电路。
设计一个 32 位字的相等电路需要 32 个字级的异或电路，另外还要两个逻辑门。

TODO

### 练习题 4.10

写一个电路的 HCL 代码，对于输入字 A、B 和 C，选择中间值。
也就是，输出等于三个输入中居于最小值和最大值中间的那个字。

TODO

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

这条指令的执行会怎样改变寄存器和PC呢？

TODO

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

TODO

### 练习题 4.13

根据图 4-20 中列出的步骤，指令 `pushl %esp` 会有什么样的效果？
这与练习题 4.6 中确定的 Y86 期望的行为一致吗？

TODO

### 练习题 4.14

假设 popl 在写回阶段中的两个寄存器写操作按照图 4-20 列出的顺序进行。
`popl %esp` 执行的效果会是怎样的？
这与练习题 4.7 中确定的 Y86 期望的行为一致吗？

TODO

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

TODO

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
  <tr><th>译码</th><td></td><td></td></tr>
  <tr><th>执行</th><td>valE←valB+(-4)</td><td></td></tr>
  <tr><th>访存</th><td>M<sub>4</sub>[valE]←valP</td><td></td></tr>
  <tr><th>写回</th><td>R[%esp]←valE</td><td></td></tr>
  <tr><th>更新PC</th><td>PC←valC</td><td></td></tr>
</table>

TODO

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

TODO

### 练习题 4.27

让我们来看看图 4-32 中的系统，假设将它划分成任意数据的流水线阶段 k，每个阶段有相同的延迟 300/k，每个流水线寄存器的延迟为 20ps。

* A. 系统的延迟和吞吐量写成 k 的函数是什么？
* B. 吞吐量的上限等于多少？

TODO

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
5   rrmovl %esp,%eax
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