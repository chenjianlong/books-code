package main

import "fmt"

type Base struct {
	id int
}

func (self *Base) Id() int {
	return self.id
}

func (self *Base) setId(i int) {
	self.id = i
}

type Person struct {
	Base
	FirstName string
	LastName  string
}

type Employee struct {
	Person
	salary int
}

func main() {
	e := &Employee{Person{Base{1}, "Ma", "Jack"}, 1}
	fmt.Println(e.Id())
}
