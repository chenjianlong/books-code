# file Makefile
# brief this file is use to build smart_ptr example
# author Jianlong Chen <jianlong99@gmail.com>

PROG = smart_ptr_test

all: $(PROG)

smart_ptr_test: smart_ptr_test.cpp

install:
	$(Q) install -d $(DESTDIR)/bin && install $(PROG) $(DESTDIR)/bin/

clean:
	$(Q) -rm $(PROG)

