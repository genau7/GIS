#include "search.h"

int main(int argc, char *argv[])
{
    //read distance matrix from file into Graph object
    std::string dataFile = "../GIS/src/tsp10a"; //6b, 7a sucks
    //std::string dataFile = "../GIS/src/test"; //not a A/TSP
    std::vector<std::vector<int> >* data = FileParser::readMatrix(dataFile);
    Graph graph(data);
    graph.print();

    int start = 0;

   // Search search(&graph);
    int vNum = graph.getVerticesNum();
    for (int i = 0; i < vNum; i++){
        printf("===========================\nStarting at node %d\n", i);
        Search search(&graph);
        search.findPath(i);
        search.printPath();
    }



   /* Node* a = new Node(0);
    Node* b = new Node(1);
    Node* c = new Node(2);
    a->updateCost(50,100);
    b->updateCost(20,10);
    c->updateCost(100,20);

    printf("Nodes costs are followin: %d, %d, %d\n", a->cost(), b->cost(), c->cost());

    Frontier frontier(3);
    frontier.push(a);
    frontier.push(b);
    frontier.push(c);
    printf("Frontier TOP - index=%d, cost=%d\n", frontier.top()->getIndex(), frontier.top()->cost());
    printf("Frontier end - index=%d, cost=%d\n\n", frontier.end()->getIndex(), frontier.end()->cost());

    Node* d = new Node(6);
    Node* e = new Node(7);
    Node* f = new Node(8);
    d->updateCost(0,5);
    e->updateCost(0,    15);
    f->updateCost(0,25);
    frontier.push(d);
    frontier.push(e);
    frontier.push(f);
    printf("Frontier TOP - index=%d, cost=%d\n", frontier.top()->getIndex(), frontier.top()->cost());
    printf("Frontier end - index=%d, cost=%d\n", frontier.end()->getIndex(), frontier.end()->cost());
    printf("Frontier TOP - index=%d, cost=%d\n", frontier.top()->getIndex(), frontier.top()->cost());
    printf("Frontier end - index=%d, cost=%d\n", frontier.end()->getIndex(), frontier.end()->cost());*/

    return 0;
}

