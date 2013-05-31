# file Makefile
# brief this file is the top level of Makefile
# author Jianlong Chen <jianlong99@gmail.com>
# date 2013-05-31
# $Id$

SUB_DIRS := strategy\
		   observer/weather\
		   decorator/starbuzz\
		   factory/pizzas\
		   factory/pizzafm\
		   factory/pizzaaf\
		   singleton/chocolate\
		   singleton/dcl\
		   singleton/stat\
		   command/party\
		   adapter/ducks\
		   facade/hometheater\
		   templatemethod/simplebarista\
		   templatemethod/barista\
		   templatemethod/sort\
		   iterator/dinermerger\
		   iterator/dinermergercafe\
		   composite/menu\
		   composite/menuiterator\
		   state/gumball\
		   state/gumballstate\
		   state/gumballstatewinner\
		   proxy/gumballmonitor

.PHONY: all clean
all: $(SUB_DIRS)
	@set -e;$(foreach n,$(SUB_DIRS),$(MAKE) -C $(n);)

clean:
	@set -e;$(foreach n,$(SUB_DIRS),$(MAKE) -C $(n) clean;)


