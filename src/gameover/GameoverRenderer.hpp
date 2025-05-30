#pragma once

#include <SFML/Graphics.hpp>

class GameoverRenderer {
  private:
    sf::Font font;

  public:
    GameoverRenderer();
    void draw(sf::RenderWindow& window);
};