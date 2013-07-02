# file Makefile
# brief this file is use to generate 
# author Jianlong Chen <jianlong99@gmail.com>
# date 2013-05-30
# $Id$

PROG = pizza_factory_method
include ../../depend.make

OBJS = chicago_pizza_store.o\
	   chicago_style_cheese_pizza.o\
	   chicago_style_clam_pizza.o\
	   chicago_style_pepperoni_pizza.o\
	   chicago_style_veggie_pizza.o\
	   main.o\
	   ny_pizza_store.o\
	   ny_style_cheese_pizza.o\
	   ny_style_clam_pizza.o\
	   ny_style_pepperoni_pizza.o\
	   ny_style_veggie_pizza.o\
	   pizza.o\
	   pizza_store.o\
	   pizza_test_drive.o

.PHONY: all clean
all: $(PROG)

$(PROG): $(OBJS)
	$(CXX) $^ -o $@

-include $(OBJS:.o=.d)

install:
	$(Q) install -d $(DESTDIR)/bin/ && install $(PROG) $(DESTDIR)/bin/

clean:
	$(Q) -rm *.d *.o $(PROG)

