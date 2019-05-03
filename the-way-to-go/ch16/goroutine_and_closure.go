package main

import (
	"fmt"
	"time"
)

var values = [5]int{10, 11, 12, 13, 14}

func main() {
	// 版本A:
	for ix := range values { // ix是索引值
		func() {
			fmt.Print(ix, " ")
		}() // 调用闭包打印每个索引值
	}
	fmt.Println()
	// 版本B: 和A版本类似，但是通过调用闭包作为一个协程
	for ix := range values {
		go func() {
			fmt.Print(ix, " ")
		}()
	}
	time.Sleep(5e9)
	fmt.Println()
	// 版本C: 正确的处理方式
	for ix := range values {
		go func(ix interface{}) {
			fmt.Print(ix, " ")
		}(ix)
	}
	time.Sleep(5e9)
	fmt.Println()
	// 版本D: 输出值:
	for ix := range values {
		val := values[ix]
		go func() {
			fmt.Print(val, " ")
		}()
	}
	time.Sleep(1e9)
}
