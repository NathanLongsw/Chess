#ifndef PAWN_H
#define PAWN_H
#include "piece.h"

/* Derived class which inhertis from Piece */

class Pawn : public Piece {
  public:
   Pawn(size_t r, size_t c, Colour col);
   void move(size_t r, size_t c) override;
   void check(size_t, size_t c) override;
   std::vector<std::pair<int, int>> generateMoves() noexcept override;
};

#endif
