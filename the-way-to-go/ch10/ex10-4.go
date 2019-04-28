package main

import "fmt"

type Rectangle struct {
	width  int
	height int
}

func main() {
	r := &Rectangle{3, 4}
	fmt.Println("Rectangle:", r)
	fmt.Println("Area is:", Area(r))
	fmt.Println("Perimeter is:", Perimeter(r))
}

func Area(r *Rectangle) int {
	return r.width * r.height
}

func Perimeter(r *Rectangle) int {
	return 2 * (r.width + r.height)
}
