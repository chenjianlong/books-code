package main

import (
	list "container/list"
	"fmt"
)

func main() {
	l := list.New()
	l.PushBack(101)
	l.PushBack(102)
	l.PushBack(103)

	e := l.Front()
	for ; e != nil; e = e.Next() {
		fmt.Println(e.Value)
		//fmt.Println((*e).Value) // same as above
	}
}
