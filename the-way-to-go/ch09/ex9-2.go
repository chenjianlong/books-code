package main

import (
	"fmt"
	"unsafe"
)

func main() {
	var v int
	fmt.Println("szieof(Int)=", unsafe.Sizeof(v), "bytes")
}
