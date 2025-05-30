#pragma once

#include "board/BoardRenderer.hpp"
#include "constants/Constants.hpp"
#include "core/GameController.hpp"
#include "gameover/GameoverRenderer.hpp"
#include "level/LevelManager.hpp"
#include "level/LevelRenderer.hpp"
#include "lines/LinesManager.hpp"
#include "lines/LinesRenderer.hpp"
#include "score/ScoreManager.hpp"
#include "score/ScoreRenderer.hpp"
#include "title/TitleRenderer.hpp"
#include <SFML/Graphics.hpp>

enum class GameState {
    PLAYING,
    GAME_OVER
};

class Game {
  private:
    GameState gameState;
    std::unique_ptr<sf::RenderWindow> window;
    sf::Clock clock;
    float fallTimer;

    // controller
    GameController gameController;

    // managers
    ScoreManager scoreManager;
    LinesManager linesManager;
    LevelManager levelManager;

    // renderers
    ScoreRenderer scoreRenderer;
    LinesRenderer linesRenderer;
    LevelRenderer levelRenderer;
    TitleRenderer titleRenderer;
    BoardRenderer boardRenderer;
    GameoverRenderer gameoverRenderer;

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