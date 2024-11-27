#pragma once

#include <queue>

#include "../Graph/Graph.h"

class BFS {
private:
    const Graph &graph;
public:
    BFS(const Graph &agraph);
    bool connected(Node* begin, Node* end);
};