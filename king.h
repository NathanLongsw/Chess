#ifndef KING_H
#define KING_H
#include "piece.h"

class King : public Piece {
    bool first = true;
  public:
    King(size_t r, size_t c, Colour col);
    void move(size_t r, size_t c) override;
    void check(size_t r, size_t c) override;
    std::vector<std::pair<int, int>> generateMoves() noexcept override;
};

#endif
