## archlab

本实验材料通过官方网站下载：https://csapp.cs.cmu.edu/2e/labs.html

可以通过 `simguide.pdf` 

具体的实验要求和测试方法可以查看 `archlab.pdf` 以下是我的解题过程

### Part A

主要在 `sim/misc` 下完成这部分的要求

#### sum.ys

写一个 ys 程序，通过循环求出链表的和

通过如下数据测试你写的方法：

```
# Sample linked list
    .align 4
ele1:
    .long 0x00a
    .long ele2
ele2:
    .long 0x0b0
    .long ele3
ele3:
    .long 0xc00
    .long 0
```

实验提供了这部分要实现的 y86 汇编的 C 语言版本，如下：

```c
/* 
 * Architecture Lab: Part A 
 * 
 * High level specs for the functions that the students will rewrite
 * in Y86 assembly language
 */

/* $begin examples */
/* linked list element */
typedef struct ELE {
    int val;
    struct ELE *next;
} *list_ptr;

/* sum_list - Sum the elements of a linked list */
int sum_list(list_ptr ls)
{
    int val = 0;
    while (ls) {
	val += ls->val;
	ls = ls->next;
    }
    return val;
}

/* rsum_list - Recursive version of sum_list */
int rsum_list(list_ptr ls)
{
    if (!ls)
	return 0;
    else {
	int val = ls->val;
	int rest = rsum_list(ls->next);
	return val + rest;
    }
}

/* copy_block - Copy src to dest and return xor checksum of src */
int copy_block(int *src, int *dest, int len)
{
    int result = 0;
    while (len > 0) {
	int val = *src++;
	*dest++ = val;
	result ^= val;
	len--;
    }
    return result;
}
/* $end examples */
```


这个比较简单，我的实现放在了 [ans-sum.ys](sim/misc/ans-sum.ys)

#### rsum.ys

通过递归求出链表的和

[ans-rsum.ys](sim/misc/ans-rsum.ys)

#### copy.ys

实现 `copy_block`，我的实现：[ans-copy.ys](sim/misc/ans-copy.ys)

### Part B

这部分要求实现 `iaddl` 和 `leave` 指令，在练习题已经分别实现了，简单整合下就好：[seq-full-ans.hcl](sim/seq/seq-full-ans.hcl)

### Part C

这部分要求基于 `sim/pipe/ncopy.ys` 和 `sim/pipe/pipe-full.hcl` 尽量优化程序性能，通过运行 `sim/pipe/benchmark.pl` 可以知道优化后的评分，可以使用 `sim/pipe/correctness.pl` 来检查你的修改是否正确。

先在不做任何修改的情况下看看基准评分：

```sh
$ ./benchmark.pl
....
Average CPE     16.44
Score   0.0/60.0
```

看下 `ncopy.ys` 的实现，这里只给出可以修改的部分

```y86
##################################################################
# You can modify this portion
	# Loop header
	xorl %eax,%eax		# count = 0;
	andl %edx,%edx		# len <= 0?
	jle Done		# if so, goto Done:

Loop:	mrmovl (%ebx), %esi	# read val from src...
	rmmovl %esi, (%ecx)	# ...and store it to dst
	andl %esi, %esi		# val <= 0?
	jle Npos		# if so, goto Npos:
	irmovl $1, %edi
	addl %edi, %eax		# count++
Npos:	irmovl $1, %edi
	subl %edi, %edx		# len--
	irmovl $4, %edi
	addl %edi, %ebx		# src++
	addl %edi, %ecx		# dst++
	andl %edx,%edx		# len > 0?
	jg Loop			# if so, goto Loop:
##################################################################
```

首先可以想到的是通过支持 `iaddl` 指令优化性能

pipe-full.hcl 修改为支持 `iaddl`，由于在练习题已经实现过了，这里不再赘述，[pipe-full-ans.hcl](sim/pipe/pipe-full-ans.hcl)

`ncopy.ys` 修改为：

```y86
##################################################################
# You can modify this portion
	# Loop header
	xorl %eax,%eax		# count = 0;
	andl %edx,%edx		# len <= 0?
	jle Done		# if so, goto Done:

Loop:	mrmovl (%ebx), %esi	# read val from src...
	rmmovl %esi, (%ecx)	# ...and store it to dst
	andl %esi, %esi		# val <= 0?
	jle Npos		# if so, goto Npos:
	iaddl $1, %eax		# count++
Npos:
	iaddl $-1, %edx		# len--
	iaddl $4, %ebx		# src++
	iaddl $4, %ecx		# dst++
	andl %edx,%edx		# len > 0?
	jg Loop			# if so, goto Loop:
##################################################################
```

完成文件在这里 [ncopy-iaddl.ys](sim/pipe/ncopy-iaddl.ys)

再运行下性能测试评分

```sh
$ ./benchmark.pl
....
Average CPE     13.96
Score   0.0/60.0
```

虽然还是 0 分，性能有了一定提升。

接着可以在长度大于 8 时，进行 8 次循环展开，减少循环和判断的次数：

```y86
##################################################################
# You can modify this portion
	# Loop header
	xorl %eax,%eax		# count = 0;
Large:
	iaddl $-8, %edx
	jge Loop0
	iaddl $8, %edx
	jmp Small0

Loop0:
	mrmovl (%ebx), %esi	# read val from src...
	rmmovl %esi, (%ecx)	# ...and store it to dst
	andl %esi, %esi		# val <= 0?
	jle Loop1
	iaddl $1, %eax		# count++
Loop1:
	mrmovl 4(%ebx), %esi	# read val from src...
	rmmovl %esi, 4(%ecx)	# ...and store it to dst
	andl %esi, %esi		# val <= 0?
	jle Loop2
	iaddl $1, %eax		# count++
Loop2:
	mrmovl 8(%ebx), %esi	# read val from src...
	rmmovl %esi, 8(%ecx)	# ...and store it to dst
	andl %esi, %esi		# val <= 0?
	jle Loop3
	iaddl $1, %eax		# count++
Loop3:
	mrmovl 12(%ebx), %esi	# read val from src...
	rmmovl %esi, 12(%ecx)	# ...and store it to dst
	andl %esi, %esi		# val <= 0?
	jle Loop4
	iaddl $1, %eax		# count++
Loop4:
	mrmovl 16(%ebx), %esi	# read val from src...
	rmmovl %esi, 16(%ecx)	# ...and store it to dst
	andl %esi, %esi		# val <= 0?
	jle Loop5
	iaddl $1, %eax		# count++
Loop5:
	mrmovl 20(%ebx), %esi	# read val from src...
	rmmovl %esi, 20(%ecx)	# ...and store it to dst
	andl %esi, %esi		# val <= 0?
	jle Loop6
	iaddl $1, %eax		# count++
Loop6:
	mrmovl 24(%ebx), %esi	# read val from src...
	rmmovl %esi, 24(%ecx)	# ...and store it to dst
	andl %esi, %esi		# val <= 0?
	jle Loop7
	iaddl $1, %eax		# count++
Loop7:
	mrmovl 28(%ebx), %esi	# read val from src...
	rmmovl %esi, 28(%ecx)	# ...and store it to dst
	iaddl $32, %ebx		# src+=8
	iaddl $32, %ecx		# dst+=8
	andl %esi, %esi		# val <= 0?
	jle Large
	iaddl $1, %eax		# count++
	jmp Large

Small0:
	andl %edx,%edx		# len <= 0?
	jle Done		# if so, goto Done:

Small1:	mrmovl (%ebx), %esi	# read val from src...
	rmmovl %esi, (%ecx)	# ...and store it to dst
	andl %esi, %esi		# val <= 0?
	jle Npos		# if so, goto Npos:
	iaddl $1, %eax		# count++
Npos:
	iaddl $-1, %edx		# len--
	iaddl $4, %ebx		# src++
	iaddl $4, %ecx		# dst++
	andl %edx,%edx		# len > 0?
	jg Small1
##################################################################
```

完整代码在： [ncopy-8way.ys](sim/pipe/ncopy-8way.ys)

性能测试结果为：

```sh
$ ./benchmark.pl
....
Average CPE     10.91
Score   38.2/60.0
```

下一个可以优化的点是长度大于 8 时，指令：

```y86
mrmovl (%ebx), %esi	# read val from src...
rmmovl %esi, (%ecx)	# ...and store it to dst
```

会产生 `load/use` 冒险，通过调整指令顺序可以消除这种冒险：

```y86
##################################################################
# You can modify this portion
	# Loop header
	xorl %eax,%eax		# count = 0;
Large:
	iaddl $-8, %edx
	jge Loop0
	iaddl $8, %edx
	jmp Small0

Loop0:
	mrmovl (%ebx), %esi	# read val from src...
	mrmovl 4(%ebx), %edi	# read val from src...
	rmmovl %esi, (%ecx)	# ...and store it to dst
	rmmovl %edi, 4(%ecx)	# ...and store it to dst
	andl %esi, %esi		# val <= 0?
	jle Loop1
	iaddl $1, %eax		# count++
Loop1:
	andl %edi, %edi		# val <= 0?
	jle Loop2
	iaddl $1, %eax		# count++
Loop2:
	mrmovl 8(%ebx), %esi	# read val from src...
	mrmovl 12(%ebx), %edi	# read val from src...
	rmmovl %esi, 8(%ecx)	# ...and store it to dst
	rmmovl %edi, 12(%ecx)	# ...and store it to dst
	andl %esi, %esi		# val <= 0?
	jle Loop3
	iaddl $1, %eax		# count++
Loop3:
	andl %edi, %edi		# val <= 0?
	jle Loop4
	iaddl $1, %eax		# count++
Loop4:
	mrmovl 16(%ebx), %esi	# read val from src...
	mrmovl 20(%ebx), %edi	# read val from src...
	rmmovl %esi, 16(%ecx)	# ...and store it to dst
	rmmovl %edi, 20(%ecx)	# ...and store it to dst
	andl %esi, %esi		# val <= 0?
	jle Loop5
	iaddl $1, %eax		# count++
Loop5:
	andl %edi, %edi		# val <= 0?
	jle Loop6
	iaddl $1, %eax		# count++
Loop6:
	mrmovl 24(%ebx), %esi	# read val from src...
	mrmovl 28(%ebx), %edi	# read val from src...
	rmmovl %esi, 24(%ecx)	# ...and store it to dst
	rmmovl %edi, 28(%ecx)	# ...and store it to dst
	andl %esi, %esi		# val <= 0?
	jle Loop7
	iaddl $1, %eax		# count++
Loop7:
	iaddl $32, %ebx		# src+=8
	iaddl $32, %ecx		# dst+=8
	andl %edi, %edi		# val <= 0?
	jle Large
	iaddl $1, %eax		# count++
	jmp Large

Small0:
	andl %edx,%edx		# len <= 0?
	jle Done		# if so, goto Done:

Small1:	mrmovl (%ebx), %esi	# read val from src...
	rmmovl %esi, (%ecx)	# ...and store it to dst
	andl %esi, %esi		# val <= 0?
	jle Npos		# if so, goto Npos:
	iaddl $1, %eax		# count++
Npos:
	iaddl $-1, %edx		# len--
	iaddl $4, %ebx		# src++
	iaddl $4, %ecx		# dst++
	andl %edx,%edx		# len > 0?
	jg Small1
##################################################################
```

完整代码在 [ncopy-8way-no-load-use-hazard.ys](sim/pipe/ncopy-8way-no-load-use-hazard.ys)

性能测试结果：

```sh
$ ./benchmark.pl
....
Average CPE     10.12
Score   57.2/60.0
```

最后，当 len 小于 8 是也可以消除 `load/use 冒险`

```y86
##################################################################
# You can modify this portion
	# Loop header
	xorl %eax,%eax		# count = 0;
Large:
	iaddl $-8, %edx
	jge Loop0
	iaddl $8, %edx
	jmp Small0

Loop0:
	mrmovl (%ebx), %esi	# read val from src...
	mrmovl 4(%ebx), %edi	# read val from src...
	rmmovl %esi, (%ecx)	# ...and store it to dst
	rmmovl %edi, 4(%ecx)	# ...and store it to dst
	andl %esi, %esi		# val <= 0?
	jle Loop1
	iaddl $1, %eax		# count++
Loop1:
	andl %edi, %edi		# val <= 0?
	jle Loop2
	iaddl $1, %eax		# count++
Loop2:
	mrmovl 8(%ebx), %esi	# read val from src...
	mrmovl 12(%ebx), %edi	# read val from src...
	rmmovl %esi, 8(%ecx)	# ...and store it to dst
	rmmovl %edi, 12(%ecx)	# ...and store it to dst
	andl %esi, %esi		# val <= 0?
	jle Loop3
	iaddl $1, %eax		# count++
Loop3:
	andl %edi, %edi		# val <= 0?
	jle Loop4
	iaddl $1, %eax		# count++
Loop4:
	mrmovl 16(%ebx), %esi	# read val from src...
	mrmovl 20(%ebx), %edi	# read val from src...
	rmmovl %esi, 16(%ecx)	# ...and store it to dst
	rmmovl %edi, 20(%ecx)	# ...and store it to dst
	andl %esi, %esi		# val <= 0?
	jle Loop5
	iaddl $1, %eax		# count++
Loop5:
	andl %edi, %edi		# val <= 0?
	jle Loop6
	iaddl $1, %eax		# count++
Loop6:
	mrmovl 24(%ebx), %esi	# read val from src...
	mrmovl 28(%ebx), %edi	# read val from src...
	rmmovl %esi, 24(%ecx)	# ...and store it to dst
	rmmovl %edi, 28(%ecx)	# ...and store it to dst
	andl %esi, %esi		# val <= 0?
	jle Loop7
	iaddl $1, %eax		# count++
Loop7:
	iaddl $32, %ebx		# src+=8
	iaddl $32, %ecx		# dst+=8
	andl %edi, %edi		# val <= 0?
	jle Large
	iaddl $1, %eax		# count++
	jmp Large

Small0:
    iaddl $-2, %edx
	jge Small1
    iaddl $2, %edx
	jle Done		# if so, goto Done:
	mrmovl (%ebx), %esi	# read val from src...
	rmmovl %esi, (%ecx)	# ...and store it to dst
	andl %esi, %esi		# val <= 0?
	jle Done
	iaddl $1, %eax		# count++
	jmp Done

Small1:	mrmovl (%ebx), %esi	# read val from src...
	mrmovl 4(%ebx), %edi	# read val from src...
	rmmovl %esi, (%ecx)	# ...and store it to dst
	rmmovl %edi, 4(%ecx)	# ...and store it to dst
	andl %esi, %esi		# val <= 0?
	jle Small2
	iaddl $1, %eax		# count++
Small2:
	andl %edi, %edi		# val <= 0?
	jle Npos
	iaddl $1, %eax		# count++
Npos:
	iaddl $8, %ebx		# src++
	iaddl $8, %ecx		# dst++
	andl %edx,%edx		# len > 0?
	jg Small0
##################################################################
```

最终版本的完整代码在 [ncopy-ans.ys](sim/pipe/ncopy-ans.ys)

性能测试结果：

```sh
$ ./benchmark.pl
....
Average CPE     9.40
Score   60.0/60.0
```