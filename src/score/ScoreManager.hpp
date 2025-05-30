#pragma once

#include <SFML/Graphics.hpp>

class ScoreManager {
  private:
    int score;

  public:
    ScoreManager();
    void addScore(int score);
    int calculateScore(int lines, int level);
    int getScore();
};