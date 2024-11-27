#pragma once

#include "../Graph/Graph.h"
#include "../PriorityQueue/PriorityQueue.h"
#include "../MarkedNode.cpp"
#include "../Way.cpp"

class Dijkstra
{
    const Graph &graph;
public:
    Dijkstra(const Graph &agraph) : graph(agraph) {}
    Way shortestWay(Node *begin, Node *end);
    Way unroll(std::map<Node *, MarkedNode> visited,
               Node *begin, Node *curr);
};
