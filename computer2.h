#ifndef COMPUTER2_H
#define COMPUTER2_H
#include "computer1.h"

/* Derived class which inhertis from Computer1 */

class Computer2: public Computer1 {
protected: 
    // Returns the colour of the opposing Player
    Colour getEnemyColour() const noexcept;

    // Attemps to play a capturing move
    void playCapture();
public:
    Computer2(Board* gameboard, Colour colour, unsigned);
    virtual ~Computer2();
    void play() override;
};

#endif
