include ../Make.defines.macos

PROGS =	fig14.1\
		fig14.7\
		fig14.12\
		fig14.19\
		ex14.1\
		ex14.6\
		ex14.8\
		ex14.11

all:	${PROGS}

savedid: savedid.o
		$(LINK.c) -o savedid savedid.o $(LDLIBS)

clean:
	rm -f ${PROGS} ${TEMPFILES}
