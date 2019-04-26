package main

import "fmt"

func main() {
	fmt.Println("1+2+3+4=", sum(1, 2, 3, 4))
	fmt.Println("3+5+7+9=", sum(3, 5, 7, 9))
}

func sum(nums ...int) (res int) {
	for _, n := range nums {
		res += n
	}

	return
}
