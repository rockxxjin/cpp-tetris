#include <iostream>
#include <vector>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;

constexpr int END_Y = 0;    // 게임 종료 선
constexpr int TABLE_WIDTH = 12; //테트리스판 가로 크기
constexpr int TABLE_HEIGHT = 22; //테트리스판 세로 크기

constexpr int EMPTY = 0;
constexpr int WALL = 1;
constexpr int FALLING = 2;
constexpr int LANDED = 3;
constexpr int FLOOR = 4;
constexpr int END_LINE = 5;

constexpr int LEFT = 75; // ←
constexpr int RIGHT = 77;  // →
constexpr int UP = 72; // ↑
constexpr int DOWN = 80; // ↓
constexpr int SPACE = 32; // space
constexpr int AUTO_DROP = 9999;

constexpr int GRAY = 8;
constexpr int BLUE = 9;
constexpr int GREEN = 10;
constexpr int BLUE_GREEN = 11;
constexpr int RED = 12;
constexpr int PURPLE = 13;
constexpr int YELLOW = 14;
constexpr int WHITE = 15;

/*커서 숨기기(0) or 보이기(1) */
void cursorView(char show) {
    HANDLE hConsole;
    CONSOLE_CURSOR_INFO ConsoleCursor;

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    ConsoleCursor.bVisible = show;
    ConsoleCursor.dwSize = 1;

    SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}

/*콘솔 커서 위치 이동*/
void gotoxy(int x, int y) {
    COORD pos = { x,y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

/*1번 블럭*/
constexpr int block1[4][4][4] = {
        {
                        {0, 0, 0, 0},
                        {0, 0, 0, 0},
                        {2, 2, 2, 2},
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
                        {0, 0, 0, 0},
                        {2, 2, 2, 2},
                        {0, 0, 0, 0}

        },
        {
                        {0, 0, 2, 0},
                        {0, 0, 2, 0},
                        {0, 0, 2, 0},
                        {0, 0, 2, 0}
        },

};
/*2번 블럭*/
constexpr int block2[4][4][4] = {
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
/*3번 블럭*/
constexpr int block3[4][4][4] = {
        {
                        {0, 2, 0, 0},
                        {0, 2, 0, 0},
                        {0, 2, 2, 0},
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
        {
                        {0, 0, 0, 0},
                        {0, 0, 2, 0},
                        {2, 2, 2, 0},
                        {0, 0, 0, 0}

        },

};
/*4번 블럭*/
constexpr int block4[4][4][4] = {
        {
                        {0, 0, 0, 0},
                        {0, 2, 0, 0},
                        {0, 2, 2, 0},
                        {0, 0, 2, 0}
        },
        {
                        {0, 0, 0, 0},
                        {0, 2, 2, 0},
                        {2, 2, 0, 0},
                        {0, 0, 0, 0}

        },
        {
                        {0, 0, 0, 0},
                        {0, 2, 0, 0},
                        {0, 2, 2, 0},
                        {0, 0, 2, 0}

        },
        {
                        {0, 0, 0, 0},
                        {0, 2, 2, 0},
                        {2, 2, 0, 0},
                        {0, 0, 0, 0}

        },

};
/*5번 블럭*/
constexpr int block5[4][4][4] = {
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

/*블럭 부모 클래스*/
class Block {
private:
    int shape[4][4][4]; // shape[rotate][y][x]
    int x; // x좌표
    int y; // y좌표
    int rotationCount; // shape[0][y][x], shape[1][y][x], shape[2][y][x], shaoe[3][y][x]로 4가지 상태 표현
    bool landed;
    clock_t fallStartTime;
    int color;
public:
    Block() {

    }
    Block(const int shape[4][4][4], int color) {
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
        this->color = color;
    }
    int getShape(int rotationCount, int y, int x) {
        return shape[rotationCount][y][x];
    }
    int getX() {
        return x;
    }
    int getY() {
        return y;
    }
    int getRotationCount() {
        return rotationCount;
    }
    double getFallElapsedTime() {
        return ((double)(clock() - fallStartTime) / CLOCKS_PER_SEC);
    }
    void setFallElapsedTime(clock_t fallStartTime) {
        this->fallStartTime = fallStartTime;
    }
    bool hasLanded() {
        return landed;
    }
    int getColor() {
        return color;
    }
    void setLanded(bool landed) {
        this->landed = landed;
    }
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
    void setX(int x) {
        this->x = x;
    }
    void setY(int y) {
        this->y = y;
    }
    void setRotationCount(int r) {
        this->rotationCount = r;
    }
    void setShape(int r, int y, int x, int value) {
        this->shape[r][y][x] = value;
    }
    void up() { //hard drop 처리용 블럭 한 칸 위로 이동
        y--;
    }
};

class MainMenu {
public:
    MainMenu() {
        cout << "\n\n\n\n";
        cout << "\t\t"; cout << "@@@@@@@@@@@@  @@@@@@@@@   @@@@@@@@@@@  @@@@@@@@   @   @@@@@@@@@@@\n";
        cout << "\t\t"; cout << "      @       @                @       @      @   @   @          \n";
        cout << "\t\t"; cout << "      @       @                @       @      @   @   @          \n";
        cout << "\t\t"; cout << "      @       @@@@@@@@@        @       @     @    @   @@@@@@@@@@@\n";
        cout << "\t\t"; cout << "      @       @                @       @ @ @      @             @\n";
        cout << "\t\t"; cout << "      @       @                @       @     @    @             @\n";
        cout << "\t\t"; cout << "      @       @@@@@@@@@        @       @      @   @   @@@@@@@@@@@\n\n\n\n\n";
        cout << "\t\t"; cout << "                게임을 시작하려면 아무키나 누르세요.\n\n\n\n\n\n\n";

        getchar(); // 아무키 입력 기다림
        system("cls"); // 콘솔 창 clear
    }
};

class GameTable {
private:
    Block block;
    Block backupBlock;

    vector<vector<int> > table;
    vector<vector<int> > backupTable;

    clock_t start, end;

public:
    GameTable() { //테트리스 판 뼈대 생성
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
        for (int tableY = 1; tableY < TABLE_HEIGHT - 1; tableY++) {
            table[tableY][0] = 1;
            table[tableY][TABLE_WIDTH - 1] = WALL;
        }
        for (int tableX = 1; tableX < TABLE_WIDTH - 1; tableX++) {
            table[TABLE_HEIGHT - 1][tableX] = FLOOR;
        }
        for (int tableX = 1; tableX < TABLE_WIDTH - 1; tableX++) {
            table[END_Y][tableX] = END_LINE;
        }
        createBlock(true);
        drawGameTable();
    }

    bool isInvalidPosition(const int tableY, const int tableX) {
        return (tableY < 0 || tableX < 0 || tableY >= TABLE_HEIGHT || tableX >= TABLE_WIDTH);
    }
    bool isColor(const int y, const int x) {
        return (9 <= table[y][x] and table[y][x] <= 14);
    }
    bool isFloor(const int y, const int x) {
        return table[y][x] == FLOOR;
    }
    void restore() {
        block = backupBlock;
        table = backupTable;
    }
    void backup() {
        backupBlock = block;
        backupTable = table;
    }


    /*게임판 그리는 함수*/
    void drawGameTable() {
        gotoxy(0, 0); //system("cls") 안쓰고 (0, 0)으로 커서 이동 후
        for (int y = 0; y < TABLE_HEIGHT; y++) {
            for (int x = 0; x < TABLE_WIDTH; x++) {
                if (table[y][x] == WALL) {
                    setColor(GRAY);
                    cout << "▧ ";
                } else if (table[y][x] == FALLING) {
                    setColor(block.getColor());
                    cout << "▧ ";
                } else if (table[y][x] == FLOOR) {
                    setColor(GRAY);
                    cout << "▧ ";
                } else if (isColor(y, x)) {
                    setColor(table[y][x]);
                    cout << "▧ ";
                } else {
                    cout << "  ";
                }
            }
            cout << "\n";
        }
    }
    /*블럭 생성*/
    bool createBlock(bool isFirstBlock) {
        if (!isFirstBlock && !block.hasLanded()) {
            return true;
        }

        srand((unsigned int)time(NULL));
        int select = rand() % 5 + 1; // 1 ~ 5 블럭
        if (select == 1) block = Block(block1, BLUE_GREEN); // 1번 블럭 생성
        else if (select == 2)block = Block(block2, YELLOW); // 2번 블럭 생성
        else if (select == 3)block = Block(block3, BLUE); // 3번 블럭 생성
        else if (select == 4)block = Block(block4, GREEN); // 4번 블럭 생성
        else if (select == 5)block = Block(block5, RED); // 5번 블럭 생성

        for (int blockY = 0; blockY < 4; blockY++) {
            for (int blockX = 0; blockX < 4; blockX++) {
                int tableY = blockY + block.getY();
                int tableX = blockX + block.getX();

                if (isInvalidPosition(tableY, tableX)) continue;
                if (isColor(tableY, tableX)) {
                    return false;
                }
                table[tableY][tableX] = block.getShape(block.getRotationCount(), blockY, blockX);
            }
        }
        block.setFallElapsedTime(clock());
    }

    void eraseFallingBlockFromTable() {
        /*테이블에서 블럭 객체 지우기*/
        for (int blockY = 0; blockY < 4; blockY++) {
            for (int blockX = 0; blockX < 4; blockX++) {
                int tableY = blockY + block.getY();
                int tableX = blockX + block.getX();

                if (isInvalidPosition(tableY, tableX)) continue;

                if (table[tableY][tableX] == FALLING) {
                    table[tableY][tableX] = EMPTY;
                }
            }
        }
    }

    bool canMoveOrRotateBlock(const int key) {
        if (key == UP) {
            block.rotate();
        } else if (key == DOWN || key == AUTO_DROP) {
            block.down();
        } else if (key == LEFT) {
            block.left();
        } else if (key == RIGHT) {
            block.right();
        }

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                int x = j + block.getX();
                int y = i + block.getY();

                if (isInvalidPosition(y, x)) continue;

                int blockValue = block.getShape(block.getRotationCount(), i, j);

                if (blockValue != FALLING) {
                    continue;
                }

                if (table[y][x] != EMPTY) {
                    return false;
                }
                table[y][x] = blockValue; // 블럭을 이동시킴
            }
        }
        return true;
    }

    void operateBlock(const int key) {
        if (key == UP || key == DOWN || key == LEFT || key == RIGHT) {
            backup();
            eraseFallingBlockFromTable();
            if (!canMoveOrRotateBlock(key)) {
                restore();
            }
            return;
        }

        if (key == AUTO_DROP && block.getFallElapsedTime() >= 1.5) {
            backup();
            eraseFallingBlockFromTable();
            if (!canMoveOrRotateBlock(key)) {
                restore();
                landBlock();
            }
            return;
        }

        if (key == SPACE) {
            hardDropBlock();
        }
    }

    void landBlock() {
        for (int blockY = 0; blockY < 4; blockY++) {
            for (int blockX = 0; blockX < 4; blockX++) {
                int tableY = blockY + block.getY();
                int tableX = blockX + block.getX();

                if (isInvalidPosition(tableY, tableX)) continue;

                int blockValue = block.getShape(block.getRotationCount(), blockY, blockX);
                if (blockValue != FALLING) {
                    continue;
                }
                table[tableY][tableX] = block.getColor();
            }
        }
        block.setLanded(true);
    }
    /*스페이스바 누를 시 바로 떨어짐*/
    void hardDropBlock() {
        /*테이블에서 블럭 객체 지우기*/
        for (int blockY = 0; blockY < 4; blockY++) {
            for (int blockX = 0; blockX < 4; blockX++) {
                int tableY = blockY + block.getY();
                int tableX = blockX + block.getX();

                if (isInvalidPosition(tableY, tableX)) continue;

                if (table[tableY][tableX] == FALLING) {
                    table[tableY][tableX] = EMPTY;
                }
            }
        }
        while (true) { //바닥이나 블럭을 만날때까지 반복
            for (int blockY = 0; blockY < 4; blockY++) {
                for (int blockX = 0; blockX < 4; blockX++) {
                    int tableY = blockY + block.getY();
                    int tableX = blockX + block.getX();

                    if (isInvalidPosition(tableY, tableX)) continue;

                    int blockValue = block.getShape(block.getRotationCount(), blockY, blockX);

                    if (blockValue != FALLING) {
                        continue;
                    }
                    if (isColor(tableY, tableX) || isFloor(tableY, tableX)) {
                        block.up(); // 한 칸 위로 올리고
                        landBlock(); // 블럭을 쌓는다.
                        deleteLinear();
                        return;
                    }
                }
            }
            block.down(); // 블럭을 한 칸 아래로 이동
        }
    }
    /*일직선 삭제*/
    void deleteLinear() {
        for (int tableY = END_Y + 1; tableY < TABLE_HEIGHT - 1; tableY++) {
            bool isLinear = true;
            for (int tableX = 1; tableX < TABLE_WIDTH - 1; tableX++) {
                if (!isColor(tableY, tableX)) {
                    isLinear = false;
                    break;
                }
            }
            if (isLinear) {
                for (int shiftY = tableY; shiftY > END_Y + 1; shiftY--) {
                    for (int tableX = 1; tableX < TABLE_WIDTH - 1; tableX++) {
                        table[shiftY][tableX] = table[shiftY - 1][tableX];
                    }
                }
            }
        }
    }
    /*쌓은 블록이 게임 종료 선에 닿았는지 체크*/
    bool hasReachedEnd() {
        for (int tableX = 1; tableX < TABLE_WIDTH - 1; tableX++) {
            if (isColor(END_Y, tableX)) {
                return true;
            }
        }
        return false;
    }
};

class GamePlay {
private:
    GameTable* gt;
public:
    int readKey() {

        if (_kbhit()) {
            int nSelect = _getch();
            if (nSelect == 224) {
                return _getch();

            }
            return nSelect;
        }
    }
    GamePlay() {
        gt = new GameTable();
        while (true) {
            gt->deleteLinear();
            if (gt->hasReachedEnd()) {
                return;
            }
            gt->operateBlock(AUTO_DROP);
            gt->operateBlock(readKey());
            gt->createBlock(false);
            gt->drawGameTable();
        }
    }
    ~GamePlay() { // 게임 종료 이벤트
        gotoxy(50, 10);
        cout << "Game Over!";
        delete gt;
    }
};
int main(void) {
    cursorView(false); // 콘솔 화면 커서 제거
    SetConsoleTitle(TEXT("테트리스 게임"));
    MainMenu(); // 메인 메뉴 그리기 생성자 호출
    GamePlay(); // 게임 플레이
    getchar();
    return 0;
}