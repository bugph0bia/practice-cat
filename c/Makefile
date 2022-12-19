# Makefile
CC=gcc
SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)
CFLAGS= -std=c99 -Wall -O2

cat: $(OBJS)
	$(CC) -o cat $(OBJS) $(LDFLAGS)

test: cat
	./test.sh

clean:
	rm -f cat *.o *~ tmp*

.PHONY: test clean
