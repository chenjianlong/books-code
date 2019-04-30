//
// ex12-1.go
// Copyright (C) 2019 Jianlong Chen <jianlong99@gmail.com>
//
// Distributed under terms of the MIT license.
//

package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"
)

//const NL = "\r\n"
const NL = "\n"

func main() {
	inputReader := bufio.NewReader(os.Stdin)
	fmt.Println("Please enter some input: ")
	input, err := inputReader.ReadString('S')
	if err != nil {
		panic("failed")
	}

	replacer := strings.NewReplacer("\r", "", "\n", "")
	fmt.Printf("The input bytes count: %d\n", len(replacer.Replace(input)))
	fmt.Printf("The input lines: %d\n", len(strings.Split(input, NL)))
	str := strings.Replace(input, "\t", " ", -1)
	str = strings.Replace(str, "\r", " ", -1)
	str = strings.Replace(str, "\n", " ", -1)
	fmt.Printf("The input words: %d\n", len(strings.Split(str, " ")))
}
