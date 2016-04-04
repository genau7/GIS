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
    int bestVertexIndex(int minDistanceFromTree[], bool treeSet[]);
    void printTree(int parent[]);
};

#endif // SEARCH_H
