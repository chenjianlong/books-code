include ../Make.defines.solaris


PROGS =	ex6.3\
		ex6.5

all:	${PROGS}

savedid: savedid.o
		$(LINK.c) -o savedid savedid.o $(LDLIBS)

clean:
	rm -f ${PROGS} ${TEMPFILES}
