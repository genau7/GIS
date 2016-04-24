#ifndef SEARCH_H
#define SEARCH_H

#include "graph.h"


class Node{
public:
    Node(){g=h=f=0;}
    Node(int index);
    Node(int index, Node* parent);

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
    Frontier(){}
    bool contains(Node* node);
    void push(Node* node);
    Node* pop();
    Node* top();
    void remove(Node* node);
    bool empty();
private:
    std::priority_queue<Node*, std::vector<Node*>, LessByCost > opened;

};

class Search {
public:
    Search(Graph* graph, int startIndex, int goalIndex = 0);
    void findPath();
    int getPathCost();
    void printPath();
    void heuristic();
    int bestVertexIndex(std::vector<int> minDistanceFromTree, std::vector<bool> treeSet, int vNum);
    void printTree(std::vector<int> parent, int vNum);

private:
    Graph* graph;
    int distance(int u, int v);
    bool nodeInPQ(Node* node, std::priority_queue<Node*> pq);
    bool isGoal(Node* node);
    int startIndex;
    int goalIndex;
    std::deque<int> path;
    int totalCost;
};


#endif // SEARCH_H
