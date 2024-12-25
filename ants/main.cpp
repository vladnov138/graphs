#include "exceptions/FileNotOpenException.h"
#include "exceptions/ValidationException.h"
#include "models/AntColonyAlgorithm/AntColonyAlgorithm.h"
#include "models/Graph/Graph.h"
#include "libs/matplotlibcpp.h"
#include <iostream>
#include <regex>

using namespace std;
namespace plt = matplotlibcpp;

void plot(std::map<int, std::vector<Way>>& iterWays, const int antIdx, const int iterationCount) {
    // Подготовка данных

    std::vector<int> iterations;
    std::vector<int> maxLengths;
    for (int i = 1; i <= iterationCount; i++) {
        if (iterWays[i][antIdx].length > 0) {
            iterations.push_back(i + 1);
            maxLengths.push_back(iterWays[i][antIdx].length);
        }
    }

    plt::plot(iterations, maxLengths);
}

int main()
{
    setlocale(LC_ALL, "ru");
    std::cout << "Введите название файла:\n";
    std::string filename;
    // std::cin >> filename;
    filename = "/home/vladnov138/graphs/ants/data/synthetic.txt";
    std::regex rgx(".+\.(csv|txt)");
    if (!regex_match(filename, rgx)) {
        std::cout << "Некорректное имя файла!";
        return -1;
    }
    const double ALPHA = 1.0;
    const double BETA = 2.0;
    const double PHERAMONE_HOLD_SPEED = 0.05;
    const int MAX_ITERATIONS = 1000;
    const int ANTS_COUNT = 3;
    const bool isDirectional = true;

    try {
        Graph graph(filename, isDirectional);
        AntColonyAlgorithm antColonyAlgorithm(graph, ALPHA, BETA, PHERAMONE_HOLD_SPEED, MAX_ITERATIONS);
        node_iterator begin = graph.begin();
        Way finalWay = antColonyAlgorithm.findWay(ANTS_COUNT, *begin);
        std::vector<Node> wayNodes  = finalWay.nodes;
        if (finalWay.length <= 0) {
            std::cout << "Путь не найден";
            return -1;
        }

        // Данные для графиков
        std::map<int, std::vector<Way>> results = antColonyAlgorithm.getPlotData();
        std::vector<Way> bestWays = antColonyAlgorithm.getBestWaysData();
        std::vector<std::map<std::pair<std::string, std::string>, double>> nodesStates = antColonyAlgorithm.getNodesStates();

        // Векторы для данных
        std::vector<int> iterations;
        std::vector<double> lengths;
        std::vector<double> pheramones;
        // Заполнение векторов данными
        for (const auto& [iteration, way] : results) {
            iterations.push_back(iteration);
        }
        for (const auto& bestWay : bestWays) {
            lengths.push_back(bestWay.length);
        }
        for (int it = 0; it < nodesStates.size(); it++) {
            double pheromoneSum = 0;
            for (int i = 1; i < wayNodes.size(); i++) {
                pheromoneSum += nodesStates[it][make_pair(wayNodes[i - 1].getName(), wayNodes[i].getName())];
            }
            pheramones.push_back(pheromoneSum);
        }

        // Отрисовка данных
        plt::subplot2grid(3, 1, 0, 0);
        plot(results, 0, MAX_ITERATIONS);
        plt::title("Ant Path Lengths Across Iterations");
        plt::xlabel("Iteration");
        plt::ylabel("Path Length");
        plt::legend();
        plt::grid(true);
        plt::subplot2grid(3, 1, 1, 0);
        plt::plot(lengths, "r-"); // "r-" — красная линия
        plt::xlabel("Iterations");
        plt::ylabel("Path Length");
        plt::title("Path Length vs Iterations");
        plt::subplot2grid(3, 1, 2, 0);
        plt::plot(pheramones, "r-"); // "r-" — красная линия
        plt::xlabel("Iterations");
        plt::ylabel("Pheromones");
        plt::title("Pheromones sum");
        plt::show();

        std:: cout << "Кратчайший путь: " << std::endl;
        // Выводим:
        for (auto it = wayNodes.begin(); it != wayNodes.end(); ++it) {
            std::cout << it->getName() << " ";
        }
        std::cout << std::endl;
        std::cout << "Длина пути: " << finalWay.length << std::endl;
    } catch (FileNotOpenException) {
        std::cout << "Невозможно открыть файл. Убедитесь, что он существует";
        return -2;
    } catch (ValidationException) {
        std::cout << "Ошибка валидации. УБедитесь, что константы указаны верно";
        return -3;
    }

    return 0;
}
