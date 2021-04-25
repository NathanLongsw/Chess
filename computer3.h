#ifndef COMPUTER3_H
#define COMPUTER3_H
#include "computer2.h"

/* Derived class which inhertis from Computer2 */

class Computer3: public Computer2 {
    bool positionatRisk(int row, int col) noexcept;

public:
    Computer3(Board *gameboard, Colour colour, unsigned);
    virtual ~Computer3();
    void play() override;
};

#endif
