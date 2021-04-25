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

void move(size_t r, size_t c) { 
    return;
}

void check(size_t r, size_t c) {
    return;
}

vector<pair<int, int>> Blank::generateMoves() noexcept {
    return vector<pair<int, int>>();
}
