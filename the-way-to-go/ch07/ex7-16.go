package main

import "fmt"

func main() {
	nums := []int{1, 3223, -1, -2, 2341, 2, 512, 351325}
	bubbleSort(nums)
	fmt.Println(nums)
}

func bubbleSort(nums []int) {
	n := len(nums)
	for n > 0 {
		m := 0
		for i := 1; i < n; i++ {
			if nums[i-1] > nums[i] {
				nums[i-1], nums[i] = nums[i], nums[i-1]
				m = i
			}
		}

		n = m
	}
}
