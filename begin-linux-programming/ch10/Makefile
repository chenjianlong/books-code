# file Makefile
# brief this file is use to build ch10 example
# author Jianlong Chen <jianlong99@gmail.com>
# date 2013-07-23
# $Id$
CFLAGS:= $(CFLAGS) -Wall -pedantic -ansi

PROG = debug1\
	   debug2\
	   debug3\
	   cinfo\
	   debug4\
	   debug5\
	   assert\
	   efence\
	   checker

all: $(PROG)


debug1: debug1.c
debug2: debug2.c
debug3: debug3.c
	$(CC) -o $@ $< $(CFLAGS) -g
cinfo: cinfo.c
	$(CC) -o $@ $< $(CFLAGS) -DDEBUG
debug4: debug4.c
	$(CC) -o $@ $< $(CFLAGS) -g
debug5: debug5.c
	$(CC) -o $@ $< $(CFLAGS) -g -pg
assert: assert.c
	$(CC) -o $@ $< $(CFLAGS) -g -lm
efence: efence.c
	$(CC) -o $@ $< $(CFLAGS) -g -lefence
checker: checker.c

install:
	$(Q) install -d $(DESTDIR)/bin/ && install $(PROG) $(DESTDIR)/bin

clean:
	$(Q) -rm $(PROG)

