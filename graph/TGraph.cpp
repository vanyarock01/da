#include "TGraph.h"

TGraph::TGraph(std::istream &is, int n, int m) {

	this->n = n + 1;
	this->m = m + 1;
	
	nodes.resize(this->n);
	int v, u;
	long long int w;
	
	while (is >> v >> u >> w) {
		edge first, second;
		
		first.to  = u;
		second.to = v;
		
		first.weight  = w;
		second.weight = w;
		
		nodes[v].push_back(first);
		nodes[u].push_back(second);
	}

}

void TGraph::Print() {
	for (int i = 1; i < nodes.size(); i++) {
		std::cout << "From node: " << i << std::endl;
		for (edge e: nodes[i])
			std::cout << "to: " << e.to <<  " weight: " << e.weight << std::endl; 
	}
}

long long int TGraph::Dijkstra(int start, int finish) {

	 std::priority_queue < std::pair    <int, int>, 
		                   std::vector  <std::pair <int, int>>,
	 			           std::greater <std::pair <int, int>>
 			    	     > PQ;

    distance.assign(n, std::numeric_limits<long long int>::max());
    distance[start] = 0;
    PQ.push({0, start});

    while (!PQ.empty()) {
    	int v = PQ.top().second;
    	PQ.pop();
    	for (edge tmp: nodes[v]) {
    		if (distance[tmp.to] > distance[v] + tmp.weight) {
				distance[tmp.to] = distance[v] + tmp.weight;
    			PQ.push({distance[tmp.to], tmp.to});
    		}
    	}
    }
    if (distance[finish] == std::numeric_limits<long long int>::max()) {
    	return -1;
    }
    return distance[finish];
}
