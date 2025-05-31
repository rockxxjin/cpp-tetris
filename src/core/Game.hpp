#pragma once

#include "block/BlockManager.hpp"
#include "constants/Constants.hpp"
#include "level/LevelManager.hpp"
#include "lines/LinesManager.hpp"
#include "score/ScoreManager.hpp"
#include "ui/BoardRenderer.hpp"
#include "ui/GameoverRenderer.hpp"
#include "ui/LevelRenderer.hpp"
#include "ui/LinesRenderer.hpp"
#include "ui/ScoreRenderer.hpp"
#include "ui/TitleRenderer.hpp"
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

    // managers
    ScoreManager scoreManager;
    LinesManager linesManager;
    LevelManager levelManager;
    BlockManager blockManager;
    BoardManager boardManager;

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
    bool spawnBlock(bool isFirstBlock);
    bool canMoveOrRotateBlock(const int key);
    void dropBlockUntilCollision();
    void landBlock();
    void hardDropBlock();
    void landGhostPiece();
    void hardDropGhostPiece();
    void operateBlock(const int key);
};