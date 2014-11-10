CC = g++
CFLAGS= -c -std=c++11

all: magic

magic: main.o population.o square.o
	$(CC) main.o population.o square.o -o magic

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

population.o: population.cpp
	$(CC) $(CFLAGS) population.cpp

square: square.cpp
	$(CC) $(CFLAGS) square.cpp

clean:
	rm -rf *o magic
