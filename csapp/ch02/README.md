# 第2章 信息的表示和处理

## 练习题

### 练习题 2.1

完成下列数字转换：

* A: 将 0x39A7F8 转换为二进制
* B：将 1100100101111011 转换为十六进制
* C: 将 0xD5E4C 转换为二进制
* D: 将二进制 1001101110011110110101 转换为十六进制

答案：

* A: 0011 1001 1010 0111 1111 1000
* B: 0xC97B
* C: 1101 0101 1110 0100 1100
* D: 0x26E7B5

### 练习题 2.2

填写下表中的空白，给出 2 的不同次幂的二进制和十六进制表示：

|n|2<sup>n</sup>（十进制）|2<sup>n</sup>（十六进制）|
|-|-|-|
|9|512|0x200|
|19||
||16384||
||0x10000|
|17|||
||32||
|||0x80|

答案：

|n|2<sup>n</sup>（十进制）|2<sup>n</sup>（十六进制）|
|-|-|-|
|9|512|0x200|
|19|524288|0x80000|
|14|16384|0x4000|
|16|65536|0x10000|
|17|131072|0x20000|
|5|32|0x20|
|7|128|0x80|

### 练习题 2.3

一个字节可以用两个十六进制数字来表示。填写下表中缺失的项，给出不同字节模式的十进制、二进制和十六进制值。

|十进制|二进制|十六进制|
|-|-|-|
|0|0000 0000|0x00|
|167|||
|62|||
|188|||
||0011 0111||
||1000 1000||
||1111 0011||
|||0x52|
|||0xAC|
|||0xE7|

答案：

|十进制|二进制|十六进制|
|-|-|-|
|0|0000 0000|0x00|
|167|1010 0111|0xA7|
|62|0011 1110|0x3E|
|188|1011 1100|0xBC|
|55|0011 0111|0x37|
|136|1000 1000|0x88|
|243|1111 0011|0xF3|
|82|0101 0010|0x52|
|172|1010 1100|0xAC|
|231|1110 0111|0xE7|

### 练习题 2.4

不将数字转换为十进制或者二进制，试着解答下面的算术题，答案要用十六进制表示。

提示：将执行十进制加法和减法所使用的方法改成以 16 为基数。

* A. 0x503c+0x8=
* B. 0x503c-0x40=
* C. 0x503c+64=
* D. 0x50ea-0x503c=

答案：

* A. 0x503c+0x8=0x5044
* B. 0x503c-0x40=0x4ffc
* C. 0x503c+64=0x507c
* D. 0x50ea-0x503c=0xae

### 练习题 2.5

思考下面对 show_bytes 的三次调用：

```c
int val = 0x87654321;
byte_pointer valp = (byte_pointer) &val;
show_bytes(valp, 1); /* A. */
show_bytes(valp, 2); /* B. */
show_bytes(valp, 3); /* C. */
```

指出在小端法机器和大端法机器上，每次调用的输出值。

```
A. 小端法：    大端法：
B. 小端法：    大端法：
C. 小端法：    大端法：
```

答案：

```
A. 小端法：21             大端法：87
B. 小端法：21 43          大端法：87 65
C. 小端法：21 43 65       大端法：87 65 43
```

### 练习题 2.6

使用 show_int 和 show_float，我们确定整数 3510593 的十六进制表示为 0x00359141，而浮点数 3510593.0 的十六进制表示为 0x4A564504。

```
A. 写出这两个十六进制值的二进制表示。
B. 移动这两个二进制串的相对位置，是的它们相匹配的位数最多。有多少位相匹配呢？
C. 串中的什么部分不相匹配？
```

答案：

```
A. 写出这两个十六进制值的二进制表示。

0x00359141 的二进制表示 0000 0000 0011 0101 1001 0001 0100 0001
0x4A564504 的二进制表示 0100 1010 0101 0110 0100 0101 0000 0100

B. 移动这两个二进制串的相对位置，使得它们相匹配的位数最多。有多少位相匹配呢？

0x00359141 的二进制表示 00000000001101011001000101000001
0x4A564504 的二进制表示   01001010010101100100010100000100

浮点数右移两位，有 21 位匹配

C. 串中的什么部分不相匹配？

整数除了最高有效位 1 其他部分与浮点数匹配，另外浮点数有部分非 0 的高位不与整数匹配
```

### 练习题 2.7

下面对 show_bytes 的调用将输出什么结果？

```c
const char *s = "abcdef";
show_bytes((byte_pointer) s, strlen(s));
```

注意字母 'a' ~ 'z' 的 ASCII 码为 0x61 ~ 0x7A。

答案：

```
61 62 63 64 65 66
```

 ### 练习题 2.8
 
 填写下表，给出位向量的布尔运算求值结果。

 |运算|结果|
 |-|-|
 |a|[01101001]|
 |b|[01010101]|
 |~a||
 |~b||
 |a&b||
 |a\|b||
 |a^b||

答案：

 |运算|结果|
 |-|-|
 |a|[01101001]|
 |b|[01010101]|
 |~a|[10010110]|
 |~b|[10101010]|
 |a&b|[01000001]|
 |a\|b|[01111101]|
 |a^b|[00111100]|

### 练习题 2.9

通过混合三种不同颜色的光（红色、绿色和蓝色），计算机可以在视频屏幕或者液晶显示器上产生彩色的画面。
设想一种简单的方法，使用三种不同颜色的光，每种光都能打开或关闭，投射到玻璃屏幕上

那么基于光源 R(红)、G(绿)、B(蓝) 的关闭(0)或打开(1)，我们能够创建8种不同的颜色：

|R|G|B|颜色|
|-|-|-|-|
|0|0|0|黑色|
|0|0|1|蓝色|
|0|1|0|绿色|
|0|1|1|蓝绿色|
|1|0|0|红色|
|1|0|1|红紫色|
|1|1|0|黄色|
|1|1|1|白色|

这些颜色中的每一种都能用一个长度为 3 的位向量来表示，我们可以对它们进行布尔运算。

A. 一种颜色的补是通过关掉打开的光源，且打开关闭的光源而形成的。那么上面列出的 8 种颜色每一种的补是什么？

B. 描述下列颜色应用布尔运算的结果：

```
蓝色 | 绿色 =
黄色 & 蓝绿色 =
红色 ^ 红紫色 =
```

答案：

A. 

|颜色|对应的补|
|-|-|
|黑色|白色|
|蓝色|黄色|
|绿色|红紫色|
|蓝绿色|红色|
|红色|蓝绿色|
|红紫色|绿色|
|黄色|蓝色|
|白色|黑色|

B.

```
蓝色 | 绿色 = 蓝绿色
黄色 & 蓝绿色 = 绿色
红色 ^ 红紫色 = 蓝色
```

### 练习题 2.10

对于任一位向量 a，有 a^a=0。
应用这一属性，考虑下面的程序：

```c
void inplace_swap(int *x, int *y) {
    *y = *x ^ *y; /* Step 1 */
    *x = *x ^ *y; /* Step 2 */
    *y = *x ^ *y; /* Step 3 */
}
```

正如程序名字所暗示的那样，我们认为这个过程的效果是交换指针变量 x 和 y 所指向的存储位置处存放的值。
注意，与通常的交换两个数值的技术不一样，当移动一个值时，我们不需要第三个位置来临时存储另一个值。
这种交换方式并没有性能上的优势，它仅仅是一个智力游戏。
以指针 x 和 y 指向的位置存储的值分别是 a 和 b 作为开始，填写下表，给出在程序的每一步之后，存储在这两个位置中的值。
利用 ^ 的属性证明达到了所希望的效果。
回想一下，每个元素就是它自身的加法逆元（a^a = 0）。

|步骤|\*x|\*y|
|-|-|-|
|初始|a|b|
|第一步|||
|第二步|||
|第三步|||

答案：

|步骤|\*x|\*y|
|-|-|-|
|初始|a|b|
|第一步|a|a^b|
|第二步|b|a^b|
|第三步|b|a|

这个方法在某些情况下会失败，详见 练习题 2.11

### 练习题 2.11

在练习题 2.10 中的 inplace_swap 函数的基础上，你决定写一段代码，实现将一个数组中的元素头尾两端依次对调。你写出下面这个函数：

```c
void reverse_array(int a[], int cnt) {
    int first, last;
    for (first = 0, last = cnt - 1;
         first <= last;
         first++, last--)
        inplace_swap(&a[first], &a[last]);
}
```

当你对一个包含元素 1、2、3 和 4 的数组使用这个函数时，正如预期的那样，现在数组的元素变成了 4、3、2 和 1。
不过，当你对一个包含元素 1、2、3、4 和 5 的数组使用这个函数时，你会很惊奇地看到得到数组的元素为 5、4、0、2 和 1。
实际上，你会发现这段代码对所有偶数长度的数组都能正确地工作，但是当数组的长度为奇数时，它就会把中间的元素设置为 0.

A. 对于一个长度为奇数的数组，长度 cnt=2k+1，函数 reverse_array 最后一次循环中，变量 first 和 last 的值分别是什么？

B. 为什么这时调用 inplace_swap 会将数组元素设置为 0？

C. 对于 reverse_array 的代码做哪些简单改动就能消除这个问题？

答案：

A. first 和 last 都是 k

B. 由于这时 first 和 last 相同，传给 inplace_swap 的两个参数相同，因此会将元素设置为 0

C. 将 for 循环的 first &lt;= last 改成 first &lt; last 即可

### 练习题 2.12

对于下面的值，写出变量 x 的 C 语言表达式。你的代码应该对任何字长 w >= 8 都能工作。

我们给出了当 x = 0x87654321 以及 w = 32 时表达式求值的结果，仅供参考。

A. x 的最低有效字节，其他位均置为 0。[0x00000021]。

B. 除了 x 的最低有效字节外，其他的位都取补，最低有效字节保持不变。[0x789ABC21]

C. x 的最低有效字节设置成全 1，其他字节都保持不变。[0x876543FF]。

答案：

A. x = x & 0xFF;

B. x = x ^ ~0xFF;

C. x = x | 0xFF;

### 练习题 2.13

从 20 世纪 70 年代末到 80 年代末，Digital Equipment 的 VAX 计算机是一种非常流行的机型。

它没有布尔运算 AND 和 OR 指令，只有 bis（位设置）和 bic（位清楚）这两种指令。
两种指令的输入都是一个数据字 x 和一个掩码字 m。
它们生成一个结果 z，z 是由根据掩码 m 的位来修改 x 的位得到的。
使用 bis 指令，这种修改就是在 m 为 1 的每个位置上，将 z 对应的位设置为 1。
使用 bic 指令，这种修改就是在 m 为 1 的每个位置，将 z 对应的位设置为 0。

为了清楚因为这些运算与 C 语言位级运算的关系，假设我们有两个函数 bis 和 bic 来实现位设置和清楚操作。
只想用这两个函数，而不适用任何其他 C 语言运算，来实现按位 | 和 ^ 运算。
填写下列代码中缺失的代码。
提示：写出 bis 和 bic 运算的 C 语言表达式。

```c
/* Declarations of functions implementing operations bis and bic */
int bis(int x, int m);
int bic(int x, int m);

/* Compute x|y using only calls to functions bis and bic */
int bool_or(int x, int y) {
    int result = ___________;
    return result;
}

/* Compute x^y using only calls to functions bis and bic */
int bool_xor(int x, int y) {
    int result = ____________;
    return result;
}
```

答案：

```c
/* Declarations of functions implementing operations bis and bic */
int bis(int x, int m);
int bic(int x, int m);

/* Compute x|y using only calls to functions bis and bic */
int bool_or(int x, int y) {
    int result = bis(x, y);
    return result;
}

/* Compute x^y using only calls to functions bis and bic */
int bool_xor(int x, int y) {
    int result = bis(bic(x,y), bic(y,x));
    return result;
}

int bis(int x, int m) {
    return x | m;
}

int bic(int x, int m) {
    return x & ~m;
}
```

也可以参考 [ex2.13.c](ex2.13.c)

### 练习题 2.14

假设 x 和 y 的字节值分别为 0x66 和 0x39。
填写下表，指明各个 C 表达式的字节值。

|表达式|值|
|-|-|
|x & y||
|x \| y||
|~x \| ~y||
|x & !y||
|x && y||
|x \|\| y||
|!x \|\| !y||
|x && ~y||

答案：

|表达式|值|
|-|-|
|x & y|0x20|
|x \| y|0x7F|
|~x \| ~y|0xDF|
|x & !y|0x00|
|x && y|0x01|
|x \|\| y|0x01|
|!x \|\| !y|0x00|
|x && ~y|0x01|

程序参考 [ex2.14.c](ex2.14.c)

### 练习题 2.15

只使用位级和逻辑运算，编写一个表达式，它等价于 x==y。
换句话说，当 x 和 y 相等时它将返回 1，否则返回 0。

答案：!(x^y)

程序参考：[ex2.15.c](ex2.15.c)

### 练习题 2.16

填写下表，说明不通移位运算对单字节数的影响。

思考移位运算的最好方式是使用二进制表示。
将最初的值转换为二进制执行移位运算，然后再转换回十六进制。
每个答案都应该是 8 个二进制数字或者 2 个十六进制数字。

<table>
    <tr><th colspan=2>x</th><th colspan=2>x&lt;&lt;3</th><th colspan=2>x&gt;&gt;2（逻辑的）</th><th colspan=2>x&gt;&gt;2（算术的）</th></tr>
    <tr><th>十六进制</th><th>二进制</th><th>二进制</th><th>十六进制</th><th>二进制</th><th>十六进制</th><th>二进制</th><th>十六进制</th></tr>
    <tr><td>0xC3</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr>
    <tr><td>0x75</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr>
    <tr><td>0x87</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr>
    <tr><td>0x66</td><td></td><td></td><td></td><td></td><td></td><td></td><td></td></tr>
</table>

答案：

<table>
    <tr><th colspan=2>x</th><th colspan=2>x&lt;&lt;3</th><th colspan=2>x&gt;&gt;2（逻辑的）</th><th colspan=2>x&gt;&gt;2（算术的）</th></tr>
    <tr><th>十六进制</th><th>二进制</th><th>二进制</th><th>十六进制</th><th>二进制</th><th>十六进制</th><th>二进制</th><th>十六进制</th></tr>
    <tr><td>0xC3</td><td>1100 0011</td><td>0001 1000</td><td>0x18</td><td>0011 0000</td><td>0x30</td><td>1111 0000</td><td>0xF0</td></tr>
    <tr><td>0x75</td><td>0111 0101</td><td>1010 1000</td><td>0xA8</td><td>0001 1101</td><td>0x1D</td><td>0001 1101</td><td>0x1D</td></tr>
    <tr><td>0x87</td><td>1000 0111</td><td>0011 1000</td><td>0x38</td><td>0010 0001</td><td>0x21</td><td>1110 0001</td><td>0xE1</td></tr>
    <tr><td>0x66</td><td>0110 0110</td><td>0011 0000</td><td>0x30</td><td>0001 1001</td><td>0x11</td><td>0001 1001</td><td>0x19</td></tr>
</table>

### 练习题 2.17

假设 w = 4，我们能给每个可能的十六进制数字赋予一个数值，假设用一个无符号或者补码表示。

请根据这些表示，写出等式（2-1）和等式（2-3）所示的求和公式中的 2 的非零次幂，填写下表：

<table>
    <tr><th colspan=2>x</th><th rowspan=2>B2U<sub>4</sub>(X)</th><th rowspan=2>B2T<sub>4</sub>(X)</th></tr>
    <tr><th>十六进制</th><th>二进制</th></tr>
    <tr><td>0xE</td><td>[1110]</td><td>2<sup>3</sup>+2<sup>2</sup>+2<sup>1</sup>=14</td><td>-2<sup>3</sup>+2<sup>2</sup>+2<sup>1</sup>=-2</td></tr>
    <tr><td>0x0</td><td></td><td></td><td></td></tr>
    <tr><td>0x5</td><td></td><td></td><td></td></tr>
    <tr><td>0x8</td><td></td><td></td><td></td></tr>
    <tr><td>0xD</td><td></td><td></td><td></td></tr>
    <tr><td>0xF</td><td></td><td></td><td></td></tr>
</table>

答案：

<table>
    <tr><th colspan=2>x</th><th rowspan=2>B2U<sub>4</sub>(X)</th><th rowspan=2>B2T<sub>4</sub>(X)</th></tr>
    <tr><th>十六进制</th><th>二进制</th></tr>
    <tr><td>0xE</td><td>[1110]</td><td>2<sup>3</sup>+2<sup>2</sup>+2<sup>1</sup>=14</td><td>-2<sup>3</sup>+2<sup>2</sup>+2<sup>1</sup>=-2</td></tr>
    <tr><td>0x0</td><td>[0000]</td><td>0+0+0+0=0</td><td>-0*2<sup>3</sup>+0+0+0=0</td></tr>
    <tr><td>0x5</td><td>[0101]</td><td>2<sup>2</sup>+1=5</td><td>-0*2<sup>3</sup>+2<sup>2</sup>+1=5</td></tr>
    <tr><td>0x8</td><td>[1000]</td><td>2<sup>3</sup>=8</td><td>-1*2<sup>3</sup>=-8</td></tr>
    <tr><td>0xD</td><td>[1101]</td><td>2<sup>3</sup>+2<sup>2</sup>+1=13</td><td>-1*2<sup>3</sup>+2<sup>2</sup>+1=-3</td></tr>
    <tr><td>0xF</td><td>[1111]</td><td>2<sup>3</sup>+2<sup>2</sup>+2<sup>1</sup>+1=15</td><td>-1*2<sup>3</sup>+2<sup>2</sup>+2<sup>1</sup>+1=-1</td></tr>
</table>

### 练习题 2.18

在第 3 章，我们将看到由反汇编器生成的列表，反汇编器是一种将可执行程序文件转换回可读性更好的 ASCII 码形式的程序。

这些文件包含许多十六进制数字，都是用典型的补码形式来表示这些值。
能够认识这些数字并理解它们的意义（例如，它们是正数还是负数），是一项重要的技巧。

在下面的列表中，对于标号 A ~ J（标记在右边）的那些行，将指令名（sub、mov 和 add）右边显示的（用 32 位补码形式表示的）十六进制值转换为等价的十进制值。

```
8048337: 81 ec b8 01 00 00        sub $0x1b8,%esp             A.
804833d: 8b 55 08                 mov 0x8(%ebp),%edx
8048340: 83 c2 14                 add $0x14,%edx              B. 
8048343: 8b 85 58 fe ff ff        mov 0xfffffe58(%ebp),%eax   C. 
8048349: 03 02                    add (%edx),%eax
804834b: 89 85 74 fe ff ff        mov %eax,0xfffffe74(%ebp)   D. 
8048351: 8b 55 08                 mov 0x8(%ebp),%edx
8048354: 83 c2 44                 add $0x44,%edx              E. 
8048357: 8b 85 c8 fe ff ff        mov 0xfffffec8(%ebp),%eax   F. 
804835d: 89 02                    mov %eax,(%edx)
804835f: 8b 45 10                 mov 0x10(%ebp),%eax         G. 
8048362: 03 45 0c                 add 0xc(%ebp),%eax          H. 
8048365: 89 85 ec fe ff ff        mov %eax,0xfffffeec(%ebp)   I. 
804836b: 8b 45 08                 mov 0x8(%ebp),%eax
804836e: 83 c0 20                 add $0x20,%eax              J. 
8048371: 8b 00                    mov (%eax),%eax
```

答案：

* A. 440
* B. 20
* C. -424
* D. -396
* E. 68
* F. -312
* G. 16
* H. 12
* I. -276
* J. 32

### 练习题 2.19

利用你解答练习题 2.17 时填写的表格，填下下列描述函数 T2U<sub>4</sub> 的表格。

|x|T2U<sub>4</sub>(x)|
|-|-|
|-8||
|-3||
|-2||
|-1||
|0||
|5||

答案：


|x|T2U<sub>4</sub>(x)|
|-|-|
|-8|8|
|-3|0xD|
|-2|0xE|
|-1|0xF|
|0|0|
|5|5|

### 练习题 2.20

请说明解答练习题 2.19 时生成的表格中，你是如何将 (2-6) 应用到其中各项的。

答案：

对于非负数不变，对于负数加上 2<sup>4</sup> 也就是 16。

### 练习题 2.21

假设在采用补码运算的 32 位机器上对这些表达式求值，按照图 2-18 的格式填写下表，描述强制类型转换和关系运算的结果。

|表达式|类型|求值|
|-|-|-|
|-2147483647-1 == 2147483648U|||
|-2147483647-1 &lt; 2147483647|||
|-2147483647-1U &lt; 2147483647|||
|-2147483647-1 &lt; -2147483647|||
|-2147483647-1U &lt; -2147483647|||

答案：

|表达式|类型|求值|
|-|-|-|
|-2147483647-1 == 2147483648U|无符号|1|
|-2147483647-1 &lt; 2147483647|有符号|1|
|-2147483647-1U &lt; 2147483647|无符号|0|
|-2147483647-1 &lt; -2147483647|有符号|1|
|-2147483647-1U &lt; -2147483647|无符号|1|

### 练习题 2.22

应用等式（2-3），证明下列每个位向量都是 -5 的补码表示。

```
A. [1011]
B. [11011]
C. [111011]
```

答案：

```
A. -1 * 2^3 + 2 + 1 = -5
B. -1 * 2^4 + 2^3 + 2 + 1 = -5
C. -1 * 2^5 + 2^4 + 2^3 + 2 + 1 = -5
```

### 思考题 2.23

考虑下面的 C 函数：

```c
int fun1(unsigned word) {
    return (int) ((word << 24) >> 24);
}

int fun2(unsigned word) {
    return ((int) word << 24) >> 24;
}
```

假设在一个采用补码运算的 32 位字长的机器上执行这些函数。还假设有符号数值的右移是算术右移，而无符号数值的右移是逻辑右移。

A. 填下下表，说明这些函数对几个示例参数的结果。你会发现用十六进制表示来做会更方便，只要记住十六进制数字 8 到 F 的最高有效位等于 1。

|w|fun1(w)|fun2(w)|
|-|-|-|
|0x00000076|||
|0x87654321|||
|0x000000C9|||
|0xEDCBA987|||

B. 用语言来描述这些函数执行的有用的计算。

答案：

代码参考: [ex2.23.c](ex2.23.c)

A.

|w|fun1(w)|fun2(w)|
|-|-|-|
|0x00000076|0x00000076|0x00000076|
|0x87654321|0x00000021|0x00000021|
|0x000000C9|0x000000C9|0xFFFFFFC9|
|0xEDCBA987|0x00000087|0xFFFFFF87|

B. 

* fun1 进行 24 位左移，再进行 24 位右移，由于都是无符号移位，相当于只保留最低的 8 位
* fun1 进行 24 位左移，再进行 24 位右移，由于都是有符号移位，相当于保留最低的 8 位，将其看成有符号数值，再将其扩展为 32 位有符号数值

### 练习题 2.24

假设将一个 4 位数值（用十六进制数字 0 ~ F 表示）截断到一个 3 位数值（用十六进制数字 0 ~ 7 表示）。

填写下表，根据那些位模式的无符号和补码解释，说明这种截断对某些情况的结果。

<table>
    <tr><th colspan=2>十六进制</th><th colspan=2>无符号</th><th colspan=2>补码</th></tr>
    <tr><th>原始值</th><th>截断值</th><th>原始值</th><th>截断值</th><th>原始值</th><th>截断值</th></tr>
    <tr><td>0</td><td>0</td><td>0</td><td></td><td>0</td><td></td></tr>
    <tr><td>2</td><td>2</td><td>2</td><td></td><td>2</td><td></td></tr>
    <tr><td>9</td><td>1</td><td>9</td><td></td><td>-7</td><td></td></tr>
    <tr><td>B</td><td>3</td><td>11</td><td></td><td>-5</td><td></td></tr>
    <tr><td>F</td><td>7</td><td>15</td><td></td><td>-1</td><td></td></tr>
</table>

解释如何将等式（2-9）和等式（2-10）应用到这些示例上。

答案：

<table>
    <tr><th colspan=2>十六进制</th><th colspan=2>无符号</th><th colspan=2>补码</th></tr>
    <tr><th>原始值</th><th>截断值</th><th>原始值</th><th>截断值</th><th>原始值</th><th>截断值</th></tr>
    <tr><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td></tr>
    <tr><td>2</td><td>2</td><td>2</td><td>2</td><td>2</td><td>2</td></tr>
    <tr><td>9</td><td>1</td><td>9</td><td>1</td><td>-7</td><td>1</td></tr>
    <tr><td>B</td><td>3</td><td>11</td><td>3</td><td>-5</td><td>3</td></tr>
    <tr><td>F</td><td>7</td><td>15</td><td>7</td><td>-1</td><td>-1</td></tr>
</table>

转成二进制序列，截掉最高位，再将其转换成 10 进制数值

### 练习题 2.25

考虑下列代码，这段代码试图计算数组 a 中所有元素的和，其中元素的数量由参数 length 给出。

```c
/* WARNING: This is buddy code */
float sum_elements(float a[], unsigned length) {
    int i;
    float result = 0;

    for (i = 0; i <= length-1; i++) {
        result += a[i];
    }

    return result;
}
```

当参数 length 等于 0 时，运行这段代码应该返回 0.0。
但实际上，运行时会遇到一个存储器错误。
请解释为什么会发生这样的情况，并且说明如何修改代码。

答案：由于 length 是无符号整数，当 length 为 0 时，循环中的 length-1 变成 UINT\_MAX 循环会出现越界的情况。
修改方案为将 `i <= length-1` 修改为： `i < length`。

### 练习题 2.26

现在给你一个任务，写一个函数用来判定一个字符串是否比另一个更长。

前提是你要用字符串库函数，它的声明如下：

```c
/* Prototype for library function strlen */
size_t strlen(const char *s);
```

最开始你写的函数是这样的：

```c
/* Determine whether string s is longer than string t */
/* WARNING: This function is buggy */
int strlonger(const *s, char *t) {
    return strlen(s) - strlen(t) > 0;
}
```

当你在一些示例数据上测试这个函数时，一切似乎都是正确的。
进一步研究发现在头文件 stdio.h 中数据类型 size_t 是定义成 unsigned int 的。

* A. 在什么情况下，这个函数会产生不正确的结果？
* B. 解释为什么会出现这样不正确的结果。
* C. 说明如何修改这段代码好让它能可靠地工作。

答案：

字符串 s 比 t 要短的时候返回结果有误，原因是 strlen 返回的是无符号的整数
两个无符号的整数相减结果也是无符号整数，因此 `strlen(s) - strlen(t)` 的结果总是大于等于 0。
将 `strlen(s) - strlen(t) > 0` 修改为 `strlen(s) > strlen(t)` 即可。

### 练习题 2.27

写出一个具有如下原型的函数：

```c
/* Determine whether arguments can be added without overflow */
int uadd_ok(unsigned x, unsigned y);
```

答案：

```c
/* Determine whether arguments can be added without overflow */
int uadd_ok(unsigned x, unsigned y)
{
    unsigned sum = x + y;
    return sum >= x;
}
```

如果发生溢出，sum = (x + y - UINT_MAX)，必然小于 x 和 y。 

### 练习题 2.28

我们能用一个十六进制数字来表示长度 w = 4 的位模式。

对于这些数字的无符号解释，使用等式（2-12）填写下表，给出所示数字的无符号加法逆元的位表示（使用十六进制形式）。

<table>
    <tr><th colspan=2>x</th><th colspan=2>-<sup>u</sup><sub>4</sub>x</th></tr>
    <tr><th>十六进制</th><th>十进制</th><th>十六进制</th><th>十进制</th></tr>
    <tr><td>0</td><td></td><td></td><td></td></tr>
    <tr><td>5</td><td></td><td></td><td></td></tr>
    <tr><td>8</td><td></td><td></td><td></td></tr>
    <tr><td>D</td><td></td><td></td><td></td></tr>
    <tr><td>F</td><td></td><td></td><td></td></tr>
</table>

答案：

<table>
    <tr><th colspan=2>x</th><th colspan=2>-<sup>u</sup><sub>4</sub>x</th></tr>
    <tr><th>十六进制</th><th>十进制</th><th>十六进制</th><th>十进制</th></tr>
    <tr><td>0</td><td>0</td><td>0</td><td>0</td></tr>
    <tr><td>5</td><td>5</td><td>B</td><td>11</td></tr>
    <tr><td>8</td><td>8</td><td>8</td><td>8</td></tr>
    <tr><td>D</td><td>13</td><td>3</td><td>3</td></tr>
    <tr><td>F</td><td>15</td><td>1</td><td>1</td></tr>
</table>

### 练习题 2.29

按照图 2-24 的形式填写下表。

分别列出 5 位参数的整数值、整数和的数值、补码和的数值、补码和的位级表示，以及属于等式 (2-24) 推导中的哪种情况。

|x|y|x+y|x+<sup>t</sup><sub>5</sub>y|情况|
|-|-|-|-|-|
|[10100]|[10001]||||
|[11000]|[11000]||||
|[10111]|[01000]||||
|[00010]|[00101]||||
|[01100]|[00100]||||

答案：

|x|y|x+y|x+<sup>t</sup><sub>5</sub>y|情况|
|-|-|-|-|-|
|-12</br>[10100]|-15</br>[10001]|-27</br>[100101]|5</br>[00101]|1|
|-8</br>[11000]|-8</br>[11000]|-16</br>[110000]|-16</br>[10000]|2|
|-9</br>[10111]|8</br>[01000]|-1</br>[111111]|-1</br>[11111]|2|
|2</br>[00010]|5</br>[00101]|7</br>[000111]|7</br>[00111]|3|
|12</br>[01100]|4</br>[00100]|16</br>[010000]|-16</br>[10000]|4|

### 练习题 2.30

写出一个具有如下原型的函数：

```c
/* Determine whether arguments can be added without overflow */
int tadd_ok(int x, int y);
```

如果参数 x 和 y 相加不会产生溢出，这个函数就返回 1。

答案：

```c
/* Determine whether arguments can be added without overflow */
int tadd_ok(int x, int y) {
    int sum = x + y;
    return !((sum >= 0 && x < 0 && y < 0)
        || (sum < 0 && x >= 0 && y >= 0));
}
```

### 练习题 2.31

你的同事对你的补码加法溢出条件的分析有些不耐烦了，他给出了一个函数 tadd_ok 的实现，如下所示：

```c
/* Determine whether arguments can be added without overflow */
/* WARNING: This code is buggy */
int tadd_ok(int x, int y) {
    int sum = x + y;
    return (sum-x == y) && (sum-y == x);
}
```

你看了代码以后笑了。解释一下为什么。

 答案：

 补码加法会形成阿贝尔群，因此 `(x+y)-x` 总是等于 y，而 `(x+y)-y` 总是等于 x，无论是否发生溢出。

 ### 练习题 2.32
 
 你现在有个任务，编写函数 tsub_ok 的代码，函数的参数是 x 和 y，如果计算 x-y 不产生溢出，函数就返回1。

 假设你写的练习题 2.30 的代码如下所示：

 ```c
 /* Determine whether arguments can be subtracted without overflow */
 /* WARNING: This code is buggy. */
 int tsub_ok(int x, int y) {
    return tadd_ok(x, -y);
 }
 ```

 x 和 y 取什么值时，这个函数会产生错误的结果？写一个该函数的正确版本（家庭作业 2.74）。

 答案：当 y 等于 TMin 并且 x 为负数时，会产生错误的结果，但由于 -y 也等于 TMin，会不会发生溢出。

 可以对 y 进行特殊处理，代码如下：

 ```c
 int tsub_ok(int x, int y) {
    if (y == INT_MIN) {
        return 1;
    }

    return tadd_ok(x, -y);
}
```

### 练习题 2.33

我们可以用一个十六进制数字来表示长度 w=4 的位模式。

根据这些数字的补码的解释，填写下表，确定所示数字的加法逆元。

<table>
    <tr><th colspan=2>x</th><th colspan=2>-<sup>t</sup><sub>4</sub>x</th></tr>
    <tr><th>十六进制</th><th>十进制</th><th>十六进制</th><th>十进制</th></tr>
    <tr><td>0</td><td></td><td></td><td></td></tr>
    <tr><td>5</td><td></td><td></td><td></td></tr>
    <tr><td>8</td><td></td><td></td><td></td></tr>
    <tr><td>D</td><td></td><td></td><td></td></tr>
    <tr><td>F</td><td></td><td></td><td></td></tr>
</table>

对于补码和无符号（见练习题 2.28）非（negation）产生的位模式，你观察到什么？

答案：

<table>
    <tr><th colspan=2>x</th><th colspan=2>-<sup>t</sup><sub>4</sub>x</th></tr>
    <tr><th>十六进制</th><th>十进制</th><th>十进制</th><th>十六进制</th></tr>
    <tr><td>0</td><td>0</td><td>0</td><td>0</td></tr>
    <tr><td>5</td><td>5</td><td>-5</td><td>B</td></tr>
    <tr><td>8</td><td>-8</td><td>-8</td><td>8</td></tr>
    <tr><td>D</td><td>-3</td><td>3</td><td>3</td></tr>
    <tr><td>F</td><td>-1</td><td>1</td><td>1</td></tr>
</table>

补码和无符号非产生的位模式一样。

### 练习题 2.34

按照 图 2-26 的格式填下表，说明不同的 3 位数字乘法的结果。

|模式|x|y|x*y|截断的 x*y|
|-|-|-|-|-|
|无符号</br>补码|[100]</br>[100]|[101]</br>[101]|||
|无符号</br>补码|[010]</br>[010]|[111]</br>[111]|||
|无符号</br>补码|[110]</br>[110]|[110]</br>[110]|||

我们可以看出，w 位数字上的无符号运算和补码运算是同构的 +<sup>u</sup><sub>w</sub>、
-<sup>u</sup><sub>w</sub>、*<sup>u</sup><sub>w</sub> 和 +<sup>t</sup><sub>w</sub>、
-<sup>t</sup><sub>w</sub>、*<sup>t</sup><sub>w</sub> 在位级上有相同的结果。

答案：

|模式|x|y|x*y|截断的 x*y|
|-|-|-|-|-|
|无符号</br>补码|4 [100]</br>-4 [100]|5 [101]</br>-3 [101]|20 [010 100]</br>12 [001 100]|4 [100]</br>-4 [100]|
|无符号</br>补码|2 [010]</br>2 [010]|7 [111]</br>-1 [111]|14 [001 110]</br>-2 [111 110]|6 [110]</br>-2 [110]|
|无符号</br>补码|6 [110]</br>-2 [110]|6 [110]</br>-2 [110]|36 [100 100]</br>4 [000 100]|4 [100]</br>-4 [100]|

### 练习题 2.35

给你一个任务，开发函数 tmult_ok 的代码，该函数会判断两个参数相乘是否会产生溢出。下面是你的解决方案：

```c
/* Determine whether arguments can be multiplied without overflow */
int tmult_ok(int x, int y) {
    int p = x*y;
    /* Either x is zero, or dividing p by x gives y */
    return !x || p/x == y;
}
```

你用 x 和 y 的很多值来测试这段代码，似乎都工作正常。
你的同时向你挑战，说：“如果我不能用减法校验加法是否溢出（参见练习题 2.31），那么你怎么能用除法来检验乘法是否溢出呢？”
按照下面的思路，用数学推导来证明你的方法是对的。首先，证明 x = 0 的情况是正确的。
另外，考虑 w 位数字 x(x!=0)、y、p 和 q，这里的 p 是 x 和 y 的补码乘法的结果，而 q 是 p 除以 x 的结果。

1. 说明 x 和 y 的整数乘积 x\*y，可以写成这样的形式：x\*y=p+t2<sup>w</sup>，其中t!=0当且仅当p的计算溢出。
2. 说明 p 可以写成这样的形式：p=x*q+r，其中 |r|&lt;|x|。
3. 说明 q=y 当且仅当 r=t=0。

答案：

1. 我们知道 x * y 可以写成一个 2w 位的补码数字。用 u 表示低 w 位的无符号数，v 表示高 w 位的补码数字。
那么根据等式 (2-3)，我们可以得到 x * y = v2<sup>w</sup>+u。
</br>我们还知道 u=T2U<sub>w</sub>(p)，这里p<sub>w-1</sub>是p的最高有效位。设t=v+p<sub>w-1</sub>，我们得到 x*y= p+t2<sup>w</sup>
</br>当 t=0 时，有 x\*y=p；乘法不会溢出。当 t!=0时，有 x\*y!=p；乘法溢出。
2. 根据整数除法的定义，用非零数x除以p会得到商q和余数r，即 p=x*q+r，且 |r|&lt;|x|。（这里用的是绝对值，因为x和r符号可能不一致。例如，-7除以2得到商-3和余数-1。）
3. 假设 q=y，那么有 x\*y=x\*y+r+t2<sup>w</sup>。在此，我们可以得到 r+t2<sup>w</sup>=0。但是 |r|&lt;|x|&lt;=2<sup>w</sup>，所以只有当 t=0时，这个等式才会成立，此时 r=0。
</br>假设 r=t=0，那么我们有 x*y=x*q，隐含 y=q。
</br>当 x=0 时，乘法不溢出，所以我们的代码提供了一种可靠的方法来测试补码乘法是否会导致溢出。


### 练习题 2.36

对于数据类型 int 为 32 位的情况，设计一个版本的 tmult_ok 函数（见练习题 2.35），要使用 64 位精度的数据类型 long long 而不使用除法。

答案：

```c
/* Determine whether arguments can be multiplied without overflow */
int tmult_ok(int x, int y) {
    long long p = long long(x)*y;
    //return p <= INT_MAX && p >= INT_MIN;
    return p == (int)(p);
}
```

### 练习题 2.37

现在你的任务是修补上述 XDR 代码中的漏洞。

你决定将待分配字节数设置为数据类型 `long long unsigned`，来消除乘法溢出的可能性（至少在 32 位机器上）。
你把原来对 malloc 函数的调用（第 10 行）替换如下：

```c
long long unsigned asize = ele_cnt * (long long unsigned) ele_size;
void *result = malloc(asize);
```

* A. 这段代码在原始代码基础上有了哪些改进？
* B. 假设数据类型 size_t 和 unsigned int 是一样的，并且都是 32 位长，你该如何修改代码来消除这个漏洞？

答案：

* A. aszie 使用了 64 位字长，消除了 32 位机器上乘法溢出的问题
* B. size_t 和 unsigned int 都是 32 位的情况下，如果 asize 超过 32 位无符号整数的大小，调用 malloc 的时候会发生截断，改进方法如下：

```c
long long unsigned asize = ele_cnt * (long long unsigned) ele_size;
if (asize != (size_t)asize) {
    return NULL;
}

void *result = malloc(asize);
```

### 练习题 2.38

就像我们将在第 3 章中看到的那样，LEA 指令能够执行形如 (a&lt;&lt;k)+b 的计算，这里 k 等于 0、1、2或3，而 b 等于 0 或者某个程序值。

编译器常常用这条指令来执行常数因子乘法。例如我们可以用 (a&lt;&lt;1)+a 来计算 3\*a。

考虑 b 等于 0 或者 a、k 为任意可能的值的情况，用一条 LEA 指令可以计算 a 的哪些倍数？

答案：LEA 执行可以计算 a\*2<sup>k</sup> 以及 a\*2<sup>k</sup>+a。

### 练习题 2.39

对于位置 n 为最高有效位的情况，我们要怎样修改形式B的表达式？

答案：此时形式B变成：-(x&lt;&lt;m)

### 练习题 2.40

对于下面每个 K 的值，找出只用指定数量的运算表达式 x \* K 的方法，这里我们认为加法和减法的开销相当。

除了我们已经考虑过的简单的形式 A 和 B 原则，你可能需要使用一些技巧。

|K|移位|加法/减法|表达式|
|-|-|-|-|
|6|2|1||
|31|1|1||
|-6|2|1||
|55|2|2||

答案：

|K|移位|加法/减法|表达式|
|-|-|-|-|
|6|2|1|(x&lt;&lt;2)+(x&lt;&lt;1)|
|31|1|1|(x&lt;&lt;5)-x|
|-6|2|1|(x&lt;&lt;1)-(x&lt;&lt;3)|
|55|2|2|(x&lt;&lt;6)-(x&lt;&lt;3)-x|

### 练习题 2.41

对于一组从位位置 n 开始到位位置 m 结束的连续的 1 (n>=m)，我们看到可以产生两种形式的代码，A 和 B 。编译器如何决定使用哪一种呢？

答案：假设加法和减法有同样的性能，那么原则就是当 n=m 时，选择形式 A，当 n=m+1 时，随便选哪种，而当 n&gt;m+1 时，选择形式 B。

### 练习题 2.42

写一个函数 div16，对于整数参数 x 返回 x/16 的值。

你的函数不能使用除法、模运算、乘法、任何条件语句（if 或者 ?:）、任何比较运算符（例如&lt;、&gt;或==）或任何循环。
你可以假设数据类型 int 是 32 位长，使用补码表示，而右移是算术右移。

答案：

```c
int div16(int x) {
    int bias = (x >> 31) & 0xF;
    return (x + bias) >> 4;
}
```

代码：[ex2.42.c](ex2.42.c)

### 练习题 2.43

在下面的代码中，我们省略了常数 M 和 N 的定义：

```c
#define M /* Mystery number 1 */
#define N /* Mystery number 2 */
int arith(int x, int y) {
    int result = 0;
    result = x*M + y/N; /* M and N are mystery numbers */
    return result;
}
```

我们以某个 M 和 N 的值编译这段代码。
编译器用我们讨论过的方法优化乘法和除法。下面是将产生出的机器代码翻译回 C 语言的结果：

```c
/* Translation of assembly code for arith */
int optarith(int x, int y) {
    int t = x;
    x <<= 5;
    x -= t;
    if (y < 0) y += 7;
    y >>= 3; /* Arithmetic shift */
    return x+y;
}
```

M 和 N 的值为多少？

答案：M=15，N=8

### 练习题 2.44

假设我们对有符号值使用补码运算的 32 位机器上运行代码。

对于由符号值使用的是算术右移，而对于无符号值使用的是逻辑右移。变量的声明和初始化如下：

```c
int x = foo(); /* Arbitrary value */
int y = bar(); /* Arbitrary value */

unsigned ux = x;
unsigned uy = y;
```

对于下面每个 C 表达式，1）证明对于所有的 x 和 y值，它都为真（等于1）；或者 2）给出使得它为假（等于 0）的 x 和 y 的值：

* A. (x &gt; 0) || (x-1 &lt; 0)
* B. (x & 7) != 7 || (x&lt;&lt;29 &lt; 0)
* C. (x \* x) >= 0
* D. x &lt; 0 || -x &lt;= 0
* E. x &gt; 0 || -x &gt;= 0
* F. x+y == ux+uy
* G. x\*~y + ux\*uy == -x

答案：

* A. 当 x = 0x80000000 时表达式为假
* B. 表达式为真，当 (x & 7) == 7 时， (x&lt;&lt;29) 最高位为 1，数值必然为负
* C. 当 x = 0xF000 时表达式为假，此时结果为 0xE100 0000(-520093696)
* D. 表达式为真,如果 x 为非负数，则 -x 必然为非正数
* E. 当 x = 0x80000000 时表达式为假
* F. 真，补码和无符号加法有相同的位级行为，而且它们是可交换的
* G. 真，~y等于-y-1。uy\*ux等于x\*y。因此等式左边等价于 x\*-y-x+x\*y

### 练习题 2.45

填写下表中的缺失信息：

|小数值|二进制表示|十进制表示|
|-|-|-|
|1/8|0.001|0.125|
|3/4|||
|25/16|||
||10.1011||
||1.001||
|||5.875|
|||3.1875|

答案：

|小数值|二进制表示|十进制表示|
|-|-|-|
|1/8|0.001|0.125|
|3/4|0.11|0.75|
|25/16|1.1001|1.5625|
|43/16|10.1011|2.6875|
|9/8|1.001|1.125|
|47/8|101.111|5.875|
|51/16|11.0011|3.1875|

### 练习题 2.46

浮点运算的不精确性能够产生灾难性的后果。

爱国者导弹系统中有一个内置的时钟，其实现类似一个计数器，每 0.1 秒就加 1。
为了以秒为单位来精确时间，程序将一个24位的近似于 1/10 的二进制小数值来乘以这个计数器的值。
特别地，1/10 的二进制表达式是一个无穷序列 0.000110011[0011]...<sub>2</sub>，其中，方括号里面的部分是无限循环的。
程序用值 x 近似地表示 0.1，x 只考虑这个序列的二进制小数点右边的前 23 位：x=0.00011001100110011001100。
（参考练习题 2.51，里面有关于如何更精确地近似表示 0.1 的讨论。）

* A. 0.1 - x 的二进制表示是什么？
* B. 0.1 - x 的近似的十进制值是多少？
* C. 当系统初始启动时，时钟从 0 开始，并且一直保持计数。在这个例子中，系统已经运行了大约 100 个小时。
程序计算出的时间和实际的时间之差为多少？
* D. 系统根据一枚来袭导弹的速率和它最后被雷达侦测到的时间，来预测它将在哪里出现。
假定飞毛腿导弹的速率大约是 2000 米每秒，对它的预测偏差了多少？

通过一次读取时钟得到的绝对时间中的一个轻微错误，通常不会影响跟踪的计算。
相反，它应该依赖于两次连续的读取之间的相对时间。
问题是爱国者导弹的软件已经升级，可以使用更精确的函数来读取时间，但不是所有的函数调用都用新的代码替换。
结果就是，跟踪软件一次读取用的是精确的时间，而另一个读取用的是不精确的时间。

答案：

* A. .1 - x 的二进制表示是 0.0000,0000,0000,0000,0000,000[1100]...
* B. 0.1 - x 等于 2^<sup>-20</sup> \* 0.1，约等于 9.54\*10<sup>-8</sup>
* C. 9.54\*10<sup>-8</sup>\*100\*3600\*10约等于0.343秒
* D. 0.343\*2000约等于684米

### 练习题 2.47

假设一个基于 IEEE 浮点格式的 5 位浮点表示，有 1 个符号位、2 个阶码位（k=2）和两个小数位（n=2）。
价码偏置量是 2<sup>2-1</sup>-1=1。

下表中列举了这个 5 位浮点表示的全部非负取值范围。
使用下面的条件，填写表格中的空白项：

* e: 假定阶码字段是一个无符号整数表示的值。
* E：偏置之后的阶码置。
* 2<sup>E</sup>：阶码的权重数。
* f：小数值。
* M：尾数的值。
* 2<sup>E</sup>：阶码的权重数。
* _f_：小数值
* M：尾数的值
* 2<sup>E</sup>*M：该数（未归约的）小数值。
* V：该数归约后的小数值。
* 十进制：该数的十进制表示。

写出 2<sup>E</sup>、_f_、M、2<sup>E</sup>*M 和 V 的值，要么是整数（如果可能的话），要么是形如 x/y 的小数，这里 y 是 2 的幂。
标注“—”的条目不用填。

|位|e|E|2<sup>E</sup>|_f_|M|2<sup>E</sup>*M|V|十进制|
|-|-|-|-|-|-|-|-|-|
|0 00 00|||||||||
|0 00 01|||||||||
|0 00 10|||||||||
|0 00 11|||||||||
|0 01 00|||||||||
|0 01 01|1|0|1|1/4|5/4|5/4|5/4|1.25|
|0 01 10|||||||||
|0 01 11|||||||||
|0 10 00|||||||||
|0 10 01|||||||||
|0 10 10|||||||||
|0 10 11|||||||||
|0 11 00|—|—|—|—|—|—||—|
|0 11 01|—|—|—|—|—|—||—|
|0 11 10|—|—|—|—|—|—||—|
|0 11 11|—|—|—|—|—|—||—|

答案：

|位|e|E|2<sup>E</sup>|_f_|M|2<sup>E</sup>*M|V|十进制|
|-|-|-|-|-|-|-|-|-|
|0 00 00|0|0|1|0/4|0/4|0/4|0|0.0|
|0 00 01|0|0|1|1/4|1/4|1/4|1/4|0.25|
|0 00 10|0|0|1|2/4|2/4|2/4|1/2|0.5|
|0 00 11|0|0|1|3/4|3/4|3/4|3/4|0.75|
|0 01 00|1|0|1|0/4|4/4|4/4|1|1.0|
|0 01 01|1|0|1|1/4|5/4|5/4|5/4|1.25|
|0 01 10|1|0|1|2/4|6/4|6/4|3/2|1.5|
|0 01 11|1|0|1|3/4|7/4|7/4|7/4|1.75|
|0 10 00|2|1|2|0/4|4/4|8/4|2|2.0|
|0 10 01|2|1|2|1/4|5/4|10/4|5/2|2.5|
|0 10 10|2|1|2|2/4|6/4|12/4|3|3.0|
|0 10 11|2|1|2|3/4|7/4|14/4|7/2|3.5|
|0 11 00|—|—|—|—|—|—|正无穷大|—|
|0 11 01|—|—|—|—|—|—|NaN|—|
|0 11 10|—|—|—|—|—|—|NaN|—|
|0 11 11|—|—|—|—|—|—|NaN|—|

### 练习题 2.48

正如在练习题 2.6 中提到的，整数 3 510 593 的十六进制表示为 0x00359141，而单精度浮点数 3510593.0 的十六进制表示为 0x4A564504。

推导出这个浮点表示，并解释整数和浮点数表示的位之间的关系。

答案：

整数 3,510,593 转换为二进制：11,0101,1001,0001,0100,0001=1.1,0101,1001,0001,0100,0001\*2<sup>21</sup>。

为了使用 IEEE 单精度浮点数编码，我们丢弃开头的 1，并且在末尾增加 2 个 0，来构造小数字段，得到二进制表示 

[101,0110,0100,0101,0000,0100]。为了构造阶码字段，我们用 21 加上偏置量 127，得到 148，其二进制表示为 
[1001,0100]，加上符号位 0，我们就得到二进制浮点数表示 [0100,1010,0101,0110,0100,0101,0000,0100]即：0x4A564504。

验证代码：[ex2.48.c](ex2.48.c)

### 练习题 2.49

* A. 对于一种具有 n 位小数的浮点格式，给出不能精确描述的最小正整数的公式（因为想要准确表示它需要 n+1 位小数）。
假设阶码字段长度 k 足够大，可以表示的阶码范围不会限制这个问题。
* B. 对于单精度格式（n=23），这个整数的数字值是多少？

答案：

* A. 2<sup>n+1</sup>+1
* B. 2<sup>24</sup>+1=16,777,217

### 练习题 2.50

根据舍入到偶数规则，说明如何将下列二进制小数值舍入到最接近的二分之一（二进制小数点右边一位）。
对每种情况，输出舍入前后的数字值。

* A. 10.010<sub>2</sub>
* B. 10.011<sub>2</sub>
* C. 10.110<sub>2</sub>
* D. 11.001<sub>2</sub>

答案：

* A. 10.010<sub>2</sub>(
2<math>
  <mfrac>
    <mtext>1</mtext>
    <mtext>4</mtext>
  </mfrac>
</math>
)舍入后 10.0<sub>2</sub>(2)
* B. 10.011<sub>2</sub>(
2<math>
  <mfrac>
    <mtext>3</mtext>
    <mtext>8</mtext>
  </mfrac>
</math>
)舍入后 10.1<sub>2</sub>(
2<math>
  <mfrac>
    <mtext>1</mtext>
    <mtext>2</mtext>
  </mfrac>
</math>
)
* C. 10.110<sub>2</sub>(
2<math>
  <mfrac>
    <mtext>3</mtext>
    <mtext>4</mtext>
  </mfrac>
</math>
)舍入后 11.0<sub>2</sub>(
3
)
* D. 11.001<sub>2</sub>(
2<math>
  <mfrac>
    <mtext>1</mtext>
    <mtext>8</mtext>
  </mfrac>
</math>
)舍入后 11.0<sub>2</sub>(
3
)

### 练习题 2.51

在练习题 2.46 中我们看到，爱国者导弹软件 0.1 近似表示为 x=0.000110011001100110110<sub>2</sub>。
假设使用 IEEE 舍入到偶数方式确定 0.1 的二进制小数点右边 23 位的近似表示 x'。

* A. x' 的二进制表示是什么？
* B. x'-0.1 的十进制表示的近似值是什么？
* C. 运行 100 小时后，计算时钟值会有多少偏差？
* D. 该程序对飞毛腿导弹位置的预测会有多少偏差？

答案：

* A. 从 1/10 的无穷序列中我们可以看到，舍入位置右边 2 位都是 1，所以 1/10 更好一点儿的近似值应该是对 x 加 1，得到 x'=0.00011001100110011001101<sub>2</sub>，它比 0.1 大一点儿。
* B. 我们可以看到 x'-0.1 的二进制表示为：0.0000,0000,0000,0000,0000,0000,0[1100]
将这个值与 1/10 的二进制表示比较，她等于 2<sup>-22</sup>\*1/10，大约等于 2.38*10<sup>-8</sup>
* C. 2.38\*10<sup>-8</sup>\*100\*3600\*10≈0.086秒
* D. 0.086\*2000≈171米

### 练习题 2.52

考虑下列基于 IEEE 浮点格式的 7 位浮点表示。
两个格式都没有符号位——它们只能表示非负的数字。

1. 格式 A
    * 有 k=3 个阶码位。阶码偏置值是 3。
    * 有 n=4 个小数位。
2. 格式 B
    * 有 k=4 个阶码位。阶码的偏置值是 7。
    * 有 n=3 个小数位。

下面给出了一些格式 A 表示的位模式，你的任务是将它们转换成格式 B 中最接近的值。
如果有必要，请使用舍入到偶数的原则。
另外，给出由格式 A 和格式 B 表示的位模式对应的数字的值。
给出整数（例如 17）或者小数（例如 17/64）。

<table>
    <tr><th colspan=2>格式A</th><th colspan=2>格式B</th></tr>
    <tr><th>位</th><th>值</th><th>位</th><th>值</th></tr>
    <tr><td>011 0000</td><td>1</td><td>0111 000</td><td>1</td></tr>
    <tr><td>101 1110</td><td></td><td></td><td></td></tr>
    <tr><td>010 1001</td><td></td><td></td><td></td></tr>
    <tr><td>110 1111</td><td></td><td></td><td></td></tr>
    <tr><td>000 0001</td><td></td><td></td><td></td></tr>
</table>

答案：

<table>
    <tr><th colspan=2>格式A</th><th colspan=2>格式B</th><th rowspan=2>备注</th</tr>
    <tr><th>位</th><th>值</th><th>位</th><th>值</th></tr>
    <tr><td>011 0000</td><td>1</td><td>0111 000</td><td>1</td><td></td></tr>
    <tr><td>101 1110</td><td>15/2</td><td>1001 111</td><td>15/2</td><td></td></tr>
    <tr><td>010 1001</td><td>25/32</td><td>0110 100</td><td>3/4</td><td>向下舍入</td></tr>
    <tr><td>110 1111</td><td>31/2</td><td>1011 000</td><td>16</td><td>向上舍入</td></tr>
    <tr><td>000 0001</td><td>1/64</td><td>0001 000</td><td>1/64</td><td>非规格化转为规格化</td></tr>
</table>

### 练习题 2.53

完成下列宏定义，生成双精度值 +&infin;,-&infin;和 0。

```c
#define POS_INFINITY
#define NEG_INFINITY
#define NEG_ZERO
```

不能使用任何 `include` 文件（例如 `math.h`），但你能利用的是：双精度能够表示的最大的有限数：大约是 1.8×10<sup>308</sup>。

答案：

```c
#define POS_INFINITY 1e400
#define NEG_INFINITY (-POS_INFINITY)
#define NEG_ZERO (-1.0/POS_INFINITY)
```

### 练习题 2.54

假定变量 x、f 和 d 的类型分别是 int、float 和 double。
除了 f 和 d 都不能等于 +&infin;、-&infin; 或者  NaN 之外，它们的值是任意的。
下面每个 C 表达式，证明它总是为真（也就是求值为 1），或者给出一个使表达式不为真的值（也就是求值为 0）。

* A. x==(int) (double) x
* B. x==(int) (float) x
* C. d==(double) (float) d
* D. f==(float) (double) f
* E. f==-(-f)
* F. 1.0/2==1/2.0
* G. d*d>=0.0
* H. (f+d)-f==d

答案：

* A. x==(int) (double) x 总是为真，double 有 52 位表示小数位，可以保证 int 转成 double 后不会出现精度丢失的问题
* B. x==(int) (float) x 由于 float 只有 23 位小数位，当 int 需要超过超过 23 位才能精确表示时转换为 float 会丢失精度，比如 x=0x3FFFFFFF 的情况
* C. d==(double) (float) d 由于 double 精度比 float 高，d 转换为 float 时有可能丢失精度，比如 d=2147483647.0 时，等式不成立
* D. f==(float) (double) f 总是为真，将 float 转成 double 不会丢失精度
* E. f==-(-f) 总是为真，float 取负只会修改符号位，不会丢失精度
* F. 1.0/2==1/2.0 总是为真，执行除法前会将分子和分母都转成浮点数
* G. d*d>=0.0 为真，有可能溢出导致结果为 +&infin;
* H. (f+d)-f==d 假，例如当 f=1.0e20 而 d 是 1.0 时，表达式 f+d 会舍入到 1.0e20，因此左边的表达式求值得到 0.0，而右边是 1.0。

## 家庭作业

### 2.55 \*

在你能够访问的不同机器上，使用 show_bytes（文件 show_bytes.c）编译并运行示例代码。确定这些机器使用的字节顺序。

在 x86\_64 和 aarch64 架构机器上结果均为：

```
calling show_twocomp
 39 30
 c7 cf
Calling simple_show_a
 21
 21 43
 21 43 65
Calling simple_show_b
 78
 78 56
 78 56 34
Calling float_eg
For x = 3490593
 21 43 35 00
 84 0c 55 4a
For x = 3510593
 41 91 35 00
 04 45 56 4a
Calling string_ueg
 41 42 43 44 45 46
Calling string_leg
 61 62 63 64 65 66
```

### 2.56 \*

试着用不同的示例值来运行 show_bytes 的代码。

略

### 2.57 \*

编写程序 show_short、show_long 和 show_double，它们分别打印类型为 short int、long int 和 double 的 C 语言对象的字节表示。请试着在几种机器上运行。

答案：[ex2.57.c](ex2.57.c)

### 2.58 \*\*

编写过程 is_little_endian，当在小端法机器上编译和运行时返回 1，在大端法机器上编译运行时则返回 0。这个程序应该可以运行在任何机器上，无论机器的字长多少。

答案：[ex2.58.c](ex2.58.c)

### 2.59 \*\*

编写一个 C 表达式，使它生成一个字，由 x 的最低有效字节和 y 中剩下的字节组成。对于运算数 x=0x89ABCDEF 和 y=0x76543210，就得到 0x765432EF。

答案：(y & ~0xFF) | (x & 0xFF)

验证代码：[ex2.59.c](ex2.59.c)

### 2.60 \*\*

假设我们将一个 w 位的字中的字节从 0（最低位）到 w/8-1（最高位）编号。

写出下面 C 函数的代码，它会返回一个无符号值，其中参数 x 的字节 i 被替换成字节 b：

```c
unsigned replace_byte(unsigned x, unsigned char b, int i);
```

以下的一些示例，说明了这个函数该如何工作：

```c
replace_byte(0x12345678, 0xAB, 2) --> 0x12AB5678
replace_byte(0x12345678, 0xAB, 0) --> 0x123456AB
```

答案： [ex2.60.c](ex2.60.c)

### 位级整数编码规则

TODO

### 2.61 \*\*

写一个 C 表达式，在下列描述的条件下产生 1，而在其他的情况下得到 0。

假设 x 是 int 类型。

* A. x 的任何位都等于 1。
* B. x 的任何位都等于 0。
* C. x 的最低有效字节中的位都等于 1。（中文版翻译为最高有效字节，这里以英文原版为准）
* D. x 的最高有效字节中的位都等于 0。（中文版翻译为最低有效字节，这里以英文原版为准）

代码应该遵循位级整数编码规则，另外还有一个限制，你不能使用相等（==）和不相等（!=）测试。

答案：[ex2.61.c](ex2.61.c)

### 2.62 \*\*\*

编写一个函数 int_shifts_are_logical()，在对 int 类型的数使用逻辑右移的机器上运行时，这个函数生成 1，而在其他情况下生成 0。

你的代码应该可以运行在任何字长的机器上。
在几种机器上测试你的代码。

答案：[ex2.62.c](ex2.62.c)

### 2.63 \*\*\*

将下面的 C 函数代码补充完整。

函数 sr1 用算术右移（由值 xsra 给出）来完成逻辑右移，后面的其他操作不包括右移或者除法。
函数 sra 用逻辑右移（由值 xsrl 给出）来完成算术右移，后面的其他操作不包括右移或者除法。
可以通过计算 8\*sizeof(int) 来确定数据类型 int 中的位数 w。
位移量 k 的取值范围为 0\~w-1。

```c
int sra(int x, int k) {
    /* Perform shift logically */
    int xsrl = (unsigned) x >> k;
    /* ... */
}

unsigned srl(unsigned x, int k) {
    /* Perform shift arithmetically */
    unsigned xsra = (int) x >> k;
    /* ... */
}
```

答案：[ex2.63.c](ex2.63.c)

### 2.64 \*

写出代码实现如下函数

```c
/* Return 1 when any even bit of x equals 1; 0 otherwise.
   Assume w=32 */
int any_even_one(unsigned x);
```

函数应该遵循位级整数编码规则，不过你可以假设数据类型 int 有 w=32 位。
你的代码最多只能包含 12 个算术运算、位运算和逻辑运算。

答案：[ex2.64.c](ex2.64.c)

### 2.65 \*\*\*\*

写出代码实现如下函数：

```c
/* Return 1 when x contains an even number of 1s; 0 otherwise.
   Assume w=32 */
int even_ones(unsigned x);
```

函数应该遵循位级整数编码规则，不过你可以假设数据类型 int 有 w=32 位。
你的代码最多只能包含 12 个算术运算、位运算和逻辑运算。

答案：[ex2.65.c](ex2.65.c)

### 2.66 \*\*\*

写出代码实现如下函数

```c
/*
 * Generate mask indicating leftmost 1 in x. Assume w=32.
 * For example 0xFF00 -> 0x8000, and 0x6600 --> 0x4000.
 * If x = 0, then return 0.
 */
int leftmost_one(unsigned x);
```

函数应该遵循位级整数编码规则，不过你可以假设数据类型 int 有 w=32位。
你的代码最多只能包含 15 个算术运算、位运算和逻辑运算。

> **提示：** 先将 x 转换成形如 [0...011...1] 的位向量。

答案：[ex2.66.c](ex2.66.c)

### 2.67 \*\*

给你一个任务，编写一个过程 int_size_is_32()，当在一个 int 是 32 位的机器上运行时，该程序产生 1，而其他情况则产生 0。不允许使用 sizeof 运算符。下面是开始时的尝试：

```c
/* The following code does not run properly on some machines */
int bad_int_size_is_32() {
  /* Set most significant bit (msb) of 32-bit machine */
  int set_msb = 1 << 31;
  /* Shift past msb of 32-bit word */
  int beyond_msb = 1 << 32;
  /* set_msb is nonzero when word size >= 32
     beyond_msb is zero when word size <= 32 */
  return set_msb && !beyond_msb;
}
```

当在 SUN SPARC 这样的 32 位机器上编译并运行时，这个过程返回的却是 0。
下面的编译器信息给了我们一个问题的提示：

warning: left shift count &gt;= width of type

* A. 我们的代码在哪个方便没有遵守 C 语言标准
* B. 修改代码，使得它在 int 至少为 32 位的任何机器上都能正确地运行。
* C. 修改代码，使得它在 int 至少为 16 位的任何机器上都能正确地运行。

答案：

* A. 当 int 为 32 位时，1 &lt;&lt; 32 是未定义的
* B. C. 参考 [ex2.67.c](ex2.67.c)

### 2.68 \*\*

写出具有如下原型的函数的代码：

```c
/*
 * Mask with least signficant n bits set to 1
 * Examples: n = 6 --> 0x3F, n = 17 --> 0x1FFFF
 * Assume 1 <= n <= w
 */
int lower_one_mask(int n);
```

函数应该遵循位级整数编码规则。要注意 n==w 的情况。

答案：[ex2.68.c](ex2.68.c)

### 2.69 \*\*\*

写出具有如下原型的函数的代码：

```c
/*
 * Do rotating right shift. Assume 0 <= n < w
 * Examples when x = 0x12345678 and w = 32:
 * n=4 -> 0x81234567, n=20 -> 0x45678123
 */
unsigned rotate_right(unsigned x, int n);
```

函数应该遵循位级整数编码规则。要注意 n==0 的情况。

答案：[ex2.69.c](ex2.69.c)

### 2.70 \*\*

写出具有如下原型的函数的代码：

```c
/*
 * Return 1 when x can be represented as an n-bit, 2’s complement
 * number; 0 otherwise
 * Assume 1 <= n <= w
 */
int fits_bits(int x, int n);
```

函数应该遵循位级整数编码规则。

答案：[ex2.70.c](ex2.70.c)

### 2.71 \*

你刚刚开始在一家公司工作，他们要实现一组过程来操作一个数据结构，要将 4 个有符号字节封装成一个 32 位 unsigned。
一个字中的字节从 0（最低有效字节）编号到 3（最高有效字节）。
分配给你的任务是：为一个使用补码运算和算术右移的机器编写一个具有如下原型的函数：

```c
/* Declaration of data type where 4 bytes are packed
   into an unsigned */
typedef unsigned packed_t;

/* Extract byte from word. Return as signed integer */
int xbyte(packed_t word, int bytenum);
```

也就是说，函数会抽取出指定的字节，再把它符号扩展为一个 32 位 int。
你的前任（因为水平不够而被解雇了）编写了下面的代码：

```c
/* Failed attempt at xbyte */
int xbyte(packed_t word, int bytenum)
{
    return (word >> (bytenum << 3)) & 0xFF;
}
```

* A. 这段代码错在哪里？
* B. 给出函数的正确实现，只能使用左右移位和一个减法。


答案：

* A. 没有将指定字节符号扩展成 32 位 int 类型。
* B. [ex2.71.c](ex2.71.c)

### 2.72 \*\*

给你一个任务，写一个函数，将整数 val 复制到缓冲区 buf 中，但是只有当缓冲区中有足够可用的空间时，才执行复制。

你写的代码如下：

```c
/* Copy integer into buffer if space is available */
/* WARNING: The following code is buggy */
void copy_int(int val, void *buf, int maxbytes) {
    if (maxbytes-sizeof(val) >= 0)
        memcpy(buf, (void *) &val, sizeof(val));
}
```

这段代码使用了库函数 memcpy。
虽然在这里使用这个函数有点刻意，因为我们只是想复制一个 int，但是它说明了一种复制较大数据结构的常见方法。

你仔细地测试了这段代码后发现，哪怕 maxbytes 很小的时候，它也能把值复制到缓冲区中。

* A. 解释为什么代码中的条件测试总是成功。**提示：** sizeof 运算符返回类型为 size\_t 的值。
* B. 你该如何重写这个条件测试，使之工作正确。

答案：

* A. sizeof 运算符返回类型为 size\_t（无符号整数类型），因此 maxbytes-sizeof(val) 的结果也是无符号整数类型，总是大于等于 0
* B. [ex2.72.c](ex2.72.c)

### 2.73 \*\*

写出具有如下原型的函数代码：

```c
/* Addition that saturates to TMin or TMax */
int saturating_add(int x, int y);
```

同正常的补码加法溢出的方式不同，当正溢出时，saturating_add 返回 **TMax**，负溢出时，返回 **TMin**。
这种运算常常用在执行数字信号处理的程序中。

函数应该遵循位级整数编码规则。

答案：[ex2.73.c](ex2.73.c)

### 2.74 \*\*

写出具有如下原型的函数的代码：

```c
/* Determine whether subtracted arguments will cause overflow */
int tsub_ovf(int x, int y);
```

如果计算 x-y 导致溢出，这个函数就返回 1。

答案 [ex2.74.c](ex2.74.c)

### 2.75 \*\*\*

假设我们想要计算 x ∙ y 的完整的 2w 位表示，其中，x 和 y 都是无符号数，并且运行在数据类型 unsigned 是 w 位的机器上。
乘积的低 w 位能够用表达式 x\*y 计算，所以，我们只需要一个具有下列原型的函数：

```c
unsigned int unsigned_high_prod(unsigned x, unsigned y);
```

这个函数计算无符号变量 x ∙ y 的高 w 位。

我们使用一个具有下面原型的库函数：

```c
int signed_high_prod(int x, int y);
```

它计算在 x 和 y 采用补码形式的情况下，x ∙ y 的高 w 位。
编写代码调用这个过程，以实现无符号数为参数的函数。
验证你的解答的正确性。

> **提示：** 看看等式（2-18）的推导中，有符号乘积 x ∙ y 和无符号乘积 x' ∙ y' 之间的关系。

答案：[ex2.75.c](ex2.75.c)

### 2.76 \*\*

假设我们有一个任务：生成一段代码，将整数变量 x 乘以不同的常数因子 K。
为了提高效率，我们想只使用 +、- 和 &lt;&lt; 运算。
对于下列 K 的值，写出执行乘法运算的 C 表达式，每个表达式中最多使用 3 个运算。

* A. K = 5
* B. K = 9
* C. K = 30
* D. K = -56

答案：[ex2.76.c](ex2.76.c)

### 2.77 \*\*

写出具有如下原型的函数的代码：

```c
/* Divide by power of two. Assume 0 <= k < w-1 */
int divide_power2(int x, int k);
```

该函数要用正确的舍入方式计算 x/2<sup>k</sup>，并且应该遵循位级整数编码规则。

答案：[ex2.77.c](ex2.77.c)

### 2.78 \*\*

写出函数 mul5div8 的代码，对于整数参数 x，计算 5\*x/8 的值，但是要遵循位级整数编码规则。你的代码计算 5\*x 也会产生溢出。

答案：[ex2.78.c](ex2.78.c)

### 2.79 \*\*

写出函数 fiveeigths 的代码，对于整数参数 x，计算 5/8x 的值，向零舍入。
它不会溢出。函数应该位级整数编码规则。

答案：[ex2.79.c](ex2.79.c)

### 2.80 \*\*

编写 C 表达式产生如下位模式，其中 a'' 表示符号 a 重复 n 次。
假设一个 w 位的数据类型。
你的代码可以包含对参数 m 和 n 的引用，它们分别表示 m 和 n 的值，但是不能使用表示 w 的参数。

* A. 1<sup>w-n-m</sup>0<sup>n</sup>。
* B. 0<sup>w-n-m</sup>1<sup>n</sup>0<sup>m</sup>。

答案：[ex2.80.c](ex2.80.c)

### 2.81 \*

我们在一个 int 类型值为 32 位的机器上运行程序。
这些值以补码形式表示，而且它们都是算术右移的。
unsigned 类型的值也是 32 位的。

我们产生随机数 x 和 y，并且把它们转换成无符号数，显示如下：

```c
/* Create some arbitrary values */
int x = random();
int y = random();
/* Convert to unsigned */
unsigned ux = (unsigned) x;
unsigned uy = (unsigned) y;
```

对于下列每个 C 表达式，你要指出表达式是否总是为 1。
如果它总是为 1，那么请描述其中的数学原理。
否则，列举一个使它为 0 的参数示例。

* A. (x&gt;y) == (-x&lt;-y)
* B. ((x+y)&lt;&lt;4) + y-x == 17\*y+15\*x
* C. ~x+~y == ~(x+y)
* D. (int)(ux-uy) == -(y-x)
* E. ((x &gt;&gt; 2) &lt;&lt; 2) &lt;= x

答案：

* A. 当 y = INT_MIN 时不成立（注意：-INT_MIN 是未定义的行为）
* B. 总是为真，根据乘以 2 的幂小结可知无论是否发生溢出，等式成立
* C. 当 x，y 等于 1 时不成立
* D. 总是为真，-(y-x) => (x-y)
* E. 总是为真，((x &gt;&gt; 2) &lt;&lt; 2) 相当于将最低的两位置为 0

参考代码 [ex2.81.c](ex2.81.c)

### 2.82 \*\*

一些数字的二进制表示是由形如 0.yyyyyy⋯ 的无穷串组成的，其中 y 是一个 k 位的序列。
例如 <math><mfrac><mn>1</mn><mn>3</mn></mfrac></math> 而二进制表示是 0.0101010101⋯(y=01)，
而 <math><mfrac><mn>1</mn><mn>5</mn></mfrac></math> 的二进制表示是 0.001100110011⋯(y=0011)。

* A. 设 Y=B2U<sub>k</sub>(y)，也就是说，这个数具有二进制表示 y。
给出一个由 Y 和 k 组成的公式表示这个无穷串的值。
**提示：**请考虑将二进制小数右移 k 位的结果。
* B. 对于下列 y 的值，串的数值是多少？
    * (a) 001
    * (b) 1001
    * (c) 000111

答案：

* A.
```
n = 0.yyyyy...
n << k = y.yyyyy... = Y + n
n << k - n = Y
n = Y/(2^k - 1)
```
* B.
    * (a) Y=1 k=3，n=1/7
    * (b) Y=9 k=4, n=9/15=3/5
    * (c) Y=7 k=6, n=7/63

### 2.83 \*

填写下列程序的返回值，这个程序是测试它的第一个参数是否大于或者等于第二个参数。
假定函数 f2u 返回一个无符号 32 位数字，其位表示与它的浮点参数相同。
你可以假设两个参数都不是 NaN。

两种 0，+0 和 -0 被认为是相等的。

```c
int float_ge(float x, float y) {
    unsigned ux = f2u(x);
    unsigned uy = f2u(y);
    /* Get the sign bits */
    unsigned sx = ux >> 31;
    unsigned sy = uy >> 31;

    /* Give an expression using only ux, uy, sx, and sy */
    return _________;
}
```

答案：[ex2.83.c](ex2.83.c)

### 2.84 \*

给定一个浮点格式，有 k 位指数和 n 位小数，对于下列数，写出阶码 E、尾数 M、小数 f 和值 V 的公式。
另外，请描述其位表示。

* A. 数 5.0。
* B. 能够被准确描述的最大奇整数。
* C. 最小的规格化数的倒数。

答案：

```
bias = 2^(k-1) - 1
V = 2^E * M
```

* A. 5.0 = 0b101.000…

M = 0b1.01, f = 0b0.01, E = 2, e = bias + E, V = 5.0

位表示

```
0 10....01 010....
```

* B

假设 bias » n

要得到最大的奇数，M 必定为 0b1.111111…,此时 f=0b0.111111…（n 个 1）

```
E = n, V = 0b1.111111…(n+1 个 1，M)*2^n = 2^(n+1) - 1
```

位表示

```
0 bias+n 11111....
```

* C

最小的规格化数：

M 为 0b1.000...，f=0b0.000...，E=1-bias

V=2^(1-bias)

其倒数为：

V=2^(bias-1)

M 为 0b1.000...，f=0b0.000...，E=bias-1，e=E+bias=2\*bias-1

位表示

```
0 11...101 0000....
```

### 2.85 \*

与 Intel 兼容的处理器也支持 “扩展精度” 浮点格式，这种格式具有 80 位字长，被分成 1 个符号位、k=15 个阶码位、1 个单独的整数位和 n=63 个小数位。
整数位是 IEEE 浮点表示中隐含位的显式副本。
也就是说，对于规格化的值它等于 1，对于非规格化的值它等于 0。
填写下表，给出用这种格式表示的一些 “有趣的” 数字的近似值。
\
<table>
  <tr><th rowspan=2>描述</th><th colspan=2>扩展精度</th></tr>
  <tr><th>值</th><th>十进制</th></tr>
  <tr><td>最小的正非规格化数</td><td></td><td></td></tr>
  <tr><td>最小的正规格化数</td><td></td><td></td></tr>
  <tr><td>最大的规格化数</td><td></td><td></td></tr>
</table>

答案：

```c
bias = 2^(15-1) - 1=16383
```

<table>
  <tr><th rowspan=2>描述</th><th colspan=2>扩展精度</th></tr>
  <tr><th>值</th><th>十进制</th></tr>
  <tr><td>最小的正非规格化数</td><td>0 0000…(15) 0 000…(62)1</td><td>2<sup>(1-bias-63)
</sup>=2<sup>-63-2<sup>15-1</sup>+2</sup>=2<sup>-16,445</sup></td></tr>
  <tr><td>最小的正规格化数</td><td>0 000…(14)1 0 000…(62)0</td><td>2<sup>1-bias</sup>=2<sup>1-(2<sup>15-1</sup>-1)</sup>=2<sup>-16382</sup></td></tr>
  <tr><td>最大的规格化数</td><td>0 111…(14)0 0 1111…(63)</td><td>(2-2<sup>-63</sup>)*2<sup>16383</sup>=(1-2<sup>-64</sup>)*2<sup>16384</sup></td></tr>
</table>

### 2.86 \*

考虑一个基于 IEEE 浮点格式的 16 位浮点表示，它具有 1 个符号位、7 个阶码位（k=7）和 8 个小数位（n=8）。
阶码偏置量是 2<sup>7-1</sup>-1=63。

对于每个给定的数，填写下表，其中，每一列具有如下指示说明：

* Hex：描述编码形式的 4 个十六进制数字。
* M：尾数的值。这应该是一个形如 x 或 <math><mfrac><mi>x</mi><mi>y</mi></mfrac></math> 的数，其中 x 是一个整数，而 y 是 2 的整数幂。
例如：0、<math><mfrac><mn>67</mn><mn>64</mn></mfrac></math> 和 <math><mfrac><mn>1</mn><mn>256</mn></mfrac></math>。
* E：阶码的整数值。
* V：所表示的数字值。使用 x 或者 x\*2<sup>z</sup> 表示，其中 x 和 z 都是整数。

举一个例，为了表示 <math><mfrac><mn>7</mn><mn>2</mn></mfrac></math>，我们有 s=0，M=<math><mfrac><mn>7</mn><mn>4</mn></mfrac></math> 和 E=1。
因此这个数的阶码字段为 0x40（十进制值 63+1=64）,尾数字段为 0xC0（二进制 11000000<sub>2</sub>），得到一个十六进制的表示 40C0。

标记为“—”的条目不用填写。

|描述|Hex|_M_|_E_|_V_|
|-|-|-|-|-|
|-0||||—|
|最小的值&gt;1|||||
|256||||—|
|最大的非规格化数|||||
|-∞||—|—|—|
|十六进制表示为 3AA0 的数|—||||

答案：

|描述|Hex|_M_|_E_|_V_|
|-|-|-|-|-|
|-0|0x8000|0|0|—|
|最小的值&gt;1|0x3F01|257/256|0|257/256|
|256|0x4700|0|8|—|
|最大的非规格化数|0x00FF|255/256|2<sup>-62</sup>|255/(2<sup>70</sup>)|
|-∞|0xFF00|—|—|—|
|十六进制表示为 3AA0 的数|—|5/8|-5|5/256|

### 2.87 \*\*

考虑下面两个基于 IEEE 浮点格式的 9 位浮点表示。

1. 格式 A
    * 有一个符号位。
    * 有 k=5 个阶码位。阶码偏置值是 15。
    * 有 n=3 个小数位。
2. 格式 B
    * 有一个符号位。
    * 有 k=4 个阶码位。阶码偏置值是 7。
    * 有 n=4 个小数位。

下面给出了一些格式 A 表示的位模式，你的任务是把它们转换成最接近的格式 B 表示的数。
如果需要舍入，你要向 +∞ 舍入。
另外，给出用格式 A 和 格式 B 表示的位模式对应的值。
要么是整数（例如，17），要么是小数（例如，17/64 或 17/2<sup>6</sup>）。

<table>
  <tr><th colspan=2>格式 A</th><th colspan=2>格式 B</th></tr>
  <tr><th>位</th><th>值</th><th>位</th><th>值</th></tr>
  <tr><td> 1 01110 001</td><td><math><mfrac><mn>-9</mn><mn>16</mn></mfrac></math><td>1 0110 0010</td><td><math><mfrac><mn>-9</mn><mn>16</mn></mfrac></math></td></tr>
  <tr><td>0 10110 101</td><td></td><td></td><td></td></tr>
  <tr><td>1 00111 110</td><td></td><td></td><td></td></tr>
  <tr><td>0 00000 101</td><td></td><td></td><td></td></tr>
  <tr><td>1 11011 000</td><td></td><td></td><td></td></tr>
  <tr><td>0 11000 100</td><td></td><td></td><td></td></tr>
</table>

答案：

<table>
  <tr><th colspan=2>格式 A</th><th colspan=2>格式 B</th></tr>
  <tr><th>位</th><th>值</th><th>位</th><th>值</th></tr>
  <tr><td> 1 01110 001</td><td><math><mfrac><mn>-9</mn><mn>16</mn></mfrac></math><td>1 0110 0010</td><td><math><mfrac><mn>-9</mn><mn>16</mn></mfrac></math></td></tr>
  <tr><td>0 10110 101</td><td>208</td><td>0 1110 1010</td><td>208</td></tr>
  <tr><td>1 00111 110</td><td>-7*2<sup>-10</sup></td><td>1 0000 0111</td><td>-7*2<sup>-10</sup></td></tr>
  <tr><td>0 00000 101</td><td>5*2<sup>-17</sup></td><td>0 0000 0000</td><td>0</td></tr>
  <tr><td>1 11011 000</td><td>-2<sup>12</sup></td><td>1 1110 1111</td><td>-31*2<sup>3</sup></td></tr>
  <tr><td>0 11000 100</td><td>3*2<sup>8</sup></td><td>0 1111 0000</td><td>+∞</td></tr>
</table>

### 2.88 \*

我们在一个 int 类型为 32 位补码表示的机器上运行程序。
float 类型的值使用 32 位 IEEE 格式，而 double 类型的值使用 64 位 IEEE 格式。

我们产生随机整数 x、y 和 z，并且把它们转换成 double 类型的值：

```c
/* Create some arbitrary values */
int x = random();
int y = random();
int z = random();
/* Convert to double */
double dx = (double) x;
double dy = (double) y;
double dz = (double) z;
```

对于下列的每个 C 表达式，你要指出表达式是否总是为 1。
如果它总是为 1，描述其中的数学原理。
否则，列举出使它为 0 的参数的例子。
请注意，不用使用 IA32 机器运行 GCC 来测试你的答案，因为对于 float 和 double，它使用的都是 80 位的扩展精度表示。

* A. (float) x == (float) dx
* B. dx + dy == (double) (x+y)
* C. dx + dy + dz == dz + dy + dx
* D. dx \* dy \* dz == dz \* dy \* dx
* E. dx / dx == dz / dz

答案：[ex2.88.c](ex2.88.c)

### 2.89 \*

分配给你一个任务，编写一个 C 函数来计算 2<sup>x</sup> 的浮点表示。
你意识到完成这个任务的最好方法是直接创建结果的 IEEE 单精度表示。
当 x 太小时，你的程序将返回 0.0。
当 x 太大时，它会返回 +∞。
填写下列代码的空白部分，以计算出正确的结果。
假设函数 u2f 返回的浮点值与它的无符号参数有相同的位表示。

```c
float fpwr2(int x) {
    /* Result exponent and fraction */
    unsigned exp, frac;
    unsigned u;

    if (x < _______) {
        /* Too small. Return 0.0 */
        exp = _______;
        frac = _______;
    } else if (x < _______) {
        /* Denormalized result */
        exp = _______;
        frac = _______;
    } else if (x < _______) {
        /* Normalized result. */
        exp = _______;
        frac = _______;
    } else {
        /* Too big. Return +oo */
        exp = _______;
        frac = _______;
    }

    /* Pack exp and frac into 32 bits */
    u = exp << 23 | frac;
    /* Return as float */
    return u2f(u);
}
```

答案：[ex2.89.c](ex2.89.c)

### 2.90 \*

大约在公元前 250 年，希腊数学家阿基米德证明了 <math><mfrac><mn>223</mn><mn>71</mn></mfrac></math> &lt; π &lt; <math><mfrac><mn>22</mn><mn>7</mn></mfrac></math>。
如果当时有一台计算机和标准库 &lt;math.h&gt;，他就能够确定 π 的单精度浮点近似值的十六进制表示为 0x40490FDB。
当然，所有的这些都只是近似值，因为 π 不是有理数。

* A. 这个浮点值表示的二进制小数是多少？
* B. <math><mfrac><mn>22</mn><mn>7</mn></mfrac></math> 的二进制小数表示是什么？**提示：** 参见家庭作业 2.82
* C. 这两个 π 的近似值从哪一位（相对于二进制小数点）开始不同的？

答案：

* A. 0 10000000 100 1001 0000 1111 1101 1011
* B.
小数部分为 1/7 根据 2.82 有： n=Y/(2^k-1)，Y=1，k=3，得到 yyy 为 001。
22/7 的二进制表示为 11.001001001...
* C. 22/7 的单精度浮点数二进制表示为：
0 10000000 100 1001 0010 0100 1001 0010
</br>
从二进制小数点后第9位开始不同

### 位级浮点编码规则

在接下来的题目中，你要写的代码要实现浮点函数在浮点数的位级表示上直接运算。
你的代码应该完全遵循 IEEE 浮点运算的规则，包括当需要舍入时，要使用向偶数舍入的方式。
为此，我们定义数据类型 float-bits 等价于 unsigned：

```c
/* Access bit-level representation floating-point number */
typedef unsigned float_bits;
```

你的代码不使用数据类型 float，而要使用 float_bits。
你可以使用数据类型 int 和 unsigned，包括无符号和整数常数和运算。
你不可以使用任何联合、结构和数组。
更重要的是，你不能使用任何浮点数据类型、运算或者常数。
取而代之的是，你的代码应该执行实现这些指定的浮点运算的位操作。
下面的函数说明了对这些规则的使用。
对于参数 _f_，如果 _f_ 是非规格化的，该函数函数 <math><mfrac><mi>+</mi><mi>-</mi></mfrac></math>0（保持 _f_ 的符号），否则，返回 _f_。

```c
/* If f is donorm, return 0. Otherwise, return f */
float_bits float_denorm_zero(float_bits f) {
    /* Decompose bit representation into parts */
    unsigned sign = f>>31;
    unsigned exp = f>>23 & 0xFF;
    unsigned frac = f & 0x7FFFFF;
    if (exp == 0) {
        /* Denormalized. Set fraction to 0 */
        frac = 0;
    }
    /* Reassemble bits */
    return (sign << 31) | (exp << 23) | frac;
}
```

### 2.91 \*

遵循位级浮点编码规则，实现具有如下原型的函数：

```c
/* Compute |f|. If f is NaN, then return f. */
float_bits float_absval(float_bits f);
```

对于浮点数 _f_，这个函数计算 |_f_|。
如果 _f_ 是 NaN，你的函数应该简单地返回 _f_。

测试你的函数，对参数 _f_ 可以取的所有 2<sup>32</sup> 个值求值，将结果与你使用机器的浮点运算得到的结果相比较。

答案：[ex2.91.c](ex2.91.c)

### 2.92 \*\*

遵循位级浮点编码规则，实现具有如下原型的函数：

```c
/* Compute -f. If f is NaN, then return f. */
float_bits float_negate(float_bits f);
```

对于浮点数 _f_，这个函数计算 -_f_。
如果 _f_ 是 NaN，你的函数应该简单地返回 _f_。

测试你的函数，对参数 _f_ 可以取的所有 2<sup>32</sup> 个值求值，将结果与你使用机器的浮点运算得到的结果相比较。

答案：[ex2.92.c](ex2.92.c)

### 2.93 \*\*\*

遵循位级浮点编码规则，实现具有如下原型的函数：

```c
/* Compute 0.5*f. If f is NaN, then return f */
float_bits float_half(float_bits f);
```

对于浮点数 f, 这个函数计算 0.5 ∙ _f_。
如果 _f_ 是 NaN，你的函数应该简单地返回 _f_。
测试你的函数，对参数 _f_ 可以取的所有 2<sup>32</sup> 个值求值，将结果与你使用机器的浮点运算得到的结果相比较。

答案：[ex2.93.c](ex2.93.c)

### 2.94 \*\*\*

遵循位级浮点编码规则，实现具有如下原型的函数：

```c
/* Compute 2*f. If f is NaN, then return f */
float_bits float_twice(float_bits f);
```

对于浮点数 f, 这个函数计算 2 ∙ _f_。
如果 _f_ 是 NaN，你的函数应该简单地返回 _f_。
测试你的函数，对参数 _f_ 可以取的所有 2<sup>32</sup> 个值求值，将结果与你使用机器的浮点运算得到的结果相比较。

答案：[ex2.94.c](ex2.94.c)

### 2.95 \*\*\*\*

遵循位级浮点编码规则，实现具有如下原型的函数：

```c
/* Compute (float) i */
float_bits float_i2f(int i);
```

对于参数 i，这个函数计算 (float) i 的位级表示。
测试你的函数，对参数 _f_ 可以取的所有 2<sup>32</sup> 个值求值，将结果与你使用机器的浮点运算得到的结果相比较。

答案：

需要对 float 和 int 的二进制表示有深刻理解，bias=127，e的范围是127~157，都是规格化数

int 的范围是 -2^31~(2^31)-1

对于负数 x，将符号位置成 1，x=-x，其他按正数相同逻辑处理，下面是正数处理流程

找出 int 的最左侧的 1 所在的位置，就可以得到 E 的值，e=E+bias，截取最左侧 1 右边的数 frac 作为小数值，并且截断至 23位，若右侧不足 23 位则在右侧补足到23位
若超出 23 位则需要考虑向偶数舍入，假设要截断的是 n 位二进制数，如果要截断的数字大于 10..0(n-1)，等需要进位，
若刚好等于 10..0(n-1)，则需要考虑 frac 的第23位是否等于1，若等于1则需要进位

方法1：[ex2.95.c](ex2.95.c)
方法2：[ex2.95-2.c](ex2.95-2.c)

### 2.96 \*\*\*\*

遵循位级浮点编码规则，实现具有如下原型的函数：

```c
/*
 * Compute (int) f
 * If conversion causes overflow or f is NaN, return 0x80000000
 */
int float_f2i(float_bits f);
```

对于浮点数 _f_，这个函数计算 (int) _f_。
你的函数应该向零舍入。如果 _f_ 不能用整数表示（例如，超过表示范围，或者它是一个 NaN），那么函数应该返回 0x80000000。
测试你的函数，对参数 _f_ 可以取的所有 2<sup>32</sup> 个值求值，将结果与你使用机器的浮点运算得到的结果相比较。

答案：

根据浮点数定义，非规格数都转成 0，无穷和 NaN 都转成 0x80000000

规格化数中 exp 大于 127+30 的转成 0x80000000，exp &lt; 127 的转成 0，exp 在 [127, 157] 之间的转成对应的整数。
转换规则如下：

先去小数部分 frac = f & 0x7FFFFF; 在加上浮点数定义中的前导 1，frac = 0x800000 | frac; 此时小数点在第23位。
e=exp-127，根据 e 是否 &ge; 23 确定要进行的操作。

* 等于 23 表示小数点需要右移 23 位，直接将 frac 转换成整数，int i = (int) frac; 然后再根据 f 的符号确定最终结果即可。
* 大于 23 则需要将 frac &lt;&lt; (e - 23)，再将其转成整数 int i = (int) frac; 然后再根据 f 的符号确定最终结果即可。
* 小于 23 则需要将 frac &gt;&gt; (23 - e)，再将其转成整数 int i = (int) frac; 然后再根据 f 的符号确定最终结果即可。

[ex2.96.c](ex2.96.c)