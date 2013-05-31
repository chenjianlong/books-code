# file Makefile
# brief  this file is use to build gumball
# author Jianlong Chen <jianlong99@gmail.com>
# date 2013-05-31
# $Id$

PROG = gumball
include ../../depend.make

OBJS = gumball_machine.o\
	   gumball_machine_test_drive.o\
	   main.o

.PHONY: all clean
all: $(PROG)

$(PROG): $(OBJS)
	$(CXX) $^ -o $@

-include $(OBJS:.o=.d)

install:
	$(Q) mkdir -p $(DESTDIR)/bin/ && cp $(PROG) $(DESTDIR)/bin/

clean:
	$(Q) -rm *.d *.o $(PROG)

