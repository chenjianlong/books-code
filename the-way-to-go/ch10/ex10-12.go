package main

import (
	"fmt"
	"strconv"
)

type T struct {
	a int
	b float32
	c string
}

func (self *T) String() string {
	return "(" + strconv.Itoa(self.a) + " / " +
		strconv.FormatFloat(float64(self.b), 'f', 7, 32) + " / " + strconv.Quote(self.c) + ")"
}

func main() {
	t := &T{7, 3.5, "Hello\tGO"}
	fmt.Println(t)
}
