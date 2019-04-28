package main

import "fmt"

type employee struct {
	salary int
}

func main() {
	e := employee{9999}
	e.giveRaise(33)
	fmt.Println(e)
}

func (self *employee) giveRaise(percent int) {
	self.salary *= percent + 100
	self.salary /= 100

}
