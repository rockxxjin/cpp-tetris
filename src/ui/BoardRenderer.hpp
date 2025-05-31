#pragma once

#include "block/BlockManager.hpp"
#include "board/BoardManager.hpp"
#include "entities/Block.hpp"
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <vector>

class BoardRenderer {
  private:
    std::unordered_map<int, sf::Texture> blockTextureMap;

  public:
    BoardRenderer();
    bool isMino(const int cellType);
    void draw(sf::RenderWindow& window, BoardManager& boardManger, BlockManager& blockManager);
};