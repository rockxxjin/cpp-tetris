#pragma once

#include "constants/Constants.hpp"
#include "core/GameLevel.hpp"
#include "core/GameLines.hpp"
#include "core/GameOver.hpp"
#include "core/GameScore.hpp"
#include "core/GameTable.hpp"
#include "core/GameTitle.hpp"
#include <SFML/Graphics.hpp>

enum class GameState {
    PLAYING,
    GAME_OVER
};

class Game {
  private:
    GameTable gameTable;
    GameScore gameScore;
    GameLevel gameLevel;
    GameLines gameLines;
    GameTitle gameTitle;
    GameOver gameOver;
    GameState gameState;
    std::unique_ptr<sf::RenderWindow> window;
    sf::Clock clock;
    float fallTimer;

  public:
    int pollKeyPressed();
    void render();
    void processBlockActions();
    bool checkGameOver();
    void handleLineClears();
    void run();
    void resetGame();
    Game();
};