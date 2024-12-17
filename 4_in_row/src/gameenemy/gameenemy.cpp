#include "gameenemy.h"

#include <QDebug>

int GameEnemy::makeTurn(BoardCell* board) {
    int idx = aiAlgorithm.getBestMove(board);
    qDebug() << idx;
    return idx;
}
