include ../Make.defines.linux

PROGS =	fig7.1\
		fig7.3\
		fig7.4\
		fig7.11\
		fig7.13\
		fig7.13_opti\
		fig7.16

all:	${PROGS}

fig7.13_opti: fig7.13.c
	$(CC) -O $^ -o $@ $(CFLAGS) $(LDLIBS)

savedid: savedid.o
		$(LINK.c) -o savedid savedid.o $(LDLIBS)

clean:
	rm -f ${PROGS} ${TEMPFILES}
