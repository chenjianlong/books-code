# file Makefile
# brief this file is the top level of Makefile
# author Jianlong Chen <jianlong99@gmail.com>
# date 2013-05-31
# $Id$

export DESTDIR = $(shell pwd)
SUB_DIRS := auto_ptr_test\
			shared_ptr_test\
			shared_ptr_circular_ref_test\
			weak_ptr_test\
			intrusive_ptr_test

.PHONY: all clean
all: $(SUB_DIRS)
	@set -e;$(foreach n,$(SUB_DIRS),$(MAKE) -C $(n);)

install:
	@set -e;$(foreach n,$(SUB_DIRS),$(MAKE) -C $(n) install;)

clean:
	@set -e;$(foreach n,$(SUB_DIRS),$(MAKE) -C $(n) clean;)

