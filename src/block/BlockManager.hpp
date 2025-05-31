#pragma once

#include "entities/Block.hpp"

class BlockManager {
  private:
    Block block;
    Block backupBlock;

  public:
    void generate();
    void backup();
    void restore();
    void rotate();
    void up();
    void down();
    void left();
    void right();
    void land();

    const Block& get() const;
};