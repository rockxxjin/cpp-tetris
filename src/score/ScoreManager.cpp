#include "ScoreManager.hpp"
#include "constants/Constants.hpp"
#include <string>

ScoreManager::ScoreManager() {
    score = 0;
}

void ScoreManager::addScore(int score) {
    this->score += score;
}

int ScoreManager::calculateScore(int lines, int level) {
    int score = 0;
    static constexpr int lineClearScores[5] = {0, 100, 300, 500, 800};
    if (lines < 1 or lines > 4) {
        return 0;
    }
    return lineClearScores[lines] * level;
}

int ScoreManager::getScore() {
    return score;
}
