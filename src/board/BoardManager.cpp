#include "BoardManager.hpp"
#include "utils/RandomGenerator.hpp"
using namespace std;

BoardManager::BoardManager() {
    for (int boardY = 0; boardY < BOARD_HEIGHT; boardY++) {
        vector<int> temp;
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

bool BoardManager::isInvalidPosition(const int boardY, const int boardX) {
    return (boardY < 0 || boardX < 0 || boardY >= BOARD_HEIGHT || boardX >= BOARD_WIDTH);
}
bool BoardManager::isMino(const int boardY, const int boardX) {
    return (5000 <= board[boardY][boardX] and board[boardY][boardX] <= 5006);
}
bool BoardManager::isWall(const int boardY, const int boardX) { return board[boardY][boardX] == WALL; }
void BoardManager::restore() {
    block = backupBlock;
    board = backupBoard;
}
void BoardManager::restoreBlock() { block = backupBlock; }
void BoardManager::backup() {
    backupBlock = block;
    backupBoard = board;
}

/*블럭 생성*/
bool BoardManager::createBlock(bool isFirstBlock) {
    if (!isFirstBlock && !block.hasLanded()) {
        return true;
    }

    int minoType = RandomGenerator::get(5000, 5006); // I, O, Z, S, J, L, T
    block = Block(minoType);

    for (int blockY = 0; blockY < 4; blockY++) {
        for (int blockX = 0; blockX < 4; blockX++) {
            int boardY = blockY + block.getY();
            int boardX = blockX + block.getX();

            if (isInvalidPosition(boardY, boardX)) {
                continue;
            }
            if (isMino(boardY, boardX)) {
                return false;
            }
            board[boardY][boardX] = block.getShape(block.getRotationCount(), blockY, blockX);
        }
    }
    return true;
}

void BoardManager::clearCellsOfType(int cellType) {
    for (int boardY = 0; boardY < BOARD_HEIGHT; boardY++) {
        for (int boardX = 0; boardX < BOARD_WIDTH; boardX++) {
            if (board[boardY][boardX] == cellType) {
                board[boardY][boardX] = EMPTY;
            }
        }
    }
}

bool BoardManager::canMoveOrRotateBlock(const int key) {
    if (key == sf::Keyboard::Up) {
        block.rotate();
    } else if (key == sf::Keyboard::Down || key == AUTO_DROP) {
        block.down();
    } else if (key == sf::Keyboard::Left) {
        block.left();
    } else if (key == sf::Keyboard::Right) {
        block.right();
    }

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            int x = j + block.getX();
            int y = i + block.getY();

            if (isInvalidPosition(y, x)) {
                continue;
            }

            int blockValue = block.getShape(block.getRotationCount(), i, j);

            if (blockValue != FALLING) {
                continue;
            }

            if (board[y][x] != EMPTY && board[y][x] != GHOST_PIECE) {
                return false;
            }
            board[y][x] = blockValue; // 블럭을 이동시킴
        }
    }
    return true;
}

void BoardManager::operateBlock(const int key) {
    if (key == sf::Keyboard::Up || key == sf::Keyboard::Down || key == sf::Keyboard::Left || key == sf::Keyboard::Right) {
        backup();
        clearCellsOfType(FALLING);
        if (!canMoveOrRotateBlock(key)) {
            restore();
        }
        return;
    }

    if (key == AUTO_DROP) {
        backup();
        clearCellsOfType(FALLING);
        if (!canMoveOrRotateBlock(key)) {
            restore();
            landBlock();
        }
        return;
    }

    if (key == sf::Keyboard::Space) {
        hardDropBlock();
        return;
    }

    if (key == GHOST_PIECE_DROP) {
        hardDropGhostPiece();
    }
}

void BoardManager::landBlock() {
    for (int blockY = 0; blockY < 4; blockY++) {
        for (int blockX = 0; blockX < 4; blockX++) {
            int boardY = blockY + block.getY();
            int boardX = blockX + block.getX();

            if (isInvalidPosition(boardY, boardX)) {
                continue;
            }

            int blockValue = block.getShape(block.getRotationCount(), blockY, blockX);
            if (blockValue != FALLING) {
                continue;
            }
            board[boardY][boardX] = block.getMinoType();
        }
    }
    block.setLanded(true);
}

void BoardManager::landGhostPiece() {
    for (int blockY = 0; blockY < 4; blockY++) {
        for (int blockX = 0; blockX < 4; blockX++) {
            int boardY = blockY + block.getY();
            int boardX = blockX + block.getX();

            if (isInvalidPosition(boardY, boardX)) {
                continue;
            }

            int blockValue = block.getShape(block.getRotationCount(), blockY, blockX);
            if (blockValue != FALLING) {
                continue;
            }
            if (board[boardY][boardX] == EMPTY) {
                board[boardY][boardX] = GHOST_PIECE;
            }
        }
    }
}

void BoardManager::dropBlockUntilCollision() {
    while (true) {
        for (int blockY = 0; blockY < 4; blockY++) {
            for (int blockX = 0; blockX < 4; blockX++) {
                int boardY = blockY + block.getY();
                int boardX = blockX + block.getX();

                if (isInvalidPosition(boardY, boardX)) {
                    continue;
                }

                int blockValue = block.getShape(block.getRotationCount(), blockY, blockX);
                if (blockValue != FALLING) {
                    continue;
                }
                if (isMino(boardY, boardX) || isWall(boardY, boardX)) {
                    return;
                }
            }
        }
        block.down();
    }
}

void BoardManager::hardDropBlock() {
    clearCellsOfType(FALLING);
    dropBlockUntilCollision();
    block.up();
    landBlock();
}

void BoardManager::hardDropGhostPiece() {
    backup();
    clearCellsOfType(GHOST_PIECE);
    dropBlockUntilCollision();
    block.up();
    landGhostPiece();
    restoreBlock();
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
/*쌓은 블록이 게임 종료 선에 닿았는지 체크*/
bool BoardManager::hasReachedEnd() {
    for (int boardX = 1; boardX < BOARD_WIDTH - 1; boardX++) {
        if (isMino(END_Y, boardX)) {
            return true;
        }
    }
    return false;
}

int BoardManager::getCellValue(const int boardY, const int boardX) {
    return board[boardY][boardX];
}

int BoardManager::getFallingTetrominoType() {
    return block.getMinoType();
}
