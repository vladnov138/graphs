#pragma once

#include "./Node/Node.h"

struct MarkedNode
{
    Node *node;
    double mark;
    MarkedNode(Node *anode = 0, double amark = 0) : node(anode), mark(amark) {}
};
