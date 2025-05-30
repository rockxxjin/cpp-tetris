#pragma once

#include "ScoreManager.hpp"
#include <SFML/Graphics.hpp>
class ScoreRenderer {

  private:
    sf::Font font;

  public:
    ScoreRenderer();
    void draw(sf::RenderWindow& window, ScoreManager& scoreManager);
};