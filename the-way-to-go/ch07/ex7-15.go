package main

import "fmt"

func main() {
	sl := []byte{'H', 'e', 'l', 'l', 'o'}
	fmt.Println(copyNotRepeat(sl))
}

func copyNotRepeat(sl []byte) (res []byte) {
	for i := 1; i < len(sl); i++ {
		if sl[i] != sl[i-1] {
			res = append(res, sl[i])
		}
	}

	return
}
