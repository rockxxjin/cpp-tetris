#include "Game.hpp"
#include "GameScore.hpp"

int Game::pollKeyPressed() {
    sf::Event event;
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window->close();
        }

        if (event.type == sf::Event::KeyPressed) {
            // 게임 오버 상태에서 Enter 키 처리
            if (gameState == GameState::GAME_OVER && event.key.code == sf::Keyboard::Enter) {
                resetGame();
                return 0;
            }

            // 게임 플레이 중일 때만 키 입력
            if (gameState == GameState::PLAYING) {
                return event.key.code;
            }
        }
    }
    return 0;
}
void Game::render() {
    window->clear(sf::Color::Black);
    gameTable.drawGameTable(*window);
    gameScore.drawScore(*window);
    gameLevel.drawLevel(*window);
    gameLines.drawLines(*window);
    gameTitle.drawTitle(*window);

    if (gameState == GameState::GAME_OVER) {
        gameOver.drawGameOver(*window);
    }

    window->display();
}

void Game::processBlockActions() {
    gameTable.operateBlock(GHOST_PIECE_DROP);
    if (fallTimer > (float)gameLevel.calculateFallInterval()) {
        fallTimer -= gameLevel.calculateFallInterval();
        gameTable.operateBlock(AUTO_DROP);
    }
    gameTable.operateBlock(pollKeyPressed());
}

bool Game::checkGameOver() {
    return gameTable.hasReachedEnd();
}

void Game::handleLineClears() {
    if (int lines = gameTable.deleteLinear()) {
        gameLevel.decreaseRemainingLines(lines);
        gameLines.addLines(lines);
        gameScore.addScore(gameScore.calculateScore(lines, gameLevel.getLevel()));
    }
    if (gameLevel.shoudLevelUp()) {
        gameLevel.levelUp();
    }
}

void Game::run() {
    gameState = GameState::PLAYING;
    gameTable.createBlock(true);

    while (window->isOpen()) {
        float deltaTime = clock.restart().asSeconds();

        if (gameState == GameState::PLAYING) {
            fallTimer += deltaTime;
            if (checkGameOver()) {
                gameState = GameState::GAME_OVER;
            } else {
                processBlockActions();
                handleLineClears();
                gameTable.createBlock(false);
            }
        }
        pollKeyPressed();
        render();
    }
}

void Game::resetGame() {
    gameTable = GameTable();
    gameScore = GameScore();
    gameLevel = GameLevel();
    gameLines = GameLines();
    gameTitle = GameTitle();
    gameOver = GameOver();
    gameState = GameState::PLAYING;
    fallTimer = 0.0f;

    // 새 블록 생성
    gameTable.createBlock(true);
}

Game::Game() {
    window = std::make_unique<sf::RenderWindow>(sf::VideoMode(1000, 800), "Tetris");
    window->setFramerateLimit(60);
}