package main

import (
	"fmt"
)

type Address struct {
	province string
	city     string
}

type VCard struct {
	name  string
	addr  *Address
	birth string
}

func main() {
	card := &VCard{name: "Jack", addr: &Address{"GD", "GZ"}, birth: "1999-10-10"}
	showCard(card)
}

func showCard(card *VCard) {
	fmt.Println("name=", card.name)
	fmt.Println("addr=", card.addr)
	fmt.Println("birth=", card.birth)
}
