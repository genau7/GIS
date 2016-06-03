#include "result.h"
Result::Result()
{

}
Result::Result(unsigned long iterations, int n, int illegalEdgesInPath, int pathCost,
               std::deque<int> path, Graph* graph){
    this->iterations = iterations;
    this->n = n;
    this->edgesNum = n*(n-1);
    this->illegalEdgesInPath = illegalEdgesInPath;
    this->prcntIllegalInPath = illegalEdgesInPath * 100.0/path.size();
    this->pathCost = pathCost;
    this->path = path;
    this->graph = graph;
    this->prcntIllegal = graph->illegalEdgesNum()*100.0/edgesNum;
    this->illegalEdges = graph->illegalEdgesNum();
}

void Result::update(unsigned long time, std::string fileName){
    this->time = time;
    this->fileName = fileName;
    int temp =0;
    temp++;
}

void Result::print(){
    printf("Results for file %s (%d nodes) and %d (%.1f%) illegal edges in graph:\n",
           fileName.c_str(), n, illegalEdges, prcntIllegal);
    printf("Path = %d", path.at(0));
    for (int i = 1; i < path.size(); i++)
        printf("-%d", path.at(i));

    printf("\nCost = %d\n", pathCost);
    printf("illegal edges in path = %.1f %\n", prcntIllegalInPath);
    printf("time = %d [s]\n", time);
    printf("iterations = %d\n", iterations);
    printf("Number of nodes with just one bidirectional edge = %d (row-wise) and %d (column-wise)\n",
           graph->numRowsWithSingleBidirectionalEdge, graph->numColsWithSingleBidirectionalEdge);
    if(prcntIllegalInPath > 0){
        printf("Number of nodes with no outgoing edges = %d\n", graph->numNodesWithNoOutEdges);
        printf("Number of nodes with no incoming edges = %d\n", graph->numNodesWithNoInEdges);

    }
    printf("\n");
}
