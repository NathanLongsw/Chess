#ifndef KING_H
#define KING_H
#include "piece.h"

/* Derived class which inhertis from Piece */

class King : public Piece {
    // bool to determine if the king has played its first move
    bool first = true;

  public:
    King(size_t r, size_t c, Colour col);
    void move(size_t r, size_t c) override;
    void check(size_t r, size_t c) override;
    std::vector<std::pair<int, int>> generateMoves() noexcept override;
};

#endif
