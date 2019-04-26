package main

import "fmt"

func main() {
	var ar [50]int
	ar[0] = 1
	ar[1] = 1
	for i := 2; i < len(ar); i++ {
		ar[i] = ar[i-1] + ar[i-2]
	}

	for i, d := range ar {
		fmt.Println(i+1, d)
	}
}
