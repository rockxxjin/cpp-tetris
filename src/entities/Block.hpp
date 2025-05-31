#pragma once

class Block {
  private:
    int shape[4][4][4]; // shape[rotate][y][x]
    int x;              // x좌표
    int y;              // y좌표
    int rotationCount;  // shape[0][y][x], shape[1][y][x], shape[2][y][x], shaoe[3][y][x]로 4가지 회전 상태 표현
    bool landed;
    int minoType;

  public:
    int getShape(int rotationCount, int y, int x) const;
    int getX() const;
    int getY() const;
    int getRotationCount() const;

    bool hasLanded() const;
    int getMinoType() const;
    void setLanded(bool landed);
    void down();
    void left();
    void right();
    void rotate();
    void setX(int x);
    void setY(int y);
    void setRotationCount(int r);
    void setShape(const int shape[4][4][4]);
    void up();
    void setMinoType(const int minoType);
};