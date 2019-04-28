package main

import "fmt"

type Simpler interface {
	Get() int
	Set(int)
}

type Book struct {
	price int
}

func (self *Book) Get() int {
	return self.price
}

func (self *Book) Set(p int) {
	self.price = p
}

func main() {
	b := &Book{49}
	bi := Simpler(b)

	bi.Set(88)
	fmt.Println("Book price:", bi.Get())
}
