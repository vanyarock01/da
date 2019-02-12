#ifndef TGRAPH
#define TGRAPH

#include <iostream>
#include <limits>
#include <vector>
#include <queue>

class TGraph
{
public:
	TGraph(std::istream &is, int n, int m);
	~TGraph() {};

	void Print();
	long long int Dijkstra(int start, int finish);

private:
	typedef struct {
		int to;
		long long int weight;
	} edge;

	int n, m;
	std::vector <std::vector<edge>> nodes;
	std::vector <long long int> distance;	
};


#endif