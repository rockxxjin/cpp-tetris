#pragma once

#include <SFML/Graphics.hpp>

class LevelManager {
  private:
    int level;
    int remainingLinesToLevelUp;

  public:
    LevelManager();
    int getLevel();
    void decreaseRemainingLines(int lines);
    bool shoudLevelUp();
    void levelUp();
    float calculateFallInterval();
};