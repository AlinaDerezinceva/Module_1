all: task2 mysum concat max

task2: task2.c
	gcc -Wall -Wextra -std=c11 -g -o task2 task2.c

mysum: sum.c
	gcc -Wall -Wextra -std=c11 -g -o mysum sum.c

concat: concat.c
	gcc -Wall -Wextra -std=c11 -g -o concat concat.c

max: max.c
	gcc -Wall -Wextra -std=c11 -g -o max max.c

run: all
	./task2

clean:
	rm -f task2 mysum concat max