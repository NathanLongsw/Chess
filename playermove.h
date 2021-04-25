#ifndef _PLAYERMOVE_H
#define _PLAYERMOVE_H
#include <memory>
#include "piece.h"
#include "state.h"


struct Position{
    char col;
    size_t row;
    bool operator==(const Position &other){
        return other.row == row && other.col == col;
    }
    bool operator!=(const Position &other){
        return !(*this == other);
    }
    Position(char c, size_t r) : col{c}, row{r} {}
};




class PlayerMove final{
private:
    Position fromPos;
    Position toPos;
    bool first;
    Rank from;
    Rank captured;
    char moveType;

public:
    PlayerMove(char fromcol, size_t fromrow, char tocol, size_t torow, bool first,  Rank from, Rank captured, char moveType);
    Position getFrom() const;
    Position getTo() const;
    Rank getCaptured() const;
    Rank getRankFrom() const;
    char getMoveType() const;
    bool getFirst() const;
};

#endif
