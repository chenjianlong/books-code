use serde::Deserialize;
use std::borrow::Cow;
use std::mem::size_of;

#[allow(dead_code)]
#[derive(Debug, Deserialize)]
struct User<'input> {
    #[serde(borrow)]
    name: Cow<'input, str>,
    age: u8,
}

fn main() {
    let str = "xxx";
    let cow = Cow::Borrowed(str);
    let mut cow2 = cow.to_owned();
    match cow {
        Cow::Borrowed(_) => println!("cow is_borrowed"),
        Cow::Owned(_) => println!("cow is_owned"),
    }

    match cow2 {
        Cow::Borrowed(_) => println!("cow2 is_borrowed"),
        Cow::Owned(_) => println!("cow2 is_owned"),
    }

    let str2 = cow2.to_mut();
    str2.push_str("_yyy");
    println!("cow_borrow: {}, to_mut: {}", cow, str2);

    let str3 = String::new();
    let cow3: Cow<str> = Cow::Owned(str3);
    match cow3 {
        Cow::Borrowed(_) => println!("cow3 is_borrowed"),
        Cow::Owned(_) => println!("cow3 is_owned"),
    }

    println!("size_of::<Cow<str>>(): {}", size_of::<Cow<str>>());
    println!("size_of::<String>(): {}", size_of::<String>());
    println!("size_of::<&str>(): {}", size_of::<&str>());
    println!("size_of::<Cow<[u8]>>(): {}", size_of::<Cow<[u8]>>());
    println!("size_of::<Vec<u8>>(): {}", size_of::<Vec<u8>>());
    println!("size_of::<&[u8]>(): {}", size_of::<&[u8]>());
}
