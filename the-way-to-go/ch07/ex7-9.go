package main

import "fmt"

func main() {
	slice := []int{1, 2, 3, 4}
	fmt.Println(factorTimes(slice, 3))
}

func factorTimes(slice []int, factor int) (res []int) {
	res = make([]int, len(slice)*factor)
	copy(res, slice)
	return
}
