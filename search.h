#ifndef SEARCH_H
#define SEARCH_H

#include "graph.h"


class Node{
public:
    Node(){g=h=f=0;}
    Node(int index);
    Node(int index, Node* parent);
    int getCost() const {return f;}
    int getBackwardCost() const { return g;}
    int getIndex();
    Node * getParent(){return parent;}
    void setParent(Node* node){parent = node;}
    void updateCost(int h, int g = 0);
    void print();
    void printParents();
private:
    int g; // backward cost (how much does the path cost thus far?)
    int h; // forward cost (how much could the path from this node towards the goal cost?)
    int f; // f = g + h
    int index; //vertex index
    Node* parent;
};

struct LessByCost{
    bool operator()(Node* aNode, Node* bNode){
        return aNode->getCost() > bNode->getCost();
    }
};

class Frontier {
public:
    Frontier(){}
    bool contains(Node* node);
    void push(Node* node);
    void remove(Node* node);
    bool empty();
    Node* pop();
    Node* top();
private:
    std::priority_queue<Node*, std::vector<Node*>, LessByCost > opened;
};

class Search {
public:
    Search(Graph* graph, int startIndex, int goalIndex = 0);
    void findPath();
    int getPathCost();
    void printPath();
    int heuristic(int start, std::set<int> closed);
    int bestVertexIndex(std::vector<int> minDistanceFromTree, std::vector<bool> treeSet, int vNum, std::set<int> closed);
    void printTree(std::vector<int> parent, int vNum);

private:
    int calcPathCost(std::vector<int> parents);
    int distance(int u, int v);
    bool isGoal(Node* node);
    void reconstructPath(Node * last);
    Graph* graph;
    int startIndex;
    int goalIndex;
    std::deque<int> path;
    int totalCost;
};


#endif // SEARCH_H
