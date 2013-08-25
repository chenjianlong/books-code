include ../Make.defines.linux

PROGS = conf options

all:	${PROGS}

conf:	conf.c

conf.c: makeconf.awk
	nawk -f $^ >$@

options:	options.c

options.c:
	nawk -f makeopt.awk >options.c

clean:
	rm -f ${PROGS} ${TEMPFILES} options.c conf.c
