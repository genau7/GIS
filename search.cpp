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

int Frontier::size(){
    return opened.size();
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

Search::Search(Graph *graph){
    this->graph = graph;
    this->totalCost = INT_MAX;
}

bool Search::isGoal(Node *node){
    if (node->getIndex() == this->goalIndex)
        return true;
    return false;
}

void Search::findPath(int startIndex){
    this->goalIndex = startIndex;
    int vNum = graph->getVerticesNum();
    Frontier frontier;
    std::set<int> closed;

    //init values for the starting point
    Node* initNode = new Node(startIndex);
   // initNode->updateCost(heuristic2(goalIndex, initNode));
    initNode->updateCost(heuristic(startIndex, initNode));
    initNode->setParent(NULL);
    frontier.push(initNode);

    int iteration = 0;
    Node* lowestRank = NULL;
    Node* current = NULL;
    while(++iteration){
        lowestRank = frontier.top();
        if(iteration != 1 && isGoal(lowestRank))
            break; //reached the destination
        if(lowestRank->getParentsNum() == vNum-1){
            Node * goal = new Node(goalIndex, lowestRank);
            goal->updateCost(0, lowestRank->getCost());
            lowestRank = goal;
            break; //found the path, but need to add last node again (cyclic path)
        }

        if(frontier.size()==0){
            printf("No more nodes to search the path from. Failed!\n");
            break;
        }
        current = frontier.pop();
        //printf("[%d]: Popped from frontier(%d): ", iteration, frontier.size());
        //current->print();
        closed.insert(current->getIndex());

        //for each neighbor of the current vertex
        for(int i = 0; i < vNum; i++){
            if(!graph->edgeExists(current->getIndex(), i))
                continue;

            Node* neighbor = new Node(i, current);
            if (!neighbor->hasValidParents())
                continue;
            int cost = current->getBackwardCost() + distance(current->getIndex(), neighbor->getIndex());
            //int forwardCost = heuristic2(goalIndex, neighbor);
            int forwardCost = heuristic(i, neighbor);
            neighbor->updateCost(forwardCost, cost);
            //neighbor->print();
            bool inClosed = closed.find(neighbor->getIndex())!= closed.end();
            bool costMatters = cost < neighbor->getBackwardCost();
            /*if(frontier.contains(neighbor) && cost < neighbor->getBackwardCost()){
                            printf("ATTENTION!! DANGER ZONE!!!\n");
                            frontier.remove(neighbor); //TODO test this
                        }
            inClosed = closed.find(neighbor->getIndex())!= closed.end();
            if(closed.find(neighbor->getIndex())!= closed.end() && cost < neighbor->getBackwardCost()){
                closed.erase(closed.find(neighbor->getIndex()));
            }*/
            bool notExpandedYet = closed.find(neighbor->getIndex()) == closed.end() && !frontier.contains(neighbor);
            int nodesNumInPath = neighbor->getParentsNum() + 1;
            if(notExpandedYet || nodesNumInPath == vNum || true){
                frontier.push(neighbor);
                //printf("Added to frontier: ");
                //neighbor->print();
            }
        }
        /*if(iteration>vNum*100000){
            printf("Broke search iteration because it took more than the threshold value of %d\n");
            break;
        }*/
    }
    printf("Iteration finished at i=%d.\n", iteration);
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
int Search::heuristic2(int goal, Node *lastNode){
    std::set<int> closed =lastNode->path2IndexSet() ;
    int vNum = graph->getVerticesNum();
    int edgesLeftTillGoal = vNum - lastNode->getParentsNum();

    int minDistance = INT_MAX;
    for (int v = 0; v < vNum; v++){
        if (closed.find(v) == closed.end()) {
            if(distance(lastNode->getIndex(), v) < minDistance)
                minDistance = distance(lastNode->getIndex(), v);
        }
    }
    if (minDistance == INT_MAX)
        return distance(lastNode->getIndex(), goal);

    return edgesLeftTillGoal * minDistance;
}

int Search::heuristic(int start, Node* lastNode){

    std::set<int> closed =lastNode->path2IndexSet() ;
    int vNum = graph->getVerticesNum();
    if(vNum - closed.size() ==1)
        return distance(start, this->goalIndex);
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
    int temp=0;
    temp++;
   // printTree(parents, vNum);
    return calcPathCost(parents);
}

int Search::heuristic0(int start, std::set<int> closed){
    int vNum = graph->getVerticesNum();
    if(vNum - closed.size() ==1)
        return distance(start, this->goalIndex);
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
    printf("A* search found path with total cost = %d\n", this->totalCost);
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

int Node::getParentsNum(){
    Node *p = parent;
    int parentsNum = 0;
    while (p != NULL){
        parentsNum ++;
        p = p->getParent();
    }
    return parentsNum;
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

std::set<int> Node::path2IndexSet(){
    std::set<int> pathSet;
    Node* n = parent;
    while (n != NULL){
        pathSet.insert(n->index);
        n = n->parent;
    }
    return pathSet;
}

bool Node::hasValidParents(){
    std::set<int> parentsIndexes = path2IndexSet();
    //if this node's index is different than any of its parents, return true
    if (parentsIndexes.find(this->index) == parentsIndexes.end())
        return true;
    return false;

}















