#include "search.h"
#include <ctime>

int main(int argc, char *argv[])
{
    //read distance matrix from file into Graph object
    std::string dataFile = "../GIS/src/5/tsp5b"; //23 not prepared yet
    std::vector<std::vector<int> >* data = FileParser::readMatrix(dataFile);
    Graph graph(data);
    std::vector<Result> results;
    int vNum = graph.getVerticesNum();

    unsigned long startTime, endTime;
    int s = 0;

    //calculate normal
    Search searchLegal(&graph);
    startTime = std::time(NULL);
    printf("===========================\nStarting normal search\n");
    Result normalResult = searchLegal.findPath(0);
    endTime = std::time(NULL);
    normalResult.update(endTime-startTime, dataFile, 0);
    results.push_back(normalResult);
    //searchLegal.printPath();
    printf("Calculation took %lu seconds.\n", endTime - startTime);

    int testRuns = 10;
    int illegalVals[] = {1,2,3,4,5,6,7,8,9,10};
    int edgesNum = vNum*(vNum-1);

    //change x values to 9999 and check how this influences the result
    for (int i = 0; i < testRuns; i++){
        int illegalEdges = illegalVals[i];
        float illegalPercentage = 1.0*illegalEdges/edgesNum*100.0;
        printf("===========================\n");
        printf("Starting illegal search with %d(%.1f%) illegal edges\n", illegalEdges, illegalPercentage);
        graph.makeIllegal(illegalVals[i]);
        startTime = std::time(NULL);
        Search search(&graph);
        Result result = search.findPath(0);
        endTime = std::time(NULL);
        result.update(endTime-startTime, dataFile, illegalEdges);
        results.push_back(result);
        result.print();
    }

    return 0;
}

