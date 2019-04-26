package main

import "fmt"

func main() {
	ar := []int{1, 3, 5}
	fmt.Printf("%p\n", &ar)
	showAddress(ar)
}

func showAddress(a []int) {
	fmt.Printf("%p\n", &a)
}
