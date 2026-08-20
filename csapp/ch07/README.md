# 第7章 链接

## 练习题

### 练习题 7.1

这个题目是关于 图7-1b 中的 `swap.o` 模块。
对于每个在 `swap.o` 中定义或引用的符号,请指出它是否在模块 `swap.o` 中的 `.symtab` 节中有一个符号表条目。
如果是，请指出定义该符号的模块(`swap.o` 或者 `main.o`)、符号类型(本地、全局或者外部)和它在模块中占据的节(`.text`、`.data` 或者 `.bss`)。

|符号|`swap.o` `.symtab` 条目?|符号类型|在哪个模块中定义|节|
|-|-|-|-|-|
|buf|||||
|bufp0|||||
|bufp1|||||
|swap|||||
|temp|||||

附录：

```c
/* main.c */
void swap();

int buf[2] = {1, 2};

int main()
{
    swap();
    return 0;
}
```

```c
/* swap.c */
extern int buf[];

int *bufp0 = &buf[0];
int *bufp1;

void swap()
{
    int temp;

    bufp1 = &buf[1];
    temp = *bufp0;
    *bufp0 = *bufp1;
    *bufp1 = temp;
}
```

图 7.1

答：

|符号|`swap.o` `.symtab` 条目?|符号类型|在哪个模块中定义|节|
|-|-|-|-|-|
|buf|是|外部|`main.o`|`.data`|
|bufp0|是|全局|`swap.o`|`.data`|
|bufp1|是|全局|`swap.o`|`.bss`|
|swap|是|全局|`swap.o`|`.text`|
|temp|否|-|-|-|