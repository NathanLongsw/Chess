#ifndef BLANK_H
#define BLANK_H
#include "piece.h"

class Blank : public Piece {
    std::vector<std::pair<int, int>> moves;
  public:
    Blank(size_t r, size_t c);
    void move(size_t r, size_t c) override;
    void check(size_t r, size_t c) override;
    virtual std::vector<std::pair<int, int>> generateMoves() noexcept;
};

#endif
