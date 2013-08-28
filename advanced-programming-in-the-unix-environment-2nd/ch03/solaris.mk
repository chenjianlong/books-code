include ../Make.defines.solaris

PROGS =	fig3.1\
		fig3.2\
		fig3.10\
		ex3.6

all:	${PROGS}

savedid: savedid.o
		$(LINK.c) -o savedid savedid.o $(LDLIBS)

clean:
	rm -f ${PROGS} ${TEMPFILES} file.hole test.dat
