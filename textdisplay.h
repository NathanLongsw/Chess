#ifndef _TEXTDISPLAY_H_
#define _TEXTDISPLAY_H_
#include <iostream>
#include <vector>
#include "piece.h"

/* This class is class derived from the class Observer. It is used to store 
   the text display of the chess board. */

class TextDisplay : public Observer<Info, State> {
    std::vector<std::vector<char>> theDisplay;

    // Returns appropariate char for black or white square
    char squareChar(int row, int col) const noexcept;

    // Returns appropriate char icon for peice of specific colour
    char getIcon(Colour colour, Rank rank) const noexcept; 

public:
    // Constructs a board of empty squares
    TextDisplay();

    // Reacts to changes in Piece position 
    void notify(Subject<Info, State> &whoNotified) override;

    // Prints display
    friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};

#endif
