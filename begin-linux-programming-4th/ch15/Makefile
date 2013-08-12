# file Makefile
# brief this file is use to build ch15 example
# author Jianlong Chen <jianlong99@gmail.com>
# date 2013-08-11
# $Id$
CFLAGS:= $(CFLAGS) -Wall -pedantic

PROG = client1\
	   server1\
	   client2\
	   server2\
	   client3\
	   server3\
	   getname\
	   getdate\
	   server4\
	   select\
	   server5\
	   getdate-udp

.PHONY: all app install clean
all: $(PROG)

client1: client1.c
server1: server1.c
client2: client2.c
server2: server2.c
client3: client3.c
server3: server3.c
getname: getname.c
getdate: getdate.c
server4: server4.c
select: select.c
server5: server5.c
getdate-udp: getdate-udp.c

install:
	$(Q) install -d $(DESTDIR)/bin/ && install $(PROG) $(DESTDIR)/bin

clean:
	$(Q) -rm $(PROG)

