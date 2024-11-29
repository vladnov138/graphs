#ifndef ANTCOLONYALGORITHM_H
#define ANTCOLONYALGORITHM_H

#include "../Ant/Ant.h"
#include "../Way.cpp"
#include "../Graph/Graph.h"

/*
Класс муравьиного алгоритма. Предназначен для нахождения короткого пути
*/
class AntColonyAlgorithm {
    double alpha;
    double beta;
    double pheramoneHoldSpeed; // Скорость испарения ферамонов
    unsigned int maxIterations = 1000;
    const Graph &graph;

    Way simulateAnt(Node* begin); // Функция симуляции муравьев
public:
    AntColonyAlgorithm(const Graph& agraph, const double alpha, const double beta,
                       const double pheramoneHoldSpeed, const unsigned int maxIterations);
    std::map<int, Way> findWay(int antsCount, Node* begin); // Функция нахождения короткого пути
    void updatePheramones(Node* begin,
                          std::map<std::pair<std::string, std::string>, double> wayLength); // Функция обновления ферамонов
};

#endif // ANTCOLONYALGORITHM_H
