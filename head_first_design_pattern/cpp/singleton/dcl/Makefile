# file Makefile
# brief this file is use to build dcl
# author Jianlong Chen  <jianlong99@gmail.com>
# date 2013-05-31
# $Id$

PROG = dcl
export CXXFLAGS += -I$(BOOST_ROOT)
include ../../depend.make

OBJS = main.o\
	   singleton.o\
	   singleton_client.o

.PHONY: all clean
all: $(PROG)

$(PROG): $(OBJS)
	$(CXX) $^ -o $@ -L$(BOOST_ROOT)/stage/lib -lboost_system

-include $(OBJS:.o=.d)

clean:
	$(Q) -rm *.d *.o $(PROG)

