#include "LinesRenderer.hpp"
#include "constants/Constants.hpp"

LinesRenderer::LinesRenderer() {
    font.loadFromFile("assets/fonts/Press_Start_2P/PressStart2P-Regular.ttf");
}
void LinesRenderer::draw(sf::RenderWindow& window, LinesManager& linesManager) {

    sf::Text text;
    text.setFont(font);
    text.setString("LINES:");
    text.setCharacterSize(LINES_FONT_SIZE);
    text.setFillColor(sf::Color::White);
    text.setPosition(LINES_X, LINES_Y);
    window.draw(text);

    text.setString(std::to_string(linesManager.getLines()));
    text.setPosition(LINES_X + 6 * LINES_FONT_SIZE, LINES_Y);
    window.draw(text);
}
