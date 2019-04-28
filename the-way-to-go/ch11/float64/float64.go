package float64

import (
	"math/rand"
	"strconv"
)

type Float64Array []float64

func (p Float64Array) Len() int           { return len(p) }
func (p Float64Array) Less(i, j int) bool { return p[i] < p[j] }
func (p Float64Array) Swap(i, j int)      { p[i], p[j] = p[j], p[i] }

func NewFloat64Array(n int) (res Float64Array) {
	res = make(Float64Array, n)
	return
}

func Fill(n int) (res Float64Array) {
	res = NewFloat64Array(n)
	for i := 0; i < n; i++ {
		res[i] = rand.Float64()
	}

	return
}

func List(l Float64Array) (res string) {
	res = "["
	for idx, v := range l {
		res += strconv.FormatFloat(v, 'f', -1, 64)
		if idx != len(l)-1 {
			res += ", "
		}
	}

	res += "]"
	return
}

func (self Float64Array) String() string {
	return List(self)
}
