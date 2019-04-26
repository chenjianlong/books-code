package main

import "fmt"

func main() {
	slices := []string{"Hello", "World", "Go", "is", "easy", "to", "study", "and", "it", "is", "awesome"}
	fmt.Println(RemoveStringSlice(slices, 3, 9))
	//fmt.Printf("%p\n", &slices)
}

func RemoveStringSlice(slices []string, start int, end int) (res []string) {
	//fmt.Printf("%p\n", &slices)
	n := len(slices)
	copy(slices[start:], slices[end:])
	slices = slices[:n-(end-start)]
	res = slices
	return
}
