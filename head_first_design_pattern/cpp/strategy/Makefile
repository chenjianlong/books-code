# file Makefile
# brief this is the Makefile to build mini_duck_simulator 
# author Jianlong Chen <jianlong99@gmail.com>
# date 2013-05-28
# $Id$

PROG = mini_duck_simulator
include ../depend.make

OBJS = decoy_duck.o\
	   duck.o\
	   fake_quack.o\
	   fly_no_way.o\
	   fly_rocket_powered.o\
	   fly_with_wings.o\
	   main.o\
	   mallard_duck.o\
	   mini_duck_simulator.o\
	   model_duck.o\
	   mute_quack.o\
	   quack.o\
	   red_head_duck.o\
	   rubber_duck.o\
	   squeak.o



.PHONY: all clean
all: $(PROG)

$(PROG): $(OBJS)
	$(CXX)  $^ -o $@

-include $(OBJS:.o=.d)

clean:
	$(Q) -rm *.d *.o $(PROG)

