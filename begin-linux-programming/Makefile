# file Makefile
# brief this file is the top level of Makefile
# author Jianlong Chen <jianlong99@gmail.com>
# date 2013-05-31
# $Id$

export DESTDIR = $(shell pwd)
SUB_DIRS := ch03\
			ch04\
			ch05\
			ch06\
			ch07

.PHONY: all clean
all: $(SUB_DIRS)
	@set -e;$(foreach n,$(SUB_DIRS),$(MAKE) -C $(n);)

install:
	@set -e;$(foreach n,$(SUB_DIRS),$(MAKE) -C $(n) install;)

clean:
	@set -e;$(foreach n,$(SUB_DIRS),$(MAKE) -C $(n) clean;)

