#ifndef ALPHABETA_H
#define ALPHABETA_H

#include <vector>
#include "../boardcell/boardcell.h"

class AlphaBeta
{
    int DEPTH;
    int ROWS;
    int COLUMNS;
    BoardCell* board; // Игровая доска

    std::vector<int> getPossibleMoves(); // Счет возможных ходов
    std::vector<int> getMovesBranch(int currentDepth, bool selectWinMove); // Функция построения дерева
    int getVerticalScores(); // Подсчет очков по вертикали
    int getHorizontalScores(); // Подсчет очков по горизонтали
    int getDiagonalScores(); // Подсчет очков по диагонали
    int getScores(); // Подсчет очков
    int evalSequence(int count); // Перевод последовательности в очки
    void makeMove(int idx, BoardCell value); // Имитация хода
    bool checkVictory(BoardCell value); // Проверка победы
public:
    AlphaBeta(AlphaBeta const &ab);
    AlphaBeta(const int depth, const int rows=6, const int columns=7);
    int getBestMove(BoardCell* boardcell);
    ~AlphaBeta();
};

#endif // ALPHABETA_H
