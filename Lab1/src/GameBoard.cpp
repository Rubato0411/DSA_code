#include "../include/GameBoard.h"
#include <algorithm>
#include <random>
#include <chrono>
#include <utility>

GameBoard::GameBoard() {
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    generator = std::mt19937(seed);
    reset();
}

void GameBoard::reset() {
    // Initialize the board to be 4x4 with all values set to 0
    board = Board(4, std::vector<int>(4, 0));
    std::uniform_int_distribution<int> dist(0, 3);  // [0, 3] uniform distribution
    std::uniform_int_distribution<int> value_dist(0, 1);

    // Add two initial tiles
    for (int i = 0; i < 2; ++i) {
        int row = dist(generator);
        int col = dist(generator);
        while (board[row][col] != 0) { // Ensure we don't place a tile on an occupied cell
            row = dist(generator);
            col = dist(generator);
        }
        board[row][col] = (value_dist(generator) + 1) * 2; // Place either a 2 or a 4
    }
}

int GameBoard::move(Direction direction) {
    Board previousBoard = board;
    slide(direction);
    int moveScore = merge(direction);
    slide(direction);

    if (board != previousBoard) {
        std::vector<std::pair<int, int>> emptyCells;
        for (int row = 0; row < 4; ++row) {
            for (int col = 0; col < 4; ++col) {
                if (board[row][col] == 0) {
                    emptyCells.emplace_back(row, col);
                }
            }
        }
        if (!emptyCells.empty()) {
            std::uniform_int_distribution<int> cellDist(
                0, static_cast<int>(emptyCells.size()) - 1
            );
            std::uniform_int_distribution<int> valueDist(0, 1);
            auto [row, col] = emptyCells[cellDist(generator)];
            board[row][col] = (valueDist(generator) + 1) * 2;
        }
    }
    return moveScore;
}

void GameBoard::slide(Direction direction) {
    switch (direction) {
        case Direction::UP:
            for (int col = 0; col < 4; ++col) {
                int target = 3;
                for (int row = 3; row >= 0; --row) {
                    if (board[row][col] != 0) {
                        std::swap(board[target][col], board[row][col]);
                        if (target != row) board[row][col] = 0;
                        --target;
                    }
                }
            }
            break;
        case Direction::DOWN:
            for (int col = 0; col < 4; ++col) {
                int target = 0;
                for (int row = 0; row < 4; ++row) {
                    if (board[row][col] != 0) {
                        std::swap(board[target][col], board[row][col]);
                        if (target != row) board[row][col] = 0;
                        ++target;
                    }
                }
            }
            break;
        case Direction::LEFT:
            for (int row = 0; row < 4; ++row) {
                int target = 0;
                for (int col = 0; col < 4; ++col) {
                    if (board[row][col] != 0) {
                        std::swap(board[row][target], board[row][col]);
                        if (target != col) board[row][col] = 0;
                        ++target;
                    }
                }
            }
            break;
        case Direction::RIGHT:
            for (int row = 0; row < 4; ++row) {
                int target = 3;
                for (int col = 3; col >= 0; --col) {
                    if (board[row][col] != 0) {
                        std::swap(board[row][target], board[row][col]);
                        if (target != col) board[row][col] = 0;
                        --target;
                    }
                }
            }
            break;
    }
}

int GameBoard::merge(Direction direction) {
    int moveScore = 0;
    switch (direction) {
        case Direction::UP:
            for (int col = 0; col < 4; ++col) {
                for (int row = 3; row > 0; --row) {
                    if (board[row][col] != 0 && board[row][col] == board[row - 1][col]) {
                        board[row][col] *= 2;
                        moveScore += board[row][col];
                        board[row - 1][col] = 0;
                    }
                }
            }
            break;
        case Direction::DOWN:
            for (int col = 0; col < 4; ++col) {
                for (int row = 0; row < 3; ++row) {
                    if (board[row][col] != 0 && board[row][col] == board[row + 1][col]) {
                        board[row][col] *= 2;
                        moveScore += board[row][col];
                        board[row + 1][col] = 0;
                    }
                }
            }
            break;
        case Direction::LEFT:
            for (int row = 0; row < 4; ++row) {
                for (int col = 0; col < 3; ++col) {
                    if (board[row][col] != 0 && board[row][col] == board[row][col + 1]) {
                        board[row][col] *= 2;
                        moveScore += board[row][col];
                        board[row][col + 1] = 0;
                    }
                }
            }
            break;
        case Direction::RIGHT:
            for (int row = 0; row < 4; ++row) {
                for (int col = 3; col > 0; --col) {
                    if (board[row][col] != 0 && board[row][col] == board[row][col - 1]) {
                        board[row][col] *= 2;
                        moveScore += board[row][col];
                        board[row][col - 1] = 0;
                    }
                }
            }
            break;
    }

    return moveScore;
}

bool GameBoard::isGameOver() const {
    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 4; ++col) {
            if (board[row][col] == 0) return false;
            if (row < 3 && board[row][col] == board[row + 1][col]) return false;
            if (col < 3 && board[row][col] == board[row][col + 1]) return false;
        }
    }
    return true;
}

bool GameBoard::hasWinningTile() const {
    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 4; ++col) {
            if (board[row][col] == 2048) return true;
        }
    }
    return false;
}


const Board &GameBoard::getBoard() const {
    return board;
}
