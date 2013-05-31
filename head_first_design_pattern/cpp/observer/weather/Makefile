# file Makefile
# brief this is the Makefile to build weather_station
# author Jianlong Chen <jianlong99@gmail.com>
# date 2013-05-30
# $Id$

PROG = weather_station
include ../../depend.make

OBJS = current_conditions_display.o\
	   forecase_display.o\
	   heat_index_display.o\
	   main.o\
	   statistics_display.o\
	   weather_data.o\
	   weather_station.o


.PHONY: all clean
all: $(PROG)

$(PROG): $(OBJS)
	$(CXX) $^ -o $@

-include $(OBJS:.o=.d)

install:
	mkdir -p $(DESTDIR)/bin/ && cp $(PROG) $(DESTDIR)/bin/

clean:
	$(Q) -rm *.d *.o $(PROG)

