package main

import "fmt"

func main() {
	showAll("Hello", "GO", "Lang")
}

func showAll(s ...string) {
	for _, v := range s {
		fmt.Println(v)
	}
}
