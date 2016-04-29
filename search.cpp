#include "search.h"
#include <stdio.h>

const int NONE = -1;
//const int IRRELEVANT = -2;

bool Frontier::contains(Node *node){
    std::vector<Node*> copy(opened.size());
    std::copy(&(opened.top()), &(opened.top()) + opened.size(), &copy[0]);
    for(std::vector<Node*>::iterator it = copy.begin(); it != copy.end(); ++it) {
        if((*it) == node )
            return true;
    }
    return false;
}

void Frontier::push(Node *node){
    opened.push(node);
}

Node* Frontier::pop(){
    Node* node = opened.top();
    opened.pop();
    return node;
}
Node* Frontier::top(){
    return opened.top();
}

bool Frontier::empty(){
    return opened.empty();
}

//TODO test this below
void Frontier::remove(Node *node){
    if(node == opened.top())
        opened.pop();
    else {
        std::vector<Node*> copy(opened.size());
        std::copy(&(opened.top()), &(opened.top()) + opened.size(), &copy[0]);
        for(std::vector<Node*>::iterator it = copy.begin(); it != copy.end(); ++it) {
            if((*it) == node ){
                copy.erase(it);
                break;
            }
        }

        std::priority_queue<Node*, std::vector<Node*>, LessByCost > updatedQ;
        for(std::vector<Node*>::iterator it = copy.begin(); it != copy.end(); ++it) {
            updatedQ.push(*it);
        }

        this->opened = updatedQ;
    }

}

Search::Search(Graph *graph, int startIndex, int goalIndex){
    this->graph = graph;
    this->totalCost = INT_MAX;
    this->startIndex = startIndex;
    this->goalIndex = goalIndex;
}

bool Search::isGoal(Node *node){
    if (node->getIndex() == this->goalIndex)
        return true;
    return false;
}

void Search::findPath(){
    int vNum = graph->getVerticesNum();
    Frontier frontier;
    std::set<int> closed;

    //init values for the starting point
    Node* initNode = new Node(startIndex);
    initNode->updateCost(heuristic(startIndex, closed));
    initNode->setParent(NULL);
    frontier.push(initNode);

    int iteration = 0;
    Node* lowestRank = NULL;
    Node* current = NULL;
    while(++iteration){
        lowestRank = frontier.top();
        if(iteration != 1 && isGoal(lowestRank))
            break; //reached the destination

        current = frontier.pop();
        closed.insert(current->getIndex());

        //for each neighbor of the current vertex
        for(int i = 1; i < vNum; i++){
            if(!graph->edgeExists(current->getIndex(), i))
                continue;

            Node* neighbor = new Node(i, current);
            int cost = current->getBackwardCost() + distance(current->getIndex(), neighbor->getIndex());
            int forwardCost = heuristic(i, closed);
            neighbor->updateCost(forwardCost, cost);
            //neighbor->print();
            if(frontier.contains(neighbor) && cost < neighbor->getBackwardCost()){
                frontier.remove(neighbor); //TODO test this
            }
            if(closed.find(neighbor->getIndex())!= closed.end() && cost < neighbor->getBackwardCost()){
                closed.erase(closed.find(neighbor->getIndex()));
            }
            if(closed.find(neighbor->getIndex()) == closed.end() && !frontier.contains(neighbor)){
                frontier.push(neighbor);
            }
        }
        if(iteration>vNum*1000)
            break;
    }
    reconstructPath(lowestRank);
}

void Search::reconstructPath(Node *last){
    this->totalCost = last->getBackwardCost();
    Node * current = last;
    do {
        path.push_front(current->getIndex());
        current = current->getParent();
    } while (current->getParent() != NULL);

    path.push_front(current->getIndex());
}

int Search::heuristic(int start, std::set<int> closed){
    int vNum = graph->getVerticesNum();
    std::vector<int> parents(vNum, NONE); //minimum spanning tree path (first node's parent index is -1), indicated by nodes' parent
    std::vector<int> minDistanceFromTree(vNum, INT_MAX);
    std::vector<bool> minTreeSet(vNum, false);  // if i-element is set to True, than i-vertex has been placed in the tree set
    minDistanceFromTree[start] = 0;

    for (int count = 0; count < vNum-1 - closed.size(); ++count){
        //find and add to tree path node 'u' such that distance from the tree to it is smallest
        int u = bestVertexIndex(minDistanceFromTree, minTreeSet, vNum, closed);
        if (u == NONE) //we reached the goal //TODO check if works for both TSP and no TSP
            return 0;
        minTreeSet[u] = true;

        //Update vertices' distance from the tree
        for (int v = 0; v < vNum; ++v){
            // Update the distance only if graph[u][v] is smaller than key[v]
            if (distance(u,v) != INT_MAX && minTreeSet[v] == false && distance(u,v) <  minDistanceFromTree[v] & closed.find(v) == closed.end()){
                parents[v]  = u;
                minDistanceFromTree[v] = distance(u,v);
            }
        }
    }
   // printTree(parents, vNum);
    return calcPathCost(parents);
}

int Search::bestVertexIndex(std::vector<int> minDistanceFromTree, std::vector<bool> treeSet, int vNum, std::set<int> closed){
    int minIndex = NONE;
    int min = INT_MAX;

    for (int v = 0; v < vNum; v++){
        if (treeSet[v] == false && minDistanceFromTree[v] < min && closed.find(v) == closed.end()) {
            min = minDistanceFromTree[v];
            minIndex = v;
        }
    }
    return minIndex;
}

int Search::calcPathCost(std::vector<int> parents){
    int pathCost = 0;
    for (int i = 0; i < graph->getVerticesNum(); i++){
        int parent = parents[i];
        if (parent != NONE)
            pathCost += distance(parents[i], i);
    }
    return pathCost;
}

void Search::printTree(std::vector<int> parent, int vNum){
    printf("Edge   Weight\n");
    int sum = 0;
    for (int i = 1; i < vNum; i++){
        printf("%d - %d    %d \n", parent[i], i, distance(parent[i], i));
        sum += distance(parent[i], i);
    }
    printf("The minimum spanning tree path = %d\n", sum);
}

void Search::printPath(){
    printf("Edge   Weight\n");
    for (int i = 1; i < path.size(); i++){
        printf("%d - %d    %d \n", path.at(i-1), path.at(i), distance(path.at(i-1), path.at(i)));
    }
    printf("A* search tree path total cost = %d\n", this->totalCost);
}

int Search::distance(int u, int v){
    return graph->at(u,v);
}

Node::Node(int index){
    this->index = index;
    h =f = 0;//
    parent = NULL;
}

Node::Node(int index, Node *parent){
    this->index = index;
    this->parent = parent;
    this->h = 0;
}

void Node::updateCost(int h, int g){
    this->h = h;
    this->g = g;
    f = g + h;
}

int Node::getIndex(){
    return index;
}

void Node::print(){
    printf("Node %d: (g=%d, h=%d)\n", index, g, h);
    printParents();
}

void Node::printParents(){
    printf("\tParents: ");
    Node* p = parent;
    while (p != NULL){
        printf("->%d ", p->getIndex());
        p = p->getParent();
    }
    printf("\n");
}

















