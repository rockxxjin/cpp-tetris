#pragma once

#include <SFML/Graphics.hpp>

class LinesManager {
  private:
    int lines;

  public:
    LinesManager();
    void addLines(int lines);
    int getLines();
};