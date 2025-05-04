#pragma once

#include "constants/Constants.hpp"
#include <ctime>
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
    Block();
    Block(int minoType);
    int getShape(int rotationCount, int y, int x);
    int getX();
    int getY();
    int getRotationCount();
    double getFallElapsedTime();
    void setFallElapsedTime(clock_t fallStartTime);
    bool hasLanded();
    int getMinoType();
    void setLanded(bool landed);
    void down();
    void left();
    void right();
    void rotate();
    void setX(int x);
    void setY(int y);
    void setRotationCount(int r);
    void setShape(int r, int y, int x, int value);
    void up();
};