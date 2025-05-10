#include "GameTable.hpp"
#include "utils/RandomGenerator.hpp"
using namespace std;

GameTable::GameTable() {
    blockTextureMap[WALL].loadFromFile("assets/images/block_wall.png");
    blockTextureMap[MINO_I].loadFromFile("assets/images/block_I.png");
    blockTextureMap[MINO_O].loadFromFile("assets/images/block_O.png");
    blockTextureMap[MINO_Z].loadFromFile("assets/images/block_Z.png");
    blockTextureMap[MINO_S].loadFromFile("assets/images/block_S.png");
    blockTextureMap[MINO_J].loadFromFile("assets/images/block_J.png");
    blockTextureMap[MINO_L].loadFromFile("assets/images/block_L.png");
    blockTextureMap[MINO_T].loadFromFile("assets/images/block_T.png");

    for (int tableY = 0; tableY < TABLE_HEIGHT; tableY++) {
        vector<int> temp;
        for (int tableX = 0; tableX < TABLE_WIDTH; tableX++) {
            temp.push_back(0);
        }
        table.push_back(temp);
    }
    for (int tableX = 0; tableX < TABLE_WIDTH; tableX++) {
        table[TABLE_HEIGHT - 1][tableX] = WALL;
    }
    for (int tableY = 0; tableY < TABLE_HEIGHT - 1; tableY++) {
        table[tableY][0] = 1;
        table[tableY][TABLE_WIDTH - 1] = WALL;
    }
    for (int tableX = 1; tableX < TABLE_WIDTH - 1; tableX++) {
        table[TABLE_HEIGHT - 1][tableX] = WALL;
    }
}

bool GameTable::isInvalidPosition(const int tableY, const int tableX) {
    return (tableY < 0 || tableX < 0 || tableY >= TABLE_HEIGHT || tableX >= TABLE_WIDTH);
}
bool GameTable::isMino(const int y, const int x) {
    return (5000 <= table[y][x] and table[y][x] <= 5006);
}
bool GameTable::isWall(const int y, const int x) { return table[y][x] == WALL; }
void GameTable::restore() {
    block = backupBlock;
    table = backupTable;
}
void GameTable::restoreBlock() { block = backupBlock; }
void GameTable::backup() {
    backupBlock = block;
    backupTable = table;
}

/*게임판 그리는 함수*/
void GameTable::drawGameTable(sf::RenderWindow& window) {
    sf::Sprite sprite;

    for (int y = 0; y < TABLE_HEIGHT; y++) {
        for (int x = 0; x < TABLE_WIDTH; x++) {
            sprite.setColor(sf::Color::White);
            if (table[y][x] == WALL) {
                sprite.setTexture(blockTextureMap[WALL]);
                sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
                sprite.setPosition(x * 32, y * 32);
                window.draw(sprite);
            } else if (table[y][x] == FALLING) {
                sprite.setTexture(blockTextureMap[block.getMinoType()]);
                sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
                sprite.setPosition(x * 32, y * 32);
                window.draw(sprite);
            } else if (isMino(y, x)) {
                sprite.setTexture(blockTextureMap[table[y][x]]);
                sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
                sprite.setPosition(x * 32, y * 32);
                window.draw(sprite);
            } else if (table[y][x] == GHOST_PIECE) {
                sprite.setTexture(blockTextureMap[block.getMinoType()]);
                sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
                sprite.setColor(sf::Color(200, 200, 200, 150)); // 투명 효과
                sprite.setPosition(x * 32, y * 32);
                window.draw(sprite);
            }
        }
    }
}
/*블럭 생성*/
bool GameTable::createBlock(bool isFirstBlock) {
    if (!isFirstBlock && !block.hasLanded()) {
        return true;
    }

    int minoType = RandomGenerator::get(5000, 5006); // I, O, Z, S, J, L, T
    block = Block(minoType);

    for (int blockY = 0; blockY < 4; blockY++) {
        for (int blockX = 0; blockX < 4; blockX++) {
            int tableY = blockY + block.getY();
            int tableX = blockX + block.getX();

            if (isInvalidPosition(tableY, tableX)) {
                continue;
            }
            if (isMino(tableY, tableX)) {
                return false;
            }
            table[tableY][tableX] = block.getShape(block.getRotationCount(), blockY, blockX);
        }
    }
}

void GameTable::clearCellsOfType(int cellType) {
    for (int tableY = 0; tableY < TABLE_HEIGHT; tableY++) {
        for (int tableX = 0; tableX < TABLE_WIDTH; tableX++) {
            if (table[tableY][tableX] == cellType) {
                table[tableY][tableX] = EMPTY;
            }
        }
    }
}

bool GameTable::canMoveOrRotateBlock(const int key) {
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

            if (table[y][x] != EMPTY && table[y][x] != GHOST_PIECE) {
                return false;
            }
            table[y][x] = blockValue; // 블럭을 이동시킴
        }
    }
    return true;
}

void GameTable::operateBlock(const int key) {
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

void GameTable::landBlock() {
    for (int blockY = 0; blockY < 4; blockY++) {
        for (int blockX = 0; blockX < 4; blockX++) {
            int tableY = blockY + block.getY();
            int tableX = blockX + block.getX();

            if (isInvalidPosition(tableY, tableX)) {
                continue;
            }

            int blockValue = block.getShape(block.getRotationCount(), blockY, blockX);
            if (blockValue != FALLING) {
                continue;
            }
            table[tableY][tableX] = block.getMinoType();
        }
    }
    block.setLanded(true);
}

void GameTable::landGhostPiece() {
    for (int blockY = 0; blockY < 4; blockY++) {
        for (int blockX = 0; blockX < 4; blockX++) {
            int tableY = blockY + block.getY();
            int tableX = blockX + block.getX();

            if (isInvalidPosition(tableY, tableX)) {
                continue;
            }

            int blockValue = block.getShape(block.getRotationCount(), blockY, blockX);
            if (blockValue != FALLING) {
                continue;
            }
            if (table[tableY][tableX] == EMPTY) {
                table[tableY][tableX] = GHOST_PIECE;
            }
        }
    }
}

void GameTable::dropBlockUntilCollision() {
    while (true) {
        for (int blockY = 0; blockY < 4; blockY++) {
            for (int blockX = 0; blockX < 4; blockX++) {
                int tableY = blockY + block.getY();
                int tableX = blockX + block.getX();

                if (isInvalidPosition(tableY, tableX)) {
                    continue;
                }

                int blockValue = block.getShape(block.getRotationCount(), blockY, blockX);
                if (blockValue != FALLING) {
                    continue;
                }
                if (isMino(tableY, tableX) || isWall(tableY, tableX)) {
                    return;
                }
            }
        }
        block.down();
    }
}

void GameTable::hardDropBlock() {
    clearCellsOfType(FALLING);
    dropBlockUntilCollision();
    block.up();
    landBlock();
}

void GameTable::hardDropGhostPiece() {
    backup();
    clearCellsOfType(GHOST_PIECE);
    dropBlockUntilCollision();
    block.up();
    landGhostPiece();
    restoreBlock();
}

/*일직선 삭제*/
int GameTable::deleteLinear() {
    int cnt = 0;
    for (int tableY = END_Y + 1; tableY < TABLE_HEIGHT - 1; tableY++) {
        bool isLinear = true;
        for (int tableX = 1; tableX < TABLE_WIDTH - 1; tableX++) {
            if (!isMino(tableY, tableX)) {
                isLinear = false;
                break;
            }
        }
        if (isLinear) {
            cnt++;
            for (int shiftY = tableY; shiftY > END_Y + 1; shiftY--) {
                for (int tableX = 1; tableX < TABLE_WIDTH - 1; tableX++) {
                    if (table[shiftY - 1][tableX] != FALLING) {
                        table[shiftY][tableX] = table[shiftY - 1][tableX];
                    }
                }
            }
        }
    }
    return cnt;
}
/*쌓은 블록이 게임 종료 선에 닿았는지 체크*/
bool GameTable::hasReachedEnd() {
    for (int tableX = 1; tableX < TABLE_WIDTH - 1; tableX++) {
        if (isMino(END_Y, tableX)) {
            return true;
        }
    }
    return false;
}