#include "search.h"

int main(int argc, char *argv[])
{
    //read distance matrix from file into Graph object
    std::string dataFile = "../GIS/src/tsp7"; //
    std::vector<std::vector<int> > data = *(FileParser::readMatrix(dataFile));
    std::vector<std::vector<int> > originalData = *(FileParser::readMatrix(dataFile));
    int temp;
    std::cin>>temp;
    Graph graph(data);
    graph.print();
    std::vector<Result> results;
    std::srand(std::time(NULL));
    int startNode = 0;
    unsigned long startTime, endTime;

    //calculate normal TSP
    Search searchLegal(&graph);
    startTime = std::time(NULL);
    printf("===========================\nStarting normal search\n");
    Result normalResult = searchLegal.findPath(startNode);
    endTime = std::time(NULL);
    normalResult.update(endTime-startTime, dataFile);
    results.push_back(normalResult);
    normalResult.print();

    printf("\n#Starting illegal tests. Illegal edges are marked with %d, which is %.1f times bigger than max weight in matrix (%d).\n",
           BIG_WEIGHT, BIG_WEIGHT*1.0/graph.getMaxWeight(), graph.getMaxWeight());

    int testRuns = 8;
    float illegalValsPerRow[] = {0.3, 0.4, 0.5, 0.6, 0.6, 0.7, 0.8, 0.8};

    //change some values to BIG_WEIGHT and check how this influences the result
    for (int i = 0; i < testRuns; i++){
        printf("================ illegal test num %d ===============\n", i);
        graph.makeSomeEgdesIllegal(illegalValsPerRow[i]);
        graph.print();
        startTime = std::time(NULL);
        Search search(&graph);
        Result result = search.findPath(startNode);
        endTime = std::time(NULL);
        result.update(endTime-startTime, dataFile);
        results.push_back(result);
        result.print();
        graph.updateData(originalData);
    }
    printf("forbiddenPerRow[%]\t forbiddenEgdes[%]\t forbiddenInPath[%] \tBlockedRows \tBlockedCols \tRow-wise singleNode \tCol-wise singleNode\n");

    for (int i = 0; i<results.size(); i++){
        Result result = results.at(i);
        printf("%.1f\t %.1f\t %.1f\t %d\t %d\t %d\t %d\n", illegalValsPerRow[i], result.prcntIllegal, result.prcntIllegalInPath,
               result.graph->numNodesWithNoOutEdges, result.graph->numNodesWithNoInEdges,
               result.graph->numRowsWithSingleBidirectionalEdge, result.graph->numColsWithSingleBidirectionalEdge);
    }
    return 0;
}

