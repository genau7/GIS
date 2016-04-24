#ifndef GRAPH_H
#define GRAPH_H
#include "util.h"


class Graph
{
public:
    Graph();
    Graph(std::vector<std::vector<int> >* data);
    void print();
    int at(int row, int col);
    int const getVerticesNum();
    bool edgeExists(int srcIndex, int dstIndex);
    ~Graph();
private:
    int vNum; //number of vertices
    std::vector<std::vector<int> >* data;
};

#endif // GRAPH_H
