#include "GameLevel.hpp"
#include "constants/Constants.hpp"
GameLevel::GameLevel() {
    level = 1;
    remainingLinesToLevelUp = LINES_TO_LEVEL_UP;
    font.loadFromFile("assets/fonts/Press_Start_2P/PressStart2P-Regular.ttf");
}

int GameLevel::getLevel() {
    return level;
}

void GameLevel::decreaseRemainingLines(int lines) {
    remainingLinesToLevelUp -= lines;
}

bool GameLevel::shoudLevelUp() {
    return remainingLinesToLevelUp <= 0;
}

void GameLevel::levelUp() {
    level++;
    remainingLinesToLevelUp = LINES_TO_LEVEL_UP;
}

void GameLevel::drawLevel(sf::RenderWindow& window) {
    sf::Text text;
    text.setFont(font);
    text.setString("Level:");
    text.setCharacterSize(LEVEL_FONT_SIZE);
    text.setFillColor(sf::Color::White);
    text.setPosition(LEVEL_X, LEVEL_Y);
    window.draw(text);

    text.setString(std::to_string(level));
    text.setPosition(LEVEL_X + 6 * LEVEL_FONT_SIZE, LEVEL_Y);
    window.draw(text);
}
