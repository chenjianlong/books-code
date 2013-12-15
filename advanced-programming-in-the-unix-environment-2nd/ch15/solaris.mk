include ../Make.defines.solaris

PROGS =	fig15.5\
		fig15.6\
		fig15.11\
		fig15.14\
		fig15.15\
		fig15.17\
		fig15.18\
		fig15.19\
		fig15.31\
		fig15.33\
		ex15.3\
		ex15.4\
		ex15.5\
		ex15.12\
		ex15.15\
		ex15.16\
		ex15.17

all:	${PROGS}

savedid: savedid.o
		$(LINK.c) -o savedid savedid.o $(LDLIBS)

clean:
	rm -f ${PROGS} ${TEMPFILES}
