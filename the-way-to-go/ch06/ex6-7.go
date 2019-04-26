package main

import (
	"fmt"
	"strings"
)

func main() {
	replaceNotAscii := func(r rune) rune {
		if r > 255 {
			return '?'
		}

		return r
	}

	fmt.Println(strings.Map(replaceNotAscii, "Hello 中国，Hello World"))

	dropNotAscii := func(r rune) rune {
		if r > 255 {
			return -r
		}

		return r
	}

	fmt.Println(strings.Map(dropNotAscii, "Hello 中国，Hello World"))
}
