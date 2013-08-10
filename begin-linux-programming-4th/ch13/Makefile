# file Makefile
# brief this file is use to build ch13 example
# author Jianlong Chen <jianlong99@gmail.com>
# date 2013-07-23
# $Id$
CFLAGS:= $(CFLAGS) -Wall -pedantic

PROG = popen1\
	   popen2\
	   popen3\
	   popen4\
	   pipe1\
	   pipe2\
	   pipe3\
	   pipe4\
	   pipe5\
	   fifo1\
	   fifo2\
	   fifo3\
	   fifo4\
	   server\
	   client

.PHONY: all app install clean
all: $(PROG) app

popen1: popen1.c
popen2: popen2.c
popen3: popen3.c
popen4: popen4.c
pipe1: pipe1.c
pipe2: pipe2.c
pipe3: pipe3.c
pipe4: pipe4.c
pipe5: pipe5.c
fifo1: fifo1.c
fifo2: fifo2.c
fifo3: fifo3.c
fifo4: fifo4.c
server: server.c client.h
client: client.c client.h

app:
	$(MAKE) -C app

install:
	$(Q) install -d $(DESTDIR)/bin/ && install $(PROG) $(DESTDIR)/bin
	$(Q) $(MAKE) -C app install

clean:
	$(Q) -rm $(PROG)
	$(Q) $(MAKE) -C app clean

