package main

import "fmt"

func main() {
	sl := []float32{1.0, 2.0, 3.0, 4.0, 5.0, 12341.342}
	fmt.Println(SumAndAverage(sl))
}

func SumAndAverage(sl []float32) (float32, float32) {
	var sum, avg float32 = 0.0, 0.0
	if len(sl) == 0 {
		return sum, avg
	}

	for _, v := range sl {
		sum += v
	}

	avg = sum / float32(len(sl))
	return sum, avg
}
