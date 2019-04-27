package main

import "fmt"

func main() {
	days := map[string]int{"Monday": 1, "Tuesday": 2, "Wednesday": 3, "Thursday": 4, "Friday": 5, "Saturday": 6, "Sunday": 7}

	for key, val := range days {
		fmt.Printf("%s 是星期%d\n", key, val)
	}

	var value int
	var isPresent bool
	value, isPresent = days["Tuesday"]
	if isPresent {
		fmt.Printf("The value of 'Tuseday' in days is: %d\n", value)
	} else {
		fmt.Println("map1 does not contain Tuseday")
	}

	value, isPresent = days["Holiday"]
	if isPresent {
		fmt.Printf("The value of 'Holiday' in days is: %d\n", value)
	} else {
		fmt.Println("days does not contain Holiday")
	}
}
