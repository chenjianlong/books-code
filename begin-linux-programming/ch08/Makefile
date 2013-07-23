# file Makefile
# brief this file is use to build ch08 example
# author Jianlong Chen <jianlong99@gmail.com>
# date 2013-06-02
# $Id$
CFLAGS  := $(CFLAGS) -I/usr/include/mysql
LDFLAGS	:= $(LDFLAGS) -L/usr/lib/mysql -lmysqlclient

PROG = connection1\
	   connection2\
	   insert1\
	   update1\
	   insert2\
	   select1\
	   select2\
	   select3\
	   select4\
	   app

all: $(PROG)

connection1: connection1.o
	$(CC) $^ -o $@ $(LDFLAGS)
connection2: connection2.o
	$(CC) $^ -o $@ $(LDFLAGS)
insert1: insert1.o
	$(CC) $^ -o $@ $(LDFLAGS)
update1: update1.o
	$(CC) $^ -o $@ $(LDFLAGS)
insert2: insert2.o
	$(CC) $^ -o $@ $(LDFLAGS)
select1: select1.o
	$(CC) $^ -o $@ $(LDFLAGS)
select2: select2.o
	$(CC) $^ -o $@ $(LDFLAGS)
select3: select3.o
	$(CC) $^ -o $@ $(LDFLAGS)
select4: select4.o
	$(CC) $^ -o $@ $(LDFLAGS)
app: app_mysql.o app_test.o
	$(CC) $^ -o $@ $(LDFLAGS)

install:
	$(Q) install -d $(DESTDIR)/bin/ && install $(PROG) $(DESTDIR)/bin

clean:
	$(Q) -rm $(PROG) *.o

nodbmfiles:
	$(Q) -rm *.dir *.pag

