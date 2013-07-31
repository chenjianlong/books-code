# file Makefile
# brief this file is use to build ch12 example
# author Jianlong Chen <jianlong99@gmail.com>
# date 2013-07-23
# $Id$
CFLAGS:= $(CFLAGS) -Wall -pedantic -D_REENTRANT -pthread

PROG = thread1\
	   thread2\
	   thread3\
	   thread3a\
	   thread4\
	   thread5\
	   thread6\
	   thread7\
	   thread8\
	   thread8a

all: $(PROG)

thread1: thread1.c
thread2: thread2.c
thread3: thread3.c
thread3a: thread3a.c
thread4: thread4.c
thread5: thread5.c
thread6: thread6.c
thread7: thread7.c
thread8: thread8.c
thread8a: thread8a.c

install:
	$(Q) install -d $(DESTDIR)/bin/ && install $(PROG) $(DESTDIR)/bin

clean:
	$(Q) -rm $(PROG)

