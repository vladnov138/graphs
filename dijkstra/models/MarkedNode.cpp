#pragma once

#include "./Node/Node.h"

struct MarkedNode
{
    Node *node;
    int mark;
    Node *prev;
    MarkedNode(Node *anode = 0, int amark = 0, Node *aprev = 0) : node(anode), mark(amark), prev(aprev) {}
};