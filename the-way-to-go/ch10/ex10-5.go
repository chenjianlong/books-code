package main

import "fmt"

type A struct {
	f float32
	int
	string
}

type B struct {
	A
	f float32
}

func main() {
	a := &A{3.0, 1, "Hello GO"}
	fmt.Println(a)

	b := &B{A{3.0, 1, "Hello"}, 6.0}
	fmt.Println(b.A.f)
	fmt.Println(b.f)
}
