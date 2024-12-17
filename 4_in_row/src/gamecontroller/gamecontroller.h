#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "../gameenemy/gameenemy.h"
#include "../boardcell/boardcell.h"
#include "../alphabeta/alphabeta.h"

#include <QObject>
#include <QtConcurrent>
#include <QFuture>


class GameController : public QObject
{
    Q_OBJECT
    const int ROWS = 6;
    const int COLUMNS = 7;
    const int WINNING_SUBSEQUENCE = 4;
    BoardCell* board = new BoardCell[ROWS * COLUMNS];
    bool gameOver = false;
    bool isComputerTurn = false;
    GameEnemy* enemy;

    bool checkHorizontalWinning(BoardCell value);
    bool checkVerticalWinning(BoardCell value);
    bool checkDiagonalWinning(BoardCell value);
    bool checkWinning(BoardCell value);
public:
    GameController(GameEnemy* enemy);
    ~GameController();
    Q_INVOKABLE void makeMove(int index);
    Q_INVOKABLE void restartGame();
    bool getGameState() const;
signals:
    void cellUpdated(int index, int player);
    void updateGameStatus(bool gameOver, bool isPlayerWin);
};

#endif // GAMECONTROLLER_H
