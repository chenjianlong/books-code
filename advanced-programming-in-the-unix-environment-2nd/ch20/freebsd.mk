include ../Make.defines.freebsd
CFLAGS=-DLINUX -ansi -I$(WKDIR)/include -Wall

#
# Makefile for misc library.
#

AR	= ar
LIBMISC	= libapue_db.a
COMM_OBJ   = db.o
RANLIB     = ranlib

all: ${LIBMISC} libapue_db.so.1 fig20.3 ex20.7.a

libapue_db.a:	${COMM_OBJ}
	${AR} rv ${LIBMISC} ${COMM_OBJ}
	${RANLIB} ${LIBMISC}

ex20.7.a: ex20.7.o
	${AR} rv ex20.7.a ex20.7.o
	${RANLIB} ex20.7.a

libapue_db.so.1:	db.c
	$(CC) -fPIC $(CFLAGS) -c db.c
	$(CC) -shared -Wl,-soname,libapue_db.so.1 -o libapue_db.so.1 -L../lib -lapue -lc db.o

fig20.3:	libapue_db.a fig20.3.o
	$(LINK.c) -o fig20.3 fig20.3.o libapue_db.a $(LDLIBS)

clean:
	rm -f *.o a.out core temp.* $(LIBMISC) fig20.3 libapue_db.so.* *.idx *.dat ex20.7.a
