#include "LevelRenderer.hpp"
#include "constants/Constants.hpp"
#include <cmath>
LevelRenderer::LevelRenderer() {
    font.loadFromFile("assets/fonts/Press_Start_2P/PressStart2P-Regular.ttf");
}

void LevelRenderer::draw(sf::RenderWindow& window, LevelManager& levelManager) {
    sf::Text text;
    text.setFont(font);
    text.setString("Level:");
    text.setCharacterSize(LEVEL_FONT_SIZE);
    text.setFillColor(sf::Color::White);
    text.setPosition(LEVEL_X, LEVEL_Y);
    window.draw(text);

    text.setString(std::to_string(levelManager.getLevel()));
    text.setPosition(LEVEL_X + 6 * LEVEL_FONT_SIZE, LEVEL_Y);
    window.draw(text);
}
