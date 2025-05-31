#pragma once
#include <vector>

class BoardManager {
  private:
    std::vector<std::vector<int>> board;
    std::vector<std::vector<int>> backupBoard;

  public:
    BoardManager();
    void backup();
    void restore();
    void setCell(const int boardY, const int boardX, const int value);
    bool isInvalidPosition(const int boardY, const int boardX) const;
    bool isMino(const int boardY, const int boardX) const;
    bool isWall(const int boardY, const int boardX) const;
    const std::vector<std::vector<int>>& get() const;
    bool hasReachedEnd();
    int deleteLinear();
    void clearCellsOfType(int cellType);
};