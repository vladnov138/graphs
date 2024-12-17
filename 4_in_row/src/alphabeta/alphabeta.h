#ifndef ALPHABETA_H
#define ALPHABETA_H

#include <vector>
#include "../boardcell/boardcell.h"

class AlphaBeta
{
    int DEPTH;
    int ROWS;
    int COLUMNS;
    int bestMoveWinLength = 0;
    BoardCell* board;

    std::vector<int> getPossibleMoves();
    std::vector<int> getMovesBranch(int currentDepth, bool selectWinMove);
    int getVerticalScores();
    int getHorizontalScores();
    int getDiagonalScores();
    int getScores();
    int evalSequence(int count);
    void makeMove(int idx, BoardCell value);
    bool isWinningMove(int idx, BoardCell player);
    bool checkVictory(BoardCell value);
public:
    AlphaBeta(AlphaBeta const &ab);
    AlphaBeta(const int depth, const int rows=6, const int columns=7);
    int getBestMove(BoardCell* boardcell);
    // ~AlphaBeta();

    std::vector<BoardCell> vector;
    std::vector<std::vector<BoardCell>> boardsState;
    std::vector<int> boardScores;
};

#endif // ALPHABETA_H
