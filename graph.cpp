#include "graph.h"
#include <iomanip>
#include <iostream>

Graph::Graph(){}

Graph::Graph(std::vector<std::vector<int> >* data){
    this->data = data;
    this->vNum = data->size();
}

Graph::~Graph(){
    delete data;
}

void Graph::print(){
   for(int row=0; row<vNum; row++){
        for(int col=0; col<vNum; col++)
           std::cout<<std::setw(12)<<at(row,col);
        std::cout<<std::endl;
    }
}

int Graph::at(int row, int col){
    return data->at(row).at(col);
}

int const Graph::getVerticesNum(){
    return vNum;
}

bool Graph::edgeExists(int srcIndex, int dstIndex){
    return at(srcIndex,dstIndex) != INT_MAX;
}
