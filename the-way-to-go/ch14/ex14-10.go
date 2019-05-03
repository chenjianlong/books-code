//
// ex14-10.go
// Copyright (C) 2019 Jianlong Chen <jianlong99@gmail.com>
//
// Distributed under terms of the MIT license.
//

package main

import (
	"bufio"
	"fmt"
	"math"
	"os"
	"strconv"
)

type Ploar struct {
	radius float64
	radian float64
}

type Cartesian struct {
	x float64
	y float64
}

func main() {
	p := make(chan Ploar)
	c := make(chan Cartesian)
	defer close(p)
	defer close(c)
	go PloarToCartesian(p, c)
	interact(p, c)
}

func interact(pchan chan<- Ploar, cchan <-chan Cartesian) {
	for {
		ploar, err := getPloar()
		if err != nil {
			fmt.Println(err)
			os.Exit(1)
		}

		pchan <- ploar
		point, ok := <-cchan
		if !ok {
			break
		}

		fmt.Printf("Answer x=%f, y=%f\n", point.x, point.y)
	}
}

var inputReader *bufio.Reader
var input string

func getPloar() (Ploar, error) {
	fmt.Println("Please input radius")
	var ploar Ploar
	inputReader = bufio.NewReader(os.Stdin)
	input, err := inputReader.ReadString('\n')
	if err != nil {
		return Ploar{0, 0}, err
	}

	input = input[:len(input)-1]
	ploar.radius, err = strconv.ParseFloat(input, 64)
	if err != nil {
		return Ploar{0, 0}, err
	}

	fmt.Println("Please input radian")
	input, err = inputReader.ReadString('\n')
	if err != nil {
		return Ploar{0, 0}, err
	}

	input = input[:len(input)-1]
	ploar.radian, err = strconv.ParseFloat(input, 64)
	if err != nil {
		return Ploar{0, 0}, err
	}

	return ploar, nil
}

func PloarToCartesian(pchan <-chan Ploar, c chan<- Cartesian) {
	for {
		p, ok := <-pchan
		if !ok {
			break
		}

		var point Cartesian
		point.x = math.Cos(p.radian) * p.radius
		point.y = math.Sin(p.radian) * p.radius
		c <- point
	}
}
