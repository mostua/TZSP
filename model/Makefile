CC = g++
CFLAGS= -c -std=c++11

all: magic

magic: main.o 
	$(CC) mainModel.o -o magic

main.o: mainModel.cpp
	$(CC) $(CFLAGS) mainModel.cpp
	

clean:
	rm -rf *o magic
