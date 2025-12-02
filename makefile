CC = gcc
CFLAGS = -std=c99
CFLAGS += -W -Wall
CFLAGS += -O

test: test.o

clean:
	rm *.o
