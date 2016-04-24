#ifndef SEARCH_H
#define SEARCH_H

#include "graph.h"


class Node{
public:
    Node(){g=h=f=0;}
    Node(int index);

    bool operator < (const Node& otherNode);
    bool operator <= (const Node& otherNode);
    bool operator == (Node* otherNode){
        if(this->getParent() == NULL || otherNode->getParent()==NULL){
            if(this->getParent() == otherNode->getParent())
                return this->index==otherNode->index;
            return false;
        }
        return (this->index==otherNode->index) && (this->parent->getIndex()==otherNode->getParent()->getIndex());
    }
    bool operator >= (const Node& otherNode);
    bool operator > (const Node& otherNode);
    int cost() const {return f;}
    int backwardCost() const { return g;}
    void updateCost(int h, int g = 0);
    int getIndex();
    void setParent(Node* node){parent = node;}
    Node * getParent(){return parent;}
    Node* parent;
private:
    int g; // backward cost (how much does the path cost thus far?)
    int h; // forward cost (how much could the path from this node towards the goal cost?)
    int f; // f = g + h
    int index; //vertex index

};

struct LessByCost{
    bool operator()(Node* aNode, Node* bNode){
        return aNode->cost() > bNode->cost();
    }
};

class Frontier {
public:
    Frontier(int vNum);
    bool contains(Node* node);
    void push(Node* node);
    Node* pop();
   // Node* end();
    Node* top();
    void remove(Node* node);
    bool empty();
    void print();
private:
    int vNum;
    std::priority_queue<Node*, std::vector<Node*>, LessByCost > opened;
    std::vector<bool> openedIndexes;

};

class Search {
public:
    Search(Graph* graph);
    void findPath();
    int getPathCost();

    void heuristic();
    int bestVertexIndex(std::vector<int> minDistanceFromTree, std::vector<bool> treeSet, int vNum);
    void printTree(std::vector<int> parent, int vNum);

private:
    Graph* graph;
    int distance(int u, int v);
    bool nodeInPQ(Node* node, std::priority_queue<Node*> pq);
    bool isGoal(Node* node);
    int startIndex;
    std::deque<int> path;
    int totalCost;
};


#endif // SEARCH_H
