#pragma once

#include "constants/Constants.hpp"
#include "core/GameLevel.hpp"
#include "core/GameLines.hpp"
#include "core/GameScore.hpp"
#include "core/GameTable.hpp"
#include "core/GameTitle.hpp"
#include <SFML/Graphics.hpp>
class Game {
  private:
    GameTable gameTable;
    GameScore gameScore;
    GameLevel gameLevel;
    GameLines gameLines;
    GameTitle gameTitle;
    std::unique_ptr<sf::RenderWindow> window;

  public:
    int pollKeyPressed();
    void render();
    void processBlockActions();
    bool checkGameOver();
    void handleLineClears();
    void run();
    Game();
};