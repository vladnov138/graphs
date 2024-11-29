#include "exceptions/FileNotOpenException.h"
#include "exceptions/ValidationException.h"
#include "models/AntColonyAlgorithm/AntColonyAlgorithm.h"
#include "models/Graph/Graph.h"
#include "libs/matplotlibcpp.h"
#include <iostream>
#include <regex>

using namespace std;
namespace plt = matplotlibcpp;

int main()
{
    setlocale(LC_ALL, "ru");
    std::cout << "Введите название файла:\n";
    std::string filename;
    std::cin >> filename;
    // filename = "/home/vladnov138/graphs/ants/data/synthetic.txt";
    std::regex rgx(".+\.(csv|txt)");
    if (!regex_match(filename, rgx)) {
        std::cout << "Некорректное имя файла!";
        return -1;
    }
    const double ALPHA = 2.0;
    const double BETA = 4.0;
    const double PHERAMONE_HOLD_SPEED = 0.05;
    const int MAX_ITERATIONS = 100;
    const int ANTS_COUNT = 100;

    try {
        Graph graph(filename);
        AntColonyAlgorithm antColonyAlgorithm(graph, ALPHA, BETA, PHERAMONE_HOLD_SPEED, MAX_ITERATIONS);
        node_iterator begin = graph.begin();
        std::map<int, Way> results = antColonyAlgorithm.findWay(ANTS_COUNT, *begin);

        // Векторы для данных
        std::vector<int> iterations;
        std::vector<double> lengths;
        Way finalWay;
        // Заполнение векторов данными
        for (const auto& [iteration, way] : results) {
            iterations.push_back(iteration);
            lengths.push_back(way.length);
            finalWay = way;
        }

        if (finalWay.length <= 0) {
            std::cout << "Путь не найден";
            return -1;
        }

        // Отрисовка данных
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
