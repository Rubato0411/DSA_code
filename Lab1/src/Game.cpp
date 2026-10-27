#include "../include/Game.h"

Game::Game() = default;

void Game::initGame() {
    gameBoard.reset();
    score = 0;
    moveCount = 0;
    historyGameBoards = std::stack<GameBoard>();
    historyScores = std::stack<int>();
    startTime = std::chrono::steady_clock::now();
    historyGameBoards.push(gameBoard);  // The initial state is the base of the history.
    historyScores.push(score);
}

void Game::updateGame(Direction direction) {
    Board previousBoard = gameBoard.getBoard();
    int moveScore = gameBoard.move(direction);
    if (gameBoard.getBoard() == previousBoard) {
        return;
    }
    score += moveScore;
    ++moveCount;
    historyGameBoards.push(gameBoard);
    historyScores.push(score);
}

void Game::undoLastMove() {
    if (historyGameBoards.size() > 1) {
        historyGameBoards.pop();
        gameBoard = historyGameBoards.top();
        historyScores.pop();
        score = historyScores.top();
        --moveCount;
    }
    // With only the initial state in history, undo is intentionally a no-op.
}

bool Game::hasWon() const {
    return gameBoard.hasWinningTile();
}

bool Game::hasLost() const {
    return gameBoard.isGameOver();
}

double Game::getElapsedTime() const {
    auto endTime = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsedSeconds = endTime - startTime;
    return elapsedSeconds.count();
}

int Game::getScore() const {
    return score;
}

int Game::getMoveCount() const {
    return moveCount;
}

const GameBoard& Game::getGameBoard() const {
    return gameBoard;
}
