package main

import "fmt"

type Day int

const (
	MON = Day(iota + 1)
	TUE
	WED
	THU
	FRI
	SAT
	SUN
)

func (self Day) String() string {
	switch self {
	case MON:
		return "Monday"
	case TUE:
		return "Tuesday"
	case WED:
		return "Wednesday"
	case THU:
		return "Thursday"
	case FRI:
		return "Friday"
	case SAT:
		return "Saturday"
	case SUN:
		return "Sunday"
	default:
		return "Invalid Day"
	}
}

func main() {
	d := MON
	fmt.Println(d)
	d = SUN
	fmt.Println(d)
}
