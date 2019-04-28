package main

import (
	f64 "./float64"
	"./sort"
	"fmt"
)

func main() {
	l := f64.Fill(30)

	fmt.Println("Origin:", l)
	sort.Sort(l)
	if sort.IsSorted(l) {
		fmt.Println("Sorted:", l)
	} else {
		panic("Failed to sort")
	}
}
