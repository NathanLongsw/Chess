#ifndef PAWN_H
#define PAWN_H
#include "piece.h"

class Pawn : public Piece {
  public:
   Pawn(size_t r, size_t c, Colour col);
   void move(size_t r, size_t c) override;
   void check(size_t, size_t c) override;
   vector<pair<int, int>> generateMoves() override;
};

#endif
