#include "GameLines.hpp"
#include "constants/Constants.hpp"

GameLines::GameLines() {
    lines = 0;
    font.loadFromFile("assets/fonts/Press_Start_2P/PressStart2P-Regular.ttf");
}

void GameLines::drawLines(sf::RenderWindow& window) {
    sf::Text text;
    text.setFont(font);
    text.setString("LINES:");
    text.setCharacterSize(LINES_FONT_SIZE);
    text.setFillColor(sf::Color::White);
    text.setPosition(LINES_X, LINES_Y);
    window.draw(text);

    text.setString(std::to_string(lines));
    text.setPosition(LINES_X + 6 * LINES_FONT_SIZE, LINES_Y);
    window.draw(text);
}

void GameLines::addLines(int lines) {
    this->lines += lines;
}
