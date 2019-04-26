package main

import "fmt"

func main() {
	fmt.Println(sumProductAndDifference(10, 5))
	fmt.Println(sumProductAndDifference2(10, 5))
}

func sumProductAndDifference(x int, y int) (int, int, int) {
	return x + y, x * y, x - y
}

func sumProductAndDifference2(x int, y int) (s int, p int, d int) {
	s = x + y
	p = x * y
	d = x - y
	return
}
