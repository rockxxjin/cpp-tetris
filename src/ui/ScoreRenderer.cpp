#include "ScoreRenderer.hpp"
#include "constants/Constants.hpp"
#include <string>

ScoreRenderer::ScoreRenderer() {
    font.loadFromFile("assets/fonts/Press_Start_2P/PressStart2P-Regular.ttf");
}
void ScoreRenderer::draw(sf::RenderWindow& window, ScoreManager& scoreManager) {
    sf::Text text;
    text.setFont(font);
    text.setString("SCORE:");
    text.setCharacterSize(SCORE_FONT_SIZE);
    text.setFillColor(sf::Color::White);
    text.setPosition(SCORE_X, SCORE_Y);
    window.draw(text);

    text.setString(std::to_string(scoreManager.getScore()));
    text.setPosition(SCORE_X + 6 * SCORE_FONT_SIZE, SCORE_Y);
    window.draw(text);
}