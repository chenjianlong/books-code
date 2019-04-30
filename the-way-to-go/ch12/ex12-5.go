//
// ex12-5.go
// Copyright (C) 2019 Jianlong Chen <jianlong99@gmail.com>
//
// Distributed under terms of the MIT license.
//

package main

import (
	"fmt"
	"os"
	"strings"
)

func main() {
	text := "Hello "
	if len(os.Args) > 1 {
		text += strings.Join(os.Args[1:], " ")
	}

	text += "!"
	fmt.Println(text)
}
