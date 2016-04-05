#include "search.h"
#include <stdio.h>

Search::Search(Graph* graph){
    this->graph = graph;
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
    //int vNum = graph->getVerticesNum();

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
        printf("%d - %d    %d \n", parent[i], i, distance(i, parent[i]));
        sum += distance(i,parent[i]);
    }
    printf("The minimum spanning tree path = %d\n", sum);
}

int Search::distance(int u, int v){
    return graph->at(u,v);
}
