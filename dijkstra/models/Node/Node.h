#pragma once

#include <string>
#include <set>

#include "../../exceptions/NodeException.h"

class Node {
private: 
    typedef std::set<Node*>::const_iterator node_iterator;
    std::string name;
    std::set<Node*> neighbours;
    std::set<int> neighbours_weights;
    int weight;

    void addNeighbour(Node* neighbour, int weight);
    
    void removeNeighbour(Node* neighbour);
public:
    Node(std::string& aname);

    const std::string& getName() const;
    const int getWeight(Node* node) const;

    node_iterator nb_begin() const {
        return neighbours.begin();
    }

    node_iterator nb_end() const {
        return neighbours.end();
    }

    friend class Graph;
};

