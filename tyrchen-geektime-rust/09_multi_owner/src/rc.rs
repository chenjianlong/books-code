use std::rc::Rc;

#[allow(unused_variables)]
fn main() {
    let a = Rc::new(1);
    let b = a.clone();
    let c = a.clone();
}