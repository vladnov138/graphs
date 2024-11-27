#ifndef ANT_H
#define ANT_H

#include "Graph/Graph.h"
#include "Node/Node.h"

#include <set>
class Ant {
    Node* startPosition;
    Node* currentPosition;
    std::set<Node*> visitedNodes;

    double randomChoice();
public:
    Ant(Node* startPosition);
    Node* chooseWay(const int alpha, const int beta);
    Node* getCurrentPosition();
    void visitNode(Node* node);
    std::set<Node*>* getVisitedNodes();
};

#endif // ANT_H
