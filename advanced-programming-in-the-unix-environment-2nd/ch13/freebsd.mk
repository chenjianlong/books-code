include ../Make.defines.freebsd
EXTRALIBS=-pthread

PROGS =	fig13.7\
		fig13.8\
		ex13.1\
		ex13.3

all:	${PROGS}

savedid: savedid.o
		$(LINK.c) -o savedid savedid.o $(LDLIBS)

clean:
	rm -f ${PROGS} ${TEMPFILES}
