# file Makefile
# author Jianlong Chen 
# date 2013-05-28
# $Id$

PROG = mini_duck_simulator

ifeq ($(OS),Windows_NT)
	OBJ_EXT := .obj
else
	OBJ_EXT := .o
	CC := g++
endif

OBJS = decoy_duck$(OBJ_EXT)\
	   duck$(OBJ_EXT) fake_quack$(OBJ_EXT)\
	   fly_no_way$(OBJ_EXT)\
	   fly_rocket_powered$(OBJ_EXT)\
	   fly_with_wings$(OBJ_EXT)\
	   main$(OBJ_EXT)\
	   mallard_duck$(OBJ_EXT)\
	   mini_duck_simulator$(OBJ_EXT)\
	   model_duck$(OBJ_EXT)\
	   mute_quack$(OBJ_EXT)\
	   quack$(OBJ_EXT)\
	   red_head_duck$(OBJ_EXT)\
	   rubber_duck$(OBJ_EXT)\
	   squeak$(OBJ_EXT)


%.d: %.cpp
	@set -e; rm -f $@;\
	$(CC) -MM $(CPPFLAGS) $< > $@.$$$$;\
	sed 's#\($*\)$(OBJ_EXT)[ :]*#\1$(OBJ_EXT) $@: #g' < $@.$$$$ > $@;\
	rm -f $@.$$$$

.PHONY: all clean
all: $(PROG)

$(PROG): $(OBJS)
	$(CC)  $(OBJS) -o $(PROG)

-include $(OBJS:$(OBJ_EXT)=.d)

clean:
	-@rm *.d *$(OBJ_EXT) $(PROG)

