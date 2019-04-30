//
// ex12-2.go
// Copyright (C) 2019 Jianlong Chen <jianlong99@gmail.com>
//
// Distributed under terms of the MIT license.
//

package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

func main() {
	for cont := true; cont; {
		cont = run()
	}
}

func run() (res bool) {
	res = true
	inputReader := bufio.NewReader(os.Stdin)
	fmt.Println("Please enter number1: ")
	input, err := inputReader.ReadString('\n')
	if input[0] == 'q' {
		res = false
		return
	}

	if err != nil {
		panic("failed")
	}

	input = strings.Trim(input, "\r\n \t")
	n1, e1 := strconv.ParseInt(input, 10, 64)
	if e1 != nil {
		fmt.Println(n1, e1)
		panic("failed to ParseInt")
	}

	fmt.Println("Please enter number2: ")
	input, err = inputReader.ReadString('\n')
	if err != nil {
		panic("failed")
	}

	input = strings.Trim(input, "\r\n \t")
	n2, e2 := strconv.ParseInt(input, 10, 64)
	if e2 != nil {
		fmt.Println(n1, e1)
		panic("failed to ParseInt")
	}

	fmt.Println("Please enter operator: ")
	input, err = inputReader.ReadString('\n')
	if err != nil {
		panic("failed")
	}

	switch input[0] {
	case '+':
		fmt.Println("Result:", n1+n2)
	case '-':
		fmt.Println("Result:", n1-n2)
	case '*':
		fmt.Println("Result:", n1*n2)
	case '/':
		fmt.Println("Result:", n1/n2)
	default:
		fmt.Println("Invalid operator")
	}

	return
}
