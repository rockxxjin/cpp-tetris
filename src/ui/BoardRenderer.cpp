#include "BoardRenderer.hpp"
#include "constants/Constants.hpp"
#include "utils/RandomGenerator.hpp"

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

void BoardRenderer::draw(sf::RenderWindow& window, BoardManager& boardManager, BlockManager& blockManager) {
    sf::Sprite sprite;
    const Block& block = blockManager.get();
    const auto& board = boardManager.get();
    for (int y = 0; y < BOARD_HEIGHT; y++) {
        for (int x = 0; x < BOARD_WIDTH; x++) {
            sprite.setColor(sf::Color::White);
            if (board[y][x] == WALL) {
                sprite.setTexture(blockTextureMap[WALL]);
                sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
                sprite.setPosition(x * 32, y * 32);
                window.draw(sprite);
            } else if (board[y][x] == FALLING) {
                sprite.setTexture(blockTextureMap[block.getMinoType()]);
                sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
                sprite.setPosition(x * 32, y * 32);
                window.draw(sprite);
            } else if (isMino(board[y][x])) {
                sprite.setTexture(blockTextureMap[board[y][x]]);
                sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
                sprite.setPosition(x * 32, y * 32);
                window.draw(sprite);
            } else if (board[y][x] == GHOST_PIECE) {
                sprite.setTexture(blockTextureMap[block.getMinoType()]);
                sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
                sprite.setColor(sf::Color(200, 200, 200, 150)); // 투명 효과
                sprite.setPosition(x * 32, y * 32);
                window.draw(sprite);
            }
        }
    }
}