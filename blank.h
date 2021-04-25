#ifndef BLANK_H
#define BLANK_H
#include "piece.h"

class Blank : public Piece {
    std::vector<std::pair<int, int>> moves;
  public:
    Blank(size_t r, size_t c);
    virtual void move(size_t r, size_t c);
    virtual void check(size_t r, size_t c);
    virtual std::vector<std::pair<int, int>> generateMoves();
};

#endif
