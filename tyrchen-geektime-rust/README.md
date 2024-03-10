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

### 08 所有权：值的借用是如何工作的？

* [borrow](08_borrow)

### 09 所有权：一个值可以有多个所有者么？

* [multi owner](09_multi_owner)

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

* [sys\_traits](14_sys_traits/src/linked_list.rs)
