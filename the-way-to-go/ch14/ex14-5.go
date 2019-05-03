//
// ex14-5.go
// Copyright (C) 2019 Jianlong Chen <jianlong99@gmail.com>
//
// Distributed under terms of the MIT license.
//

package main

import "fmt"

func main() {
	ch := make(chan int)
	go sum(1, 2, ch)
	fmt.Println("The sum is:", <-ch)
}

func sum(a, b int, ch chan int) {
	ch <- a + b
}
