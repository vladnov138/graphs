#include "AntColonyAlgorithm.h"
#include "../../exceptions/ValidationException.h"

#include <queue>

AntColonyAlgorithm::AntColonyAlgorithm(const Graph& agraph, const double alpha, const double beta,
                                       const double pheramoneHoldSpeed, const unsigned int maxIterations) : graph(agraph) {
    if (alpha < 0 || beta < 0 || pheramoneHoldSpeed < 0 || pheramoneHoldSpeed > 1 || maxIterations == 0) {
        throw ValidationException();
    }
    this->alpha = alpha;
    this->beta = beta;
    this->pheramoneHoldSpeed = pheramoneHoldSpeed;
    this->maxIterations = maxIterations;
}

// Функция симуляции муравьев
Way AntColonyAlgorithm::simulateAnt(Node* begin) {
    Ant ant = Ant(begin);
    Way way; // промежуточный путь для каждого муравья
    Node* currentPosition = ant.getCurrentPosition();
    way.nodes.push_back(*currentPosition);
    ant.visitNode(begin);
    // Идем в цикле, пока не вернемся на старт или не зайдем в тупик
    // На старт возвращаемся, если можем и обошли все соседние вершины
    do {
        Node* nextNode = ant.chooseWay(alpha, beta);
        if (nextNode == NULL) {
            // way.length = 0;
            break;
        }
        int weight = currentPosition->getWeight(nextNode);
        way.nodes.push_back(*nextNode);
        way.length += weight;
        ant.visitNode(nextNode);
        currentPosition = ant.getCurrentPosition();
    } while (currentPosition != begin);
    return way;
}

// Функция нахождения короткого пути
Way AntColonyAlgorithm::findWay(int antsCount, Node* begin) {
    Way finalWay; // найденный короткий путь
    for (int iteration = 1; iteration <= maxIterations; iteration++) {
        std::map<std::pair<std::string, std::string>, double> wayLengths; // Key: {NodeName, NodeName}, Value: edgeLength
        std::vector<Way> currentIterationWays;
        for (int i = 0; i < antsCount; i++) {
            Way way = simulateAnt(begin);
            // Если обошли все вершины + вернулись в стартовую
            if (way.nodes.size() == graph.getNodes().size() + 1 && way.length > 0) {
                if (finalWay.length <= 0 || finalWay.length > way.length) {
                    finalWay = way;
                }

                for (int j = 1; j < way.nodes.size(); j++) {
                    // Для обновления ферамонов
                    wayLengths[std::pair(way.nodes[j - 1].getName(), way.nodes[j].getName())] += 1.0 / way.length;
                }

                currentIterationWays.push_back(way);
            } else {;
                currentIterationWays.push_back(*new Way());
            }
        }
        updatePheramones(begin, wayLengths);
        iterWays[iteration] = currentIterationWays;
    }
    return finalWay;
}

// Добавление феромонов на основе пройденного пути
void AntColonyAlgorithm::updatePheramones(Node* begin, std::map<std::pair<std::string, std::string>, double> wayLength) {
    std::set<std::pair<Node*, Node*>> updatedEdges; // Учет уже обновленных ребер
    std::queue<Node*> nodeQueue;
    nodeQueue.push(begin);

    // BFS для обхода всех соседей
    while (!nodeQueue.empty()) {
        Node* currentNode = nodeQueue.front();
        nodeQueue.pop();

        // Итерация по соседям текущего узла
        for (node_iterator it = currentNode->nb_begin(); it != currentNode->nb_end(); ++it) {
            Node* neighbor = *it;
            std::pair<Node*, Node*> edge = {currentNode, neighbor};

            // Пропускаем уже обновленные ребра
            if (updatedEdges.find(edge) != updatedEdges.end()) {
                continue;
            }

            // Рассчитываем значение нового феромона
            double currentPheramone = currentNode->getPheramone(neighbor);
            double newPheramone = (1 - pheramoneHoldSpeed) * currentPheramone;
            std::pair<std::string, std::string> stringEdge = {currentNode->getName(), neighbor->getName()};
            if (wayLength.find(stringEdge) != wayLength.end()) {
                newPheramone += wayLength.find(stringEdge)->second;
            }
            currentNode->setPheramone(neighbor, newPheramone);

            // Помечаем ребро как обновленное
            updatedEdges.insert(edge);
            nodeQueue.push(neighbor); // Добавляем соседа в очередь
        }
    }
}

std::map<int, std::vector<Way>> AntColonyAlgorithm::getPlotData() const {
    return iterWays;
}
