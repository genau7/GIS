#ifndef RESULT_H
#define RESULT_H

#import "graph.h"

class Result
{
public:
    Result();
    Result(unsigned long iterations, int n, int illegalEdgesInPath, int pathCost, std::deque<int> path);
    unsigned long time;
    unsigned long iterations;
    std::string fileName;
    int n;
    int edgesNum;
    int illegalEdges;
    int illegalEdgesInPath;
    float prcntIllegal;
    float prcntIllegalInPath;
    std::deque<int> path;
    //char* pathStr;
    int pathCost;
    void update(unsigned long time, std::string fileName, int illegal){
        this->prcntIllegal = illegal*100.0/edgesNum;
        this->illegalEdges = illegal;
        this->time = time;
        this->fileName = fileName;
        int temp =0;
        temp++;
    }
    void print(){
        printf("Results for file %s (%d nodes) and %d (%.1f%) illegal edges in graph:\n",
               fileName.c_str(), n, illegalEdges, prcntIllegal);
        printf("\tPath = %d", path.at(0));
        for (int i = 1; i < path.size(); i++)
            printf("-%d", path.at(i));

        printf("\n\tCost = %d\n", pathCost);
        printf("\tillegal edges in path = %.1f %\n", prcntIllegalInPath);
        printf("\ttime = %d [s]\n", time);
        printf("\titerations = %d\n", iterations);
    }

};

#endif // RESULT_H
