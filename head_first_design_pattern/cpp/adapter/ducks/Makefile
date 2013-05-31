# file Makefile
# brief this file is use to build ducks_adapter
# author Jianlong Chen <jianlong99@gmail.com>
# date 2013-05-31
# $Id$

PROG = ducks_adapter
include ../../depend.make

OBJS = ducks_adapter.o\
	   duck_test_drive.o\
	   main.o\
	   mallard_duck.o\
	   turkey_adapter.o\
	   turkey_test_drive.o\
	   wild_turkey.o

.PHONY: all clean
all: $(PROG)

$(PROG): $(OBJS)
	$(CXX) $^ -o $@

-include $(OBJS:.o=.d)

clean:
	$(Q) -rm *.d *.o $(PROG)

