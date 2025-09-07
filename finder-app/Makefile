#Cross-compiling check
CC=$(CROSS_COMPILE)gcc
CFLAGS=-Wall -Werror -O0

# Default target
all: writer

writer: writer.c
	$(CC) $(CFLAGS) -o writer writer.c

#clean target
clean:
	rm -f writer *.o

.PHONY: all clean