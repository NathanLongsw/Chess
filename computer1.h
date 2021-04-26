#ifndef COMPUTER1_H
#define COMPUTER1_H
#include "player.h"
#include "piece.h"
#include <stdlib.h>

class Board;

/* Derived class which inhertis from Player */

class Computer1: public Player {
protected:
    // Stores copy of the Board
    std::vector<std::vector<std::shared_ptr<Piece>>> pieces;

    // Seed for random number generation
    unsigned int seed;

    // Retrieves a copy of the Board
    std::vector<std::shared_ptr<Piece>> getMyPieces() const;

    // Plays a random move
    void playRandom();

public:
    Computer1(Board *gameboard, Colour colour, unsigned);
    virtual ~Computer1();
    void play() override;
};

#endif
