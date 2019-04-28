package main

import "fmt"

type obj interface{}

func main() {
	strs := []obj{"Hello", "Go", "Nice"}
	res := mapFunc(strs, func(n obj) obj {
		s := n.(string)
		return s + s
	})
	fmt.Println(res)
}

func mapFunc(objs []obj, fn func(obj) obj) (res []obj) {
	for _, n := range objs {
		res = append(res, fn(n))
	}

	return
}
