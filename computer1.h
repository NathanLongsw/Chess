#ifndef COMPUTER1_H
#define COMPUTER1_H
#include "player.h"
#include "piece.h"
#include <stdlib.h>

/* Derived class which inhertis from Player */

class Board;

class Computer1: public Player {
protected:
    std::vector<std::vector<std::shared_ptr<Piece>>> pieces;
    unsigned int seed;
    std::vector<std::shared_ptr<Piece>> getMyPieces() const;
    void playRandom();

public:
    Computer1(Board *gameboard, Colour colour, unsigned);
    virtual ~Computer1();
    virtual void play() override;
};

#endif
