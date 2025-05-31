#include "BlockManager.hpp"
#include "constants/Constants.hpp"
#include "utils/RandomGenerator.hpp"

void BlockManager::generate() {
    int minoType = RandomGenerator::get(5000, 5006); // I, O, Z, S, J, L, T
    block.setX(BOARD_WIDTH / 2 - 3);
    block.setY(-1);
    block.setRotationCount(0);
    block.setLanded(false);
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

    block.setShape(shape);
    block.setMinoType(minoType);
}
void BlockManager::backup() {
    backupBlock = block;
}
void BlockManager::restore() {
    block = backupBlock;
}
void BlockManager::rotate() {
    block.rotate();
}
void BlockManager::up() {
    block.up();
}
void BlockManager::down() {
    block.down();
}
void BlockManager::left() {
    block.left();
}
void BlockManager::right() {
    block.right();
}
void BlockManager::land() {
    block.setLanded(true);
}
const Block& BlockManager::get() const {
    return block;
}
