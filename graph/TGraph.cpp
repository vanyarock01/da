#include "TGraph.h"
#include <algorithm>
#include <ostream>
#include <istream>
#include <iomanip>
double heuristic(double lat1, double lon1, double lat2, double lon2) {
    double d = 2 * asin(sqrt(sin(fabs(lat1 - lat2) * M_PI / 360) * 
                             sin(fabs(lat1 - lat2) * M_PI / 360) +
                                          cos(lat1 * M_PI / 180) * 
                                          cos(lat2 * M_PI / 180) * 
                             sin(fabs(lon1 - lon2) * M_PI / 360) * 
                             sin(fabs(lon1 - lon2) * M_PI / 360)));
    const int R = 6371000;
    return R * d;
}

double heuristic2(double lat1, double lon1, double lat2, double lon2) {
    return sqrt((lat1 - lat2) * (lat1 - lat2) + (lon1 - lon2) * (lon1 - lon2));
}
    
/*
    FROMAT:                       N                            N
    <node_id> <lat> <lon> <number_of_edges> <node_id> <weight>...<node_id> <weight>

*/

TGraph::TGraph(const std::string &fnodes, const std::string &fedges, const std::string &graph) {
    
    std::ifstream infile;
    std::vector <std::pair <uint32_t, uint32_t>> arcs;
    std::vector <std::pair <uint32_t, uint32_t>>::iterator it_arcs;
    infile.open(fnodes);
    uint32_t id;
    double lat, lon;
    
    uint32_t idx = 0;

    while ( infile >> id >> lat >> lon ) {
        nodes.emplace_back( std::pair<uint32_t, std::pair<double, double>>(id , std::pair<double, double>(lat, lon)));
        pointers[id] = idx;
        idx++;
    }

    std::vector <int> count(nodes.size(), 0);

    infile.close();

    infile.open(fedges);    
    
    int number;
        while ( infile >> number ) { 
            
        std::vector<uint32_t> v(number);
        for (int i = 0; i < number; i++) {
            infile >> v[i];
        }

        for (int i = 1; i < number; i++) {
            //std::cout << v[i] << " ";
            count[pointers[v[i - 1]]]++;
            count[pointers[v[i]]]++;
        }
    }
    uint32_t carry = 0;
    for (uint32_t i = 0; i < count.size(); i++) {
        prefix.push_back(carry);
        carry += count[i];
    }

    prefix.push_back(carry);

    infile.close();
    infile.open(fedges);
    incident.assign(carry, 0);
    weight.assign(carry, 0);

    while ( infile >> number ) { 
        
        std::vector<uint32_t> v(number);
        for(int i = 0; i < number; i++) {
            infile >> v[i];
        }

        for (int i = 1; i < number; i++) {
            double w = heuristic(nodes[pointers[v[i - 1]]].second.first, nodes[pointers[v[i - 1]]].second.second, 
                                 nodes[pointers[v[i]]].second.first, nodes[pointers[v[i]]].second.second);
            
            uint32_t idx = prefix[pointers[v[i]] + 1] - count[pointers[v[i]]];
            incident[idx] = v[i - 1];
            weight[idx] = w;
            count[pointers[v[i]]]--;
            
            idx = prefix[pointers[v[i - 1]] + 1] - count[pointers[v[i - 1]]];
            incident[idx] = v[i];
            weight[idx] = w;
            count[pointers[v[i - 1]]]--;
        }
    }

    std::ofstream outfile(graph, std::ios::out | std::ios::binary);

    size_t size_node = nodes.size();
    outfile.write( (char*)&size_node, sizeof(size_node) );
    outfile.write( (char*)&nodes[0], size_node * sizeof(nodes[0]) );

    size_t size_prefix = prefix.size();

    outfile.write( (char*)&size_prefix, sizeof(size_prefix) );
    outfile.write( (char*)&prefix[0], size_prefix * sizeof(prefix[0]) );

    size_t size_incident = incident.size();
    outfile.write( (char*)&size_incident, sizeof(size_incident) );
    outfile.write( (char*)&incident[0], size_incident * sizeof(incident[0]) );

    outfile.write( (char*)&weight[0], size_incident * sizeof(weight[0]) );
    
    outfile.close();
}


TGraph::TGraph (const std::string &fgraph) {
    std::ifstream infile(fgraph, std::ios::in | std::ios::binary);

    size_t size_node, size_prefix, size_incident;
    
    infile.read( (char*)&size_node, sizeof(size_node) );
    nodes.assign(size_node, {0, {0.0, 0.0}});
    infile.read( (char*)&nodes[0], size_node * sizeof(nodes[0]) );
    
    for (uint32_t i = 0; i < size_node; i++) {
        pointers[nodes[i].first] = i;
    }

    infile.read( (char*)&size_prefix, sizeof(size_prefix) );
    prefix.assign(size_prefix, 0);
    
    infile.read( (char*)&prefix[0], size_prefix * sizeof(prefix[0]) );
    
    infile.read( (char*)&size_incident, sizeof(size_incident) );
    incident.assign(size_incident, 0);
    infile.read( (char*)&incident[0], size_incident * sizeof(incident[0]) );
    weight.assign(size_incident, 0);
    infile.read( (char*)&weight[0], size_incident * sizeof(weight[0]) );

    infile.close();
}


route TGraph::AStar(uint32_t start, uint32_t finish) {

    std::unordered_map <uint32_t, double>   distance;
    std::unordered_map <uint32_t, uint32_t> parent;

    std::priority_queue < std::pair    <double, uint32_t>, 
                          std::vector  <std::pair <double, uint32_t>>,
                          std::greater <std::pair <double, uint32_t>>
                        > PQ;

    std::unordered_map <uint32_t, double>::iterator   it_nodes;
    std::unordered_map <uint32_t, uint32_t>::iterator it_parent;

    uint32_t s = pointers[start], f = pointers[finish];

    PQ.emplace( 0, start );

    distance[start] = 0;
    uint32_t current_id = start;

    route result;
    result.lenght = -1;

    while ( !PQ.empty() ) {

        current_id = PQ.top().second;
        PQ.pop();

        if ( current_id == finish ) {

            uint32_t st = finish;
            result.lenght = distance[st];

            while ( st != start ) {
                result.v.push_back(st);
                st = parent[st];
            }
            
            result.v.push_back(start);
            return result;
        }

        uint32_t idx = pointers[current_id];
        int bound = prefix[idx + 1];

        for (uint32_t i = prefix[idx]; i < bound; i++) {

            double h = heuristic(nodes[pointers[incident[i]]].second.first, nodes[pointers[incident[i]]].second.second, 
                                 nodes[f].second.first, nodes[f].second.second);            
            double score = distance[current_id] + weight[i];
            it_nodes = distance.find(incident[i]);
            if (it_nodes != distance.end() && score >= distance[incident[i]]) {
                 continue;
            }
            else if ( score < distance[incident[i]] ||  it_nodes == distance.end()) {
                parent[incident[i]] = current_id;
                distance[incident[i]] = score;
                PQ.emplace( score + h, incident[i] );    
            }
        }

    }
    return result;
}

double TGraph::Dijkstra(uint32_t start, uint32_t finish) {
    
    std::priority_queue < std::pair    <double, uint32_t>, 
                             std::vector  <std::pair <double, uint32_t>>,
                          std::greater <std::pair <double, uint32_t>>
                        > PQ;

     std::map <uint32_t, double>   distance;
     std::map <uint32_t, uint32_t> parent;
     std::map <uint32_t, uint32_t>::iterator it_parent;

     std::map <uint32_t, double>::iterator it_nodes;

    distance[start] = 0;
    PQ.push({0, start});

    while (!PQ.empty()) {
        uint32_t current_id = PQ.top().second;
        PQ.pop();

        uint32_t idx = pointers[current_id];
        int bound = prefix[idx + 1];

        for (uint32_t i = prefix[idx]; i < bound; i++) {
            
            it_nodes = distance.find(incident[i]);
            if ( it_nodes == distance.end() || distance[incident[i]] > distance[current_id] + weight[i]) {
                //...
                
                distance[incident[i]] = distance[current_id] + weight[i];
                PQ.push({distance[incident[i]], incident[i]});
                parent[incident[i]] = current_id;    
            
            }
        }
    }
    it_nodes = distance.find(finish);
    if (it_nodes == distance.end()) {
        return -1;
    }
    return distance[finish];
}

