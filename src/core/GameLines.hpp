#pragma once

#include <SFML/Graphics.hpp>

class GameLines {
  private:
    int lines;
    sf::Font font;

  public:
    GameLines();
    void drawLines(sf::RenderWindow *window);
    void addLines(int lines);
};