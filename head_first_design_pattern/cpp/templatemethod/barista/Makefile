# file Makefile
# brief this file is use to build barista
# author Jianlong Chen <jianlong99@gmail.com>
# date 2013-05-31
# $Id$

PROG = barista
include ../../depend.make

OBJS = beverage_test_drive.o\
	   caffeine_beverage.o\
	   caffeiner_beverage_with_hook.o\
	   coffee.o\
	   coffee_with_hook.o\
	   main.o\
	   tea.o\
	   tea_with_hook.o

.PHONY: all clean
all: $(PROG)

$(PROG): $(OBJS)
	$(CXX) $^ -o $@

-include $(OBJS:.o=.d)

install:
	$(Q) mkdir -p $(DESTDIR)/bin/ && cp $(PROG) $(DESTDIR)/bin/

clean:
	$(Q) -rm *.d *.o $(PROG)

