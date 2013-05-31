# file depend.make
# brief this file is use to generate dpend rule for c/cpp
# author Jianlong Chen  <jianlong99@gmail.com>
# date 2013-05-30
# $Id$

%.d: %.cpp
	@set -e; rm -f $@;\
	$(CXX) -MM $(CXXFLAGS) $< > $@.$$$$;\
	sed 's#\($*\).o[ :]*#\1$.o $@: #g' < $@.$$$$ > $@;\
	rm -f $@.$$$$

