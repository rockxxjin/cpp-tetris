#include "BoardRenderer.hpp"
#include "utils/RandomGenerator.hpp"
using namespace std;

BoardRenderer::BoardRenderer() {
    blockTextureMap[WALL].loadFromFile("assets/images/block_wall.png");
    blockTextureMap[MINO_I].loadFromFile("assets/images/block_I.png");
    blockTextureMap[MINO_O].loadFromFile("assets/images/block_O.png");
    blockTextureMap[MINO_Z].loadFromFile("assets/images/block_Z.png");
    blockTextureMap[MINO_S].loadFromFile("assets/images/block_S.png");
    blockTextureMap[MINO_J].loadFromFile("assets/images/block_J.png");
    blockTextureMap[MINO_L].loadFromFile("assets/images/block_L.png");
    blockTextureMap[MINO_T].loadFromFile("assets/images/block_T.png");
}

bool BoardRenderer::isMino(const int cellType) {
    return (5000 <= cellType and cellType <= 5006);
}

void BoardRenderer::draw(sf::RenderWindow& window, GameController& gameController) {
    sf::Sprite sprite;

    for (int y = 0; y < BOARD_HEIGHT; y++) {
        for (int x = 0; x < BOARD_WIDTH; x++) {
            sprite.setColor(sf::Color::White);
            if (gameController.getCellValue(y, x) == WALL) {
                sprite.setTexture(blockTextureMap[WALL]);
                sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
                sprite.setPosition(x * 32, y * 32);
                window.draw(sprite);
            } else if (gameController.getCellValue(y, x) == FALLING) {
                sprite.setTexture(blockTextureMap[gameController.getFallingTetrominoType()]);
                sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
                sprite.setPosition(x * 32, y * 32);
                window.draw(sprite);
            } else if (isMino(gameController.getCellValue(y, x))) {
                sprite.setTexture(blockTextureMap[gameController.getCellValue(y, x)]);
                sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
                sprite.setPosition(x * 32, y * 32);
                window.draw(sprite);
            } else if (gameController.getCellValue(y, x) == GHOST_PIECE) {
                sprite.setTexture(blockTextureMap[gameController.getFallingTetrominoType()]);
                sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
                sprite.setColor(sf::Color(200, 200, 200, 150)); // 투명 효과
                sprite.setPosition(x * 32, y * 32);
                window.draw(sprite);
            }
        }
    }
}