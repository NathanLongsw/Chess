#ifndef STATE_H
#define STATE_H
#include <stddef.h>

/* State types are:
    NewPiece -- I am a new piece. I was just placed on the board. I'm letting
                you know that I exist.

    Castling -- Specific state for king when castling

    Moving -- I am requesting to move to a position

    Standing -- Default. I am not moving and have not been captured.

    Check -- A testing state, making sure no piece is between me and the king
*/

enum class StateType { NewPiece, Castling, Moving, Standing, Check};

// Used to store the colour of a Piece
enum class Colour { NoColour, Black, White };

// Used to store the rank (type) of a Piece
enum class Rank { p, r, n, b, k, q, blank };

struct State {
    StateType type; 
    Colour colour;

    // Position of the Piece
    size_t row, col;
    
    Rank rank;

};

#endif
