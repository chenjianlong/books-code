//
// ex14-11-1.go
// Copyright (C) 2019 Jianlong Chen <jianlong99@gmail.com>
//
// Distributed under terms of the MIT license.
//

package main

import (
	"fmt"
	"time"
)

func main() {
	start := time.Now()
	pi := calcPi(5000000)
	end := time.Now()
	delta := end.Sub(start)
	fmt.Printf("longCalculation took this amount of time: %s\n", delta)
	fmt.Println("Pi is:", pi)
}

func calcPi(n int) (res float64) {
	for i := 0; i < n; i++ {
		term := (1.0 / (2.0*float64(i) + 1))
		if i%2 != 0 {
			term = -1 * term
		}

		res += term
	}

	res *= 4.0
	return
}
