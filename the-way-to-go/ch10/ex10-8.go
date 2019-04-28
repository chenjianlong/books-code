package main

import "fmt"

type Engine interface {
	Start()
	Stop()
}

type Car struct {
	wheelCount int
}

type Mercedes struct {
	Car
}

func (e *Car) Start() {
	fmt.Println("start engine")
}

func (e *Car) Stop() {
	fmt.Println("stop engine")
}

func (c *Car) GoToWorkIn() {
	// get in car
	c.Start()
	// drive to work
	c.Stop()
	// get out of car
}

func (c *Car) numberOfWheels() int {
	return c.wheelCount
}

func (m *Mercedes) sayHiToMerkel() {
	m.GoToWorkIn()
	fmt.Println("wheel number:", m.numberOfWheels())
}

func main() {
	m := &Mercedes{Car{4}}
	m.GoToWorkIn()
	m.sayHiToMerkel()
}
