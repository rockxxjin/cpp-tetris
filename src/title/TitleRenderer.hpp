#pragma once

#include <SFML/Graphics.hpp>

class TitleRenderer {
  private:
    sf::Font font;

  public:
    TitleRenderer();
    void draw(sf::RenderWindow& window);
};