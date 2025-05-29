#pragma once

constexpr int END_Y = 0;         // 게임 종료 선
constexpr int TABLE_WIDTH = 12;  // 테트리스판 가로 크기
constexpr int TABLE_HEIGHT = 22; // 테트리스판 세로 크기

constexpr int EMPTY = 0;
constexpr int WALL = 1;
constexpr int FALLING = 2;
constexpr int LANDED = 3;
constexpr int GHOST_PIECE = 4;

constexpr int AUTO_DROP = 9999;
constexpr int GHOST_PIECE_DROP = 10000;

constexpr int MINO_I = 5000;
constexpr int MINO_O = 5001;
constexpr int MINO_Z = 5002;
constexpr int MINO_S = 5003;
constexpr int MINO_J = 5004;
constexpr int MINO_L = 5005;
constexpr int MINO_T = 5006;

constexpr int SCORE_X = 475;
constexpr int SCORE_Y = 75;
constexpr int SCORE_FONT_SIZE = 25;

constexpr int LEVEL_X = 475;
constexpr int LEVEL_Y = 115;
constexpr int LEVEL_FONT_SIZE = 25;

constexpr int LINES_X = 475;
constexpr int LINES_Y = 155;
constexpr int LINES_FONT_SIZE = 25;
constexpr int LINES_TO_LEVEL_UP = 10;

constexpr int TITLE_X = 410;
constexpr int TITLE_Y = 10;
constexpr int TITLE_FONT_SIZE = 50;

constexpr int GAME_OVER_FONT_SIZE = 50;

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