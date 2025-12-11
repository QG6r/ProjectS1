CC = gcc
CFLAGS = -Wall -Wextra -std=c11

all: demo

demo: src/hashmap.o src/demo.o
	$(CC) $(CFLAGS) src/hashmap.o src/demo.o -o demo

src/hashmap.o: src/hashmap.c src/hashmap.h
	$(CC) $(CFLAGS) -c src/hashmap.c -o src/hashmap.o

src/demo.o: src/demo.c src/hashmap.h
	$(CC) $(CFLAGS) -c src/demo.c -o src/demo.o

clean:
	rm -f src/*.o demo
