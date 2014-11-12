CC = g++
CFLAGS= -c -std=c++11

all: magic

magic: main.o 
	$(CC) main.o -o magic

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

clean:
	rm -rf *o magic
