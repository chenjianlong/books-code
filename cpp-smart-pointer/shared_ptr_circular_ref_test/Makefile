# file Makefile
# author Jianlong Chen <jianlong99@gmail.com>

PROG = shared_ptr_circular_ref

all: $(PROG)

shared_ptr_circular_ref: shared_ptr_circular_ref.cpp
	g++ -std=c++11 $^ -o $@

install:
	$(Q) install -d $(DESTDIR)/bin && install $(PROG) $(DESTDIR)/bin/

clean:
	$(Q) -rm $(PROG)

