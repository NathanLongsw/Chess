#ifndef STATE_H
#define STATE_H
#include <stddef.h>

/* State types are:
    NewPiece -- I am a new piece.  I was just placed on the board.  I'm letting
                you know that I exist, and to remove yourself if you were in my square.

    Castling -- Specific state for king when castling

    Moving -- I am requesting to move to a position

    Standing -- Default. I am not moving and have not been captured.

    Check -- A testing state, making sure no piece is between me and the king
*/

enum class StateType { NewPiece, Castling, Moving, Standing, Check};
enum class Colour { NoColour, Black, White };
enum class Rank { p, r, n, b, k, q, blank };

struct State {
    StateType type; 
    Colour colour; 
    size_t row;
    size_t col;
    Rank rank;
};

#endif
