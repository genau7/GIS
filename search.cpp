#include "search.h"
#include <stdio.h>

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
    int h[]={7,6,4,2,0}; //temp

    std::set<int> closedIndexes;

    //init values and choose a starting point
    startIndex = 0;
    Node* initNode = new Node(startIndex);
    initNode->updateCost(h[startIndex]); //calc heuristic instead here
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
        closedIndexes.insert(current->getIndex());

        //for each neighbor
        for(int i = 1; i < vNum; i++){
            if(!graph->edgeExists(current->getIndex(), i))
                continue;

            Node* neighbor = new Node(i, current);
            int cost = current->backwardCost() + distance(current->getIndex(), neighbor->getIndex());
            int forwardCost = h[i]; //get heuristic
            neighbor->updateCost(forwardCost, cost);
            if(frontier.contains(neighbor) && cost < neighbor->backwardCost()){
                frontier.remove(neighbor); //TODO test this
            }
            if(closedIndexes.find(neighbor->getIndex())!= closedIndexes.end() && cost < neighbor->backwardCost()){
                closedIndexes.erase(closedIndexes.find(neighbor->getIndex()));
            }
            if(closedIndexes.find(neighbor->getIndex()) == closedIndexes.end() && !frontier.contains(neighbor)){
                frontier.push(neighbor);
            }
        }
        if(iteration>vNum*1000)
            break;
    }
    current = lowestRank;
    this->totalCost = lowestRank->backwardCost();
    do {
        path.push_front(current->getIndex());
        current = current->getParent();
    } while (current->getParent() != NULL);
    path.push_front(current->getIndex());
}

bool Search::nodeInPQ(Node *node, std::priority_queue<Node *> pq){
    std::vector<Node*> copy(pq.size());
    std::copy(&(pq.top()), &(pq.top()) + pq.size(), &copy[0]);
    for(std::vector<Node*>::iterator it = copy.begin(); it != copy.end(); ++it) {
        if((*it)->getIndex() == node->getIndex())
            return true;
    }
    return false;
}

void Search::heuristic(){
    int vNum = graph->getVerticesNum();
    std::vector<int> parent(vNum); //minimum spanning tree path (first node's parent index is -1), indicated by nodes' parent
    std::vector<int>minDistanceFromTree(vNum, INT_MAX);
    std::vector<bool> minTreeSet(vNum, false);  // if i-element is set to True, than i-vertices has been placed in the tree set

   //pick the first node
    minDistanceFromTree[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < vNum-1; ++count){
        //find and add to tree path a node 'u' such that distance from the tree to it is smallest
        int u = bestVertexIndex(minDistanceFromTree, minTreeSet, vNum);
        minTreeSet[u] = true;

        //Update vertices' distance from the tree
        for (int v = 0; v < vNum; ++v){
            // Update the distance only if graph[u][v] is smaller than key[v]
            if (distance(u,v) != INT_MAX && minTreeSet[v] == false && distance(u,v) <  minDistanceFromTree[v]){
                parent[v]  = u;
                minDistanceFromTree[v] = distance(u,v);
            }
        }
    }
    printTree(parent, vNum);
}

int Search::bestVertexIndex(std::vector<int> minDistanceFromTree, std::vector<bool> treeSet, int vNum){
    int minIndex;
    int min = INT_MAX;

    for (int v = 0; v < vNum; v++){
        if (treeSet[v] == false && minDistanceFromTree[v] < min){
            min = minDistanceFromTree[v];
            minIndex = v;
        }
    }
    return minIndex;
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
    h = 0;//
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


/*
bool Node::operator >(const Node& otherNode){
    if(this->cost() > otherNode.cost())
        return true;
    return false;
} //del?

bool Node::operator <(const Node& otherNode){
    if(this->cost() < otherNode.cost())
        return true;
    return false;
}

bool Node::operator <=(const Node& otherNode){
    if(this->cost() <= otherNode.cost())
        return true;
    return false;
}

bool Node::operator ==(const Node& otherNode){
    if(this->cost() == otherNode.cost())
        return true;
    return false;
}

bool Node::operator >=(const Node& otherNode){
    if(this->cost() >= otherNode.cost())
        return true;
    return false;
}

*/
















