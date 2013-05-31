# file Makefile
# brief this file is use to build party
# author Jianlong Chen <jianlong99@gmail.com>
# date 2013-05-31
# $Id$

PROG = party
include ../../depend.make

OBJS = ceiling_fan.o\
	   ceiling_fan_high_command.o\
	   ceiling_fan_medium_command.o\
	   ceiling_fan_off_command.o\
	   hottub.o\
	   hottub_off_command.o\
	   hottub_on_command.o\
	   light.o\
	   light_off_command.o\
	   light_on_command.o\
	   livingroom_light_off_command.o\
	   livingroom_light_on_command.o\
	   macro_command.o\
	   main.o\
	   no_command.o\
	   remote_control.o\
	   remote_loader.o\
	   stereo.o\
	   stereo_off_command.o\
	   stereo_on_command.o\
	   stereo_on_with_cd_command.o\
	   tv.o\
	   tv_off_command.o\
	   tv_on_command.o

.PHONY: all clean
all: $(PROG)

$(PROG): $(OBJS)
	$(CXX) $^ -o $@

-include $(OBJS:.o=.d)

clean:
	$(Q) -rm *.d *.o $(PROG)

