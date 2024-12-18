#ifndef GAMEENEMY_H
#define GAMEENEMY_H

#include "../alphabeta/alphabeta.h"
#include "../boardcell/boardcell.h"

#include <QObject>


class GameEnemy : public QObject
{
    AlphaBeta aiAlgorithm; // ИИ алгоритм для игры
public:
    GameEnemy(AlphaBeta& aiAlgorithm) : aiAlgorithm(aiAlgorithm) {};
    int makeTurn(BoardCell* board); // ход противника
};

#endif // GAMEENEMY_H
