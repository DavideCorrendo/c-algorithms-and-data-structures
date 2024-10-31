CFLAGS = -g -Wall -Wextra -Wpedantic -Wconversion
INCLUDES = -I src -I unitTest

all: bin/sort.o bin/main.o
	gcc $(CFLAGS) $(INCLUDES) bin/sort.o bin/main.o -o bin/ex1_main

bin/sort.o: src/sort.c
	mkdir -p bin
	gcc $(CFLAGS) $(INCLUDES) -c src/sort.c -o bin/sort.o

bin/main.o: src/main.c
	mkdir -p bin
	gcc $(CFLAGS) $(INCLUDES) -c src/main.c -o bin/main.o

test:
	mkdir -p bin
	gcc $(CFLAGS) $(INCLUDES) -o bin/ex1_test src/sortTest.c src/sort.c unitTest/unity.c

clean:
	rm -rf bin
