include ../Make.defines.solaris
EXTRALIBS=-lpthread

PROGS =	fig12.8\
		fig12.16\
		fig12.17

all:	${PROGS}

savedid: savedid.o
		$(LINK.c) -o savedid savedid.o $(LDLIBS)

clean:
	rm -f ${PROGS} ${TEMPFILES}
