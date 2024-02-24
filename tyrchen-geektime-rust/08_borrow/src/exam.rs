fn main() {
    let mut arr = vec![1, 2, 3];
    // cache the last item
    // let last = arr.last();
    // method 1 clone
    // method 2 println before push
    //let last = arr.last().unwrap().clone();
    let last = arr[arr.len() - 1];
    arr.push(4);
    // consume previously stored last item
    println!("last: {:?}", last);
}