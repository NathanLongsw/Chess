#ifndef COMPUTER3_H
#define COMPUTER3_H
#include "computer2.h"

/*  Derived class which inhertis from Computer2. Prioritizes moving its
    pieces out of danger. If no pieces in danger, plays like Computer2. */

class Computer3: public Computer2 {
    // Determines if position row, col is at risk of being captured
    bool positionatRisk(int row, int col) noexcept;

public:
    Computer3(Board *gameboard, Colour colour, unsigned);
    virtual ~Computer3();
    void play() override;
};

#endif
