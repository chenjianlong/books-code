# file Makefile
# brief this file is use to build shared_ptr example
# author Jianlong Chen <jianlong99@gmail.com>

PROG = weak_ptr_test \
		my_weak_ptr_test

all: $(PROG)

weak_ptr_test: weak_ptr_test.cpp
	g++ -std=c++11 $^ -o $@

my_weak_ptr_test: my_weak_ptr_test.cpp
	g++ -std=c++11 $^ -o $@

install:
	$(Q) install -d $(DESTDIR)/bin && install $(PROG) $(DESTDIR)/bin/

clean:
	$(Q) -rm $(PROG)

