# file Makefile
# brief this build is use to build ch03 example
# author Jianlong Chen <jianlong99@gmail.com>
# date 2013-06-02
# $Id$

PROG = screen1\
	   moveadd\
	   ipmode\
	   mulitw1\
	   subsc1\
	   keypad\
	   color\
	   pad\
	   curses_app

all: $(PROG)

screen1: screen1.c
	$(CC) $^ -o $@ -lcurses
moveadd: moveadd.c
	$(CC) $^ -o $@ -lcurses
ipmode: ipmode.c
	$(CC) $^ -o $@ -lcurses
mulitw1: multiw1.c
	$(CC) $^ -o $@ -lcurses
subsc1: subsc1.c
	$(CC) $^ -o $@ -lcurses
keypad: keypad.c
	$(CC) $^ -o $@ -lcurses
color: color.c
	$(CC) $^ -o $@ -lcurses
pad: pad.c
	$(CC) $^ -o $@ -lcurses
curses_app: curses_app.c
	$(CC) $^ -o $@ -lcurses

install:
	$(Q) mkdir -p $(DESTDIR)/bin/ && install $(PROG) $(DESTDIR)/bin

clean:
	$(Q) -rm $(PROG)

