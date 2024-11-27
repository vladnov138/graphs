#include "exceptions/FileNotOpenException.h"
#include "models/AntColonyAlgorithm.h"
#include "models/Graph/Graph.h"
#include <iostream>
#include <regex>

using namespace std;

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
    try {
        Graph graph(filename);
        AntColonyAlgorithm antColonyAlgorithm(graph);
        node_iterator begin = graph.begin();
        Way shortest_way = antColonyAlgorithm.findWay(100, *begin);
        std::vector<Node> wayNodes  = shortest_way.nodes;
        std:: cout << "Кратчайший путь: " << std::endl;
        // Выводим в обратном порядке:
        for (auto it = wayNodes.rbegin(); it != wayNodes.rend(); ++it) {
            std::cout << it->getName() << " ";
        }
        std::cout << std::endl;
        std::cout << "Длина пути: " << shortest_way.length << std::endl;
    } catch (FileNotOpenException) {
        std::cout << "Невозможно открыть файл. Убедитесь, что он существует";
        return -2;
    }
    return 0;
}
