#! /bin/sh
#
# bench.sh
# Copyright (C) 2019 Jianlong Chen <jianlong99@gmail.com>
#
# Distributed under terms of the MIT license.
#


go test gotest.go webbench_test.go -test.bench=".*"
