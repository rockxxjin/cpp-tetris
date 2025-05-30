#pragma once

#include "entities/Block.hpp"
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <vector>

class BoardManager {
  private:
    Block block;
    Block backupBlock;

    std::vector<std::vector<int>> board;
    std::vector<std::vector<int>> backupBoard;

  public:
    BoardManager();

    bool isInvalidPosition(const int boardY, const int boardX);
    bool isMino(const int boardY, const int boardX);
    bool isWall(const int boardY, const int boardX);
    void restore();
    void restoreBlock();
    void backup();

    bool createBlock(bool isFirstBlock);
    void clearCellsOfType(int cellType);

    bool canMoveOrRotateBlock(const int key);

    void operateBlock(const int key);
    void landBlock();

    void landGhostPiece();
    void dropBlockUntilCollision();
    void hardDropBlock();

    void hardDropGhostPiece();

    int deleteLinear();
    bool hasReachedEnd();

    int getCellValue(const int boardY, const int boardX);
    int getFallingTetrominoType();
};