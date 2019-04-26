package main

import "fmt"

func main() {
	slices := []int{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}
	fmt.Println(Filter(slices, func(v int) bool {
		return v%2 == 0
	}))
}

func Filter(slices []int, unary func(int) bool) (res []int) {
	for _, v := range slices {
		if unary(v) {
			res = append(res, v)
		}
	}

	return
}
