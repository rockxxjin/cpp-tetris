cmake_minimum_required(VERSION 3.10.0)
project(tetris VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)

set(SOURCES
    src/main.cpp
    src/block/Block.cpp
    src/core/GameTable.cpp
    src/core/Game.cpp
    src/core/GameScore.cpp
    src/core/GameLevel.cpp
    src/core/GameLines.cpp
    src/core/GameTitle.cpp
    src/utils/RandomGenerator.cpp
)


add_executable(tetris ${SOURCES})

target_include_directories(tetris PRIVATE ${PROJECT_SOURCE_DIR}/src)
target_link_libraries(tetris sfml-graphics sfml-window sfml-system)