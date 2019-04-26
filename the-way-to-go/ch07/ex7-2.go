package main

import "fmt"

func main() {
	var ar [15]int
	for i := 0; i < len(ar); i++ {
		ar[i] = i
	}

	fmt.Println(ar)
}
