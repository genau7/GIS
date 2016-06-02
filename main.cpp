#include "search.h"
#include <ctime>

int main(int argc, char *argv[])
{
    //read distance matrix from file into Graph object
    std::string dataFile = "../GIS/src/5/tsp5b"; //23 not prepared yet
    std::vector<std::vector<int> >* data = FileParser::readMatrix(dataFile);
    Graph graph(data);
    unsigned long startTime, endTime;
    int s = 0;
    int vNum = graph.getVerticesNum();

    //calculate normal
    Search searchLegal(&graph);
    startTime = std::time(NULL);
    printf("===========================\nStarting normal search\n");
    searchLegal.findPath(0);
    endTime = std::time(NULL);
    searchLegal.printPath();
    printf("Calculation took %lu seconds.\n", endTime - startTime);

    //change x values to 9999 and check how this influences the result
    for (int i = 0; i < 1; i++){
        graph.makeIllegal(10);
        //graph.print();
        startTime = std::time(NULL);
        Search search(&graph);
        search.findPath(0);
        endTime = std::time(NULL);
        search.printPath();
        printf("Calculation took %lu seconds.\n", endTime - startTime);
    }

    return 0;
}

