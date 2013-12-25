include ../Make.defines.linux

PROGS =	fig17.4\
		fig17.14\
		openc\
		opend\
		openc2\
		opend2\
		ex17.2

all:	${PROGS}

openc: fig17.27.o fig17.28.o
	$(LINK.c) -g -o $@ $^ $(LIB)

opend: fig17.30.o fig17.31.o fig17.32.o fig17.33.o
	$(LINK.c) -g -o $@ $^ $(LIB)

openc2: fig17.27.o fig17.34.o
	$(LINK.c) -g -o $@ $^ $(LIB)

opend2: fig17.32.o fig17.33.o fig17.36.o fig17.37.o fig17.38.o fig17.40.o
	$(LINK.c) -g -o $@ $^ $(LIB)

savedid: savedid.o
		$(LINK.c) -o savedid savedid.o $(LDLIBS)

clean:
	rm -f ${PROGS} ${TEMPFILES}
