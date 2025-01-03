#include "alphabeta.h"
#include <algorithm>
#include <climits>

AlphaBeta::AlphaBeta(AlphaBeta const &ab) {
    DEPTH = ab.DEPTH;
    ROWS = ab.ROWS;
    COLUMNS = ab.COLUMNS;
}

AlphaBeta::AlphaBeta(const int depth, const int rows, const int columns) {
    DEPTH = depth;
    ROWS = rows;
    COLUMNS = columns;
}

std::vector<int> AlphaBeta::getPossibleMoves() {
    std::vector<int> resultIndexes;
    for (int row = ROWS - 1; row >= 0; --row) {
        for (int col = COLUMNS - 1; col >= 0; --col) {
            int idx = row * COLUMNS + col;
            int bottomIdx = (row + 1) * COLUMNS + col;
            int maxIdx = ROWS * COLUMNS - 1;
            if (board[idx] == BoardCell::EMPTY) {
                if ((bottomIdx < maxIdx && board[bottomIdx] != BoardCell::EMPTY) || bottomIdx > maxIdx) {
                    resultIndexes.push_back(idx);
                }
            }
            if (resultIndexes.size() > 0 && resultIndexes.size() % COLUMNS == 0) {
                return resultIndexes;
            }
        }
    }
    return resultIndexes;
}

int AlphaBeta::evalSequence(int count) {
    switch (count) {
    case 1:
        return 10;
    case 2:
        return 100;
    case 3:
        return 1000;
    case 4:
        return 5000;
    default:
        return 0;
    }
}

int AlphaBeta::getHorizontalScores() {
    // Проверяем последовательность из 4-х ячеек по горизонтали
    int scores = 0;
    std::vector<int> possibleMoves = getPossibleMoves();
    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col <= COLUMNS - 4; col++) {
            short enemyCount = 0;
            short playerCount = 0;
            bool isCorrectLine = true;
            for (int i = 0; i < 4; i++) {
                int idx = row * COLUMNS + col + i;
                bool isPossibleIdx = std::find(possibleMoves.begin(), possibleMoves.end(), idx) != possibleMoves.end();
                if (board[idx] == BoardCell::ENEMY) {
                    enemyCount++;
                }
                if (board[idx] == BoardCell::PLAYER) {
                    playerCount++;
                }
                if (board[idx] == BoardCell::EMPTY && isPossibleIdx) {
                    isCorrectLine = false;
                }
            }
            // Оцениваем последовательность
            if (enemyCount > 0 && playerCount > 0) {
                // Если линия содержит фишки обоих игроков - она незначима
                continue;
            } else if (playerCount > 0) {
                // Если линия принадлежит игроку
                double newScore = evalSequence(playerCount);
                // if (!isCorrectLine) newScore /= (4.0 - playerCount);
                scores -= newScore;
            } else if (enemyCount > 0) {
                // Если линия принадлежит противнику (компьютеру)
                double newScore = evalSequence(enemyCount);
                // if (!isCorrectLine) newScore /= (4.0 - enemyCount);
                scores += newScore;
            }
        }
    }
    return scores;
}

int AlphaBeta::getVerticalScores() {
    // Проверяем последовательность из 4-х ячеек по горизонтали
    int scores = 0;
    std::vector<int> possibleMoves = getPossibleMoves();
    for (int row = 0; row <= ROWS - 4; row++) {
        for (int col = 0; col < COLUMNS; col++) {
            short enemyCount = 0;
            short playerCount = 0;
            bool isCorrectLine = true;
            for (int i = 0; i < 4; i++) {
                int idx = (row + i) * COLUMNS + col;
                bool isPossibleIdx = std::find(possibleMoves.begin(), possibleMoves.end(), idx) != possibleMoves.end();
                if (board[idx] == BoardCell::ENEMY) {
                    enemyCount++;
                }
                if (board[idx] == BoardCell::PLAYER) {
                    playerCount++;
                }
                if (board[idx] == BoardCell::EMPTY && isPossibleIdx) {
                    isCorrectLine = false;
                }
            }
            // Оцениваем последовательность
            if (enemyCount > 0 && playerCount > 0) {
                // Если линия содержит фишки обоих игроков — она незначима
                continue;
            } else if (playerCount > 0) {
                // Если линия принадлежит игроку
                double newScore = evalSequence(playerCount);
                // if (!isCorrectLine) newScore /= (4.0 - playerCount);
                scores -= newScore;
            } else if (enemyCount > 0) {
                // Если линия принадлежит противнику (компьютеру)
                double newScore = evalSequence(enemyCount);
                // if (!isCorrectLine) newScore /= (4.0 - enemyCount);
                scores += newScore;
            }
        }
    }
    return scores;
}

int AlphaBeta::getDiagonalScores() {
    int scores = 0;
    std::vector<int> possibleMoves = getPossibleMoves();
    // Прямая диагональ
    for (int row = 0; row <= ROWS - 4; row++) {
        for (int col = 0; col <= COLUMNS - 4; col++) {
            short enemyCount = 0, playerCount = 0;
            for (int i = 3; i >= 0; i--) {
                int idx = (row + i) * COLUMNS + (col + 3 - i);
                if (board[idx] == BoardCell::ENEMY) enemyCount++;
                if (board[idx] == BoardCell::PLAYER) playerCount++;
            }
            if (enemyCount > 0 && playerCount > 0) continue;
            else if (enemyCount > 0) scores += evalSequence(enemyCount);
            else if (playerCount > 0) scores -= evalSequence(playerCount);
        }
    }

    // Обратная диагональ
    for (int row = 0; row <= ROWS - 4; row++) {
        for (int col = 0; col <= COLUMNS - 4; col++) {
            short enemyCount = 0, playerCount = 0;
            for (int i = 0; i < 4; i++) {
                int idx = (row + i) * COLUMNS + (col + i);
                if (board[idx] == BoardCell::ENEMY) enemyCount++;
                if (board[idx] == BoardCell::PLAYER) playerCount++;
            }
            if (enemyCount > 0 && playerCount > 0) continue;
            else if (enemyCount > 0) scores += evalSequence(enemyCount);
            else if (playerCount > 0) scores -= evalSequence(playerCount);
        }
    }
    return scores;
}

bool AlphaBeta::checkVictory(BoardCell value) {
    // Проверяем горизонтальные линии
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

    // Проверяем вертикальные линии
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
                return true;
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

int AlphaBeta::getScores() {
    int a = getVerticalScores();
    int b = getHorizontalScores();
    int c = getDiagonalScores();
    return a + b + c;
}

void AlphaBeta::makeMove(int idx, BoardCell value) {
    if (idx < ROWS * COLUMNS) {
        board[idx] = value;
    }
}

std::vector<int> AlphaBeta::getMovesBranch(int currentDepth, bool selectWinMove) {
    std::vector<int> result;
    // Получаем все возможные ходы
    std::vector<int> possibleMovesIdx = getPossibleMoves();

    int bestScore = selectWinMove ? INT_MIN : INT_MAX; // Максимизатор/минимизатор
    int alpha = INT_MIN; // Альфа - лучший результат для максимизатора
    int beta = INT_MAX;  // Бета - лучший результат для минимизатора
    int bestMove = -1;
    bool gameOver = checkVictory(selectWinMove ? BoardCell::ENEMY : BoardCell::PLAYER);

    if (currentDepth >= DEPTH || possibleMovesIdx.empty() || gameOver) {
        int depthScores = getScores();
        // Увеличиваем очки в зависимости от кол-ва ходов до победы
        if (gameOver) {
            depthScores *= (DEPTH - currentDepth);
        }
        result.push_back(depthScores); // Возвращаем оценку доски
        return result;
    }

    // Проходим по всем возможным ходам
    for (auto moveIdx : possibleMovesIdx) {
        // Совершаем ход
        makeMove(moveIdx, selectWinMove ? BoardCell::ENEMY : BoardCell::PLAYER);
        // Рекурсивный вызов для следующего уровня
        std::vector<int> branchResult = getMovesBranch(currentDepth + 1, !selectWinMove);
        int score = branchResult[0];
        // Откатываем ход
        makeMove(moveIdx, BoardCell::EMPTY);

        // Проверяем, нужно ли обновить лучший результат
        if (selectWinMove) {
            if (score > bestScore) {
                bestScore = score;
                bestMove = moveIdx;
                // bestMoveWinLength = currentDepth;
                alpha = std::max(alpha, bestScore); // Обновляем альфа
            }
        } else {
            if (score < bestScore) {
                bestScore = score;
                bestMove = moveIdx;
                beta = std::min(beta, bestScore); // Обновляем бета
            }
        }

        // Если альфа >= бета, прекращаем поиск
        if (alpha >= beta) {
            break;
        }
    }
    if (currentDepth == 0) {
        result.push_back(bestMove);
    }

    // Добавляем лучшую оценку в результат
    result.insert(result.begin(), bestScore);
    return result;
}

int AlphaBeta::getBestMove(BoardCell* board) {
    this->board = new BoardCell[ROWS * COLUMNS];
    for (int i = 0; i < ROWS * COLUMNS; i++) {
        this->board[i] = board[i];
    }
    // Получаем лучший ход через getMovesBranch
    std::vector<int> result = getMovesBranch(0, true);
    delete[] this->board;
    return result[1]; // Возвращаем индекс лучшего хода
}

AlphaBeta::~AlphaBeta() {
    delete[] board;
}
