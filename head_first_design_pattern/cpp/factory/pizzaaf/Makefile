# file Makefile
# brief this file is use to generate pizza_abstract_factory
# author Jianlong Chen  <jianlong99@gmail.com>
# date 2013-05-31
# $Id$

PROG = pizza_abstract_factory
export CXXFLAGS += -I$(BOOST_ROOT)
include ../../depend.make

OBJS = black_olives.o\
	   cheese_pizza.o\
	   chicago_pizza_ingredient_factory.o\
	   chicago_pizza_store.o\
	   clam_pizza.o\
	   eggplant.o\
	   fresh_clams.o\
	   frozen_clams.o\
	   garlic.o\
	   main.o\
	   marinara_sauce.o\
	   mozzarella_cheese.o\
	   mushroom.o\
	   ny_pizza_ingredient_factory.o\
	   ny_pizza_store.o\
	   onion.o\
	   parmesam_cheese.o\
	   pepperoni_pizza.o\
	   pizza.o\
	   pizza_store.o\
	   pizza_test_drive.o\
	   plum_tomato_sauce.o\
	   red_pepper.o\
	   reggiano_cheese.o\
	   sliced_pepperoni.o\
	   spinach.o\
	   thick_crust_dough.o\
	   thin_crust_dough.o\
	   veggie_pizza.o

.PHONY: all clean
all: $(PROG)

$(PROG): $(OBJS)
	$(CXX) $^ -o $@

-include $(OBJS:.o=.d)

clean:
	$(Q) -rm *.d *.o $(PROG)

