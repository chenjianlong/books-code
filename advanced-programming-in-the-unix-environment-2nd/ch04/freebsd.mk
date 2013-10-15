include ../Make.defines.freebsd

PROGS =	fig4.3\
		fig4.8\
		fig4.9\
		fig4.12\
		fig4.16\
		fig4.21\
		fig4.22\
		fig4.23\
		fig4.24\
		fig4.25\
		ex4.1\
		ex4.11

all:	${PROGS}

savedid: savedid.o
		$(LINK.c) -o savedid savedid.o $(LDLIBS)

clean:
	rm -f ${PROGS} ${TEMPFILES} bar foo
