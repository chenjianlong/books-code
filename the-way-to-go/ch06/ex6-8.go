package main

import "fmt"

func main() {
	fv := func() {
		fmt.Println("Hello World")
	}

	fv()
	fmt.Printf("%T\n", fv)
}
