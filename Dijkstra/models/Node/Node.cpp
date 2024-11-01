#include "Node.h"

Node::Node(std::string& aname) : name(aname) { }

void Node::addNeighbour(Node* neighbour, int weight) {
    if (!neighbour) {
        throw NodeException();
    }
    neighbours.insert(neighbour);
    neighbours_weights[neighbour] = weight;
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
