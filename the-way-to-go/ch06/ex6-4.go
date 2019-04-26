package main

import "fmt"

func main() {
	idx, result := 0, 0
	for i := 0; i <= 10; i++ {
		idx, result = fibonacci(i)
		fmt.Printf("fibonacci(%d) is: %d\n", idx, result)
	}
}

func fibonacci(n int) (idx int, res int) {
	idx = n
	if n <= 1 {
		res = 1
	} else {
		_, res = fibonacci(n - 1)
		_, n2 := fibonacci(n - 2)
		res += n2
	}
	return
}
