include ../Make.defines.freebsd

PROGS =	fig16.8\
		fig16.14\
		fig16.15\
		fig16.16\
		fig16.17\
		fig16.18\
		ex16.1\
		ex16.4c\
		ex16.4s\
		ex16.5

all:	${PROGS}

savedid: savedid.o
		$(LINK.c) -o savedid savedid.o $(LDLIBS)

clean:
	rm -f ${PROGS} ${TEMPFILES}
