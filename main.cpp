#include "search.h"

int main(int argc, char *argv[])
{
    //read distance matrix from file into Graph object
    std::string dataFile = "../GIS/src/5/tsp5b"; //23 not prepared yet
    std::vector<std::vector<int> > data = *(FileParser::readMatrix(dataFile));
    std::vector<std::vector<int> > originalData = *(FileParser::readMatrix(dataFile));

    Graph graph(data);
    std::vector<Result> results;
    std::srand(std::time(NULL));
    int vNum = graph.getVerticesNum();
    unsigned long startTime, endTime;

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

    int testRuns = 5;
    float illegalValsPerRow[] = {0.5, 0.5, 0.5, 0.5, 0.5};
    int edgesNum = vNum*(vNum-1);

    //change x values to 9999 and check how this influences the result
    for (int i = 0; i < testRuns; i++){
        float illegalEdges = illegalValsPerRow[i];
      //  float illegalPercentage = 1.0*illegalEdges/edgesNum*100.0;
        printf("===========================\n");
       // graph.makeIllegal(illegalVals[i]);
        graph.makeSomeEgdesIllegal(0.5);
        graph.print();
        printf("Starting illegal search with %d(%.1f%) illegal edges\n", graph.illegalEdgesNum(), graph.illegalEdgesNum()*1.0/edgesNum*100.0 );
        startTime = std::time(NULL);
        Search search(&graph);
        Result result = search.findPath(0);
        endTime = std::time(NULL);
        result.update(endTime-startTime, dataFile, graph.illegalEdgesNum());
        results.push_back(result);
        result.print();
        graph.updateData(originalData);
    }

    return 0;
}

