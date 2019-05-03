//
// goFibonacci.go
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
	term := 25
	ch := make(chan int)

	start := time.Now()
	go fibnterms(term, ch)
	for i := 0; ; i++ {
		result, ok := <-ch
		if ok {
			fmt.Printf("fibonacci(%d) is: %d\n", i, result)
		} else {
			break
		}
	}
	end := time.Now()
	delta := end.Sub(start)
	fmt.Printf("longCalculation took this amount of time: %s\n", delta)
}

func fibnterms(term int, c chan int) {
	for i := 0; i <= term; i++ {
		c <- fibonacci(i)
	}
	close(c)
}

func fibonacci(n int) (res int) {
	if n <= 1 {
		res = 1
	} else {
		res = fibonacci(n-1) + fibonacci(n-2)
	}
	return
}
