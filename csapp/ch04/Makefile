#
# Makefile
# Jianlong Chen, 2025-06-16 11:05
#

ASSEMBLES = ex4.3.s ex4.45atmp.s
BIN = ex4.45a

all: $(ASSEMBLES) $(BIN)
	@echo "All completed!"

$(ASSEMBLES): %.s: %.c
	$(CC) -m32 -mtune=i386 -O1 -S $<

clean:
	@rm $(ASSEMBLES) $(BIN)

# vim:ft=make
#
