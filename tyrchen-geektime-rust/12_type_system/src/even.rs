fn main() {
    let numbers = vec![1, 2, 3, 4, 5, 6, 7, 8, 9, 10];

    //let even_numbers: Vec<_> = numbers.into_iter().filter(|n| n % 2 == 0).collect();
    let even_numbers = numbers
        .into_iter()
        .filter(|n| n % 2 == 0)
        .collect::<Vec<_>>();

    println!("{:?}", even_numbers);
}
