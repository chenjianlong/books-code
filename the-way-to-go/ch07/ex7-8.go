package main

import (
	"fmt"
	"math"
	"strconv"
)

func main() {
	sl := []int{-341, 342, 38, 68, 3, -4312}
	fmt.Println("slices=", sl)
	fmt.Println("min is:", minSlice(sl))
	fmt.Println("max is:", maxSlice(sl))
}

func minSlice(sl []int) (min int) {
	if strconv.IntSize == 64 {
		min = math.MaxInt64
	} else {
		min = math.MaxInt32
	}

	for _, v := range sl {
		if v < min {
			min = v
		}
	}

	return
}

func maxSlice(sl []int) (max int) {
	if strconv.IntSize == 64 {
		max = math.MinInt64
	} else {
		max = math.MinInt32
	}

	for _, v := range sl {
		if v > max {
			max = v
		}
	}

	return
}
