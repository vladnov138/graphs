#pragma once

#include <vector>

#include "../MarkedNode.cpp"

class PriorityQueue {
    std::vector<MarkedNode> nodes;
public:
    std::vector<MarkedNode> getNodes() const;
    MarkedNode pop();
    void push(Node* node, int mark, Node* prev);
    bool empty() const { return nodes.empty(); }
};
