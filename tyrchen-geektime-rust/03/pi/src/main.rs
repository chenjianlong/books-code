fn pi()-> f64 {
    3.1415926
}

fn not_pi() {
    3.1415926;
}

fn main() {
    let is_pi = pi();
    let is_unit1 = not_pi();
    let is_unit2 = {
        pi();
    };

    println!("is_pi: {:?}, is unit1: {:?}, is_unit2: {:?}", is_pi, is_unit1, is_unit2);
}