CC      = gcc
CFLAGS  = -Wall -Wextra -std=c11 -g

all: task4 mysum concat max

task4: main.c logic.c logic.h structures.h
	$(CC) $(CFLAGS) -o task4 main.c logic.c

mysum: sum.c
	$(CC) $(CFLAGS) -o mysum sum.c

concat: concat.c
	$(CC) $(CFLAGS) -o concat concat.c

max: max.c
	$(CC) $(CFLAGS) -o max max.c

run: all
	./task4

clean:
	rm -f task4 mysum concat max *.o