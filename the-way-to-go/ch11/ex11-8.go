package main

import (
	"./sort"
	"fmt"
)

type Person struct {
	firstName string
	lastName  string
}

type Persons []Person

func (self Persons) Len() int {
	return len(self)
}

func (self Persons) Less(i, j int) (res bool) {
	if self[i].firstName != self[j].firstName {
		res = self[i].firstName < self[j].firstName
	}

	res = self[i].lastName < self[j].lastName
	return
}

func (self Persons) Swap(i, j int) {
	self[i], self[j] = self[j], self[i]
}

func main() {
	p := Persons{{"Ma", "Jack"}, {"Ma", "T"}, {"Cheng", "Jack"}}
	fmt.Println("origin:", p)
	sort.Sort(p)
	fmt.Println("sorted", p)
}
