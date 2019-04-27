package main

import "./greeting"

func main() {
	if greeting.IsEvening() {
		greeting.GoodNight()
	} else {
		greeting.GoodDay()
	}
}
