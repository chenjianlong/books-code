package main

import (
	"fmt"
)

type Any interface{}
type EvalFunc func(Any, Any) (Any, Any)

func main() {
	fibFunc := func(prevState, state Any) (Any, Any) {
		pre := prevState.(int64)
		os := state.(int64)
		ns := pre + os
		return os, ns
	}

	even := BuildLazyIntEvaluator(fibFunc, int64(0), int64(1))

	for i := 0; i < 10; i++ {
		fmt.Printf("%vth even: %v\n", i, even())
	}
}

func BuildLazyEvaluator(evalFunc EvalFunc, prev, initState Any) func() Any {
	retValChan := make(chan Any)
	loopFunc := func() {
		var retVal, actState Any = prev, initState
		for {
			retVal, actState = evalFunc(retVal, actState)
			retValChan <- retVal
		}
	}
	retFunc := func() Any {
		return <-retValChan
	}
	go loopFunc()
	return retFunc
}

func BuildLazyIntEvaluator(evalFunc EvalFunc, prev, initState Any) func() int64 {
	ef := BuildLazyEvaluator(evalFunc, prev, initState)
	return func() int64 {
		return ef().(int64)
	}
}
