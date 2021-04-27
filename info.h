#ifndef __INFO_H__
#define __INFO_H__
#include <cstddef>
#include "state.h"

/*  Struct to store information regarding the position, colour and rank (type)
    of a Piece.  */   

struct Info {
    size_t row, col;
    Colour colour;
    Rank rank;
};

#endif
