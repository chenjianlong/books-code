# file Makefile
# brief this file is use to build diner_merger
# author Jianlong Chen <jianlong99@gmail.com>
# date 2013-05-31
# $Id$

PROG = diner_merger
include ../../depend.make

OBJS = alternating_diner_menu_iterator.o\
	   diner_menu.o\
	   diner_menu_iterator.o\
	   main.o\
	   menu_item.o\
	   menu_test_drive.o\
	   pancake_house_menu.o\
	   pancake_house_menu_iterator.o\
	   waitress.o

.PHONY: all clean
all: $(PROG)

$(PROG): $(OBJS)
	$(CXX) $^ -o $@

-include $(OBJS:.o=.d)

install:
	$(Q) mkdir -p $(DESTDIR)/bin/ && cp $(PROG) $(DESTDIR)/bin/

clean:
	$(Q) -rm *.d *.o $(PROG)

