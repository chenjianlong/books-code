# 第9章 虚拟存储器

## 练习题

### 练习题 9.1

完成下面的表格，填写缺失的条目，并且用适当的整数取代每个问号。
利用下列单位: K=2<sup>10</sup> (千), M=2<sup>20</sup>(兆,百万), G=2<sup>30</sup>(千兆，十亿)，T=2<sup>40</sup>(万亿)，
P=2<sup>50</sup>(千千兆)，或 E=2<sup>60</sup>(千兆兆)。

|虚拟地址位数(n)|虚拟地址数(N)|最大可能的虚拟地址|
|-|-|-|
|8|||
||2<sup>?</sup>=64K||
|||2<sup>32</sup> - 1 = ?G - 1|
||2<sup>?</sup>=256T||
|64|||

答：

|虚拟地址位数(n)|虚拟地址数(N)|最大可能的虚拟地址|
|-|-|-|
|8|2<sup>8</sup>=256|255|
|16|2<sup>16</sup>=64K|2<sup>16</sup>-1=64K-1|
|32|2<sup>32</sup>=4G|2<sup>32</sup>-1=4G-1|
|48|2<sup>48</sup>=256T|2<sup>48</sup>-1=256T-1|
|64|2<sup>64</sup>=16E|2<sup>64</sup>-1=16E-1|

### 练习题 9.2

确定下列虚拟地址大小(n)和页大小(P)的组合所需要的 PTE 数量:

|n|P=2<sup>p</sup>|# PTE#
|-|-|-|
|16|4K||
|16|8K||
|32|4K||
|32|8K||

答：

|n|P=2<sup>p</sup>|# PTE#
|-|-|-|
|16|4K|2<sup>4</sup>=16|
|16|8K|2<sup>3</sup>=8|
|32|4K|2<sup>20</sup>|
|32|8K|2<sup>19</sup>|

### 练习题 9.3

给定一个32位的虚拟地址空间和一个24位的物理地址，对于下面的页面大小P，确定 VPN、VPO、PPN和PPO中的位数:

|P|# VPN位|# VPO位|# PPN位|# PPO位|
|-|-|-|-|-|
|1KB|||||
|2KB|||||
|4KB|||||
|8KB|||||

附录：

<table>
  <thead>
    <tr><th colspan="2">基本参数</th></tr>
    <tr><th>符号</th><th>描述</th></tr>
  </thead>
  <tbody>
    <tr><td>N=2<sup>n</sup></td><td>虚拟地址空间中的地址数量</td></tr>
    <tr><td>M=2<sup>m</sup></td><td>物理地址空间中的地址数量</td></tr>
    <tr><td>P=2<sup>p</sup></td><td>页的大小（字节）</td></tr>
  </tbody>
</table>

<table>
  <thead>
    <tr><th colspan="2">虚拟地址（VA）的组成部分</th></tr>
    <tr><th>符号</th><th>描述</th></tr>
  </thead>
  <tbody>
    <tr><td>VPO</td><td>虚拟页面偏移量（字节）</td></tr>
    <tr><td>VPN</td><td>虚拟页号</td></tr>
    <tr><td>TLBI</td><td>TLB索引</td></tr>
    <tr><td>TLBT</td><td>TLB标记</td></tr>
  </tbody>
</table>

<table>
  <thead>
    <tr><th colspan="2">物理地址（PA）的组成部分</th></tr>
    <tr><th>符号</th><th>描述</th></tr>
  </thead>
  <tbody>
    <tr><td>PPO</td><td>物理页面偏移量（字节）</td></tr>
    <tr><td>PPN</td><td>物理页号</td></tr>
    <tr><td>CO</td><td>缓冲块内的字节偏移量</td></tr>
    <tr><td>CI</td><td>高速缓存索引</td></tr>
    <tr><td>CT</td><td>高速缓存标记</td></tr>
  </tbody>
</table>

**图 9-11 地址翻译符号小结**

答：

|P|# VPN位|# VPO位|# PPN位|# PPO位|
|-|-|-|-|-|
|1KB|22|10|14|10|
|2KB|21|11|13|11|
|4KB|20|12|12|12|
|8KB|19|13|11|13|