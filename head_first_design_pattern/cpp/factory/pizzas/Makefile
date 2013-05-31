# file Makefile
# brief this file is use to generate simple_pizza_factory
# author Jianlong Chen <jianlong99@gmail.com>
# date 2013-05-30
# $Id$

PROG = simple_pizza_factory
include ../../depend.make

OBJS = cheese_pizza.o\
	   clam_pizza.o\
	   main.o\
	   pepperon_pizza.o\
	   pizza.o\
	   pizza_store.o\
	   pizza_test_drive.o\
	   simple_pizza_factory.o\
	   veggie_pizza.o

.PHONY: all clean
all: $(PROG)

$(PROG): $(OBJS)
	$(CXX) $^ -o $@

-include $(OBJS:.o=.d)

install:
	$(Q) mkdir -p $(DESTDIR)/bin/ && cp $(PROG) $(DESTDIR)/bin/

clean:
	$(Q) -rm *.d *.o $(PROG)

