include ../Make.defines.freebsd

PROGS =	fig18.10\
		fig18.11\
		fig18.16\
		fig18.18\
		fig18.21\
		fig18.22\
		ex18.1

all:	${PROGS}

savedid: savedid.o
		$(LINK.c) -o savedid savedid.o $(LDLIBS)

clean:
	rm -f ${PROGS} ${TEMPFILES}
