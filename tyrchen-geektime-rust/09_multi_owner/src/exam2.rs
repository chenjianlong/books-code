fn main() {
    let s = std::sync::Arc::new("hello");

    {
        let my_s = s.clone();
        std::thread::spawn(move || {
            println!("{:}", my_s);
        });
    }


    println!("{}", s);
}