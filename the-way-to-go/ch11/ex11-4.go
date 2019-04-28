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

type RSimple struct {
	r int
}

func (self *RSimple) Get() int {
	return self.r
}

func (self *RSimple) Set(p int) {
	self.r = p
}

func main() {
	b := &Book{49}
	r := &RSimple{8}
	bi := []Simpler{b, r}

	for _, v := range bi {
		fi(v)
	}
}

func fi(s Simpler) {
	switch s.(type) {
	case *Book:
		fmt.Println("Book type")
	case *RSimple:
		fmt.Println("RSimple")
	default:
		fmt.Println("Unknown")
	}
}
