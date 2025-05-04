#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <unordered_map>
#include <vector>
using namespace std;

constexpr int END_Y = 0;         // 게임 종료 선
constexpr int TABLE_WIDTH = 12;  // 테트리스판 가로 크기
constexpr int TABLE_HEIGHT = 22; // 테트리스판 세로 크기

constexpr int EMPTY = 0;
constexpr int WALL = 1;
constexpr int FALLING = 2;
constexpr int LANDED = 3;
constexpr int END_LINE = 4;
constexpr int GHOST_PIECE = 5;

constexpr int AUTO_DROP = 9999;
constexpr int GHOST_PIECE_DROP = 10000;

constexpr int MINO_I = 5000;
constexpr int MINO_O = 5001;
constexpr int MINO_Z = 5002;
constexpr int MINO_S = 5003;
constexpr int MINO_J = 5004;
constexpr int MINO_L = 5005;
constexpr int MINO_T = 5006;

// clang-format off
// I 블록
constexpr int blockI[4][4][4] = {
    {
        {0, 0, 0, 0},
        {2, 2, 2, 2},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },
    {
        {0, 0, 2, 0},
        {0, 0, 2, 0},
        {0, 0, 2, 0},
        {0, 0, 2, 0}
    },
    {
        {0, 0, 0, 0},
        {2, 2, 2, 2},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },
    {
        {0, 0, 2, 0},
        {0, 0, 2, 0},
        {0, 0, 2, 0},
        {0, 0, 2, 0}
    },
};

// O 블록
constexpr int blockO[4][4][4] = {
    {
        {0, 0, 0, 0},
        {0, 2, 2, 0},
        {0, 2, 2, 0},
        {0, 0, 0, 0}
    },
    {
        {0, 0, 0, 0},
        {0, 2, 2, 0},
        {0, 2, 2, 0},
        {0, 0, 0, 0}
    },
    {
        {0, 0, 0, 0},
        {0, 2, 2, 0},
        {0, 2, 2, 0},
        {0, 0, 0, 0}
    },
    {
        {0, 0, 0, 0},
        {0, 2, 2, 0},
        {0, 2, 2, 0},
        {0, 0, 0, 0}
    },
};

// S 블록
constexpr int blockS[4][4][4] = {
    {
        {0, 0, 0, 0},
        {0, 0, 2, 2},
        {0, 2, 2, 0},
        {0, 0, 0, 0}
    },
    {
        {0, 0, 2, 0},
        {0, 0, 2, 2},
        {0, 0, 0, 2},
        {0, 0, 0, 0}
    },
    {
        {0, 0, 0, 0},
        {0, 0, 2, 2},
        {0, 2, 2, 0},
        {0, 0, 0, 0}
    },
    {
        {0, 0, 2, 0},
        {0, 0, 2, 2},
        {0, 0, 0, 2},
        {0, 0, 0, 0}
    },
};

// Z 블록
constexpr int blockZ[4][4][4] = {
    {
        {0, 0, 0, 0},
        {0, 2, 2, 0},
        {0, 0, 2, 2},
        {0, 0, 0, 0}
    },
    {
        {0, 0, 0, 2},
        {0, 0, 2, 2},
        {0, 0, 2, 0},
        {0, 0, 0, 0}
    },
    {
        {0, 0, 0, 0},
        {0, 2, 2, 0},
        {0, 0, 2, 2},
        {0, 0, 0, 0}
    },
    {
        {0, 0, 0, 2},
        {0, 0, 2, 2},
        {0, 0, 2, 0},
        {0, 0, 0, 0}
    },
};

// J 블록
constexpr int blockJ[4][4][4] = {
    {
        {0, 0, 0, 0},
        {0, 2, 0, 0},
        {0, 2, 2, 2},
        {0, 0, 0, 0}
    },
    {
        {0, 0, 2, 2},
        {0, 0, 2, 0},
        {0, 0, 2, 0},
        {0, 0, 0, 0}
    },
    {
        {0, 0, 0, 0},
        {0, 2, 2, 2},
        {0, 0, 0, 2},
        {0, 0, 0, 0}
    },
    {
        {0, 0, 2, 0},
        {0, 0, 2, 0},
        {0, 2, 2, 0},
        {0, 0, 0, 0}
    },
};

// L 블록
constexpr int blockL[4][4][4] = {
    {
        {0, 0, 0, 0},
        {0, 0, 0, 2},
        {0, 2, 2, 2},
        {0, 0, 0, 0}
    },
    {
        {0, 0, 2, 0},
        {0, 0, 2, 0},
        {0, 0, 2, 2},
        {0, 0, 0, 0}
    },
    {
        {0, 0, 0, 0},
        {0, 2, 2, 2},
        {0, 2, 0, 0},
        {0, 0, 0, 0}
    },
    {
        {0, 2, 2, 0},
        {0, 0, 2, 0},
        {0, 0, 2, 0},
        {0, 0, 0, 0}
    },
};

// T 블록
constexpr int blockT[4][4][4] = {
    {
        {0, 0, 0, 0},
        {0, 2, 2, 2},
        {0, 0, 2, 0},
        {0, 0, 0, 0}
    },
    {
        {0, 0, 2, 0},
        {0, 2, 2, 0},
        {0, 0, 2, 0},
        {0, 0, 0, 0}
    },
    {
        {0, 0, 2, 0},
        {0, 2, 2, 2},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },
    {
        {0, 0, 2, 0},
        {0, 0, 2, 2},
        {0, 0, 2, 0},
        {0, 0, 0, 0}
    },
};

// clang-format on
class RandomGenerator {
  public:
    static int get(int min, int max) {
        static thread_local mt19937 mt{random_device{}()};
        return uniform_int_distribution<int>{min, max}(mt);
    }
};

class Block {
  private:
    int shape[4][4][4]; // shape[rotate][y][x]
    int x;              // x좌표
    int y;              // y좌표
    int rotationCount;  // shape[0][y][x], shape[1][y][x], shape[2][y][x], shaoe[3][y][x]로 4가지 회전 상태 표현
    bool landed;
    clock_t fallStartTime;
    int minoType;

  public:
    Block() {}
    Block(const int shape[4][4][4], int minoType) {
        x = TABLE_WIDTH / 2 - 3;
        y = -1;
        rotationCount = 0;
        landed = false;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                for (int k = 0; k < 4; k++) {
                    this->shape[i][j][k] = shape[i][j][k];
                }
            }
        }
        this->minoType = minoType;
    }
    int getShape(int rotationCount, int y, int x) {
        return shape[rotationCount][y][x];
    }
    int getX() { return x; }
    int getY() { return y; }
    int getRotationCount() { return rotationCount; }
    double getFallElapsedTime() {
        return ((double)(clock() - fallStartTime) / CLOCKS_PER_SEC);
    }
    void setFallElapsedTime(clock_t fallStartTime) {
        this->fallStartTime = fallStartTime;
    }
    bool hasLanded() { return landed; }
    int getMinoType() { return minoType; }
    void setLanded(bool landed) { this->landed = landed; }
    void down() { // 블럭 한 칸 아래 이동
        y++;
        fallStartTime = clock();
    }
    void left() { // 블럭 한 칸 왼쪽 이동
        x--;
    }
    void right() { // 블럭 한 칸 오른쪽 이동
        x++;
    }
    void rotate() { // 블럭 회전
        rotationCount = (rotationCount + 1) % 4;
    }
    void setX(int x) { this->x = x; }
    void setY(int y) { this->y = y; }
    void setRotationCount(int r) { this->rotationCount = r; }
    void setShape(int r, int y, int x, int value) {
        this->shape[r][y][x] = value;
    }
    void up() { // hard drop 처리용 블럭 한 칸 위로 이동
        y--;
    }
};

class GameTable {
  private:
    Block block;
    Block backupBlock;

    vector<vector<int>> table;
    vector<vector<int>> backupTable;

    clock_t start, end;

    unordered_map<int, sf::Texture> blockTextureMap;

  public:
    GameTable() {
        blockTextureMap[WALL].loadFromFile("images/block_wall.png");
        blockTextureMap[MINO_I].loadFromFile("images/block_I.png");
        blockTextureMap[MINO_O].loadFromFile("images/block_O.png");
        blockTextureMap[MINO_Z].loadFromFile("images/block_Z.png");
        blockTextureMap[MINO_S].loadFromFile("images/block_S.png");
        blockTextureMap[MINO_J].loadFromFile("images/block_J.png");
        blockTextureMap[MINO_L].loadFromFile("images/block_L.png");
        blockTextureMap[MINO_T].loadFromFile("images/block_T.png");

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
        for (int tableX = 1; tableX < TABLE_WIDTH - 1; tableX++) {
            table[END_Y][tableX] = END_LINE;
        }
    }

    bool isInvalidPosition(const int tableY, const int tableX) {
        return (tableY < 0 || tableX < 0 || tableY >= TABLE_HEIGHT || tableX >= TABLE_WIDTH);
    }
    bool isMino(const int y, const int x) {
        return (5000 <= table[y][x] and table[y][x] <= 5006);
    }
    bool isWall(const int y, const int x) { return table[y][x] == WALL; }
    void restore() {
        block = backupBlock;
        table = backupTable;
    }
    void restoreBlock() { block = backupBlock; }
    void backup() {
        backupBlock = block;
        backupTable = table;
    }

    /*게임판 그리는 함수*/
    void drawGameTable(sf::RenderWindow *window) {
        window->clear(sf::Color::Black);
        sf::Sprite sprite;

        for (int y = 0; y < TABLE_HEIGHT; y++) {
            for (int x = 0; x < TABLE_WIDTH; x++) {
                sprite.setColor(sf::Color::White);
                if (table[y][x] == WALL) {
                    sprite.setTexture(blockTextureMap[WALL]);
                    sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
                    sprite.setPosition(x * 32, y * 32);
                    window->draw(sprite);
                } else if (table[y][x] == FALLING) {
                    sprite.setTexture(blockTextureMap[block.getMinoType()]);
                    sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
                    sprite.setPosition(x * 32, y * 32);
                    window->draw(sprite);
                } else if (isMino(y, x)) {
                    sprite.setTexture(blockTextureMap[table[y][x]]);
                    sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
                    sprite.setPosition(x * 32, y * 32);
                    window->draw(sprite);
                } else if (table[y][x] == GHOST_PIECE) {
                    sprite.setTexture(blockTextureMap[block.getMinoType()]);
                    sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
                    sprite.setColor(sf::Color(200, 200, 200, 150)); // 투명 효과
                    sprite.setPosition(x * 32, y * 32);
                    window->draw(sprite);
                }
            }
        }

        window->display();
    }
    /*블럭 생성*/
    bool createBlock(bool isFirstBlock) {
        if (!isFirstBlock && !block.hasLanded()) {
            return true;
        }

        int select = RandomGenerator::get(1, 7); // I, O, Z, S, J, L, T
        if (select == 1) {
            block = Block(blockI, MINO_I); // I미노 생성
        } else if (select == 2) {
            block = Block(blockO, MINO_O); // O미노 생성
        } else if (select == 3) {
            block = Block(blockZ, MINO_Z); // Z미노 생성
        } else if (select == 4) {
            block = Block(blockS, MINO_S); // S미노 생성
        } else if (select == 5) {
            block = Block(blockJ, MINO_J); // J미노 생성
        } else if (select == 6) {
            block = Block(blockL, MINO_L); // L미노 생성
        } else if (select == 7) {
            block = Block(blockT, MINO_T); // T미노 생성
        }
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
        block.setFallElapsedTime(clock());
    }

    void clearCellsOfType(int cellType) {
        for (int tableY = 0; tableY < TABLE_HEIGHT; tableY++) {
            for (int tableX = 0; tableX < TABLE_WIDTH; tableX++) {
                if (table[tableY][tableX] == cellType) {
                    table[tableY][tableX] = EMPTY;
                }
            }
        }
    }

    bool canMoveOrRotateBlock(const int key) {
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

    void operateBlock(const int key) {
        if (key == sf::Keyboard::Up || key == sf::Keyboard::Down || key == sf::Keyboard::Left || key == sf::Keyboard::Right) {
            backup();
            clearCellsOfType(FALLING);
            if (!canMoveOrRotateBlock(key)) {
                restore();
            }
            return;
        }

        if (key == AUTO_DROP && block.getFallElapsedTime() >= 1.5) {
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

    void landBlock() {
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

    void landGhostPiece() {
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

    void dropBlockUntilCollision() {
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

    void hardDropBlock() {
        clearCellsOfType(FALLING);
        dropBlockUntilCollision();
        block.up();
        landBlock();
    }

    void hardDropGhostPiece() {
        backup();
        clearCellsOfType(GHOST_PIECE);
        dropBlockUntilCollision();
        block.up();
        landGhostPiece();
        restoreBlock();
    }

    /*일직선 삭제*/
    void deleteLinear() {
        for (int tableY = END_Y + 1; tableY < TABLE_HEIGHT - 1; tableY++) {
            bool isLinear = true;
            for (int tableX = 1; tableX < TABLE_WIDTH - 1; tableX++) {
                if (!isMino(tableY, tableX)) {
                    isLinear = false;
                    break;
                }
            }
            if (isLinear) {
                for (int shiftY = tableY; shiftY > END_Y + 1; shiftY--) {
                    for (int tableX = 1; tableX < TABLE_WIDTH - 1; tableX++) {
                        if (table[shiftY - 1][tableX] != FALLING) {
                            table[shiftY][tableX] = table[shiftY - 1][tableX];
                        }
                    }
                }
            }
        }
    }
    /*쌓은 블록이 게임 종료 선에 닿았는지 체크*/
    bool hasReachedEnd() {
        for (int tableX = 1; tableX < TABLE_WIDTH - 1; tableX++) {
            if (isMino(END_Y, tableX)) {
                return true;
            }
        }
        return false;
    }
};

class GamePlay {
  private:
    GameTable *gt;
    sf::RenderWindow *window;

  public:
    int pollKeyPressed() {
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window->close();
            }

            if (event.type == sf::Event::KeyPressed) {
                return event.key.code;
            }
        }
        return 0;
    }
    GamePlay() {
        gt = new GameTable();
        window = new sf::RenderWindow(sf::VideoMode(1000, 800), "Tetris");
        gt->createBlock(true);
        while (window->isOpen()) {
            gt->drawGameTable(window);
            if (gt->hasReachedEnd()) {
                return;
            }
            gt->operateBlock(GHOST_PIECE_DROP);
            gt->operateBlock(AUTO_DROP);
            gt->operateBlock(pollKeyPressed());
            gt->deleteLinear();
            gt->createBlock(false);
        }
    }
    ~GamePlay() { // 게임 종료 이벤트
        cout << "Game Over!";
        delete gt;
        delete window;
    }
};

int main() {
    GamePlay();
    return 0;
}