# file Makefile
# brief this file is use to build ch14 example
# author Jianlong Chen <jianlong99@gmail.com>
# date 2013-08-10
# $Id$
CFLAGS:= $(CFLAGS) -Wall -pedantic

PROG = sem1\
	   shm1\
	   shm2\
	   msg1\
	   msg2

.PHONY: all app install clean
all: $(PROG) app

sem1: sem1.c
shm1: shm1.c
shm2: shm2.c
msg1: msg1.c
msg2: msg2.c

app:
	$(MAKE) -C app

install:
	$(Q) install -d $(DESTDIR)/bin/ && install $(PROG) $(DESTDIR)/bin
	$(Q) $(MAKE) -C app install

clean:
	$(Q) -rm $(PROG)
	$(Q) $(MAKE) -C app clean

