package main

import (
	"bufio"
	"fmt"
	"os"
)

const NL = "\n"

// const NL := "\r\n"

func main() {
	inputReader := bufio.NewReader(os.Stdin)
	fmt.Println("Please enter your name:")
	input, err := inputReader.ReadString('\n')

	if err != nil {
		fmt.Println("There were errors reading, exiting program.")
		return
	}

	fmt.Printf("Your name is %s", input)
	// For Unix: test with delimiter "\n", for Windows: test with "\r\n"
	switch input {
	case "Philip" + NL:
		fmt.Println("Welcome Philip!")
	case "Chris" + NL:
		fmt.Println("Welcome Chris!")
	case "Ivo" + NL:
		fmt.Println("Welcome Ivo!")
	default:
		fmt.Printf("You are not welcome here! Goodbye!")
	}

	// version 2:
	switch input {
	case "Philip" + NL:
		fallthrough
	case "Ivon" + NL:
		fallthrough
	case "Chris" + NL:
		fmt.Printf("Welcome %s\n", input)
	default:
		fmt.Printf("You are not welcome here! Goodbye!\n")
	}

	// version 3:
	switch input {
	case "Philip" + NL, "Ivo" + NL:
		fmt.Printf("Welcome %s\n", input)
	default:
		fmt.Printf("You are not welcome here! Goodbye!\n")
	}
}
