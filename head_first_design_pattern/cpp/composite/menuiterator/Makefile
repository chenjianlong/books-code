# file Makefile
# brief this file is use to build menu_iterator
# author Jianlong Chen <jianlong99@gmail.com>
# date 2013-05-31
# $Id$

PROG = menu_iterator
export CXXFLAGS += -I$(BOOST_ROOT)
include ../../depend.make

OBJS = composite_iterator.o\
	   main.o\
	   menu.o\
	   menu_component.o\
	   menu_item.o\
	   menu_test_drive.o\
	   null_iterator.o\
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

