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