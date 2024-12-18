#include "gamecontroller.h"
#include <climits>

GameController::GameController(GameEnemy* enemy){
    this->enemy = enemy;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            int idx = i * COLUMNS + j;
            board[idx] = BoardCell::EMPTY;
        }
    }
}

void GameController::makeMove(int index) {
    // Если игра окончена или сейчас ходит компьютер, то выходим
    if (gameOver || isComputerTurn) {
        return;
    }
    int selectedRow = index / COLUMNS;
    for (int row = ROWS - 1; row >= selectedRow; row--) {
        int idx = row * COLUMNS + index % COLUMNS;
        if (board[idx] == BoardCell::EMPTY) {
            board[idx] = BoardCell::PLAYER;
            emit cellUpdated(idx, 1);
            checkWinning(BoardCell::PLAYER);

            if (checkWinning(BoardCell::PLAYER)) {
                emit updateGameStatus(gameOver, true);
                return;
            }

            isComputerTurn = true;
            // Асинхронный ход компьютера (работа в отдельном потоке, чтобы обновить ход юзера сразу)
            QtConcurrent::run([this]() {
                int bestIdx = enemy->makeTurn(board);

                // Переходим обратно в главный поток для обновления интерфейса
                QMetaObject::invokeMethod(this, [this, bestIdx]() {
                    board[bestIdx] = BoardCell::ENEMY;
                    emit cellUpdated(bestIdx, 2);
                    isComputerTurn = false;
                    if (checkWinning(BoardCell::ENEMY)) {
                        emit updateGameStatus(gameOver, false);
                    }
                }, Qt::QueuedConnection);
            });

            return;
        }
    }
}

void GameController::setPlayerFirst(bool checked) {
    isPlayerFirst = checked;
}

bool GameController::checkHorizontalWinning(BoardCell value) {
    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col <= COLUMNS - 4; col++) {
            bool win = true;
            for (int i = 0; i < 4; i++) {
                if (board[row * COLUMNS + col + i] != value) {
                    win = false;
                    break;
                }
            }
            if (win) {
                return true;
            }
        }
    }
    return false;
}

bool GameController::checkVerticalWinning(BoardCell value) {
    for (int row = 0; row <= ROWS - 4; row++) {
        for (int col = 0; col < COLUMNS; col++) {
            bool win = true;
            for (int i = 0; i < 4; i++) {
                if (board[(row + i) * COLUMNS + col] != value) {
                    win = false;
                    break;
                }
            }
            if (win) {
                return true;
            }
        }
    }
    return false;
}

bool GameController::checkDiagonalWinning(BoardCell value) {
    // Проверяем диагонали прямые
    for (int row = 0; row <= ROWS - 4; row++) {
        for (int col = 0; col <= COLUMNS - 4; col++) {
            bool win = true;
            for (int i = 3; i >= 0; i--) {
                int idx = (row + i) * COLUMNS + (col + 3 - i);
                if (board[idx] != value) {
                    win = false;
                    break;
                }
            }
            if (win) {
                gameOver = true;
                return gameOver;
            }
        }
    }

    // Проверяем диагонали обратные
    for (int row = 0; row <= ROWS - 4; row++) {
        for (int col = 0; col <= COLUMNS - 4; col++) {
            bool win = true;
            for (int i = 0; i < 4; i++) {
                int idx = (row + i) * COLUMNS + (col + i);
                if (board[idx] != value) {
                    win = false;
                    break;
                }
            }
            if (win) {
                return true;
            }
        }
    }
    return false;
}

bool GameController::checkWinning(BoardCell value) {
    gameOver = checkHorizontalWinning(value) || checkVerticalWinning(value) || checkDiagonalWinning(value);
    return gameOver;
}

void GameController::restartGame() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            int idx = i * COLUMNS + j;
            board[idx] = BoardCell::EMPTY;
            emit cellUpdated(idx, 0);
        }
    }
    gameOver = false;
    isComputerTurn = false;
    emit updateGameStatus(gameOver, false);

    // ход компьютера
    if (!isPlayerFirst) {
        int idx = enemy->makeTurn(board);
        board[idx] = BoardCell::ENEMY;
        emit cellUpdated(idx, 2);
    }
}

bool GameController::getGameState() const {
    return gameOver;
}

GameController::~GameController() {
    delete[] board;
}
