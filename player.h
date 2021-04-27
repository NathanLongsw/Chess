#ifndef PLAYER_H
#define PLAYER_H
#include "state.h"
#include <memory>
#include <vector>

/*  Base class which enables the Strategy design pattern. Types of
    Players used in this program are humans and computers.  */

class Board;

/* Pure virtual class used for strategy design pattern */

class Player {
  protected:
    // The player's colour
    Colour colour;

    // Pointer to the chess board
    Board* gameboard;

  public:
    Player(Board *Board, Colour colour);
    virtual ~Player();

    // Pure virtual method used to play a move
    virtual void play() = 0;
};

#endif
