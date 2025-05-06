#include "GameScore.hpp"
#include "constants/Constants.hpp"
#include <string>
GameScore::GameScore() {
    score = 0;
    font.loadFromFile("assets/fonts/Press_Start_2P/PressStart2P-Regular.ttf");
}
void GameScore::drawScore(sf::RenderWindow& window) {
    sf::Text text;
    text.setFont(font);
    text.setString("SCORE:");
    text.setCharacterSize(SCORE_FONT_SIZE);
    text.setFillColor(sf::Color::White);
    text.setPosition(SCORE_X, SCORE_Y);
    window.draw(text);

    text.setString(std::to_string(score));
    text.setPosition(SCORE_X + 6 * SCORE_FONT_SIZE, SCORE_Y);
    window.draw(text);
}

void GameScore::addScore(int score) {
    this->score += score;
}

int GameScore::calculateScore(int lines, int level) {
    int score = 0;
    static constexpr int lineClearScores[5] = {0, 100, 300, 500, 800};
    if (lines < 1 or lines > 4) {
        return 0;
    }
    return lineClearScores[lines] * level;
}
