package main

import (
	"fmt"
)

func main() {
	type Rope string

	var s Rope = "hello"
	fmt.Println(s)
}
