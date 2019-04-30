package main

import (
	"bufio"
	"flag"
	"fmt"
	"io"
	"os"
)

var LineNumber = flag.Bool("n", false, "print line number")

func cat(r *bufio.Reader) {
	ln := 1
	for {
		buf, err := r.ReadBytes('\n')
		if err == io.EOF {
			break
		}
		if *LineNumber {
			fmt.Fprintf(os.Stdout, "%d: %s", ln, buf)
		} else {
			fmt.Fprintf(os.Stdout, "%s", buf)
		}

		ln++
	}
	return
}

func main() {
	flag.Parse()
	if flag.NArg() == 0 {
		cat(bufio.NewReader(os.Stdin))
	}
	for i := 0; i < flag.NArg(); i++ {
		f, err := os.Open(flag.Arg(i))
		if err != nil {
			fmt.Fprintf(os.Stderr, "%s:error reading from %s: %s\n", os.Args[0], flag.Arg(i), err.Error())
			continue
		}
		cat(bufio.NewReader(f))
	}
}
