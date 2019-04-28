package main

import "fmt"

const DEFAULT_SIZE = 4

type Stack struct {
	idx     int
	content []int
}

func (self *Stack) expand(size int) {
	n := len(self.content)
	if n < size {
		tmp := self.content
		self.content = make([]int, n*2)
		copy(self.content, tmp)
	}
}

func (self *Stack) Push(val int) {
	self.expand(self.idx + 1)
	self.content[self.idx] = val
	self.idx++
}

func (self *Stack) Pop() int {
	if self.idx <= 0 {
		panic("Failed to pop, stack is empty")
	}

	self.idx--
	res := self.content[self.idx]
	return res
}

func main() {
	s := &Stack{0, make([]int, DEFAULT_SIZE)}
	for i := 1; i <= 10; i++ {
		s.Push(i)
	}

	for i := 1; i <= 10; i++ {
		fmt.Println("Pop:", s.Pop())
	}

	// fmt.Println("Pop:", s.Pop()) // panic, stakc is empty

}
