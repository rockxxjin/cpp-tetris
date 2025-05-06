#pragma once

#include "block/Block.hpp"
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <vector>

class GameTable {
  private:
    Block block;
    Block backupBlock;

    std::vector<std::vector<int>> table;
    std::vector<std::vector<int>> backupTable;

    clock_t start, end;

    std::unordered_map<int, sf::Texture> blockTextureMap;

  public:
    GameTable();

    bool isInvalidPosition(const int tableY, const int tableX);
    bool isMino(const int y, const int x);
    bool isWall(const int y, const int x);
    void restore();
    void restoreBlock();
    void backup();

    void drawGameTable(sf::RenderWindow& window);
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
};