# file Makefile
# brief this file is use to build home_theater
# author Jianlong Chen <jianlong99@gmail.com>
# date 2013-05-31
# $Id$

PROG = home_theater
include ../../depend.make

OBJS = amplifier.o\
	   cd_player.o\
	   dvd_player.o\
	   home_theater_facade.o\
	   home_theater_test_drive.o\
	   main.o\
	   popcorn_popper.o\
	   projector.o\
	   screen.o\
	   theater_lights.o\
	   tuner.o

.PHONY: all clean
all: $(PROG)

$(PROG): $(OBJS)
	$(CXX) $^ -o $@

-include $(OBJS:.o=.d)

