#include "LevelManager.hpp"
#include "constants/Constants.hpp"
#include <cmath>
LevelManager::LevelManager() {
    level = 1;
    remainingLinesToLevelUp = LINES_TO_LEVEL_UP;
}

int LevelManager::getLevel() {
    return level;
}

void LevelManager::decreaseRemainingLines(int lines) {
    remainingLinesToLevelUp -= lines;
}

bool LevelManager::shoudLevelUp() {
    return remainingLinesToLevelUp <= 0;
}

void LevelManager::levelUp() {
    level++;
    remainingLinesToLevelUp = LINES_TO_LEVEL_UP;
}

// Reference: https://tetris.wiki/Marathon
float LevelManager::calculateFallInterval() {
    return std::pow(0.8f - ((level - 1.0f) * 0.007f), (level - 1.0f));
}
