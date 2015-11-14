# file Makefile
# author Jianlong Chen <jianlong99@gmail.com>

PROG = intrusive_ptr_test

all: $(PROG)

intrusive_ptr_test: intrusive_ptr_test.cpp
	g++ -std=c++11 $^ -o $@

install:
	$(Q) install -d $(DESTDIR)/bin && install $(PROG) $(DESTDIR)/bin/

clean:
	$(Q) -rm $(PROG)

