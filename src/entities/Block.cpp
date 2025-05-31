#include "Block.hpp"

int Block::getShape(int rotationCount, int y, int x) const {
    return shape[rotationCount][y][x];
}

int Block::getX() const {
    return x;
}

int Block::getY() const {
    return y;
}

int Block::getRotationCount() const {
    return rotationCount;
}

bool Block::hasLanded() const {
    return landed;
}

int Block::getMinoType() const {
    return minoType;
}

void Block::setLanded(bool landed) {
    this->landed = landed;
}

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

void Block::setX(int x) {
    this->x = x;
}

void Block::setY(int y) {
    this->y = y;
}

void Block::setRotationCount(int r) {
    this->rotationCount = r;
}

void Block::setShape(const int shape[4][4][4]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 4; k++) {
                this->shape[i][j][k] = shape[i][j][k];
            }
        }
    }
}

void Block::up() { // hard drop 처리용 블럭 한 칸 위로 이동
    y--;
}

void Block::setMinoType(const int minoType) {
    this->minoType = minoType;
}
