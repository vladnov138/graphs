#include "Ant.h"
#include "../PriorityQueue/PriorityQueue.h"
#include <cmath>
#include <random>
#include <chrono>

// Конструктор
Ant::Ant(Node* startPosition) {
    this->startPosition = startPosition;
    this->currentPosition = startPosition;
}

// Выбрать путь
Node* Ant::chooseWay(const double alpha, const double beta) {
    node_iterator nb_it = currentPosition->nb_begin(); // Итератор
    node_iterator nb_end = currentPosition->nb_end(); // Ссылка на конец
    PriorityQueue probalitiesNodes; // Очередь с приоритетом по числу p (которое считаем по формуле)
    bool isStartAvailable = false; // Есть ли стартовая вершина в соседях
    double sumProbability = 0.0; // Сумма вероятностей
    for (node_iterator it = nb_it; it != nb_end; it++) {
        // Пропускаем уже посещенные узлы
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

    // Если муравей не обошел никакой узел (т.к. ранее все обошел), и есть стартовая позиция в соседях, то идем туда
    if (probalitiesNodes.empty() && isStartAvailable) {
        return startPosition;
    }

    double mainProbability = randomChoice(); // рандомная p
    double cumulative = 0.0; // Кумулятивная сумма для подсчета вероятностей

    // Считаем вероятность
    while (!probalitiesNodes.empty()) {
        MarkedNode markedNode = probalitiesNodes.pop();
        cumulative += markedNode.mark / sumProbability;
        if (mainProbability <= cumulative) {
            return markedNode.node;
        }
    }
    return NULL; // Если зашел в тупик
}

// Генератор случайных чисел от 0 до 1
double Ant::randomChoice() {
    std::uniform_real_distribution<> dist(0.0, 1.0);
    static std::default_random_engine re(std::chrono::system_clock::now().time_since_epoch().count());
    return dist(re);
}

// Геттер посещенных узлов
std::set<Node*>* Ant::getVisitedNodes() {
    return &visitedNodes;
}

// Посетить узел
void Ant::visitNode(Node* node) {
    currentPosition = node;
    visitedNodes.insert(node);
}

// Геттер текущего узла
Node* Ant::getCurrentPosition() {
    return currentPosition;
}
