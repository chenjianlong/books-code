include ../Make.defines.macos

PROGS =	fig10.2\
		fig10.5\
		fig10.6\
		fig10.9\
		fig10.10\
		fig10.11\
		fig10.15\
		fig10.20\
		fig10.22\
		fig10.23\
		fig10.26\
		fig10.30\
		ex10.6

all:	${PROGS}

savedid: savedid.o
		$(LINK.c) -o savedid savedid.o $(LDLIBS)

clean:
	rm -f ${PROGS} ${TEMPFILES}
