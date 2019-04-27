package main

import (
	"fmt"
	"sort"
)

func main() {
	drinks := map[string]string{"Coca Cola": "可口可乐", "pepsi": "百事可乐", "Starbucks": "星巴克"}

	fmt.Println("unsort:")
	drinksInEnglish := make([]string, len(drinks))
	i := 0
	for k, v := range drinks {
		fmt.Println(k, v)
		drinksInEnglish[i] = k
		i++
	}

	sort.Strings(drinksInEnglish)
	fmt.Println("sort:")
	for _, k := range drinksInEnglish {
		fmt.Println(k, drinks[k])
	}
}
