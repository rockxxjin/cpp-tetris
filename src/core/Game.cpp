#include "Game.hpp"

int Game::pollKeyPressed() {
    sf::Event event;
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window->close();
        }

        if (event.type == sf::Event::KeyPressed) {
            // 게임 오버 상태에서 Enter 키 처리
            if (gameState == GameState::GAME_OVER && event.key.code == sf::Keyboard::Enter) {
                resetGame();
                return 0;
            }

            // 게임 플레이 중일 때만 키 입력
            if (gameState == GameState::PLAYING) {
                return event.key.code;
            }
        }
    }
    return 0;
}
void Game::render() {
    window->clear(sf::Color::Black);

    boardRenderer.draw(*window, boardManager, blockManager);
    scoreRenderer.draw(*window, scoreManager);
    linesRenderer.draw(*window, linesManager);
    levelRenderer.draw(*window, levelManager);
    titleRenderer.draw(*window);

    if (gameState == GameState::GAME_OVER) {
        gameoverRenderer.draw(*window);
    }

    window->display();
}

void Game::processBlockActions() {
    operateBlock(GHOST_PIECE_DROP);
    if (fallTimer > (float)levelManager.calculateFallInterval()) {
        fallTimer -= levelManager.calculateFallInterval();
        operateBlock(AUTO_DROP);
    }
    operateBlock(pollKeyPressed());
}

bool Game::checkGameOver() {
    return hasReachedEnd();
}

void Game::handleLineClears() {
    if (int lines = deleteLinear()) {
        levelManager.decreaseRemainingLines(lines);
        linesManager.addLines(lines);
        scoreManager.addScore(scoreManager.calculateScore(lines, levelManager.getLevel()));
    }
    if (levelManager.shoudLevelUp()) {
        levelManager.levelUp();
    }
}

void Game::run() {
    gameState = GameState::PLAYING;
    spawnBlock(true);

    while (window->isOpen()) {
        float deltaTime = clock.restart().asSeconds();

        if (gameState == GameState::PLAYING) {
            fallTimer += deltaTime;
            if (checkGameOver()) {
                gameState = GameState::GAME_OVER;
            } else {
                processBlockActions();
                handleLineClears();
                spawnBlock(false);
            }
        }
        pollKeyPressed();
        render();
    }
}

void Game::resetGame() {
    gameState = GameState::PLAYING;
    fallTimer = 0.0f;

    // managers
    scoreManager = ScoreManager();
    linesManager = LinesManager();
    levelManager = LevelManager();
    blockManager = BlockManager();
    boardManager = BoardManager();

    // 새 블록 생성
    spawnBlock(true);
}

Game::Game() {
    window = std::make_unique<sf::RenderWindow>(sf::VideoMode(1000, 800), "Tetris");
    window->setFramerateLimit(60);
}

bool Game::spawnBlock(bool isFirstBlock) {
    if (!isFirstBlock && !blockManager.get().hasLanded()) {
        return true;
    }

    blockManager.generate();
    const Block& block = blockManager.get();
    for (int blockY = 0; blockY < 4; blockY++) {
        for (int blockX = 0; blockX < 4; blockX++) {
            int boardY = blockY + block.getY();
            int boardX = blockX + block.getX();

            if (boardManager.isInvalidPosition(boardY, boardX)) {
                continue;
            }
            if (boardManager.isMino(boardY, boardX)) {
                return false;
            }
            boardManager.setCell(boardY, boardX, block.getShape(block.getRotationCount(), blockY, blockX));
        }
    }
    return true;
}

void Game::clearCellsOfType(int cellType) {
    const auto& board = boardManager.get();
    for (int boardY = 0; boardY < BOARD_HEIGHT; boardY++) {
        for (int boardX = 0; boardX < BOARD_WIDTH; boardX++) {
            if (board[boardY][boardX] == cellType) {
                boardManager.setCell(boardY, boardX, EMPTY);
            }
        }
    }
}

bool Game::canMoveOrRotateBlock(const int key) {
    const Block& block = blockManager.get();
    if (key == sf::Keyboard::Up) {
        blockManager.rotate();
    } else if (key == sf::Keyboard::Down || key == AUTO_DROP) {
        blockManager.down();
    } else if (key == sf::Keyboard::Left) {
        blockManager.left();
    } else if (key == sf::Keyboard::Right) {
        blockManager.right();
    }

    const auto& board = boardManager.get();

    for (int blockY = 0; blockY < 4; blockY++) {
        for (int blockX = 0; blockX < 4; blockX++) {
            int boardY = blockY + block.getY();
            int boardX = blockX + block.getX();

            if (boardManager.isInvalidPosition(boardY, boardX)) {
                continue;
            }

            int blockValue = block.getShape(block.getRotationCount(), blockY, blockX);

            if (blockValue != FALLING) {
                continue;
            }

            if (board[boardY][boardX] != EMPTY && board[boardY][boardX] != GHOST_PIECE) {
                return false;
            }
            boardManager.setCell(boardY, boardX, blockValue); // 블럭을 이동시킴
        }
    }
    return true;
}

void Game::landBlock() {
    const Block& block = blockManager.get();
    for (int blockY = 0; blockY < 4; blockY++) {
        for (int blockX = 0; blockX < 4; blockX++) {
            int boardY = blockY + block.getY();
            int boardX = blockX + block.getX();

            if (boardManager.isInvalidPosition(boardY, boardX)) {
                continue;
            }

            int blockValue = block.getShape(block.getRotationCount(), blockY, blockX);
            if (blockValue != FALLING) {
                continue;
            }
            boardManager.setCell(boardY, boardX, block.getMinoType());
        }
    }
    blockManager.land();
}
void Game::dropBlockUntilCollision() {
    const Block& block = blockManager.get();
    while (true) {
        for (int blockY = 0; blockY < 4; blockY++) {
            for (int blockX = 0; blockX < 4; blockX++) {
                int boardY = blockY + block.getY();
                int boardX = blockX + block.getX();

                if (boardManager.isInvalidPosition(boardY, boardX)) {
                    continue;
                }

                int blockValue = block.getShape(block.getRotationCount(), blockY, blockX);
                if (blockValue != FALLING) {
                    continue;
                }
                if (boardManager.isMino(boardY, boardX) || boardManager.isWall(boardY, boardX)) {
                    return;
                }
            }
        }
        blockManager.down();
    }
}

void Game::hardDropBlock() {
    clearCellsOfType(FALLING);
    dropBlockUntilCollision();
    blockManager.up();
    landBlock();
}

void Game::landGhostPiece() {
    const Block& block = blockManager.get();
    const auto& board = boardManager.get();
    for (int blockY = 0; blockY < 4; blockY++) {
        for (int blockX = 0; blockX < 4; blockX++) {
            int boardY = blockY + block.getY();
            int boardX = blockX + block.getX();

            if (boardManager.isInvalidPosition(boardY, boardX)) {
                continue;
            }

            int blockValue = block.getShape(block.getRotationCount(), blockY, blockX);
            if (blockValue != FALLING) {
                continue;
            }
            if (board[boardY][boardX] == EMPTY) {
                boardManager.setCell(boardY, boardX, GHOST_PIECE);
            }
        }
    }
}

void Game::hardDropGhostPiece() {
    blockManager.restore();
    clearCellsOfType(GHOST_PIECE);
    dropBlockUntilCollision();
    blockManager.up();
    landGhostPiece();
    blockManager.restore();
}

void Game::operateBlock(const int key) {
    blockManager.backup();
    boardManager.backup();
    if (key == sf::Keyboard::Up || key == sf::Keyboard::Down || key == sf::Keyboard::Left || key == sf::Keyboard::Right) {

        clearCellsOfType(FALLING);
        if (!canMoveOrRotateBlock(key)) {
            blockManager.restore();
            boardManager.restore();
        }
        return;
    }

    if (key == AUTO_DROP) {
        clearCellsOfType(FALLING);
        if (!canMoveOrRotateBlock(key)) {
            blockManager.restore();
            boardManager.restore();
            landBlock();
        }
        return;
    }

    if (key == sf::Keyboard::Space) {
        hardDropBlock();
        return;
    }

    if (key == GHOST_PIECE_DROP) {
        hardDropGhostPiece();
    }
}

/*일직선 삭제*/
int Game::deleteLinear() {
    const auto& board = boardManager.get();
    int cnt = 0;
    for (int boardY = END_Y + 1; boardY < BOARD_HEIGHT - 1; boardY++) {
        bool isLinear = true;
        for (int boardX = 1; boardX < BOARD_WIDTH - 1; boardX++) {
            if (!boardManager.isMino(boardY, boardX)) {
                isLinear = false;
                break;
            }
        }
        if (isLinear) {
            cnt++;
            for (int shiftY = boardY; shiftY > END_Y + 1; shiftY--) {
                for (int boardX = 1; boardX < BOARD_WIDTH - 1; boardX++) {
                    if (board[shiftY - 1][boardX] != FALLING) {
                        boardManager.setCell(shiftY, boardX, board[shiftY - 1][boardX]);
                    }
                }
            }
        }
    }
    return cnt;
}
/*쌓은 블록이 게임 종료 선에 닿았는지 체크*/
bool Game::hasReachedEnd() {
    for (int boardX = 1; boardX < BOARD_WIDTH - 1; boardX++) {
        if (boardManager.isMino(END_Y, boardX)) {
            return true;
        }
    }
    return false;
}