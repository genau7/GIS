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
    void makeSomeEgdesIllegal(float percentPerRow, std::deque<int> legalPath);
    int illegalEdgesNum();
    int numNodesWithNoInEdges;
    int numNodesWithNoOutEdges;
    int numRowsWithSingleBidirectionalEdge;
    int numColsWithSingleBidirectionalEdge;
    void updateData(std::vector<std::vector<int> > data);
    void evaluateNodes();
    void findMaxWeight();
    int getMaxWeight();
private:
    int vNum; //number of vertices
    std::vector<std::vector<int> > data;
    int maxWeight;
    int illegalEdgesNumInRow(int row);
};

#endif // GRAPH_H
