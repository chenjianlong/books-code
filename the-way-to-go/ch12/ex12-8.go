//
// ex12-8.go
// Copyright (C) 2019 Jianlong Chen <jianlong99@gmail.com>
//
// Distributed under terms of the MIT license.
//

package main

import (
	"encoding/gob"
	"fmt"
	"log"
	"os"
)

type Address struct {
	Type    string
	City    string
	Country string
}

type VCard struct {
	FirstName string
	LastName  string
	Addresses []*Address
	Remark    string
}

func main() {
	file, _ := os.OpenFile("vcard.gob", os.O_RDONLY, 0666)
	defer file.Close()
	dec := gob.NewDecoder(file)

	var vc VCard
	err := dec.Decode(&vc)
	if err != nil {
		log.Fatal("decode error:", err)
	}
	fmt.Println(vc)
}
