# file Makefile
# brief this file is use to build gumball_state
# author Jianlong Chen <jianlong99@gmail.com>
# date 2013-05-31
# $Id$

PROG = gumball_state
include ../../depend.make

OBJS = gumball_machine.o\
	   gumball_machine_test_drive.o\
	   has_quarter_state.o\
	   main.o\
	   no_quarter_state.o\
	   sold_out_state.o\
	   sold_state.o

.PHONY: all clean
all: $(PROG)

$(PROG): $(OBJS)
	$(CXX) $^ -o $@

-include $(OBJS:.o=.d)

clean:
	$(Q) -rm *.d *.o $(PROG)

