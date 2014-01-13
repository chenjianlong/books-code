include ../Make.defines.solaris

#
# Makefile for misc library.
#

AR	= ar
LIBMISC	= libapue_db.a
COMM_OBJ   = db.o

all: ${LIBMISC} libapue_db.so.1 fig20.3

libapue_db.a:	${COMM_OBJ}
		${AR} rv ${LIBMISC} ${COMM_OBJ}

libapue_db.so.1:	db.c
		$(CC) -fPIC $(CFLAGS) -c db.c
		$(CC) -shared -o libapue_db.so.1 -L../lib -lapue -lc db.o

#
# NB:
# set LD_LIBRARY_PATH to the directory containing libapue_db.so.1 to run fig20.3
#
fig20.3:		libapue_db.a fig20.3.o
		$(CC) $(CFLAGS) -I. -c fig20.3.c
		$(CC) -o fig20.3 fig20.3.o libapue_db.so.1 -L../lib -lapue

clean:
	rm -f *.o a.out core temp.* $(LIBMISC) fig20.3 libapue_db.so.*
