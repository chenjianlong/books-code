package main

import (
	"fmt"
	"strings"
)

func main() {
	for i := 0; i < 10; i++ {
		fmt.Println(strings.Repeat("*", 20))
	}
}
