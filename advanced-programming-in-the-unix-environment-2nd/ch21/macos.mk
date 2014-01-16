include ../Make.defines.macos
EXTRA=-DDEBUG -DOS_INLINE=static

PROGS = print printd
HDRS = print.h ipp.h

all:	${PROGS} 

util.o:		util.c ${HDRS}

print.o:	print.c ${HDRS}

printd.o:	printd.c ${HDRS}

print:		print.o util.o clconn.o
		$(CC) $(CFLAGS) -o print print.o util.o clconn.o $(LDFLAGS) $(LDLIBS)

printd:		printd.o util.o clconn.o initsrv2.o
		$(CC) $(CFLAGS) -o printd printd.o util.o clconn.o initsrv2.o $(LDFLAGS) $(LDLIBS) -lpthread

clean:
	rm -f ${PROGS} ${TEMPFILES} *.o

