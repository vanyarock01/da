#include <iostream>
#include <cstring>
#include <iomanip> 
#include <vector>
#include "TGraph.h"


//    0      1           2     3        4     5        6      7
//    1      2           3     4        5     6        7      8
// ./prog preprocess --nodes <file> --edges <file> --output <file>
// ./prog search     --graph <file> --input <file> --output <file>
//
//./graph search --graph NY.graph --input input --output result
//./graph preprocess --nodes NY.nodes --edges NY.edges --output gex



int main(int argc, char const *argv[]) {
    const int num_arg  = 9;
    const int flag_pos = 2;

    if ( argc > num_arg || argc < num_arg - 1) {
        std::cout << "Incorrect arguments." << "\n";
        return 0;
    }

    if ( strcmp(argv[1], "preprocess") == 0 ) {
        std::string nodes, edges, output;

        for (int i = flag_pos; i < num_arg - 1; i += 2) {
            if ( strcmp(argv[i], "--nodes") == 0 ) {
                nodes = argv[i + 1];
            } else if ( strcmp(argv[i], "--edges" ) == 0 ) {
                edges = argv[i + 1];
            } else if ( strcmp(argv[i], "--output" ) == 0 ) {
                output = argv[i + 1];
            }
        }
        TGraph G(nodes, edges, output);

    } else if ( strcmp(argv[1], "search") == 0 ) {
        std::string graph, input, output;
        bool full_output = false;
        for (int i = flag_pos; i < argc; i++) {
            if ( strcmp(argv[i], "--graph") == 0 ) {
                graph = argv[i + 1];
            } else if ( strcmp(argv[i], "--input" ) == 0 ) {
                input = argv[i + 1];
            } else if ( strcmp(argv[i], "--output" ) == 0 ) {
                output = argv[i + 1];
            } else if ( strcmp(argv[i], "--full-output") == 0 ) {
                full_output = true;
            }
        }

        TGraph G(graph);

        std::ifstream infile;
        std::ofstream outfile;

        infile.open(input);
        if ( !infile.is_open() ) {
            std::cout << input << ": fopen error." << "\n";
            return 1;
        }
        
        outfile.open(output);
        if ( !outfile.is_open() ) {
            std::cout << output << ": fopen error." << "\n";
            return 1;
        }

        uint32_t start, finish;
        while ( infile >> start >> finish ) {

            //double resultDijkstra = G.Dijkstra(start, finish);
            route result = G.AStar(start, finish);

            std::vector <uint32_t>::reverse_iterator it;
            //outfile << resultDijkstra << " Dijkstra" << std::endl;    
            outfile << result.lenght << "\n";
            if ( result.lenght < 0 && full_output) {
                outfile << 0 << "\n";    
            } else if (full_output) { 
                outfile << result.v.size();
                for (it = result.v.rbegin(); it != result.v.rend(); it++) {
                    outfile << " " << *it;
                }

                outfile << "\n";
            }
             
        }
        infile.close();
        outfile.close();
    }    


    /*route result = G.AStar(16, 220);
    
*/
    return 0;
}
