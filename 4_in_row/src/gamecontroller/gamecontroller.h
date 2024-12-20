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
    BoardCell* board = new BoardCell[ROWS * COLUMNS]; // игровая доска
    bool gameOver = false; // статус игры
    bool isComputerTurn = false; // ход компьютера
    bool isPlayerFirst = true; // игрок ходит первым
    GameEnemy* enemy; // противник

    bool checkHorizontalWinning(BoardCell value); // проверка победы по горизонтали
    bool checkVerticalWinning(BoardCell value); // проверка победы по вертикали
    bool checkDiagonalWinning(BoardCell value); // проверка победы по диагонали
    bool checkWinning(BoardCell value); // проверка победы
public:
    GameController(GameEnemy* enemy);
    ~GameController();
    Q_INVOKABLE void makeMove(int index); // функция хода
    Q_INVOKABLE void restartGame(); // перезапуск игры
    Q_INVOKABLE void setPlayerFirst(bool checked); // сеттер кто ходит первым
    bool getGameState() const; // геттер статуса игры
signals:
    void cellUpdated(int index, int player); // обновить ячейку
    void updateGameStatus(bool gameOver, bool isPlayerWin); // обновить статус игры
};

#endif // GAMECONTROLLER_H
