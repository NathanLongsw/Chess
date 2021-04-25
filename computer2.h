#ifndef COMPUTER2_H
#define COMPUTER2_H
#include <stdlib.h>
#include "computer1.h"

class Board;

class Computer2: public Computer1 {
protected:
    Colour getEnemyColour();
    void playCapture();
public:
    Computer2(Board* gameboard, Colour colour, unsigned);
    virtual ~Computer2();
    void play() override;
};

#endif
