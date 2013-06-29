# file Makefile
# brief this file is use to generate starbuzz_coffee
# author Jianlong Chen <jianlong99@gmail.com>
# date 2013-05-30
# $Id$

PROG = starbuzz_coffee
include ../../depend.make

OBJS = dark_roast.o\
	   decaf.o\
	   espresso.o\
	   house_blend.o\
	   main.o\
	   milk.o\
	   mocha.o\
	   soy.o\
	   starbuzz_coffee.o\
	   whip.o

.PHONY: all clean
all: $(PROG)

$(PROG): $(OBJS)
	$(CXX) $^ -o $@

-include $(OBJS:.o=.d)

install:
	$(Q) mkdir -p $(DESTDIR)/bin/ && install $(PROG) $(DESTDIR)/bin/

clean:
	$(Q) -rm *.d *.o $(PROG)

