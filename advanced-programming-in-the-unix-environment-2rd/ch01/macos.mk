include ../Make.defines.macos

PROGS =	fig1.3\
		fig1.4\
		fig1.5\
		fig1.6\
		fig1.7\
		fig1.8\
		fig1.9\
		fig1.10

all:	${PROGS}

clean:
	rm -f ${PROGS} ${TEMPFILES}
