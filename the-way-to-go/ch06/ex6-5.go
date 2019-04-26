package main

import "fmt"

func main() {
	show(10)
}

func show(i int) {
	fmt.Println(i)
	if i > 1 {
		show(i - 1)
	}
}
