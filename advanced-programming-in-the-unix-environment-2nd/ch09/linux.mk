include ../Make.defines.linux

PROGS =	fig9.11\
		ex9.2

all:	${PROGS}

savedid: savedid.o
		$(LINK.c) -o savedid savedid.o $(LDLIBS)

clean:
	rm -f ${PROGS} ${TEMPFILES}
