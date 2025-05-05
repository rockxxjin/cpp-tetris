#pragma once

#include "constants/Constants.hpp"
#include "core/GameLevel.hpp"
#include "core/GameLines.hpp"
#include "core/GameScore.hpp"
#include "core/GameTable.hpp"
#include "core/GameTitle.hpp"
#include <SFML/Graphics.hpp>
class GamePlay {
  private:
    GameTable *gameTable;
    GameScore *gameScore;
    GameLevel *gameLevel;
    GameLines *gameLines;
    GameTitle *gameTitle;
    sf::RenderWindow *window;

  public:
    int pollKeyPressed();
    GamePlay();
    ~GamePlay();
};