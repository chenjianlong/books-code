# file Makefile
# brief this build is use to build ch03 example
# author Jianlong Chen <jianlong99@gmail.com>
# date 2013-06-02
# $Id$

PROG = simple_read\
	   simple_write\
	   copy_system\
	   copy_block\
	   copy_stdio\
	   print_dir\
	   mmap

all: $(PROG)

simple_read: simple_read.c
simple_write: simple_write.c
copy_system: copy_system.c
copy_block: copy_block.c
copy_stdio: copy_stdio.c
print_dir: print_dir.c
mmap: mmap.c

install:
	$(Q) install -d $(DESTDIR)/bin && install $(PROG) $(DESTDIR)/bin/

clean:
	$(Q) -rm $(PROG)

