#ifndef COMPUTER2_H
#define COMPUTER2_H
#include <stdlib.h>
#include "computer1.h"

/* Derived class which inhertis from Computer1 */

class Board;

class Computer2: public Computer1 {
protected:
    Colour getEnemyColour() const noexcept;
    void playCapture();
public:
    Computer2(Board* gameboard, Colour colour, unsigned);
    virtual ~Computer2();
    void play() override;
};

#endif
