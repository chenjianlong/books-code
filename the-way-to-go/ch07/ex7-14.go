package main

import "fmt"

func main() {
	s := "Hello GO Language"
	fmt.Println("Origin:", s)
	fmt.Println("Reverse:", reverse_string(s))
}

func reverse_string(s string) (res string) {
	bytes := []byte(s)
	for start, end := 0, len(bytes)-1; start < end; {
		bytes[start], bytes[end] = bytes[end], bytes[start]
		start++
		end--
	}

	res = string(bytes)
	return
}
