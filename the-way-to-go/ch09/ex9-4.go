package main

import (
	"./even"
	"fmt"
)

func main() {
	nums := make([]int, 100)
	for i := 1; i <= 100; i++ {
		nums[i-1] = i
	}

	for _, n := range nums {
		if even.IsEven(n) {
			fmt.Println(n)
		}
	}
}
