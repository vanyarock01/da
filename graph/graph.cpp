#include <iostream>
#include <vector>
#include "TGraph.h"

int main(int argc, char const *argv[]) {
	
	int n, m, start, finish;
	std::cin >> n >> m >> start >> finish;
	TGraph g(std::cin, n, m);
	
	long long int result = g.Dijkstra(start, finish);
	if (result < 0)
		std::cout << "No solution";
	else  
		std::cout << result;
	
	std::cout << std::endl;

	return 0;
}