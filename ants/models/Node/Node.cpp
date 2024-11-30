#include "Node.h"

Node::Node(std::string& aname) : name(aname) { }

void Node::addNeighbour(Node* neighbour, int weight) {
    if (!neighbour || weight <= 0 || neighbour == this) {
        throw NodeException();
    }
    neighbours.insert(neighbour);
    neighbours_weights[neighbour] = weight;
    neighbours_pheramones[neighbour] = 0.01;
}

void Node::removeNeighbour(Node* neighbour) {
    neighbours.erase(neighbour);
}

const std::string& Node::getName() const {
    return name;
}

const int Node::getWeight(Node* node) const {
    auto it = neighbours_weights.find(node);
    if (it != neighbours_weights.end()) {
        return it->second;
    }
    throw NodeException();
}

const std::set<Node*> Node::getNeighbours() const {
    return neighbours;
}

const double Node::getPheramone(Node* node) const {
    auto it = neighbours_pheramones.find(node);
    if (it != neighbours_pheramones.end()) {
        return it->second;
    }
    throw NodeException();
}

void Node::setPheramone(Node* node, double delta) {
    auto it = neighbours_pheramones.find(node);
    if (delta < 0.01) {
        delta = 0.01;
    }
    if (it != neighbours_pheramones.end()) {
        it->second = delta;
    } else {
        throw NodeException();
    }
}
