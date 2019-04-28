package main

import (
	"fmt"
	"math"
	"reflect"
)

type Shaper interface {
	Area() float32
}

type PeriInterface interface {
	Perimeter() float32
}

type Square struct {
	side float32
}

func (sq *Square) Area() float32 {
	return sq.side * sq.side
}

func (self *Square) Perimeter() float32 {
	return self.side * 4
}

type Rectangle struct {
	length, width float32
}

func (r Rectangle) Area() float32 {
	return r.length * r.width
}

type Circle struct {
	radius float32
}

func (c *Circle) Area() float32 {
	return c.radius * math.Pi
}

type Triangle struct {
	length float32
	height float32
}

func (self *Triangle) Area() float32 {
	return (self.length * self.height) / 2.0
}

func main() {

	r := Rectangle{5, 3} // Area() of Rectangle needs a value
	q := &Square{5}      // Area() of Square needs a pointer
	c := &Circle{5}
	t := &Triangle{3, 5}
	// shapes := []Shaper{Shaper(r), Shaper(q)}
	// or shorter
	shapes := []Shaper{r, q, c, t}
	fmt.Println("Looping through shapes for area ...")
	for n, _ := range shapes {
		fmt.Println("Shape details: ", shapes[n])
		fmt.Println("Area of this shape is: ", shapes[n].Area())
	}

	p := q
	fmt.Println("Square Perimeter:", p.Perimeter())
	fmt.Println("Square Perimeter:", p.Area())
	fmt.Println(reflect.TypeOf(p))
}
