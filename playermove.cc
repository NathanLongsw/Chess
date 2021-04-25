#include "playermove.h"

PlayerMove::PlayerMove(char fromcol, size_t fromrow, char tocol, size_t torow, bool first, Rank from, Rank captured, char moveType): fromPos{fromcol, fromrow}, toPos{tocol, torow}, first{first}, from{from}, captured{captured}, 
moveType{moveType} {}


Position PlayerMove::getFrom() const{
    return fromPos;
}

Position PlayerMove::getTo() const{
    return toPos;
}

bool PlayerMove::getFirst() const{
    return first;
}

Rank PlayerMove::getRankFrom() const{
    return from;
}

Rank PlayerMove::getCaptured() const{
    return captured;
}

char PlayerMove::getMoveType() const{
    return moveType;
}
