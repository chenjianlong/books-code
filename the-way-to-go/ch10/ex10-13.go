package main

import (
	"fmt"
	"strconv"
)

type Celsius float64

func (self Celsius) String() string {
	return strconv.FormatFloat(float64(self), 'f', -1, 64) + " °C "
}

func main() {
	c := Celsius(36.8)
	fmt.Println(c)
}
