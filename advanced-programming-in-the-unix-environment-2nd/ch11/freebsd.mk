include ../Make.defines.freebsd
EXTRALIBS=-pthread

PROGS =	fig11.2\
		fig11.3\
		fig11.4\
		fig11.5\
		ex11.1\
		ex11.3

all:	${PROGS}

savedid: savedid.o
		$(LINK.c) -o savedid savedid.o $(LDLIBS)

clean:
	rm -f ${PROGS} ${TEMPFILES}
