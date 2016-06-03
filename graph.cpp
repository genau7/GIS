#include "graph.h"
#include <iomanip>
#include <iostream>

Graph::Graph(){}

Graph::Graph(std::vector<std::vector<int> > data){
    this->data = data;
    this->vNum = data.size();
    this->numNodesWithNoInEdges = 0;
    this->numNodesWithNoOutEdges = 0;
    this->numRowsWithSingleBidirectionalEdge = 0;
    this->numColsWithSingleBidirectionalEdge = 0;
    this->numRowsWithSingleBidirectionalEdge = 0;
    findMaxWeight();
}

void Graph::updateData(std::vector<std::vector<int> > data){
    this->data = data;
}

void Graph::print(){
   for(int row=0; row<vNum; row++){
        for(int col=0; col<vNum; col++)
           std::cout<<std::setw(12)<<at(row,col);
        std::cout<<std::endl;
    }
   std::cout<<std::endl;
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
    evaluateNodes();
}

void Graph::makeSomeEgdesIllegal(float percentPerRow){
    int numPerRow = vNum*percentPerRow;
    //randomIndex = new int[numPerRow];
    for (int row = 0; row < vNum; row++){
        int check = 0;
        while(illegalEdgesNumInRow(row) < numPerRow && check < vNum*100){
        //for (int i = 0; i < numPerRow; i++){
            int col= std::rand() % vNum;
            if(col != row)
                data.at(row).at(col) = BIG_WEIGHT;
            check++;
        }
    }
    evaluateNodes();
}


void Graph::evaluateNodes(){
    numRowsWithSingleBidirectionalEdge = numColsWithSingleBidirectionalEdge = 0;
    numNodesWithNoInEdges = numNodesWithNoOutEdges = 0;
    for(int row=0; row < vNum; row++){
        int illegalRowCells = illegalEdgesNumInRow(row);
        if(illegalRowCells == vNum - 1)
             numNodesWithNoOutEdges++;
        else if (illegalRowCells == vNum -2)
             numRowsWithSingleBidirectionalEdge++;
        illegalRowCells = 0;
    }

    int illegalColCells = 0;
    for(int col=0; col < vNum; col++){
         for(int row=0; row < vNum; row++)
             if(at(row,col) == BIG_WEIGHT)
                 illegalColCells++;
         if(illegalColCells == vNum - 1)
             numNodesWithNoInEdges++;
         else if(illegalColCells == vNum -2)
             numColsWithSingleBidirectionalEdge++;
         illegalColCells = 0;
    }

}

int Graph::illegalEdgesNumInRow(int row){
    int res = 0;
    for(int col=0; col<vNum; col++)
        if(at(row,col) == BIG_WEIGHT)
            res++;
    return res;
}

int Graph::illegalEdgesNum(){
    int num = 0;
    for(int row=0; row<vNum; row++)
        for(int col=0; col<vNum; col++)
             if(at(row,col) == BIG_WEIGHT)
                 num++;
    return num;
}

int Graph::getMaxWeight(){
    return maxWeight;
}

void Graph::findMaxWeight(){
    maxWeight = 0;
    for(int row=0; row < vNum; row++)
         for(int col=0; col < vNum; col++)
             if (at(row,col) < INT_MAX && at(row,col) > maxWeight)
                 maxWeight = at(row,col);

}
