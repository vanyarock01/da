CC = g++
FLAGS = -std=c++11 -pedantic -Wall -Werror -Wno-sign-compare -Wno-maybe-uninitialized -Wno-long-long -lm -O3
SOURCES = main.o PatriciaTree.o PatriciaNode.o
EXECUTABLE = patricia
all: build


build: main.o PatriciaTree.o PatriciaNode.o
	$(CC) $(FLAGS) -o $(EXECUTABLE) $(SOURCES)

main.o: main.cpp PatriciaTree.h PatriciaNode.h
	$(CC) $(FLAGS) -c main.cpp

PatriciaTree.o: PatriciaTree.cpp PatriciaTree.h PatriciaNode.h
	$(CC) $(FLAGS) -c PatriciaTree.cpp


PatriciaNode.o: PatriciaNode.cpp PatriciaNode.h
	$(CC) $(FLAGS) -c PatriciaNode.cpp

clean:
	rm -f $(SOURCES) $(EXECUTABLE)
