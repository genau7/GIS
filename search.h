#ifndef SEARCH_H
#define SEARCH_H

#include "graph.h"

class Search
{
private:
    Graph* graph;
    int distance(int u, int v);
public:
    Search(Graph* graph);
    void heuristic();
    int bestVertexIndex(std::vector<int> minDistanceFromTree, std::vector<bool> treeSet, int vNum);
    void printTree(std::vector<int> parent, int vNum);
};

#endif // SEARCH_H
