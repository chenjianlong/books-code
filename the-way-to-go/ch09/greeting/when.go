package greeting

import "time"

func IsEvening() bool {
	n := time.Now()
	return n.Hour() >= 20
}
