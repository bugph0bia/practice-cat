# Makefile
CC=g++
SRCS=$(wildcard *.cpp)
OBJS=$(SRCS:.cpp=.o)
CFLAGS= -std=c++14 -Wall -O2

cat: $(OBJS)
	$(CC) -o cat $(OBJS) $(LDFLAGS)

test: cat
	./test.sh

clean:
	rm -f cat *.o *~ tmp*

.PHONY: test clean
