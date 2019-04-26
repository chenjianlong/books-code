package main

import "fmt"

func main() {
	slices := []byte{'h', 'e', 'l', 'l', 'o'}
	n := 3
	p1, p2 := slices[:n], slices[n:]
	fmt.Println(p1, len(p1), cap(p1))
	fmt.Println(p2, len(p2), cap(p2))
}
