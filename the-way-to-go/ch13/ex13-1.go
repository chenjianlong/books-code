//
// ex13-1.go
// Copyright (C) 2019 Jianlong Chen <jianlong99@gmail.com>
//
// Distributed under terms of the MIT license.
//

package main

import "fmt"

func main() {
	defer func() {
		if e := recover(); e != nil {
			fmt.Printf("Panicing %s\n", e)
		}
	}()

	a := 3 / b()
	fmt.Println(a)
}

func b() int {
	return 0
}
