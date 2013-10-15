include ../Make.defines.solaris


PROGS =	fig5.4\
		fig5.5\
		fig5.11\
		fig5.12\
		fig5.13

all:	${PROGS}

savedid: savedid.o
		$(LINK.c) -o savedid savedid.o $(LDLIBS)

clean:
	rm -f ${PROGS} ${TEMPFILES}
