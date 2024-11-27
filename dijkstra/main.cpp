#include <iostream>
#include <string>
#include <regex>

#include "exceptions/FileNotOpenException.h"
#include "models/Graph/Graph.h"
#include "models/Dijkstra/Dijkstra.h"

int main() {
    setlocale(LC_ALL, "ru");
    std::cout << "Введите название файла:\n";
    std::string filename;
    filename = "1000.txt";
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
        Way shortest_way = dijsktra.shortestWay(*begin, *end);
    } catch (FileNotOpenException) {
        std::cout << "Невозможно открыть файл. Убедитесь, что он существует";
        return -2;
    }
    return 0;
}