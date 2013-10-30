include ../Make.defines.macos

PROGS =	fig8.1\
		fig8.3\
		fig8.6\
		fig8.8\
		fig8.12\
		fig8.13\
		fig8.16\
		fig8.17\
		fig8.20\
		fig8.23\
		fig8.24\
		fig8.25\
		fig8.28\
		fig8.29\
		fig8.30\
		ex8.1\
		ex8.2\
		ex8.6\
		ex8.7

all:	${PROGS}

savedid: savedid.o
		$(LINK.c) -o savedid savedid.o $(LDLIBS)

clean:
	rm -f ${PROGS} ${TEMPFILES}
