package main

import "fmt"

func main() {
	s1 := []byte{'h', 'e', 'l', 'l', 'o'}
	s2 := []byte{' ', 'w', 'o', 'r', 'l', 'd'}
	s3 := Append(s1, s2)
	fmt.Println(s3, len(s3), cap(s3))
}

func Append(slice []byte, data []byte) []byte {
	n := len(slice)
	if cap(slice)-len(slice) < len(data) {
		s2 := make([]byte, len(slice)+len(data))
		copy(s2, slice)
		slice = s2
	}

	copy(slice[n:], data)
	return slice
}
