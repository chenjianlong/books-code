package main

import "fmt"

func main() {
	slices := []string{"Hello", "World", "Go", "is", "awesome"}
	toBeInserted := []string{"is", "easy", "to", "study", "and", "it"}
	fmt.Println(InsertStringSlice(slices, 3, toBeInserted))
}

func InsertStringSlice(slices []string, idx int, toBeInserted []string) (res []string) {
	if cap(slices)-len(slices) < len(toBeInserted) {
		res = make([]string, len(slices)+len(toBeInserted))
		copy(res, slices[:idx])
	} else {
		res = slices
		res = res[:len(slices)+len(toBeInserted)]
	}

	copy(res[idx+len(toBeInserted):], slices[idx:])
	copy(res[idx:idx+len(toBeInserted)], toBeInserted)
	return
}
