#
# Makefile
# Jianlong Chen, 2025-06-16 11:05
#

ASSEMBLES = ex4.3.s

all: $(ASSEMBLES)
	@echo "All completed!"

$(ASSEMBLES): %.s: %.c
	$(CC) -m32 -mtune=i386 -O1 -S $<

# vim:ft=make
#
