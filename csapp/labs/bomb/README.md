## bomb 实验

附带的 x86-64 bomb 程序是官方提供给自学学生学习的程序

下面是我的分析过程

### phase_1

* 通过 gdb 运行程序
* 通过 bomb.c 可以或者 gdb 命令知道 `phase_1` 所在的代码行数
* 设置断点
* 然后使用 stepi 命令进入 `phase_1` 函数体
* 使用 disas 得到反汇编后的汇编代码，如下：

```asm
Dump of assembler code for function phase_1:
=> 0x0000000000400ee0 <+0>:     sub    $0x8,%rsp
   0x0000000000400ee4 <+4>:     mov    $0x402400,%esi
   0x0000000000400ee9 <+9>:     call   0x401338 <strings_not_equal>
   0x0000000000400eee <+14>:    test   %eax,%eax
   0x0000000000400ef0 <+16>:    je     0x400ef7 <phase_1+23>
   0x0000000000400ef2 <+18>:    call   0x40143a <explode_bomb>
   0x0000000000400ef7 <+23>:    add    $0x8,%rsp
   0x0000000000400efb <+27>:    ret
End of assembler dump.
```

* 解析汇编代码可知逻辑为对比输入字符串和 `0x402400` 所在字符串，若相等则通过检查，通过以下命令查看要对比的字符串

```
(gdb) x/56xb 0x402400
0x402400:       0x42    0x6f    0x72    0x64    0x65    0x72    0x20    0x72
0x402408:       0x65    0x6c    0x61    0x74    0x69    0x6f    0x6e    0x73
0x402410:       0x20    0x77    0x69    0x74    0x68    0x20    0x43    0x61
0x402418:       0x6e    0x61    0x64    0x61    0x20    0x68    0x61    0x76
0x402420:       0x65    0x20    0x6e    0x65    0x76    0x65    0x72    0x20
0x402428:       0x62    0x65    0x65    0x6e    0x20    0x62    0x65    0x74
0x402430:       0x74    0x65    0x72    0x2e    0x00    0x00    0x00    0x00
```

得到正确的字符串是：

```
得到字符串：Border relations with Canada have never been better.
```

### phase_2

类似地，可以得到这个函数的反汇编代码，方法这里不再赘述

```asm
Dump of assembler code for function phase_2:
=> 0x0000000000400efc <+0>:     push   %rbp
   0x0000000000400efd <+1>:     push   %rbx
   0x0000000000400efe <+2>:     sub    $0x28,%rsp
   0x0000000000400f02 <+6>:     mov    %rsp,%rsi
   0x0000000000400f05 <+9>:     call   0x40145c <read_six_numbers>
   0x0000000000400f0a <+14>:    cmpl   $0x1,(%rsp)
   0x0000000000400f0e <+18>:    je     0x400f30 <phase_2+52>
   0x0000000000400f10 <+20>:    call   0x40143a <explode_bomb>
   0x0000000000400f15 <+25>:    jmp    0x400f30 <phase_2+52>
   0x0000000000400f17 <+27>:    mov    -0x4(%rbx),%eax
   0x0000000000400f1a <+30>:    add    %eax,%eax
   0x0000000000400f1c <+32>:    cmp    %eax,(%rbx)
   0x0000000000400f1e <+34>:    je     0x400f25 <phase_2+41>
   0x0000000000400f20 <+36>:    call   0x40143a <explode_bomb>
   0x0000000000400f25 <+41>:    add    $0x4,%rbx
   0x0000000000400f29 <+45>:    cmp    %rbp,%rbx
   0x0000000000400f2c <+48>:    jne    0x400f17 <phase_2+27>
   0x0000000000400f2e <+50>:    jmp    0x400f3c <phase_2+64>
   0x0000000000400f30 <+52>:    lea    0x4(%rsp),%rbx
   0x0000000000400f35 <+57>:    lea    0x18(%rsp),%rbp
   0x0000000000400f3a <+62>:    jmp    0x400f17 <phase_2+27>
   0x0000000000400f3c <+64>:    add    $0x28,%rsp
   0x0000000000400f40 <+68>:    pop    %rbx
   0x0000000000400f41 <+69>:    pop    %rbp
   0x0000000000400f42 <+70>:    ret
End of assembler dump.
```

通过 `call   0x40145c <read_six_numbers>` 可以猜测是从输入的字符串中读取 6 个数字（有兴趣的可以反汇编 `read_six_numbers` 的函数体，这里略过），
继续解析汇编代码确定这个想法，并且数字的规则是 1 开始的等比数列，也就是：

```
1 2 4 8 16 32
```

### phase_3

* 首先，得到汇编代码

```asm
Dump of assembler code for function phase_3:
=> 0x0000000000400f43 <+0>:     sub    $0x18,%rsp
   0x0000000000400f47 <+4>:     lea    0xc(%rsp),%rcx
   0x0000000000400f4c <+9>:     lea    0x8(%rsp),%rdx
   0x0000000000400f51 <+14>:    mov    $0x4025cf,%esi
   0x0000000000400f56 <+19>:    mov    $0x0,%eax
   0x0000000000400f5b <+24>:    call   0x400bf0 <__isoc99_sscanf@plt>
   0x0000000000400f60 <+29>:    cmp    $0x1,%eax
   0x0000000000400f63 <+32>:    jg     0x400f6a <phase_3+39>
   0x0000000000400f65 <+34>:    call   0x40143a <explode_bomb>
   0x0000000000400f6a <+39>:    cmpl   $0x7,0x8(%rsp)
   0x0000000000400f6f <+44>:    ja     0x400fad <phase_3+106>
   0x0000000000400f71 <+46>:    mov    0x8(%rsp),%eax
   0x0000000000400f75 <+50>:    jmp    *0x402470(,%rax,8)
   0x0000000000400f7c <+57>:    mov    $0xcf,%eax
   0x0000000000400f81 <+62>:    jmp    0x400fbe <phase_3+123>
   0x0000000000400f83 <+64>:    mov    $0x2c3,%eax
   0x0000000000400f88 <+69>:    jmp    0x400fbe <phase_3+123>
   0x0000000000400f8a <+71>:    mov    $0x100,%eax
   0x0000000000400f8f <+76>:    jmp    0x400fbe <phase_3+123>
   0x0000000000400f91 <+78>:    mov    $0x185,%eax
   0x0000000000400f96 <+83>:    jmp    0x400fbe <phase_3+123>
   0x0000000000400f98 <+85>:    mov    $0xce,%eax
   0x0000000000400f9d <+90>:    jmp    0x400fbe <phase_3+123>
   0x0000000000400f9f <+92>:    mov    $0x2aa,%eax
   0x0000000000400fa4 <+97>:    jmp    0x400fbe <phase_3+123>
   0x0000000000400fa6 <+99>:    mov    $0x147,%eax
   0x0000000000400fab <+104>:   jmp    0x400fbe <phase_3+123>
   0x0000000000400fad <+106>:   call   0x40143a <explode_bomb>
   0x0000000000400fb2 <+111>:   mov    $0x0,%eax
   0x0000000000400fb7 <+116>:   jmp    0x400fbe <phase_3+123>
   0x0000000000400fb9 <+118>:   mov    $0x137,%eax
   0x0000000000400fbe <+123>:   cmp    0xc(%rsp),%eax
   0x0000000000400fc2 <+127>:   je     0x400fc9 <phase_3+134>
   0x0000000000400fc4 <+129>:   call   0x40143a <explode_bomb>
   0x0000000000400fc9 <+134>:   add    $0x18,%rsp
   0x0000000000400fcd <+138>:   ret
End of assembler dump.
```

* 函数首先用 sscanf 解析输入的字符串，其中 %esi(`0x4025cf`) 指定了格式化字符串的地址
* dump 出所在地址的值

```
(gdb) x/8xb 0x4025cf
0x4025cf:       0x25    0x64    0x20    0x25    0x64    0x00    0x45    0x72
```

可知格式化字符串为：

```
%d %d
```

* 由下面代码可知，第一个数字不能大于 7

```
   0x0000000000400f6a <+39>:    cmpl   $0x7,0x8(%rsp)
   0x0000000000400f6f <+44>:    ja     0x400fad <phase_3+106>
```

* 由下面代码可知，根据输入的第一个数字跳转到对应地址

```
   0x0000000000400f71 <+46>:    mov    0x8(%rsp),%eax
   0x0000000000400f75 <+50>:    jmp    *0x402470(,%rax,8)
```

* 解析对应地址的内容

```
(gdb) x/56xb 0x402470
0x402470:       0x7c    0x0f    0x40    0x00    0x00    0x00    0x00    0x00
0x402478:       0xb9    0x0f    0x40    0x00    0x00    0x00    0x00    0x00
0x402480:       0x83    0x0f    0x40    0x00    0x00    0x00    0x00    0x00
0x402488:       0x8a    0x0f    0x40    0x00    0x00    0x00    0x00    0x00
0x402490:       0x91    0x0f    0x40    0x00    0x00    0x00    0x00    0x00
0x402498:       0x98    0x0f    0x40    0x00    0x00    0x00    0x00    0x00
```

* 解析后续汇编代码可知，这一步有多个合法答案，下面每一行都是这一步的合法答案：

```
0 207
1 311
2 707
3 256
4 389
5 206
6 682
```

### phase_4

* 首先，得到汇编代码

```asm
(gdb) disas
Dump of assembler code for function phase_4:
=> 0x000000000040100c <+0>:     sub    $0x18,%rsp
   0x0000000000401010 <+4>:     lea    0xc(%rsp),%rcx
   0x0000000000401015 <+9>:     lea    0x8(%rsp),%rdx
   0x000000000040101a <+14>:    mov    $0x4025cf,%esi
   0x000000000040101f <+19>:    mov    $0x0,%eax
   0x0000000000401024 <+24>:    call   0x400bf0 <__isoc99_sscanf@plt>
   0x0000000000401029 <+29>:    cmp    $0x2,%eax
   0x000000000040102c <+32>:    jne    0x401035 <phase_4+41>
   0x000000000040102e <+34>:    cmpl   $0xe,0x8(%rsp)
   0x0000000000401033 <+39>:    jbe    0x40103a <phase_4+46>
   0x0000000000401035 <+41>:    call   0x40143a <explode_bomb>
   0x000000000040103a <+46>:    mov    $0xe,%edx
   0x000000000040103f <+51>:    mov    $0x0,%esi
   0x0000000000401044 <+56>:    mov    0x8(%rsp),%edi
   0x0000000000401048 <+60>:    call   0x400fce <func4>
   0x000000000040104d <+65>:    test   %eax,%eax
   0x000000000040104f <+67>:    jne    0x401058 <phase_4+76>
   0x0000000000401051 <+69>:    cmpl   $0x0,0xc(%rsp)
   0x0000000000401056 <+74>:    je     0x40105d <phase_4+81>
   0x0000000000401058 <+76>:    call   0x40143a <explode_bomb>
   0x000000000040105d <+81>:    add    $0x18,%rsp
   0x0000000000401061 <+85>:    ret
End of assembler dump.
```

* 同样，看下 sscanf 的格式化字符串：

```
(gdb) x/8xb 0x4025cf
0x4025cf:       0x25    0x64    0x20    0x25    0x64    0x00    0x45    0x72
```

得到

```
%d %d
```

同样是输入两个数字

* 接着看

```
0x000000000040102e <+34>:    cmpl   $0xe,0x8(%rsp)
0x0000000000401033 <+39>:    jbe    0x40103a <phase_4+46>
0x0000000000401035 <+41>:    call   0x40143a <explode_bomb>
```

可以知道第一个数字需要小于等于 `0xe` 即小于等于 `14`

* 接着反汇编 `func4`

```asm
Dump of assembler code for function func4:
=> 0x0000000000400fce <+0>:     sub    $0x8,%rsp				Allocate 8 byte
   0x0000000000400fd2 <+4>:     mov    %edx,%eax				eax = 14
   0x0000000000400fd4 <+6>:     sub    %esi,%eax				eax -= 0
   0x0000000000400fd6 <+8>:     mov    %eax,%ecx				ecx = 14
   0x0000000000400fd8 <+10>:    shr    $0x1f,%ecx				ecx = 0
   0x0000000000400fdb <+13>:    add    %ecx,%eax				eax = 14
   0x0000000000400fdd <+15>:    sar    %eax						eax = 7
   0x0000000000400fdf <+17>:    lea    (%rax,%rsi,1),%ecx		ecx = 7
   0x0000000000400fe2 <+20>:    cmp    %edi,%ecx				Compare ecx:edi
   0x0000000000400fe4 <+22>:    jle    0x400ff2 <func4+36>		If <= goto ff2
   0x0000000000400fe6 <+24>:    lea    -0x1(%rcx),%edx			edx=ecx-1
   0x0000000000400fe9 <+27>:    call   0x400fce <func4>			Call func4
   0x0000000000400fee <+32>:    add    %eax,%eax				eax *= 2
   0x0000000000400ff0 <+34>:    jmp    0x401007 <func4+57>		goto end
   0x0000000000400ff2 <+36>:    mov    $0x0,%eax				eax = 0
   0x0000000000400ff7 <+41>:    cmp    %edi,%ecx				Compare ecx:edi
   0x0000000000400ff9 <+43>:    jge    0x401007 <func4+57>		If >= goto end
   0x0000000000400ffb <+45>:    lea    0x1(%rcx),%esi			esi = ecx + 1
   0x0000000000400ffe <+48>:    call   0x400fce <func4>			Call func4
   0x0000000000401003 <+53>:    lea    0x1(%rax,%rax,1),%eax	eax = 2 * eax + 1
   0x0000000000401007 <+57>:    add    $0x8,%rsp				end:
   0x000000000040100b <+61>:    ret
End of assembler dump.
```

翻译成 C 代码更直观：

```c
// x = 0, y = 14
int func4(int num, int x, int y) {
	int ret = y - x;
	unsigned ecx = ret;
	ecx >>= 31;
	ret += ecx;
	ret >>= 1;
	ecx = ret + x;
	if (num <= ecx) {
		ret = 0
		if (num >= ecx) {
			return ret;
		} else {
			x = ecx + 1;
			return 2 * func4(num, x, y) + 1;
		}
	} else {
		y = ecx - 1;
		return 2 * func4(num, x, y);
	}
}
```

可以知道第一个数字是 7。

* 接下来

```asm
   0x0000000000401051 <+69>:    cmpl   $0x0,0xc(%rsp)
   0x0000000000401056 <+74>:    je     0x40105d <phase_4+81>
   0x0000000000401058 <+76>:    call   0x40143a <explode_bomb>
```

可以知道第二个数字是 0。

得到这一步的答案：

```
7 0
```

### phase_5

* 得到汇编代码

```asm
Dump of assembler code for function phase_5:
=> 0x0000000000401062 <+0>:     push   %rbx
   0x0000000000401063 <+1>:     sub    $0x20,%rsp
   0x0000000000401067 <+5>:     mov    %rdi,%rbx
   0x000000000040106a <+8>:     mov    %fs:0x28,%rax
   0x0000000000401073 <+17>:    mov    %rax,0x18(%rsp)
   0x0000000000401078 <+22>:    xor    %eax,%eax
   0x000000000040107a <+24>:    call   0x40131b <string_length>
   0x000000000040107f <+29>:    cmp    $0x6,%eax
   0x0000000000401082 <+32>:    je     0x4010d2 <phase_5+112>
   0x0000000000401084 <+34>:    call   0x40143a <explode_bomb>
   0x0000000000401089 <+39>:    jmp    0x4010d2 <phase_5+112>
   0x000000000040108b <+41>:    movzbl (%rbx,%rax,1),%ecx
   0x000000000040108f <+45>:    mov    %cl,(%rsp)
   0x0000000000401092 <+48>:    mov    (%rsp),%rdx
   0x0000000000401096 <+52>:    and    $0xf,%edx
   0x0000000000401099 <+55>:    movzbl 0x4024b0(%rdx),%edx
   0x00000000004010a0 <+62>:    mov    %dl,0x10(%rsp,%rax,1)
   0x00000000004010a4 <+66>:    add    $0x1,%rax
   0x00000000004010a8 <+70>:    cmp    $0x6,%rax
   0x00000000004010ac <+74>:    jne    0x40108b <phase_5+41>
   0x00000000004010ae <+76>:    movb   $0x0,0x16(%rsp)
   0x00000000004010b3 <+81>:    mov    $0x40245e,%esi
   0x00000000004010b8 <+86>:    lea    0x10(%rsp),%rdi
   0x00000000004010bd <+91>:    call   0x401338 <strings_not_equal>
   0x00000000004010c2 <+96>:    test   %eax,%eax
   0x00000000004010c4 <+98>:    je     0x4010d9 <phase_5+119>
   0x00000000004010c6 <+100>:   call   0x40143a <explode_bomb>
   0x00000000004010cb <+105>:   nopl   0x0(%rax,%rax,1)
   0x00000000004010d0 <+110>:   jmp    0x4010d9 <phase_5+119>
   0x00000000004010d2 <+112>:   mov    $0x0,%eax
   0x00000000004010d7 <+117>:   jmp    0x40108b <phase_5+41>
   0x00000000004010d9 <+119>:   mov    0x18(%rsp),%rax
   0x00000000004010de <+124>:   xor    %fs:0x28,%rax
   0x00000000004010e7 <+133>:   je     0x4010ee <phase_5+140>
   0x00000000004010e9 <+135>:   call   0x400b30 <__stack_chk_fail@plt>
   0x00000000004010ee <+140>:   add    $0x20,%rsp
   0x00000000004010f2 <+144>:   pop    %rbx
   0x00000000004010f3 <+145>:   ret
End of assembler dump.
```

* 由下面的代码可以知道输入的字符串长度为 6

```
   0x000000000040107a <+24>:    call   0x40131b <string_length>
   0x000000000040107f <+29>:    cmp    $0x6,%eax
   0x0000000000401082 <+32>:    je     0x4010d2 <phase_5+112>
   0x0000000000401084 <+34>:    call   0x40143a <explode_bomb>
```

* 再看

```
   0x00000000004010b3 <+81>:    mov    $0x40245e,%esi
   0x00000000004010b8 <+86>:    lea    0x10(%rsp),%rdi
   0x00000000004010bd <+91>:    call   0x401338 <strings_not_equal>
```

对比某个字符串和 `0x40245e` 所在的字符串是否相等

* 查看 `0x40245e` 所在的字符串

```
x/8xb 0x40245e
0x40245e:       0x66    0x6c    0x79    0x65    0x72    0x73    0x00    0x00
```

即：

```
flyers
```

* 通过解析汇编代码得知程序逻辑是用输入字符串的低 4 位作为索引从下面的下面找到跟上面字符匹配的 6 个字符 'flyers'

```
(gdb) x/16bx 0x4024b0
0x4024b0 <array.3449>:  0x6d    0x61    0x64    0x75    0x69    0x65    0x72    0x73
0x4024b8 <array.3449+8>:        0x6e    0x66    0x6f    0x74    0x76    0x62    0x79    0x6c
```

合法的索引为：

```
0x9 0xf 0xe 0x5 0x6 0x7
```

通过 ASCII 码表查找适合的英文字符（非唯一解），得到：

```
0x69 0x6f 0x6e 0x65 0x66 0x67
```

即：

```
ionefg
```

### phase_6

* 得到汇编代码

```
Dump of assembler code for function phase_6:
=> 0x00000000004010f4 <+0>:     push   %r14
   0x00000000004010f6 <+2>:     push   %r13
   0x00000000004010f8 <+4>:     push   %r12
   0x00000000004010fa <+6>:     push   %rbp
   0x00000000004010fb <+7>:     push   %rbx
   0x00000000004010fc <+8>:     sub    $0x50,%rsp
   0x0000000000401100 <+12>:    mov    %rsp,%r13
   0x0000000000401103 <+15>:    mov    %rsp,%rsi
   0x0000000000401106 <+18>:    call   0x40145c <read_six_numbers>
   0x000000000040110b <+23>:    mov    %rsp,%r14
   0x000000000040110e <+26>:    mov    $0x0,%r12d
   0x0000000000401114 <+32>:    mov    %r13,%rbp
   0x0000000000401117 <+35>:    mov    0x0(%r13),%eax
   0x000000000040111b <+39>:    sub    $0x1,%eax
   0x000000000040111e <+42>:    cmp    $0x5,%eax
   0x0000000000401121 <+45>:    jbe    0x401128 <phase_6+52>
   0x0000000000401123 <+47>:    call   0x40143a <explode_bomb>
   0x0000000000401128 <+52>:    add    $0x1,%r12d
   0x000000000040112c <+56>:    cmp    $0x6,%r12d
   0x0000000000401130 <+60>:    je     0x401153 <phase_6+95>
   0x0000000000401132 <+62>:    mov    %r12d,%ebx
   0x0000000000401135 <+65>:    movslq %ebx,%rax
   0x0000000000401138 <+68>:    mov    (%rsp,%rax,4),%eax
   0x000000000040113b <+71>:    cmp    %eax,0x0(%rbp)
   0x000000000040113e <+74>:    jne    0x401145 <phase_6+81>
   0x0000000000401140 <+76>:    call   0x40143a <explode_bomb>
   0x0000000000401145 <+81>:    add    $0x1,%ebx
   0x0000000000401148 <+84>:    cmp    $0x5,%ebx
   0x000000000040114b <+87>:    jle    0x401135 <phase_6+65>
   0x000000000040114d <+89>:    add    $0x4,%r13
   0x0000000000401151 <+93>:    jmp    0x401114 <phase_6+32>
   0x0000000000401153 <+95>:    lea    0x18(%rsp),%rsi
   0x0000000000401158 <+100>:   mov    %r14,%rax
   0x000000000040115b <+103>:   mov    $0x7,%ecx
   0x0000000000401160 <+108>:   mov    %ecx,%edx
   0x0000000000401162 <+110>:   sub    (%rax),%edx
   0x0000000000401164 <+112>:   mov    %edx,(%rax)
   0x0000000000401166 <+114>:   add    $0x4,%rax
   0x000000000040116a <+118>:   cmp    %rsi,%rax
   0x000000000040116d <+121>:   jne    0x401160 <phase_6+108>
   0x000000000040116f <+123>:   mov    $0x0,%esi
   0x0000000000401174 <+128>:   jmp    0x401197 <phase_6+163>
   0x0000000000401176 <+130>:   mov    0x8(%rdx),%rdx
   0x000000000040117a <+134>:   add    $0x1,%eax
   0x000000000040117d <+137>:   cmp    %ecx,%eax
   0x000000000040117f <+139>:   jne    0x401176 <phase_6+130>
   0x0000000000401181 <+141>:   jmp    0x401188 <phase_6+148>
   0x0000000000401183 <+143>:   mov    $0x6032d0,%edx
   0x0000000000401188 <+148>:   mov    %rdx,0x20(%rsp,%rsi,2)
   0x000000000040118d <+153>:   add    $0x4,%rsi
   0x0000000000401191 <+157>:   cmp    $0x18,%rsi
   0x0000000000401195 <+161>:   je     0x4011ab <phase_6+183>
   0x0000000000401197 <+163>:   mov    (%rsp,%rsi,1),%ecx
   0x000000000040119a <+166>:   cmp    $0x1,%ecx
   0x000000000040119d <+169>:   jle    0x401183 <phase_6+143>
   0x000000000040119f <+171>:   mov    $0x1,%eax
   0x00000000004011a4 <+176>:   mov    $0x6032d0,%edx
   0x00000000004011a9 <+181>:   jmp    0x401176 <phase_6+130>
   0x00000000004011ab <+183>:   mov    0x20(%rsp),%rbx
   0x00000000004011b0 <+188>:   lea    0x28(%rsp),%rax
   0x00000000004011b5 <+193>:   lea    0x50(%rsp),%rsi
   0x00000000004011ba <+198>:   mov    %rbx,%rcx
   0x00000000004011bd <+201>:   mov    (%rax),%rdx
   0x00000000004011c0 <+204>:   mov    %rdx,0x8(%rcx)
   0x00000000004011c4 <+208>:   add    $0x8,%rax
   0x00000000004011c8 <+212>:   cmp    %rsi,%rax
   0x00000000004011cb <+215>:   je     0x4011d2 <phase_6+222>
   0x00000000004011cd <+217>:   mov    %rdx,%rcx
   0x00000000004011d0 <+220>:   jmp    0x4011bd <phase_6+201>
   0x00000000004011d2 <+222>:   movq   $0x0,0x8(%rdx)
   0x00000000004011da <+230>:   mov    $0x5,%ebp
   0x00000000004011df <+235>:   mov    0x8(%rbx),%rax
   0x00000000004011e3 <+239>:   mov    (%rax),%eax
   0x00000000004011e5 <+241>:   cmp    %eax,(%rbx)
   0x00000000004011e7 <+243>:   jge    0x4011ee <phase_6+250>
   0x00000000004011e9 <+245>:   call   0x40143a <explode_bomb>
   0x00000000004011ee <+250>:   mov    0x8(%rbx),%rbx
   0x00000000004011f2 <+254>:   sub    $0x1,%ebp
   0x00000000004011f5 <+257>:   jne    0x4011df <phase_6+235>
   0x00000000004011f7 <+259>:   add    $0x50,%rsp
   0x00000000004011fb <+263>:   pop    %rbx
   0x00000000004011fc <+264>:   pop    %rbp
   0x00000000004011fd <+265>:   pop    %r12
   0x00000000004011ff <+267>:   pop    %r13
   0x0000000000401201 <+269>:   pop    %r14
   0x0000000000401203 <+271>:   ret
End of assembler dump.
```

* 这一步比较复杂（比前面5步加起来都难），为了减少逻辑思维负担，先转成 C 代码（通过注释标注了对应的汇编代码位置）

引用到的全局变量：

```
(gdb) x /96xb 0x6032d0
0x6032d0 <node1>:       0x4c    0x01    0x00    0x00    0x01    0x00    0x00    0x00
0x6032d8 <node1+8>:     0xe0    0x32    0x60    0x00    0x00    0x00    0x00    0x00
0x6032e0 <node2>:       0xa8    0x00    0x00    0x00    0x02    0x00    0x00    0x00
0x6032e8 <node2+8>:     0xf0    0x32    0x60    0x00    0x00    0x00    0x00    0x00
0x6032f0 <node3>:       0x9c    0x03    0x00    0x00    0x03    0x00    0x00    0x00
0x6032f8 <node3+8>:     0x00    0x33    0x60    0x00    0x00    0x00    0x00    0x00
0x603300 <node4>:       0xb3    0x02    0x00    0x00    0x04    0x00    0x00    0x00
0x603308 <node4+8>:     0x10    0x33    0x60    0x00    0x00    0x00    0x00    0x00
0x603310 <node5>:       0xdd    0x01    0x00    0x00    0x05    0x00    0x00    0x00
0x603318 <node5+8>:     0x20    0x33    0x60    0x00    0x00    0x00    0x00    0x00
0x603320 <node6>:       0xbb    0x01    0x00    0x00    0x06    0x00    0x00    0x00
0x603328 <node6+8>:     0x00    0x00    0x00    0x00    0x00    0x00    0x00    0x00
```

C 代码

```c
struct Node {
	int val;
	int idx;
	struct Node *next;
};

static struct Node g_nodes[6];

// call before phase_6
void g_nodes_init()
{
	struct Node *node = g_nodes;
	node->val = 0x14c;
	node->idx = 0x1;
	node->next = &(g_nodes[1]);
	
	node = node->next;
	node->val = 0xa8;
	node->idx = 0x2;
	node->next = &(g_nodes[2]);
	
	node = node->next;
	node->val = 0x39c;
	node->idx = 0x3;
	node->next = &(g_nodes[3]);
	
	node = node->next;
	node->val = 0x2b3;
	node->idx = 0x4;
	node->next = &(g_nodes[4]);
	
	node = node->next;
	node->val = 0x1dd;
	node->idx = 0x5;
	node->next = &(g_nodes[5]);
	
	node = node->next;
	node->val = 0x1bb;
	node->idx = 0x6;
	node->next = NULL;
}

void phase_6(char *s)
{
	int num[6];
	struct Node* nodes[6];
	read_six_numbers(s, num);
	// 输入数组需要满足个数为 6，每个数字的大小小于7，从第二个数字开始，每个数字都不等于第一个数字
	for (int i = 0; i != 6; ++i) {
		if (num[i] - 1 > 5) {
			explode_bomb();
			return;
		}

		for (int j = i + 1; j <= 5; ++j) { // +52~+87
			if (num[j] == num[0]) {
				explode_bomb();
				return;
			}
		}
	}
	
	// +95~+121 将输入数组修改为 7-n
	for (int *begin = num; begin != num + 6; begin++) {
		int n = *begin;
		*begin = 7 - n;
	}
	
	// +123~+181
	// g_nodes 初始化为 g_nodes[i].next = g_nodes[i+1]
	// 这段的逻辑为根据修改后的 num 数组设置 nodes 数组
	// nodes[i] = g_nodes[num[i]-1]
	for (int i = 0; i != 6; i++) {
		int n =  num[i];
		if (n <= 1) {
			nodes[i] = &(g_nodes[0]);
		} else {
			int j = 1;
			struct Node *node = g_nodes[0].next;
			while (++j != n) {
				node = node->next;
			}
			
			nodes[i] = node->val;
		}
	}
	
	// +183~+220 设置 next 指针，按照 nodes 顺序组成链表
	struct Node** begin = nodes + 1;
	struct Node* tmp = nodes[0];
	while (true) {
		struct Node* t2 = *begin;
		tmp->next = t2;
		begin++;
		if (begin == nodes + 6) {
			break;
		}
		
		tmp = t2;
	}
	
	// +222
	tmp->next = NULL;
	
	// +230~+257 链表的特性为按照 val 从大到小排列
	int count = 5;
	tmp = nodes[0];
	do {
		if (tmp->val >= tmp->next->val) {
			tmp = tmp->next;
		} else {
			explode_bomb();
			return;
		}
	} while (--count);
}
```

* 这里从后面往前推导

`nodes[0]` 组成的链表特性为 val 按递减排列，也就是说 

```c
nodes[0] = g_nodes + 2;
nodes[1] = g_nodes + 3;
nodes[2] = g_nodes + 4;
nodes[3] = g_nodes + 5;
nodes[4] = g_nodes + 0;
nodes[5] = g_nodes + 1;
```

* 由 `// +123~+181` 的逻辑 `nodes[i] = g_nodes[num[i]-1]`

可以推断修改后的 num 数组

```c
num[0] = 3
num[1] = 4
num[2] = 5
num[3] = 6
num[4] = 1
num[5] = 2
```

可知修改前的原始数组为：

```
4 3 2 1 6 5
```

### 完整的答案：

[bomb_solver.txt](bomb_solver.txt)