#pragma once

#include <SFML/Graphics.hpp>

class GameTitle {
  private:
    sf::Font font;

  public:
    GameTitle();
    void drawTitle(sf::RenderWindow& window);
};