#include "GamePlay.hpp"
#include "GameScore.hpp"
#include <iostream>

int GamePlay::pollKeyPressed() {
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

GamePlay::GamePlay() {
    gameTable = new GameTable();
    gameScore = new GameScore();
    gameLevel = new GameLevel();
    gameLines = new GameLines();
    gameTitle = new GameTitle();
    window = new sf::RenderWindow(sf::VideoMode(1000, 800), "Tetris");
    gameTable->createBlock(true);
    while (window->isOpen()) {
        window->clear(sf::Color::Black);
        gameTable->drawGameTable(window);
        gameScore->drawScore(window);
        gameLevel->drawLevel(window);
        gameLines->drawLines(window);
        gameTitle->drawTitle(window);
        window->display();

        if (gameTable->hasReachedEnd()) {
            return;
        }
        gameTable->operateBlock(GHOST_PIECE_DROP);
        gameTable->operateBlock(AUTO_DROP);
        gameTable->operateBlock(pollKeyPressed());
        if (int lines = gameTable->deleteLinear()) {
            gameLevel->decreaseRemainingLines(lines);
            gameLines->addLines(lines);
            gameScore->addScore(gameScore->calculateScore(lines, gameLevel->getLevel()));
        }
        if (gameLevel->shoudLevelUp()) {
            gameLevel->levelUp();
        }
        gameTable->createBlock(false);
    }
}

GamePlay::~GamePlay() { // 게임 종료 이벤트
    std::cout << "Game Over!";
    delete gameTable;
    delete gameScore;
    delete gameLevel;
    delete gameLines;
    delete window;
}
