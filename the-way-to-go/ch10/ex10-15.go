package main

import "fmt"

type TZ int

const (
	UTC = TZ(iota)
	PDT
	MDT
	CDT
	EDT
	BST
	CEST
	MSK
	IST
	CST
	AEST
	NZST
)

var m = map[TZ]string{
	UTC:  "Universal Greenwich time",
	PDT:  "Pacific Time (US)",
	MDT:  "Mountain Time (US)",
	CDT:  "Central Time (US)",
	EDT:  "Eastern Time (US)",
	BST:  "London, United Kingdom",
	CEST: "Berlin, Germany",
	MSK:  "Moscow, Russian Federation",
	IST:  "Mumbai, India",
	CST:  "Beijing, China",
	AEST: "Sydney, Australia",
	NZST: "Auckland, New Zealand",
}

func (self TZ) String() string {
	return m[self]
}

func main() {
	t := UTC
	fmt.Println(t)
	t = CST
	fmt.Println(t)
}
