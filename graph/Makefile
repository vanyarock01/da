CC = g++
FLAGS = -std=c++11 -O2 -pedantic -Wall -Wno-sign-compare -Wno-long-long -lm
FILES = TGraph.cpp graph.cpp 
PROG = graph
graph:
	$(CC) $(FLAGS) -o $(PROG) $(FILES)

clean:
	rm -f *.o graph