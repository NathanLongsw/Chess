#ifndef HUMAN_H
#define HUMAN_H
#include "player.h"

/* Derived class which inhertis from Player */

class Board;

class Human: public Player {
  public:
    Human(Board *gameboard, Colour colour);
    virtual ~Human();
    void play() override;
};


#endif
