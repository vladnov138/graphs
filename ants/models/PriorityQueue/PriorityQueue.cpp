#include "PriorityQueue.h"

MarkedNode PriorityQueue::pop()
{
    MarkedNode mn = nodes.back();
    nodes.pop_back();
    return mn;
}

void PriorityQueue::push(Node *node, double mark)
{
    std::vector<MarkedNode>::iterator it = nodes.begin();
    MarkedNode mn(node, mark);
    while (it != nodes.end() && mark < it->mark)
        it++;
    if (it == nodes.end())
        nodes.push_back(mn);
    else
        nodes.insert(it, mn);
}

