//
// ex14-11-1.go
// Copyright (C) 2019 Jianlong Chen <jianlong99@gmail.com>
//
// Distributed under terms of the MIT license.
//

package main

import (
	"fmt"
	"runtime"
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
	NCPU := runtime.GOMAXPROCS(0)
	out := make(chan float64, 1000)
	defer close(out)
	for i := 0; i < NCPU; i++ {
		go Calcterm(out, (n/NCPU)*i, n/NCPU*(i+1))
	}

	for i := 0; i < n; i++ {
		term := <-out
		res += term
	}

	res *= 4.0
	return
}

func Calcterm(out chan<- float64, start int, end int) {
	for i := start; i <= end; i++ {
		term := (1.0 / (2.0*float64(i) + 1))
		if i%2 != 0 {
			term *= -1.0
		}

		out <- term
	}
}
