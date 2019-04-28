package main

import "fmt"

const DEFAULT_SIZE = 4

type Element interface{}

type Stack struct {
	idx     int
	content []Element
}

func (self *Stack) expand(size int) {
	n := self.idx
	if n < 0 {
		self.content = make([]Element, DEFAULT_SIZE)
		self.idx = 0
		return
	}

	n = len(self.content)
	if n < size {
		tmp := self.content
		self.content = make([]Element, n*2)
		copy(self.content, tmp)
	}
}

func (self *Stack) Push(val Element) {
	self.expand(self.idx + 1)
	self.content[self.idx] = val
	self.idx++
}

func (self *Stack) Pop() Element {
	if self.IsEmpty() {
		panic("Failed to pop, stack is empty")
	}

	self.idx--
	res := self.content[self.idx]
	return res
}

func (self *Stack) Len() int {
	return self.idx
}

func (self *Stack) IsEmpty() bool {
	return self.idx <= 0
}

func NewStack() (res *Stack) {
	res = &Stack{-1, nil}
	return
}

func main() {
	s := NewStack()
	for i := 1; i <= 10; i++ {
		s.Push(i)
	}

	s.Push("Hello")
	s.Push("GO")
	s.Push("Language")
	for !s.IsEmpty() {
		fmt.Println("Pop:", s.Pop())
	}

	// fmt.Println("Pop:", s.Pop()) // panic, stakc is empty

}
