DIRS = lib\
	   ch01\
	   ch02\
	   ch03\
	   ch04\
	   ch05\
	   ch06\
	   ch07\
	   ch08\
	   ch09\
	   ch10\
	   ch11\
	   ch12\
	   ch13\
	   ch14\
	   ch15\
	   ch16\
	   ch17\
	   ch18\
	   ch19\
	   ch20\
	   ch21

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
