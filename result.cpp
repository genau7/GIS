#include "result.h"
Result::Result()
{

}
Result::Result(unsigned long iterations, int n, int illegalEdgesInPath,
               int pathCost, std::deque<int> path){
    this->iterations = iterations;
    this->n = n;
    this->edgesNum = n*(n-1);
    this->illegalEdgesInPath = illegalEdgesInPath;
    this->prcntIllegalInPath = illegalEdgesInPath * 100.0/path.size();
    this->pathCost = pathCost;
    this->path = path;
}
