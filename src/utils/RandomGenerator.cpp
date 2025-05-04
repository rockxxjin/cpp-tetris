#include "RandomGenerator.hpp"
#include <random>

int RandomGenerator::get(int min, int max) {
    static thread_local std::mt19937 mt{std::random_device{}()};
    return std::uniform_int_distribution<int>{min, max}(mt);
}