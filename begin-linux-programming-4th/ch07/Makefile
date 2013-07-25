# file Makefile
# brief this file is use to build ch07 example
# author Jianlong Chen <jianlong99@gmail.com>
# date 2013-06-02
# $Id$

PROG = memory1\
	   memory2\
	   memory3\
	   memory4\
	   memory5a\
	   memory5b\
	   memory6\
	   lock1\
	   lock2\
	   lock3\
	   lock4\
	   lock5\
	   dbm1\
	   dbm2\
	   application

all: $(PROG)

memory1: memory1.c
memory2: memory2.c
memory3: memory3.c
memory4: memory4.c
memory5a: memory5a.c
memory5b: memory5b.c
memory6: memory6.c
lock1: lock1.c
lock2: lock2.c
lock3: lock3.c
lock4: lock4.c
lock5: lock5.c
dbm1: dbm1.c
	$(CC) $^ -o $@ -lgdbm_compat -lgdbm
dbm2: dbm2.c
	$(CC) $^ -o $@ -lgdbm_compat -lgdbm
application: app_ui.o cd_access.o
	$(CC) $^ -o $@ -lgdbm_compat -lgdbm
app_ui.o: app_ui.c cd_data.h
	$(CC) -c app_ui.c
cd_access.o: cd_access.c cd_data.h
	$(CC) -c cd_access.c

install:
	$(Q) install -d $(DESTDIR)/bin/ && install $(PROG) $(DESTDIR)/bin

clean:
	$(Q) -rm $(PROG) *.o

nodbmfiles:
	$(Q) -rm *.dir *.pag

