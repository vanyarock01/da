#ifndef TGRAPH
#define TGRAPH

#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <cstdint>
#include <fstream>
#include <limits>
#include <vector>
#include <queue>
#include <cmath>
#include <set>
#include <map>

typedef struct {
    std::vector<uint32_t> v;
    double lenght;
} route;

class TGraph
{
public:
    //typedef std::pair <long int, double> arc;
    TGraph  (const std::string &fnodes, const std::string &fedges, const std::string &graph);
    TGraph  (const std::string &fnodes, const std::string &fedges);
    TGraph  (const std::string &fgraph);
    ~TGraph () {};

    void Preprocessing (const std::string &file);
    void InsertNode    (uint32_t id, double lat, double lon);
    void InsertEdge    () {};
    bool At            (uint32_t id);

    route AStar    (uint32_t start, uint32_t finish);
    double Dijkstra(uint32_t start, uint32_t finish);
private:
    
    std::unordered_map <uint32_t, uint32_t> pointers;    
    std::vector <std::pair <uint32_t, std::pair <double, double>>> nodes;
    std::vector <uint32_t> prefix;
    std::vector <uint32_t> incident;
    std::vector <double>   weight;
};

#endif