#pragma once

#include <SFML/Graphics.hpp>

class GameOver {
  private:
    sf::Font font;

  public:
    GameOver();
    void drawGameOver(sf::RenderWindow& window);
};