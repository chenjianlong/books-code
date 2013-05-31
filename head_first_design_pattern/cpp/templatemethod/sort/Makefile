# file Makefile
# brief this file is use to build sort
# author Jianlong Chen <jianlong99@gmail.com>
# date 2013-05-31
# $Id$

PROG = sort
include ../../depend.make

OBJS = ducks.o\
	   duck_sort_test_drive.o\
	   main.o

.PHONY: all clean
all: $(PROG)

-include $(OBJS:.o=.d)

clean:
	$(Q) -rm *.d *.o $(PROG)

