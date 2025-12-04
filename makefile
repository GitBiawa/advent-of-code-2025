CC = gcc
CFLAGS = -std=c99
CFLAGS += -W -Wall
CFLAGS += -O

test: test.o
	$(CC) $(CFLAGS) test.c -o test -lm
clean:
	rm *.o
