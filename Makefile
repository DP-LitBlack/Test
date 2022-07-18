# build an executable named test from test.c
all: test main signal_generator

test: test.c
	gcc -g -Wall -c test.c -lpthread

main: main.c
	gcc -g -Wall -c main.c

signal_generator: signal_generator.c
	gcc -g -Wall -c signal_generator.c

	gcc -o main test.o signal_generator.o -lpthread

clean: 
	$(RM) test main signal_generator