package main

import (
	"fmt"
	"math/big"
)

func main() {
	var i int64 = 1
	for ; i <= 30; i++ {
		var v = factorial(i)
		fmt.Printf("%v!=%v\n", i, &v)
	}
}

func factorial(n int64) (res big.Int) {
	if n <= 1 {
		res = *big.NewInt(1)
		return
	}

	res = factorial(n - 1)
	res.Mul(&res, big.NewInt(n))
	return
}
