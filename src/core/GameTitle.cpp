#include "GameTitle.hpp"
#include "constants/Constants.hpp"

GameTitle::GameTitle() {
    font.loadFromFile("assets/fonts/Press_Start_2P/PressStart2P-Regular.ttf");
}

void GameTitle::drawTitle(sf::RenderWindow *window) {
    std::string title = "TETRIS";
    sf::Color colors[] = {
        sf::Color(160, 0, 240), // T - 보라색 (Purple, T 블록)
        sf::Color(0, 240, 240), // E - 하늘색/시안 (Cyan, I 블록)
        sf::Color(240, 240, 0), // T - 노란색 (Yellow, O 블록)
        sf::Color(0, 0, 240),   // R - 파란색 (Blue, J 블록)
        sf::Color(240, 160, 0), // I - 주황색 (Orange, L 블록)
        sf::Color(0, 240, 0)    // S - 초록색 (Green, S 블록)
    };

    sf::Text text;
    for (int i = 0; i < title.size(); ++i) {
        text.setString(title[i]);
        text.setFont(font);
        text.setCharacterSize(TITLE_FONT_SIZE);
        text.setFillColor(colors[i]);
        text.setPosition(TITLE_X + i * TITLE_FONT_SIZE, TITLE_Y);
        window->draw(text);
    }
}