#include "LinesManager.hpp"
#include "constants/Constants.hpp"

LinesManager::LinesManager() {
    lines = 0;
}

void LinesManager::addLines(int lines) {
    this->lines += lines;
}

int LinesManager::getLines() {
    return lines;
}
