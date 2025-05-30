#pragma once

#include "LinesManager.hpp"
#include <SFML/Graphics.hpp>
class LinesRenderer {
  private:
    sf::Font font;

  public:
    LinesRenderer();
    void draw(sf::RenderWindow& window, LinesManager& linesManager);
};