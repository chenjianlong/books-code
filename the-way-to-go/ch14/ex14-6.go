//
// ex14-6.go
// Copyright (C) 2019 Jianlong Chen <jianlong99@gmail.com>
//
// Distributed under terms of the MIT license.
//

package main

import "fmt"

func main() {
	ch := make(chan int)
	doneChan := make(chan bool)
	go producer(ch, doneChan)
	go consumer(ch, doneChan)
	<-doneChan
	<-doneChan
}

func producer(ch chan int, doneChan chan bool) {
	for i := 0; i < 10; i++ {
		ch <- i * 10
	}

	doneChan <- true
}

func consumer(ch chan int, doneChan chan bool) {
	for i := 0; i < 10; i++ {
		fmt.Println(<-ch)
	}

	doneChan <- true
}
