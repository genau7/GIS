#include "search.h"
#include <stdio.h>

const int vNum = 5; //changed to dynamic value and dynamic arrays later on

Search::Search(Graph* graph){
    this->graph = graph;
}

void Search::heuristic(){
    //int vNum = graph->getVerticesNum();
    int parent[vNum]; //minimum spanning tree path (first node's parent index is -1)
    int minDistanceFromTree[vNum];
    bool minTreeSet[vNum];  // if i-element is set to True, than i-vertices has been placed in the tree set

    for (int i = 0; i < vNum; i++){
        minDistanceFromTree[i] = INT_MAX;
        minTreeSet[i] = false;
    }

   //pick the first node
    minDistanceFromTree[0] = 0;
    parent[0] = -1;
    minTreeSet[0] = true;

    for (int count = 1; count < vNum-1; ++count){
        //find and add to tree path a node 'u' such that distance from the tree to it is smallest
        int u = bestVertexIndex(minDistanceFromTree, minTreeSet);
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
    printTree(parent);
}

int Search::bestVertexIndex(int minDistanceFromTree[], bool treeSet[]){
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

void Search::printTree(int parent[]){
    //int vNum = graph->getVerticesNum();
    printf("Edge   Weight\n");
    for (int i = 1; i < vNum; i++)
        printf("%d - %d    %d \n", parent[i], i, distance(i, parent[i]));
}

int Search::distance(int u, int v){
    return graph->at(u,v);
}
