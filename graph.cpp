#include "graph.h"
#include <iomanip>
#include <iostream>

Graph::Graph(){}

Graph::Graph(std::vector<std::vector<int> > data){
    this->data = data;
    this->vNum = data.size();
}

void Graph::updateData(std::vector<std::vector<int> > data){
    this->data = data;
}

Graph::~Graph(){
    ;//delete data;
}

void Graph::print(){
   for(int row=0; row<vNum; row++){
        for(int col=0; col<vNum; col++)
           std::cout<<std::setw(12)<<at(row,col);
        std::cout<<std::endl;
    }
}

int Graph::at(int row, int col){
    return data.at(row).at(col);
}

int const Graph::getVerticesNum(){
    return vNum;
}

bool Graph::edgeExists(int srcIndex, int dstIndex){
    return at(srcIndex,dstIndex) != INT_MAX;
}

void Graph::makeIllegal(int num){
    for (int i = 0; i < num; i++){
        int row = i/vNum;
        int col = i-vNum*row;
        if(at(row,col) != INT_MAX){
            data.at(row).at(col) = BIG_WEIGHT;
        }
    }
}

void Graph::makeSomeEgdesIllegal(float percentPerRow){
    int numPerRow = vNum*percentPerRow;
    //randomIndex = new int[numPerRow];
    for (int row = 0; row < vNum; row++){
        for (int i = 0; i < numPerRow; i++){
            int col= std::rand() % vNum;
            if(col != row)
                data.at(row).at(col) = BIG_WEIGHT;
        }

    }
}

int Graph::illegalEdgesNum(){
    int num = 0;
    for(int row=0; row<vNum; row++)
         for(int col=0; col<vNum; col++)
             if(at(row,col) == BIG_WEIGHT)
                 num++;
    return num;
}
