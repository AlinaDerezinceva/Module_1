CC = gcc
CFLAGS = -Wall

program: main.c ip_utils.c ip_utils.h
	$(CC) $(CFLAGS) -o program main.c ip_utils.c

clean:
	rm -f program

.PHONY: clean