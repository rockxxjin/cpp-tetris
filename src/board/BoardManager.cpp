#include "BoardManager.hpp"
#include "constants/Constants.hpp"
BoardManager::BoardManager() {
    for (int boardY = 0; boardY < BOARD_HEIGHT; boardY++) {
        std::vector<int> temp;
        for (int boardX = 0; boardX < BOARD_WIDTH; boardX++) {
            temp.push_back(0);
        }
        board.push_back(temp);
    }
    for (int boardX = 0; boardX < BOARD_WIDTH; boardX++) {
        board[BOARD_HEIGHT - 1][boardX] = WALL;
    }
    for (int boardY = 0; boardY < BOARD_HEIGHT - 1; boardY++) {
        board[boardY][0] = 1;
        board[boardY][BOARD_WIDTH - 1] = WALL;
    }
    for (int boardX = 1; boardX < BOARD_WIDTH - 1; boardX++) {
        board[BOARD_HEIGHT - 1][boardX] = WALL;
    }
}

void BoardManager::backup() {
    backupBoard = board;
}
void BoardManager::restore() {
    board = backupBoard;
}

void BoardManager::setCell(const int boardY, const int boardX, const int value) {
    board[boardY][boardX] = value;
}

bool BoardManager::isInvalidPosition(const int boardY, const int boardX) const {
    return (boardY < 0 || boardX < 0 || boardY >= BOARD_HEIGHT || boardX >= BOARD_WIDTH);
}
bool BoardManager::isMino(const int boardY, const int boardX) const {
    return (5000 <= board[boardY][boardX] and board[boardY][boardX] <= 5006);
}
bool BoardManager::isWall(const int boardY, const int boardX) const {
    return board[boardY][boardX] == WALL;
}
const std::vector<std::vector<int>>& BoardManager::get() const {
    return this->board;
}