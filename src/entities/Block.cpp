#include "Block.hpp"

Block::Block() {}

Block::Block(int minoType) {
    x = BOARD_WIDTH / 2 - 3;
    y = -1;
    rotationCount = 0;
    landed = false;
    const int (*shape)[4][4] = nullptr;

    switch (minoType) {
    case MINO_I:
        shape = blockI;
        break;
    case MINO_O:
        shape = blockO;
        break;
    case MINO_Z:
        shape = blockZ;
        break;
    case MINO_S:
        shape = blockS;
        break;
    case MINO_J:
        shape = blockJ;
        break;
    case MINO_L:
        shape = blockL;
        break;
    case MINO_T:
        shape = blockT;
        break;
    }

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 4; k++) {
                this->shape[i][j][k] = shape[i][j][k];
            }
        }
    }
    this->minoType = minoType;
}

int Block::getShape(int rotationCount, int y, int x) {
    return shape[rotationCount][y][x];
}

int Block::getX() { return x; }

int Block::getY() { return y; }

int Block::getRotationCount() { return rotationCount; }

bool Block::hasLanded() { return landed; }

int Block::getMinoType() { return minoType; }

void Block::setLanded(bool landed) { this->landed = landed; }

void Block::down() { // 블럭 한 칸 아래 이동
    y++;
}

void Block::left() { // 블럭 한 칸 왼쪽 이동
    x--;
}

void Block::right() { // 블럭 한 칸 오른쪽 이동
    x++;
}

void Block::rotate() { // 블럭 회전
    rotationCount = (rotationCount + 1) % 4;
}

void Block::setX(int x) { this->x = x; }

void Block::setY(int y) { this->y = y; }

void Block::setRotationCount(int r) { this->rotationCount = r; }

void Block::setShape(int r, int y, int x, int value) {
    this->shape[r][y][x] = value;
}

void Block::up() { // hard drop 처리용 블럭 한 칸 위로 이동
    y--;
}
