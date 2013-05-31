# file Makefile
# brief this file is use to build menu
# author Jianlong Chen <jianlong99@gmail.com>
# date 2013-05-31
# $Id$

PROG = menu
CXXFLAGS += -I$(BOOST_ROOT)
include ../../depend.make

OBJS = main.o\
	   menu.o\
	   menu_component.o\
	   menu_item.o\
	   menu_test_drive.o\
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

