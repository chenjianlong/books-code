# 陈天 Rust 编程第一课

## 基础篇

### 03 初窥门径：从你的第一个Rust程序开始！

* [hello world](03_grammar/hello_world/)
* [第一个实用的 Rust  程序](03_grammar/scrape_url/)
* [函数作为参数](03_grammar/apply/)
* [返回值类型](03_grammar/pi/)
* [数据结构](03_grammar/user/)
* [控制流程](03_grammar/fib/)
* [思考题1](03_grammar/fib2/)
* [思考题2](03_grammar/scrape_url2/)

### 04 get hands dirty：来写个实用的CLI小工具

* [HTTPie命令行解析](04_httpie/httpie1/)
* [HTTPie添加参数验证](04_httpie/httpie2/)
* [HTTPie添加主体功能](04_httpie/httpie3/)
* [HTTPie添加高亮显示](04_httpie/httpie4/)
* [HTTPie body 显示优化](04_httpie/httpie5/)

### 05 get hands dirty：做一个图片服务器有多难？

* [Thumbor](05_thumbor/thumbor/)

### 06 gethandsdirty：SQL查询工具怎么一鱼多吃？

* [queryer](06_queryer/queryer)
* [queryer-js](06_queryer/queryer-js)
* [queryer-py](06_queryer/queryer-py)
* [data-viewer](06_queryer/data-viewer)


### 07 所有权：值的生杀大权到底在谁手上？

* [ownership](07_ownership)

#### 思考题

1. 在 Rust 下，分配在堆上的数据结构可以引用栈上的数据么？为什么？

可以，只要栈上的属生命周期大于堆上数据的生命周期就可以，简单的例子可以看代码 heap_ref_stack.rs

2. main() 函数传递给 find\_pos() 函数的另一个参数 v，也会被移动吧？为什么图上并没有将其标灰？

不会，参数 v 是基本数据类型 u32，实现了 Copy trait

### 08 所有权：值的借用是如何工作的？

* [borrow](08_borrow)

为了保证内存安全，Rust 对可变引用的使用做了严格的约束：

1. 在一个作用域内，仅允许一个活跃的可变引用
2. 活跃的可变引用（写）和只读引用（读）是互斥的，不能同时存在

小结：

1. 一个值在同一时刻只有一个所有者。当所有者离开作用域，其拥有的值会被丢弃。赋值或者传参会导致值 Move，所有权被转移，一旦所有权转移，之前的变量就不能访问
2. 如果值实现了 Copy trait，那么赋值或传参会使用 Copy 语义，相应的值会被按位拷贝，产生新的值
3. 一个值可以有多个只读引用
4. 一个值可有唯一一个活跃的可变引用。可变引用和只读引用是互斥的关系，就像并发下数据的读写互斥那样
5. 引用的生命周期不能超出值的生命周期

![](images/values_under_scoped.jpg)

#### 思考题

1. 上一讲我们在讲 Copy trait 时说道，可变引用没有实现 Copy trait。结合这一讲的内容，想想为什么？

可变引用如果可以 Copy 就违背了一个值可有唯一一个活跃的可变引用的约束

2. 下面这段代码，如何修改才能使其编译通过，避免同时有只读引用和可变引用？

```rust
fn main() {
    let mut arr = vec![1, 2, 3];
    // cache the last item
    let last = arr.last();
    arr.push(4);
    // consume previously stored last item
    println!("last: {:?}", last);
}
```

方法一：克隆最后一个元素
方法二：打印 last 后，再push

详细请看代码 exam.rs

### 09 所有权：一个值可以有多个所有者么？

* [multi owner](09_multi_owner)

外部可变性和内部可变性的区别：

||**使用方法**|**所有权检查**|
|-|-|-|
|**外部可变性**|let mut或者 &mut|编译时，如果不符合规则，产生编译错误|
|**内部可变性**|使用 Cell/RefCell|运行时，如果不符合规则，产生 panic|

Rc/Arc 是不可变的，如果想要修改内部的数据，**需要引入内部可变性**，在单线程环境下，可以在 Rc 内部使用 RefCell；在多线程环境下，可以使用 Arc 嵌套 Mutex 或者 RwLock 的方法。

<table>
    <thead>
        <tr>
            <th colspan=2>访问方式</th>
            <th>数据</th>
            <th>不可变借用</th>
            <th>可变借用</th>
        </tr>
    </thead>
    <tbody>
        <tr>
            <td colspan=2>单一所有权</td>
            <td>T</td>
            <td>&T</td>
            <td>&mut T</td>
        </tr>
        <tr>
            <td rowspan=5>共享所有权</td>
            <td rowspan=2>单线程</td>
            <td>Rc&lt;T&gt;</td>
            <td>&Rc&lt;T&gt;</td>
            <td>无法得到可变借用</td>
        </tr>
        <tr>
            <td>Rc&lt;RefCell&lt;T&gt;&gt;</td>
            <td>v.borrow()</td>
            <td>v.borrow_mut()</td>
        </tr>
        <tr>
            <td rowspan=3>多线程</td>
            <td>Arc&lt;T&gt;</td>
            <td>&Arc&lt;T&gt;</td>
            <td>无法得到可变借用</td>
        </tr>
        <tr>
            <td>Arc&lt;Mutex&lt;T&gt;&gt;</td>
            <td>v.lock()</td>
            <td>v.lock()</td>
        </tr>
        <tr>
            <td>Arc&lt;RwLock&lt;T&gt;&gt;</td>
            <td>v.read()</td>
            <td>v.write()</td>
        </tr>
    </tbody>
</table>

#### 思考题

1. 运行下面的代码，查看错误，并阅读 std::thread::spawn 的文档，找到问题原因后，修改代码使其编译通过。

```rust
fn main() {
    let arr = vec![1];

    std::thread::spawn(|| {
        println!(":?", arr);
    });
}
```

答案：使用 move，具体请看 exam1.rs

2. 你可以写一段代码，在 main() 函数里生成一个字符串，然后通过 std::thread::spawn 创建一个线程，让 main() 函数所在的主线程和新的线程共享这个字符串么？提示：使用 std::sync::Arc。

答案：具体请看 exam2.rs

3. 我们看到了 Rc 的 clone() 方法的实现：

```rust
fn clone(&self) -> Rc<T> {
    // 增加引用计数
    self.inner().inc_strong();
    // 通过 self.ptr 生成一个新的 Rc 结构
    Self::from_inner(self.ptr);
}
```

你有没有注意到，这个方法传入的参数是 &self，是个不可变引用，然而它调用了 self.inner().inc_string()，光看函数名字，它用来增加 self 的引用计数，可是，为什么这里对 self 的不可变引用可以改变 self 的内部数据呢？

答：这里引入了内部可变性，inner() 获取了 RcBox&lt;T&gt;，而 inc\_strong 的实现为：

```rust
#[inline]
fn inc_strong(&self) {
    let strong = self.strong();

    // We insert an `assume` here to hint LLVM at an otherwise
    // missed optimization.
    // SAFETY: The reference count will never be zero when this is
    // called.
    unsafe {
        hint::assert_unchecked(strong != 0);
    }

    let strong = strong.wrapping_add(1);
    self.strong_ref().set(strong);

    // We want to abort on overflow instead of dropping the value.
    // Checking for overflow after the store instead of before
    // allows for slightly better code generation.
    if core::intrinsics::unlikely(strong == 0) {
        abort();
    }
}
```

strong 为 Cell&lt;T&gt;，是内部可变的，可以使用 set 函数改变内部的引用计数

### 10 生命周期：你创建的值究竟能活多久？

* [lifetime](10_lifetime)

### 11 内存管理：从创建到消亡，值都经历了什么？

* [memory](11_memory)

### 12 类型系统：Rust的类型系统有什么特点？

* [type system](12_type_system)

### 13 类型系统：如何使用trait来定义接口？

* [traits](13_traits)

### 14 类型系统：有哪些必须掌握的Trait？

* [sys\_traits](14_sys_traits)

#### Send/Sync

Send/Sync 是 Rust 并发安全的基础:

* 如果一个类型 T 实现了 Send trait，意味着 T 可以安全地从一个线程移动到另一个线程也就是说所有权可以在线程间移动。
* 如果一个类型 T实现了 Sync trait，则意味着 &T 可以安全地在多个线程中共享。一个类型T 满足 Sync trait，当且仅当 &T 满足 Send trait。

对于 Send/Sync 在线程安全中的作用，可以这么看，**如果一个类型 T::Send，那么T在某个线程中的独占访问是线程安全的;如果一个类型T::Sync，那么T在线程间的只读共享是安全的。**

#### 思考题

1. Vec\<T\> 可以实现 Copy trait 么？为什么？

不可以，Vec 含有指向了堆数据的指针，并且假定了对堆数据拥有所有权，当 drop Vec 时，它会回收相应的堆数据，实现 Copy 会导致多个 Vec 实例 drop 时对堆数据进行回收。

2. 在使用 Arc\<Mutex\<T\>\> 时，为什么下面这段代码可以直接使用 shared\.lock()?

```rust
use std::sync::{Arc, Mutex};
let shared = Arc::new(Mutex::new(1));
let mut g = shared.lock().unwrap();
*g += 1;
```

Arc 实现了 Deref trait

3. 有余力的同学可以尝试一下，为下面的 List\<T\> 类型实现 Index，使得所有的测试都能 通过。这段代码使用了 std::collections::LinkedList，你可以参考官方文档阅读它支持的方法

```rust
use std::{
    collections::LinkedList,
    ops::{Deref, DerefMut, Index},
};

struct List<T>(LinkedList<T>);

impl<T> Deref for List<T> {
    type Target = LinkedList<T>;
    fn deref(&self) -> &Self::Target {
        &self.0
    }
}

impl<T> DerefMut for List<T> {
    fn deref_mut(&mut self) -> &mut Self::Target {
        &mut self.0
    }
}

impl<T> Default for List<T> {
    fn default() -> Self {
        Self(Default::default())
    }
}

impl<T> Index<isize> for List<T> {
    type Output = T;
    fn index(&self, index: isize) -> &Self::Output {
        todo!();
    }
}

#[test]
fn it_works() {
    let mut list: List<u32> = List::default();
    for i in 0..16 {
        list.push_back(i);
    }

    assert_eq!(list[0], 0);
    assert_eq!(list[5], 5);
    assert_eq!(list[15], 15);
    assert_eq!(list[16], 0);
    assert_eq!(list[-1], 15);
    assert_eq!(list[128], 0);
    assert_eq!(list[-128], 0);
}
```

### 15 数据结构：这些浓眉大眼的结构竟然都是智能指针？

* [smart\_pointers](15_smart_pointers)

