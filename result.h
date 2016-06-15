#ifndef RESULT_H
#define RESULT_H

#include "graph.h"

class Result
{
public:
    Result();
    Result(unsigned long iterations, int n, int illegalEdgesInPath, int pathCost,
           std::deque<int> path, Graph * graph);
    unsigned long time;
    unsigned long iterations;
    std::string fileName;
    int n;
    int edgesNum;
    int illegalEdges;
    int illegalEdgesInPath;
    float prcntIllegal;
    float prcntIllegalInPath;
    bool failed;
    std::deque<int> path;
    int pathCost;
    Graph* graph;

    void update(unsigned long time, std::string fileName);
    void print();

};

#endif // RESULT_H
