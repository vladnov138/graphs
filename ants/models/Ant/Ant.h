#ifndef ANT_H
#define ANT_H

#include "../Graph/Graph.h"
#include "../Node/Node.h"
#include <set>

/*
Класс муравей. Является частью муравьиного алгоритма, предназначен
для симуляции поведения муравья (выбор пути и переход в него)
*/
class Ant {
    Node* startPosition; // Стартовая позиция муравья
    Node* currentPosition; // Текущая позиция муравья
    std::set<Node*> visitedNodes; // Посещенные узлы

    double randomChoice(); // Функция для генерации рандомного числа от 0 до 1
public:
    Ant(Node* startPosition); // Конструктор
    Node* chooseWay(const double alpha, const double beta); // Выбрать путь
    Node* getCurrentPosition(); // Геттер текущей позиции
    void visitNode(Node* node); // Посетить узел
    std::set<Node*>* getVisitedNodes(); // Геттер посещенных узлов
};

#endif // ANT_H
