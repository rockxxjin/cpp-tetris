#pragma once

#include "LevelManager.hpp"
#include <SFML/Graphics.hpp>
class LevelRenderer {
  private:
    sf::Font font;

  public:
    LevelRenderer();
    void draw(sf::RenderWindow& window, LevelManager& levelManager);
};