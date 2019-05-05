package main

import (
	"fmt"
	"os"
)

func main() {
	userFile := "astaxie.txt"
	fl, err := os.Open(userFile)
	if err != nil {
		fmt.Println(err.(*os.PathError))
		return
	}
	defer fl.Close()
	buf := make([]byte, 1024)
	for {
		n, _ := fl.Read(buf)
		if 0 == n {
			break
		}
		os.Stdout.Write(buf[:n])
	}
}
