#pragma once
#include <string>
#include <map>
#include <set>

#include "../../exceptions/NodeException.h"

class Node {
private:
    typedef std::set<Node*>::const_iterator node_iterator;
    std::string name;
    std::set<Node*> neighbours;
    std::map<Node*, int> neighbours_weights; // Key: Node, Value: Weight
    std::map<Node*, double> neighbours_pheramones; // Key: Node, Value: Pheramone

    void addNeighbour(Node* neighbour, int weight);
    void removeNeighbour(Node* neighbour);
public:
    Node(std::string& aname);

    const std::string& getName() const;
    const int getWeight(Node* node) const;
    const double getPheramone(Node* node) const;
    const std::map<Node*, double> getPheramones() const;
    const std::set<Node*> getNeighbours() const;
    void setPheramone(Node* node, double delta);
    void updateGlobalPheramones(Node* node);

    node_iterator nb_begin() const {
        return neighbours.begin();
    }

    node_iterator nb_end() const {
        return neighbours.end();
    }

    friend class Graph;
};

