#ifndef PLAYER_H
#define PLAYER_H
#include "state.h"
#include <memory>
#include <vector>

class Board;

/* Pure virtual class used for strategy design pattern */

enum class PlayerType {Human, C1, C2, C3, C4 };

class Player {
  protected:
    Colour colour;
    Board* gameboard;
  public:
    Player(Board *Board, Colour colour);
    virtual ~Player();
    virtual void play() = 0;
};

#endif
