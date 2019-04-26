package main

import (
	"fmt"
	"math"
)

func main() {
	fmt.Println(MySqrt(16.0))
	fmt.Println(MySqrt(-16.0))
	fmt.Println(MySqrt2(16.0))
	fmt.Println(MySqrt2(-16.0))
}

func MySqrt(v float64) (float64, string) {
	if v < 0.0 {
		return 0.0, "Invalid input"
	}

	return math.Sqrt(v), ""
}

func MySqrt2(v float64) (r float64, errmsg string) {
	if v < 0.0 {
		errmsg = "Invalid input"
		return
	}

	r = math.Sqrt(v)
	return
}
