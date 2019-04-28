package main

import "fmt"

type Minor interface {
	Less(i, j int) bool
	At(i int) interface{}
	Len() int
}

func Min(data Minor) interface{} {
	if data.Len() < 1 {
		panic("failed, Minor.Len() small than 1")
	}

	mIdx := 0
	for i := 1; i < data.Len(); i++ {
		if data.Less(i, mIdx) {
			mIdx = i
		}
	}

	return data.At(mIdx)
}

type IntArray []int

func (p IntArray) Len() int {
	return len(p)
}

func (p IntArray) At(i int) interface{} {
	return p[i]
}

func (p IntArray) Less(i, j int) bool {
	return p[i] < p[j]
}

func main() {
	p := &IntArray{1, 3, 9, 3412, -143, -1, 0}
	m := Min(p)
	v, ok := m.(int)
	if ok {
		fmt.Println(v)
	} else {
		panic("failed")
	}
}
