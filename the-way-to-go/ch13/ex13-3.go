//
// ex13-3.go
// Copyright (C) 2019 Jianlong Chen <jianlong99@gmail.com>
//
// Distributed under terms of the MIT license.
//

package main

import (
	"fmt"
	"math"
)

func main() {
	var v int64 = 3
	fmt.Println(IntFromInt64(v))
	v = math.MaxInt32 + 1
	fmt.Println(IntFromInt64(v))
	v = math.MinInt32 - 1
	fmt.Println(IntFromInt64(v))
}

func IntFromInt64(v int64) int32 {
	defer func() {
		if e := recover(); e != nil {
			fmt.Printf("Recover from IntFromInt64 %s\r\n", e)
		}
	}()

	return ConvertInt64ToInt(v)
}

func ConvertInt64ToInt(v int64) int32 {
	if v > math.MaxInt32 {
		panic("overflow")
	}

	if v < math.MinInt32 {
		panic("underflow")
	}

	return int32(v)
}
