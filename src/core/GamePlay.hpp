#pragma once

#include "constants/Constants.hpp"
#include "core/GameTable.hpp"
#include <SFML/Graphics.hpp>
class GamePlay {
  private:
    GameTable *gt;
    sf::RenderWindow *window;

  public:
    int pollKeyPressed();
    GamePlay();
    ~GamePlay();
};