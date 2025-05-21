#
# Makefile
# Jianlong Chen, 2025-04-27 17:56
#

ASSEMBLES = ex3.19.s ex3.22.s ex3.33.s

all: $(ASSEMBLES)
	@echo "All completed!"

$(ASSEMBLES): %.s: %.c
	$(CC) -m32 -mtune=i386 -O1 -S $<

# vim:ft=make
#
