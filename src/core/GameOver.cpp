#include "GameOver.hpp"
#include "constants/Constants.hpp"
GameOver::GameOver() {
    font.loadFromFile("assets/fonts/Press_Start_2P/PressStart2P-Regular.ttf");
}

void GameOver::drawGameOver(sf::RenderWindow& window) {
    sf::RectangleShape overlay(sf::Vector2f(1000, 800));
    overlay.setFillColor(sf::Color(0, 0, 0, 180));
    window.draw(overlay);

    sf::Text text;
    text.setFont(font);
    text.setString("GAME OVER");
    text.setCharacterSize(GAME_OVER_FONT_SIZE);
    text.setFillColor(sf::Color::White);
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    text.setPosition(1000 / 2.0f, 800 / 3.0f - 30.0f);
    window.draw(text);

    text.setString("Press Enter to Restart Game");
    text.setCharacterSize(GAME_OVER_FONT_SIZE / 2.5);
    textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    text.setPosition(1000 / 2.0f, 800 / 3.0f + GAME_OVER_FONT_SIZE);
    window.draw(text);
}
