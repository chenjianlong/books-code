# file Makefile
# brief this file is use to build ch04 demo
# author Jianlong Chen <jianlong99@gmail.com>
# date 2013-06-10
# $Id$

PROG = args\
	   argopt\
	   longopt\
	   environ\
	   showenv\
	   envtime\
	   gmtime\
	   ctime\
	   strftime\
	   tmpnam\
	   user\
	   hostget\
	   syslog\
	   logmask\
	   limits

all: $(PROG)

args: args.c
argopt: argopt.c
longopt: longopt.c
environ: environ.c
showenv: showenv.c
envtime: envtime.c
gmtime: gmtime.c
ctime: ctime.c
strftime: strftime.c
tmpnam: tmpnam.c
user: user.c
hostget: hostget.c
syslog: syslog.c
logmask: logmask.c
limits: limits.c

install:
	$(Q) mkdir -p $(DESTDIR)/bin/ && cp $(PROG) $(DESTDIR)/bin/

clean:
	$(Q) -rm $(PROG)

