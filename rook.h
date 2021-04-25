#ifndef ROOK_H
#define ROOK_H
#include "piece.h"

class Rook : public Piece {
  public:
  Rook(size_t r, size_t c, Colour col);
   void move(size_t r, size_t c) override;
   void check(size_t r, size_t c) override;
   vector<pair<int, int>> generateMoves() override;
};

#endif
