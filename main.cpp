#include "search.h"
#include <fstream>

int main(int argc, char *argv[])
{
    std::string dataFile = "../GIS/res/";
    if(argc > 1){
        dataFile += argv[1];
    }
    else
        dataFile += "tsp10";

    std::cout<<"Reading: "<<dataFile<<std::endl;
    //read distance matrix from file into Graph object
    std::vector<std::vector<int> > data = *(FileParser::readMatrix(dataFile));
    std::vector<std::vector<int> > originalData = *(FileParser::readMatrix(dataFile));

    std::cout<<"Enter any number:\n";
    int temp;
    std::cin>>temp;
    Graph graph(data);
    //graph.print();
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

  //  printf("\n#Starting illegal tests. Illegal edges are marked with %d, which is %.1f times bigger than max weight in matrix (%d).\n",
  //         BIG_WEIGHT, BIG_WEIGHT*1.0/graph.getMaxWeight(), graph.getMaxWeight());

    int testRuns = 8;
    float illegalValsPerRow[] = {0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.6, 0.7, 0.8, 0.8};

    int check = 10000;
    int failuresNum = 0;
    int i = 0;
    int illegalIndex = 2;
    while(i < check){

        graph.makeSomeEgdesIllegal(illegalValsPerRow[illegalIndex], normalResult.path);
        Search search(&graph);
        Result result = search.findPath(startNode);
        results.push_back(result);
        result.update(0, dataFile);
        graph.updateData(originalData);
        if(result.failed) failuresNum++;
        if(failuresNum >= 10){
            printf("FAILURE!!!\n");
            break;
        }
        if(i%100 == 0)
            printf("[%d] - %d\n", i, failuresNum);
        //if (failuresNum*1.0/i > 0.1)
          //  break;
      //  else if (failuresNum*1.0/i >= 0.05)
      //      printf("FAILED!!!!\n");
        i++;
    }
    printf("Performed %d tests for file named %s and %.1f illegal values in each row.\n%d times the algorithm failed (%.4f)\n",
           i, dataFile.c_str(), illegalValsPerRow[illegalIndex], failuresNum, failuresNum*1.0/i);

    printf("(%d - %.1f - %d - %.4f)\n", i, illegalValsPerRow[illegalIndex], failuresNum, failuresNum*1.0/i);
    //change some values to BIG_WEIGHT and check how this influences the result
   /*
    *  for (int i = 0; i < testRuns; i++){
        printf("================ illegal test num %d ===============\n", i);
        graph.makeSomeEgdesIllegal(illegalValsPerRow[i]);
        //graph.print();
        startTime = std::time(NULL);
        Search search(&graph);
        Result result = search.findPath(startNode);
        endTime = std::time(NULL);
        result.update(endTime-startTime, dataFile);
        results.push_back(result);
        result.print();
        graph.updateData(originalData);
    }
    printf("  forbiddenPerRow[%]\t forbiddenEgdes[%]\t forbiddenInPath[%] \tBlockedRows \tBlockedCols \tRow-wise singleNode \tCol-wise singleNode\n");

    for (int i = 1; i<results.size(); i++){
        Result result = results.at(i);
        printf("%d. \t\t%.1f\t\t %.1f\t\t\t %.1f\t\t\t %d\t\t %d\t\t\t %d\t\t %d\n", i, illegalValsPerRow[i-1], result.prcntIllegal, result.prcntIllegalInPath,
               result.graph->numNodesWithNoOutEdges, result.graph->numNodesWithNoInEdges,
               result.graph->numRowsWithSingleBidirectionalEdge, result.graph->numColsWithSingleBidirectionalEdge);
    }*/

    return 0;
}

