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
    const double PHERAMONE_HOLD_SPEED = 0.01;
    const int MAX_ITERATIONS = 5000;
    const int ANTS_COUNT = 1;
    const bool isDirectional = true;

    try {
        Graph graph(filename, isDirectional);
        AntColonyAlgorithm antColonyAlgorithm(graph, ALPHA, BETA, PHERAMONE_HOLD_SPEED, MAX_ITERATIONS);
        node_iterator begin = graph.begin();
        Way finalWay = antColonyAlgorithm.findWay(ANTS_COUNT, *begin);
        // Данные для графиков
        std::map<int, std::vector<Way>> results = antColonyAlgorithm.getPlotData();

        if (finalWay.length <= 0) {
            std::cout << "Путь не найден";
            return -1;
        }

        // Векторы для данных
        std::vector<int> iterations;
        std::vector<double> lengths;
        // Заполнение векторов данными
        for (const auto& [iteration, way] : results) {
            iterations.push_back(iteration);
            lengths.push_back(0);
        }

        // Отрисовка данных
        plt::figure(121);
        plot(results, 0, MAX_ITERATIONS);
        plt::title("Ant Path Lengths Across Iterations");
        plt::xlabel("Iteration");
        plt::ylabel("Path Length");
        plt::legend();
        plt::grid(true);
        plt::figure(122);
        plt::plot(iterations, lengths, "r-"); // "r-" — красная линия
        plt::xlabel("Iterations");
        plt::ylabel("Path Length");
        plt::title("Path Length vs Iterations");
        plt::show();

        std::vector<Node> wayNodes  = finalWay.nodes;
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
