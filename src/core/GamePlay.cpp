#include "GamePlay.hpp"
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
    gt = new GameTable();
    window = new sf::RenderWindow(sf::VideoMode(1000, 800), "Tetris");
    gt->createBlock(true);
    while (window->isOpen()) {
        gt->drawGameTable(window);
        if (gt->hasReachedEnd()) {
            return;
        }
        gt->operateBlock(GHOST_PIECE_DROP);
        gt->operateBlock(AUTO_DROP);
        gt->operateBlock(pollKeyPressed());
        gt->deleteLinear();
        gt->createBlock(false);
    }
}

GamePlay::~GamePlay() { // 게임 종료 이벤트
    std::cout << "Game Over!";
    delete gt;
    delete window;
}
