#include "search.h"

int main(int argc, char *argv[])
{
    //read distance matrix from file into Graph object
    std::string dataFile = "../GIS/src/tsp5";
    std::vector<std::vector<int> >* data = FileParser::readMatrix(dataFile);
    Graph graph(data);
    graph.print();

    Search search(&graph);
    search.heuristic();


    return 0;
}

