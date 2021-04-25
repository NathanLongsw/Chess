#ifndef _TEXTDISPLAY_H_
#define _TEXTDISPLAY_H_
#include <iostream>
#include <vector>
#include "piece.h"

class TextDisplay : public Observer<Info, State> {
    std::vector<std::vector<char>> theDisplay;
    char squareChar(int row, int col) const noexcept; // returns appropariate char for black or white square
    char getIcon(Colour colour, Rank rank) const noexcept; // returns appropriate char icon for peice of specific colour

public:
    TextDisplay(); // Constructor, empty square
    void notify(Subject<Info, State> &whoNotified) override; // reacts notifications
    friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td) const noexcept;
};

#endif
