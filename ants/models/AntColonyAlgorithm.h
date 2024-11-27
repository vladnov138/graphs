#ifndef ANTCOLONYALGORITHM_H
#define ANTCOLONYALGORITHM_H

#include "Ant.h"
#include "Way.cpp"
#include "Graph/Graph.h"

class AntColonyAlgorithm {
    const int alpha = 2;
    const int beta = 5;
    const double pheramoneHoldSpeed = 0.2; // Скорость испарения ферамонов
    const int maxIterations = 500;
    const Graph &graph;
public:
    AntColonyAlgorithm(const Graph& agraph) : graph(agraph) {}
    Way findWay(int antsCount, Node* begin);
    void updateGlobalPheramones(Node* begin, std::map<std::pair<std::string, std::string>, double> wayLength);
};

#endif // ANTCOLONYALGORITHM_H
