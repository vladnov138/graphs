#include "Ant.h"
#include "PriorityQueue/PriorityQueue.h"
#include <cmath>
#include <random>
#include <chrono>

Ant::Ant(Node* startPosition) {
    this->startPosition = startPosition;
    this->currentPosition = startPosition;
}

Node* Ant::chooseWay(const int alpha, const int beta) {
    node_iterator nb_it = currentPosition->nb_begin();
    node_iterator nb_end = currentPosition->nb_end();
    PriorityQueue probalitiesNodes;
    bool isStartAvailable = false;
    double sumProbability = 0.0;
    for (node_iterator it = nb_it; it != nb_end; it++) {
        if (visitedNodes.find(*it) != visitedNodes.end()) {
            if (*it == startPosition) {
                isStartAvailable = true;
            }
            continue;
        }

        double pheramone = currentPosition->getPheramone(*it); // Ферамоны на ребре
        double attractiveness = 1.0 / currentPosition->getWeight(*it); // Привлекательность ребра
        double prob = std::pow(pheramone, alpha) * std::pow(attractiveness, beta);
        probalitiesNodes.push(*it, prob);
        sumProbability += prob; // Считаем сумму вероятностей для формулы (знаменатель)
    }

    if (probalitiesNodes.empty() && isStartAvailable) {
        return startPosition;
    }

    double mainProbability = randomChoice(); // рандомная p
    double cumulative = 0.0; // Кумулятивная сумма для подсчета вероятностей

    while (!probalitiesNodes.empty()) {
        MarkedNode markedNode = probalitiesNodes.pop();
        cumulative += markedNode.mark / sumProbability;
        if (mainProbability <= cumulative) {
            return markedNode.node;
        }
    }
    return NULL;
}

// Генератор случайных чисел от 0 до 1
double Ant::randomChoice() {
    std::uniform_real_distribution<> dist(0.0, 1.0);
    std::default_random_engine re(std::chrono::system_clock::now().time_since_epoch().count());
    return dist(re);
}

std::set<Node*>* Ant::getVisitedNodes() {
    return &visitedNodes;
}

void Ant::visitNode(Node* node) {
    currentPosition = node;
    visitedNodes.insert(node);
}

Node* Ant::getCurrentPosition() {
    return currentPosition;
}
