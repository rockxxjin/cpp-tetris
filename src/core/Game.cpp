#include "Game.hpp"
#include "GameScore.hpp"
#include <iostream>

int Game::pollKeyPressed() {
    sf::Event event;
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window->close();
        }

        if (event.type == sf::Event::KeyPressed) {
            return event.key.code;
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
    window->display();
}

void Game::processBlockActions() {
    gameTable.operateBlock(GHOST_PIECE_DROP);
    gameTable.operateBlock(AUTO_DROP);
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
    gameTable.createBlock(true);
    while (window->isOpen()) {
        render();
        if (checkGameOver()) {
            return;
        }
        processBlockActions();
        handleLineClears();
        gameTable.createBlock(false);
    }
}

Game::Game() {
    window = std::make_unique<sf::RenderWindow>(sf::VideoMode(1000, 800), "Tetris");
}
