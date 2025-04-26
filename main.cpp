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

/*커서 숨기기(0) or 보이기(1) */
void CursorView(char show) {
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
/*1번 블럭*/
const int block1[4][4][4] = {
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
const int block2[4][4][4] = {
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
const int block3[4][4][4] = {
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
const int block4[4][4][4] = {
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
const int block5[4][4][4] = {
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
public:
    Block() {

    }
    Block(const int shape[4][4][4]) {
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
        for (int i = 0; i < TABLE_HEIGHT; i++) {
            vector<int> temp;
            for (int j = 0; j < TABLE_WIDTH; j++) {
                temp.push_back(0);
            }
            table.push_back(temp);
        }
        for (int i = 0; i < TABLE_WIDTH; i++) {
            table[TABLE_HEIGHT - 1][i] = WALL;
        }
        for (int i = 1; i < TABLE_HEIGHT - 1; i++) {
            table[i][0] = 1;
            table[i][TABLE_WIDTH - 1] = WALL;
        }
        for (int i = 1; i < TABLE_WIDTH - 1; i++) {
            table[TABLE_HEIGHT - 1][i] = FLOOR;
        }
        for (int i = 1; i < TABLE_WIDTH - 1; i++) {
            table[END_Y][i] = END_LINE;
        }
        createBlock(true);
        drawGameTable();
    }

    bool OOB(const int x, const int y) {
        return (y < 0 || x < 0 || y >= TABLE_HEIGHT || x >= TABLE_WIDTH);
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
    void drawGameTable()const {
        gotoxy(0, 0); //system("cls") 안쓰고 (0, 0)으로 커서 이동 후
        for (int i = 0; i < TABLE_HEIGHT; i++) {
            for (int j = 0; j < TABLE_WIDTH; j++) {
                if (table[i][j] == WALL) {
                    cout << "[]";
                } else if (table[i][j] == FALLING) {
                    cout << "[]";
                } else if (table[i][j] == FLOOR) {
                    cout << "[]";
                } else if (table[i][j] == LANDED) {
                    cout << "[]";
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
        if (select == 1) block = Block(block1); // 1번 블럭 생성
        else if (select == 2)block = Block(block2); // 2번 블럭 생성
        else if (select == 3)block = Block(block3); // 3번 블럭 생성
        else if (select == 4)block = Block(block4); // 4번 블럭 생성
        else if (select == 5)block = Block(block5); // 5번 블럭 생성

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                int x = j + block.getX();
                int y = i + block.getY();

                if (OOB(x, y)) continue;
                if (table[y][x] == LANDED) {
                    return false;
                }
                table[y][x] = block.getShape(block.getRotationCount(), i, j);
            }
        }
        block.setFallElapsedTime(clock());
    }

    void eraseFallingBlockFromTable() {
        /*테이블에서 블럭 객체 지우기*/
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                int x = j + block.getX();
                int y = i + block.getY();

                if (OOB(x, y)) continue;

                if (table[y][x] == FALLING) {
                    table[y][x] = EMPTY;
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

                if (OOB(x, y)) continue;

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
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                int x = j + block.getX();
                int y = i + block.getY();

                if (OOB(x, y)) continue;

                int blockValue = block.getShape(block.getRotationCount(), i, j);
                if (blockValue != FALLING) {
                    continue;
                }
                table[y][x] = LANDED;
            }
        }
        block.setLanded(true);
    }
    /*스페이스바 누를 시 바로 떨어짐*/
    void hardDropBlock() {
        /*테이블에서 블럭 객체 지우기*/
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                int x = j + block.getX();
                int y = i + block.getY();

                if (OOB(x, y)) continue;

                if (table[y][x] == FALLING) {
                    table[y][x] = EMPTY;
                }
            }
        }
        while (true) { //바닥이나 블럭을 만날때까지 반복
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    int x = j + block.getX();
                    int y = i + block.getY();

                    if (OOB(x, y)) continue;

                    int blockValue = block.getShape(block.getRotationCount(), i, j);

                    if (blockValue != FALLING) {
                        continue;
                    }
                    if (table[y][x] == LANDED || table[y][x] == FLOOR) {
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
        for (int Y = END_Y + 1; Y < TABLE_HEIGHT - 1; Y++) {
            bool isLinear = true;
            for (int X = 1; X < TABLE_WIDTH - 1; X++) {
                if (table[Y][X] != LANDED) {
                    isLinear = false;
                }
            }
            if (isLinear) {
                for (int i = Y; i > END_Y + 1; i--) {
                    for (int j = 1; j < TABLE_WIDTH - 1; j++) {
                        table[i][j] = table[i - 1][j];
                    }
                }
            }
        }
    }
    /*쌓은 블록이 게임 종료 선에 닿았는지 체크*/
    bool hasReachedEnd() {
        for (int X = 1; X < TABLE_WIDTH - 1; X++) {
            if (table[END_Y][X] == LANDED) {
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
    CursorView(false); // 콘솔 화면 커서 제거
    system("title 테트리스 게임"); // 콘솔창 제목 설정
    MainMenu(); // 메인 메뉴 그리기 생성자 호출
    GamePlay(); // 게임 플레이
    getchar();
    return 0;
}
