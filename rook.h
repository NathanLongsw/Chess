#ifndef ROOK_H
#define ROOK_H
#include "piece.h"

/* Derived class which inhertis from Piece */

class Rook : public Piece {
  public:
    Rook(size_t r, size_t c, Colour col);
    void move(size_t r, size_t c) override;
    void check(size_t r, size_t c) override;
    std::vector<std::pair<int, int>> generateMoves() noexcept override;
};

#endif
