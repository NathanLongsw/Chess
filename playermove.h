#ifndef _PLAYERMOVE_H
#define _PLAYERMOVE_H
#include <memory>
#include "state.h"

// Struct to store Piece position
struct Position {
    char col;
    size_t row;
    Position(char c, size_t r) : col{c}, row{r} {}
};

class PlayerMove {
private:
    Position fromPos;
    Position toPos;

    // Bool to determine if the king has played its first move
    bool first;

    // Stores the rank of the Piece at fromPos
    Rank from;

    // Stores the rank of the Piece at toPos
    Rank captured;

    /* Stores the type of the move
        d - default
        e - en passant
        p - pawn promotion
        c - castle */
    char moveType;

public:
    PlayerMove(char fromcol, size_t fromrow, char tocol, size_t torow, bool first,  Rank from, Rank captured, char moveType);

    // Getters to return private fields
    Position getFrom() const;
    Position getTo() const;
    Rank getCaptured() const;
    Rank getRankFrom() const;
    char getMoveType() const;
    bool getFirst() const;
};

#endif
