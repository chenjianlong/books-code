package main

import "fmt"

func main() {
	nums := []int{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}
	res := mapFunc(nums, func(n int) int {
		return n * 10
	})
	fmt.Println(res)
}

func mapFunc(nums []int, fn func(int) int) (res []int) {
	for _, n := range nums {
		res = append(res, fn(n))
	}

	return
}
