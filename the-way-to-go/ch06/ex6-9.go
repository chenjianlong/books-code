package main

import "fmt"

func main() {
	f := fibonacci()
	for i := 0; i <= 10; i++ {
		fmt.Printf("fibonacci(%d) is: %d\n", i+2, f())
	}
}

func fibonacci() func() int {
	a, b := 1, 1
	return func() int {
		a, b = b, a+b
		return b
	}
}
