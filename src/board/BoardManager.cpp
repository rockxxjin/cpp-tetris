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

/*쌓은 블록이 게임 종료 선에 닿았는지 체크*/
bool BoardManager::hasReachedEnd() {
    for (int boardX = 1; boardX < BOARD_WIDTH - 1; boardX++) {
        if (isMino(END_Y, boardX)) {
            return true;
        }
    }
    return false;
}

/*일직선 삭제*/
int BoardManager::deleteLinear() {
    int cnt = 0;
    for (int boardY = END_Y + 1; boardY < BOARD_HEIGHT - 1; boardY++) {
        bool isLinear = true;
        for (int boardX = 1; boardX < BOARD_WIDTH - 1; boardX++) {
            if (!isMino(boardY, boardX)) {
                isLinear = false;
                break;
            }
        }
        if (isLinear) {
            cnt++;
            for (int shiftY = boardY; shiftY > END_Y + 1; shiftY--) {
                for (int boardX = 1; boardX < BOARD_WIDTH - 1; boardX++) {
                    if (board[shiftY - 1][boardX] != FALLING) {
                        board[shiftY][boardX] = board[shiftY - 1][boardX];
                    }
                }
            }
        }
    }
    return cnt;
}

void BoardManager::clearCellsOfType(int cellType) {
    for (int boardY = 0; boardY < BOARD_HEIGHT; boardY++) {
        for (int boardX = 0; boardX < BOARD_WIDTH; boardX++) {
            if (board[boardY][boardX] == cellType) {
                setCell(boardY, boardX, EMPTY);
            }
        }
    }
}