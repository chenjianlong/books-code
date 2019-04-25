package main

import "fmt"

func main() {
	for i := 0; i < 15; i++ {
		fmt.Printf("current i=%d\n", i)
	}

	i := 0
loop1:
	fmt.Printf("current i=%d\n", i)
	i++
	if i < 15 {
		goto loop1
	}
}
