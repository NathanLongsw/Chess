#include "blank.h"
#include <iostream>

Blank::Blank(size_t r, size_t c) 
 {
     getRow() = r;
     getCol() = c; 
     getRank() = Rank::blank; 
     getColour() = Colour::NoColour;
     moves = generateMoves();
     setState(State{StateType::Standing, Colour::NoColour, r, c, Rank::blank});
}

vector<pair<int, int>> Blank::generateMoves() { return vector<pair<int, int>>(); }
