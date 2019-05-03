package main

import (
	"fmt"
	"io"
	"net/http"
	"strconv"
	"strings"
)

const head = `
<html><body>
	<h2>Statistics</h2>
	<label>Computes basic statistics for a given list of numbers</label>
	<br />
`

const form = `
	<form action="#" method="post" name="bar">
		<label>Numbers(space seperate)</label>
		<br />
		<input type="text" name="nums" />
		<input type="submit" value="Calculate"/>
	</form>
`

const foot = `
</body></html>
`

func getMedian(nums []float64) float64 {
	n := len(nums)
	if n == 0 {
		return 0.0
	}

	if n%2 == 0 {
		return (nums[n/2] + nums[n/2-1]) / 2.0
	}

	return nums[n/2]
}

func getMean(nums []float64) float64 {
	n := len(nums)
	if n == 0 {
		return 0.0
	}

	sum := float64(0.0)
	for _, v := range nums {
		sum += v
	}

	return sum / float64(n)
}

func processNumbers(s string) (mean float64, median float64, err error) {
	fields := strings.Fields(s)
	nums := make([]float64, len(fields))
	for _, v := range fields {
		n, e := strconv.ParseFloat(v, 64)
		if e != nil {
			err = e
			return
		}

		nums = append(nums, n)
	}

	mean = getMean(nums)
	median = getMedian(nums)
	return
}

const tableTpl = `<table border="1">
<tr><th colspan="2">Result</th></tr>
<tr><th>Numbers</th><td>%s</td></tr>
<tr><th>Mean</th><td>%v</td></tr>
<tr><th>Median</th><td>%v</td></tr>
</table>
`

func FormServer(w http.ResponseWriter, request *http.Request) {
	w.Header().Set("Content-Type", "text/html")
	switch request.Method {
	case "GET":
		/* display the form to the user */
		io.WriteString(w, head)
		io.WriteString(w, form)
		io.WriteString(w, foot)
	case "POST":
		/* handle the form data, note that ParseForm must
		be called before we can extract form data */
		//request.ParseForm();
		//io.WriteString(w, request.Form["in"][0])
		io.WriteString(w, head)
		io.WriteString(w, form)
		mean, median, err := processNumbers(request.FormValue("nums"))
		if err != nil {
			io.WriteString(w, "<p>Invalid Input</p>")
		} else {
			result := fmt.Sprintf(tableTpl, request.FormValue("nums"), mean, median)
			io.WriteString(w, result)
		}
		io.WriteString(w, foot)
	}
}

func main() {
	http.HandleFunc("/", FormServer)
	if err := http.ListenAndServe(":9001", nil); err != nil {
		panic(err)
	}
}
