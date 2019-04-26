package main

import "fmt"

func main() {
	res := fibonacci(50)
	for i, v := range res {
		fmt.Println(i+1, v)
	}
}

func fibonacci(n int) (slice []int) {
	slice = make([]int, n)
	for i := 0; i < len(slice) && i < 2; i++ {
		slice[i] = 1
	}

	for i := 2; i < len(slice); i++ {
		slice[i] = slice[i-1] + slice[i-2]
	}
	return
}
