#ifndef QUEEN_H
#define QUEEN_H
#include "piece.h"

class Queen : public Piece {
  public:
   Queen(size_t r, size_t c, Colour col);
   void move(size_t r, size_t c) override;
   void check(size_t r, size_t c) override;
   vector<pair<int, int>> generateMoves() override;
};

#endif
