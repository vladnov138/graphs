#include "gameenemy.h"

int GameEnemy::makeTurn(BoardCell* board) {
    int idx = aiAlgorithm.getBestMove(board);
    return idx;
}
