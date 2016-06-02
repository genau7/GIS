#ifndef GRAPH_H
#define GRAPH_H
#include "util.h"


class Graph
{
public:
    Graph();
    Graph(std::vector<std::vector<int> > data);
    void print();
    int at(int row, int col);
    int const getVerticesNum();
    bool edgeExists(int srcIndex, int dstIndex);
    void makeIllegal(int num);
    void makeSomeEgdesIllegal(float percentPerRow);
    int illegalEdgesNum();
    void updateData(std::vector<std::vector<int> > data);
    ~Graph();
private:
    int vNum; //number of vertices
    std::vector<std::vector<int> > data;
};

#endif // GRAPH_H
