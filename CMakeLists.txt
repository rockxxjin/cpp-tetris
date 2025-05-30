cmake_minimum_required(VERSION 3.10.0)
project(tetris VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)

set(SOURCES
    src/main.cpp
    src/entities/Block.cpp
    src/core/Game.cpp
    src/utils/RandomGenerator.cpp
    src/score/ScoreManager.cpp
    src/score/ScoreRenderer.cpp
    src/lines/LinesManager.cpp
    src/lines/LinesRenderer.cpp
    src/title/TitleRenderer.cpp
    src/gameover/GameoverRenderer.cpp
    src/level/LevelManager.cpp
    src/level/LevelRenderer.cpp
    src/core/GameController.cpp
    src/board/BoardRenderer.cpp
    
    
)


add_executable(tetris ${SOURCES})

target_include_directories(tetris PRIVATE ${PROJECT_SOURCE_DIR}/src)
target_link_libraries(tetris sfml-graphics sfml-window sfml-system)