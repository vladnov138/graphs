#include "Node.h"

Node::Node(std::string& aname) : name(aname) { }

Node::Node(Node* node) {
    if (!node) {
        throw NodeException();
    }

    this->name = node->name;

    // Скопируем веса соседей и феромоны без указателей (пока пустые связи)
    for (const auto& [neighbour, weight] : node->neighbours_weights) {
        this->neighbours_weights[neighbour] = weight;
    }

    for (const auto& [neighbour, pheromone] : node->neighbours_pheramones) {
        this->neighbours_pheramones[neighbour] = pheromone;
    }
}

void Node::addNeighbour(Node* neighbour, int weight) {
    if (!neighbour || weight <= 0 || neighbour == this) {
        throw NodeException();
    }
    neighbours.insert(neighbour);
    neighbours_weights[neighbour] = weight;
    neighbours_pheramones[neighbour] = 0.001;
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
    if (delta < 0.001) {
        delta = 0.001;
    }
    if (it != neighbours_pheramones.end()) {
        it->second = delta;
    } else {
        throw NodeException();
    }
}

