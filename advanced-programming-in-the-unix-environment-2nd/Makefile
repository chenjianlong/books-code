DIRS = lib\
	   ch01\
	   ch02\
	   ch03\
	   ch04

all:
	$(MAKE) `./systype.sh`

clean:
	for i in $(DIRS); do \
		(cd $$i && $(MAKE) -f `../systype.sh`.mk clean) || exit 1; \
	done

freebsd:
	for i in $(DIRS); do \
		(cd $$i && $(MAKE) -f freebsd.mk WKDIR=$(CURDIR)) || exit 1; \
	done

linux:
	for i in $(DIRS); do \
		(cd $$i && $(MAKE) -f linux.mk WKDIR=$(CURDIR)) || exit 1; \
	done

macos:
	for i in $(DIRS); do \
		(cd $$i && $(MAKE) -f macos.mk WKDIR=$(CURDIR)) || exit 1; \
	done

solaris:
	for i in $(DIRS); do \
		(cd $$i && $(MAKE) -f solaris.mk WKDIR=$(CURDIR)) || exit 1; \
	done
