#include "blank.h"
using namespace std;

Blank::Blank(size_t r, size_t c) {
     getRow() = r;
     getCol() = c; 
     getRank() = Rank::blank; 
     getColour() = Colour::NoColour;
     moves = generateMoves();
     setState(State{StateType::Standing, Colour::NoColour, r, c, Rank::blank});
}

virtual void move(size_t r, size_t c) { 
    return;
}

virtual void check(size_t r, size_t c) {
    return;
}

vector<pair<int, int>> Blank::generateMoves() {
    return vector<pair<int, int>>();
}
