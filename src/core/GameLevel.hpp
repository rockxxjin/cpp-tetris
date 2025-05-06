#pragma once

#include <SFML/Graphics.hpp>

class GameLevel {
  private:
    int level;
    int remainingLinesToLevelUp;
    sf::Font font;

  public:
    GameLevel();
    int getLevel();
    void decreaseRemainingLines(int lines);
    bool shoudLevelUp();
    void levelUp();
    void drawLevel(sf::RenderWindow& window);
};