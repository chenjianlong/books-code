//
// string_reverse_test.go
// Copyright (C) 2019 Jianlong Chen <jianlong99@gmail.com>
//
// Distributed under terms of the MIT license.
//

package strev

import "testing"

func TestRev(t *testing.T) {
	if Reverse("Hello") != "olleH" {
		t.Log("Hello reverse is olleH, not", Reverse("Hello"))
		t.Fail()
	}
}
