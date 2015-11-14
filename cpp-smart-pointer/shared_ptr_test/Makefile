# file Makefile
# author Jianlong Chen <jianlong99@gmail.com>

PROG = shared_ptr_test

all: $(PROG)

shared_ptr_test: shared_ptr_test.cpp
	g++ -std=c++11 $^ -o $@

install:
	$(Q) install -d $(DESTDIR)/bin && install $(PROG) $(DESTDIR)/bin/

clean:
	$(Q) -rm $(PROG)

