CC = g++
FLAGS = -std=c++11 -pedantic -Wall -Werror -Wno-sign-compare -Wno-long-long -lm
SOURCES = main.o TVector.o
EXECUTABLE = radix
all: build

build: main.o TVector.o
	$(CC) $(FLAGS) -o $(EXECUTABLE) $(SOURCES)

main.o: main.cpp TVector.h
	$(CC) $(FLAGS) -c main.cpp

TVector.o: TVector.cpp TVector.h
	$(CC) $(FLAGS) -c TVector.cpp

clean:
	rm -f $(SOURCES) $(EXECUTABLE)
