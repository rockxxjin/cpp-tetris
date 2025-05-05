#pragma once

#include <SFML/Graphics.hpp>

class GameScore {
  private:
    int score;
    sf::Font font;

  public:
    GameScore();
    void drawScore(sf::RenderWindow *window);
    void addScore(int score);
    int calculateScore(int lines, int level);
};