#include "Game.hpp"

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

    boardRenderer.draw(*window, gameController);
    scoreRenderer.draw(*window, scoreManager);
    linesRenderer.draw(*window, linesManager);
    levelRenderer.draw(*window, levelManager);
    titleRenderer.draw(*window);

    if (gameState == GameState::GAME_OVER) {
        gameoverRenderer.draw(*window);
    }

    window->display();
}

void Game::processBlockActions() {
    gameController.operateBlock(GHOST_PIECE_DROP);
    if (fallTimer > (float)levelManager.calculateFallInterval()) {
        fallTimer -= levelManager.calculateFallInterval();
        gameController.operateBlock(AUTO_DROP);
    }
    gameController.operateBlock(pollKeyPressed());
}

bool Game::checkGameOver() {
    return gameController.hasReachedEnd();
}

void Game::handleLineClears() {
    if (int lines = gameController.deleteLinear()) {
        levelManager.decreaseRemainingLines(lines);
        linesManager.addLines(lines);
        scoreManager.addScore(scoreManager.calculateScore(lines, levelManager.getLevel()));
    }
    if (levelManager.shoudLevelUp()) {
        levelManager.levelUp();
    }
}

void Game::run() {
    gameState = GameState::PLAYING;
    gameController.createBlock(true);

    while (window->isOpen()) {
        float deltaTime = clock.restart().asSeconds();

        if (gameState == GameState::PLAYING) {
            fallTimer += deltaTime;
            if (checkGameOver()) {
                gameState = GameState::GAME_OVER;
            } else {
                processBlockActions();
                handleLineClears();
                gameController.createBlock(false);
            }
        }
        pollKeyPressed();
        render();
    }
}

void Game::resetGame() {
    gameState = GameState::PLAYING;
    fallTimer = 0.0f;

    // controller
    gameController = GameController();

    // managers
    scoreManager = ScoreManager();
    linesManager = LinesManager();
    levelManager = LevelManager();

    // 새 블록 생성
    gameController.createBlock(true);
}

Game::Game() {
    window = std::make_unique<sf::RenderWindow>(sf::VideoMode(1000, 800), "Tetris");
    window->setFramerateLimit(60);
}