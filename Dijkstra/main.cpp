#include <iostream>
#include <string>
#include <regex>

#include "exceptions/FileNotOpenException.h"
#include "models/Dijkstra/Dijkstra.h"
#include "models/MarkedNode.cpp"

int main() {
    setlocale(LC_ALL, "ru");
    std::cout << "Введите название файла:\n";
    std::string filename;
    std::cin >> filename;
    // filename = "/home/vladnov138/graphs/Dijkstra/data/1000.txt";
    std::regex rgx(".+\.(csv|txt)");
    if (!regex_match(filename, rgx)) {
        std::cout << "Некорректное имя файла!";
        return -1;
    }
    try {
        Graph graph(filename);
        Dijkstra dijsktra(graph);
        node_iterator begin = graph.begin();
        node_iterator end = graph.end();
        Way shortest_way = dijsktra.shortestWay(*begin, *--end);
        std::vector<MarkedNode> wayNodes  = shortest_way.nodes;
        std:: cout << "Кратчайший путь: " << std::endl;
        // Выводим в обратном порядке:
        for (auto it = wayNodes.rbegin(); it != wayNodes.rend(); ++it) {
            std::cout << it->node->getName() << " ";
        }
        std::cout << std::endl;
        std::cout << "Длина пути: " << shortest_way.length << std::endl;
    } catch (FileNotOpenException) {
        std::cout << "Невозможно открыть файл. Убедитесь, что он существует";
        return -2;
    }
    return 0;
}
