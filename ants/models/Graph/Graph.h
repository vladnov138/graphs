#pragma once

#include <fstream>
#include <regex>
#include <string>
#include <set>

#include "../Node/Node.h"

typedef std::set<Node*>::const_iterator node_iterator;
class Graph{
private:
    std::set<Node*> nodes;
    bool isDirectional;
public:
    Graph();
    Graph(const Graph* graph);
    Graph(const std::string filename, bool isDirectional);
    void addNode(Node* node);
    void removeNode(Node* node);
    void addEdge(Node* begin, Node* end, int weight);
    void removeEdge(Node* begin, Node* end);
    void splitGraph();
    const std::set<Node*> getNodes() const;
    node_iterator begin() {
        return nodes.begin();
    }
    node_iterator end() const {
        return nodes.end();
    }
};
