# file Makefile
# brief this file is use to build ch11 example
# author Jianlong Chen <jianlong99@gmail.com>
# date 2013-07-23
# $Id$
CFLAGS:= $(CFLAGS) -Wall -pedantic

PROG = system1\
	   system2\
	   pexec\
	   fork1\
	   wait\
	   fork2\
	   upper\
	   useupper\
	   ctrlc1\
	   alarm\
	   ctrlc2

all: $(PROG)

system1: system1.c
system2: system2.c
pexec: pexec.c
fork1: fork1.c
wait: wait.c
fork2: fork2.c
upper: upper.c
useupper: useupper.c
ctrlc1: ctrlc1.c
alarm: alarm.c
ctrlc2: ctrlc2.c

install:
	$(Q) install -d $(DESTDIR)/bin/ && install $(PROG) $(DESTDIR)/bin

clean:
	$(Q) -rm $(PROG)

