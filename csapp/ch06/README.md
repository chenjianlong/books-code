# 第6章 存储器层次结构

## 练习题

### 练习题 6.1

接下来，设 r 表示一个 DRAM 阵列中的行数，c 表示列数，b<sub>r</sub> 表示行寻址所需的位数，b<sub>c</sub> 表示列寻址所需的位数。
对于下面每个 DRAM，确定 2 的幂数的阵列维数，使得 max(b<sub>r</sub>, b<sub>c</sub>) 最小，max(b<sub>r</sub>, b<sub>c</sub>) 是对阵列的行或者列寻址所需的位数中较大的值。

|组织|r|c|b<sub>r</sub>|b<sub>c</sub>|max(b<sub>r</sub>, b<sub>c</sub>)|
|-|-|-|-|-|-|
|16×1||||||
|16×4||||||
|128×8||||||
|512×4||||||
|1024×4||||||

答案：

|组织|r|c|b<sub>r</sub>|b<sub>c</sub>|max(b<sub>r</sub>, b<sub>c</sub>)|
|-|-|-|-|-|-|
|16×1|4|4|2|2|2|
|16×4|4|4|2|2|2|
|128×8|16|8|4|3|4|
|512×4|32|16|5|4|5|
|1024×4|32|32|5|5|5|

### 练习题 6.2

计算这样一个磁盘的容量，它有 2 个盘片，10000 个柱面，每条磁道平均有 400 个扇区，而每个扇区有 512 个字节。

答案：

512 \* 400 \* 10000 \* 2 \* 2 = 8192000000 ≈ 8.19G

### 练习题 6.3

估计访问下面这个磁盘上一个扇区的访问时间（以 ms 为单位）：

|参数|值|
|-|-|
|旋转速率|15 000RPM|
|T<sub>avg seek</sub>|8ms|
|每条磁道的平均扇区数|500|

答案：

最大旋转延迟为：

<math display="block">
  <mrow>
    <msub><mtext>T</mtext><mtext>max rotation</mtext></msub>
    <mo>=</mo>
    <mfrac>
      <mn>1</mn>
      <mtext>RPM</mtext>
    </mfrac>
    <mo>×</mo>
    <mfrac>
      <mrow>
        <mn>60</mn><mtext>secs</mtext>
      </mrow>
      <mrow>
        <mn>1</mn><mtext>min</mtext>
      </mrow>
    </mfrac>
  </mrow>
</math>

平均旋转时间 T<sub>avg rotation</sub> 是 T<sub>max rotation</sub> 的一半。

一个扇区以秒为单位的平均传送时间如下：


<math display="block">
  <mrow>
    <msub><mtext>T</mtext><mtext>avg transfer</mtext></msub>
    <mo>=</mo>
    <mfrac>
      <mn>1</mn>
      <mtext>RPM</mtext>
    </mfrac>
    <mo>×</mo>
    <mfrac>
      <mn>1</mn>
      <mrow>
          <mo>(</mo><mtext>平均扇区数</mtext><mo>/</mo><mtext>磁道</mtext><mo>)</mo>
      </mrow>
    </mfrac>
    <mo>×</mo>
    <mfrac>
      <mrow>
        <mn>60</mn><mtext>secs</mtext>
      </mrow>
      <mrow>
        <mn>1</mn><mtext>min</mtext>
      </mrow>
    </mfrac>
  </mrow>
</math>

平均旋转时间为：

T<sub>avg rotation</sub>=1/2×(60/15000RPM)×1000ms/sec=2ms

平均传送时间为：

T<sub>avg transfer</sub>=60/15000RPM × 1/500扇区/磁道 × 1000ms/sec ≈ 0.008ms
整个估计的访问时间为：

T<sub>access</sub>=T<sub>avg seek</sub>+T<sub>avg rotation</sub>+T<sub>avg transfer</sub>=8ms+2ms+0.008ms≈10ms

### 练习题 6.4

假设 1MB 的文件由 512 个字节的逻辑块组成，存储在具有如下特性的磁盘驱动器上：

|参数|值|
|-|-|
|旋转速率|10 000RPM|
|T<sub>avg seek</sub>|5 ms|
|平均扇区数/磁道|1000|
|表面|4|
|扇区大小|512 字节|

对于下面的情况，假设程序顺序地读文件的逻辑块，一个接一个，将 读/写 头定位到第一块上的时间是 T<sub>avg seek</sub>+T<sub>avg rotation</sub>。

* A. 最好的情况：给定逻辑块到磁盘扇区的最好的可能的映射（即顺序的），估计读这个文件需要的最优时间（以 ms 为单位）。
* B. 随机的情况：如果块是随机地映射到磁盘扇区的，估计读这个文件需要的时间（以 ms 为单位）。

