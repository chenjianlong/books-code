include ../Make.defines.freebsd

PROGS =	pty\
		pty2\
		ex19.10\
		ex19.10b

all:	${PROGS}

pty: fig19.12.o fig19.13.o fig19.17.o
	$(LINK.c) -g -o $@ $^ $(LIB)

# use select version loop
pty2: fig19.12.o ex19.4.o fig19.17.o
	$(LINK.c) -g -o $@ $^ $(LIB)

savedid: savedid.o
		$(LINK.c) -o savedid savedid.o $(LDLIBS)

clean:
	rm -f ${PROGS} ${TEMPFILES}
