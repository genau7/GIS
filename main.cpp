#include "graph.h"

int main(int argc, char *argv[])
{
    std::string dataFile = "../GIS/src/tsp17";
    std::vector<std::vector<int> >* data = FileParser::readMatrix(dataFile);
    Graph graph(data);
//    graph.print();
    return 0;
}

