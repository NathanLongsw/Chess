#include "pawn.h"
using namespace std;

Pawn::Pawn(size_t r, size_t c, Colour col) {
  getRow() = r;
  getCol() = c;
  getColour() = col;
  getRank() = Rank::p;
}

void Pawn::move(size_t r, size_t c) {
  //Ensure piece can physically move to this square (For pawn one square forward, except: first move by this pawn, en passant and capture)
  if (abs_diff(getInfo().col, c) > 1 ||
      //Not first should only move up by 1
      (!getFirst() && abs_diff(r, getInfo().row) != 1) ||

      //If moving diagonally can only move by 1
      (abs_diff(getInfo().col, c) == 1 && abs_diff(r, getInfo().row) != 1) ||

      //First move can move max 2 rows min 1
      (getFirst() && ((abs_diff(r, getInfo().row) > 2) || abs_diff(r, getInfo().row) == 0)) ||

      //If moving 2 rows can only be at starting row
      ((abs_diff(r, getInfo().row) == 2) && ((getColour() == Colour::White && getInfo().row != 1) || (getColour() == Colour::Black && getInfo().row != 6))) ||

      //Must move in appropriate direction
      ((getInfo().colour == Colour::Black && r > getInfo().row) || (getInfo().colour == Colour::White && r < getInfo().row)))
    throw InvalidMoveException();
  try {
    setState(State{StateType::Moving, getInfo().colour, r, c, getInfo().rank});
    notifyObservers();
  }
  catch (...) {
    setState(State{StateType::Standing, getInfo().colour, r, c, getInfo().rank});
    throw;
  }
}

void Pawn::check(size_t r, size_t c) {
  Colour op = getInfo().colour == Colour::White ? Colour::Black : Colour::White;
  if (getInfo().colour == Colour::White && r - getInfo().row == 1 &&
      abs_diff(c, getInfo().col) == 1)
    throw checkException(op, getInfo().row, getInfo().col, getInfo().rank);

  if (getInfo().colour == Colour::Black && getInfo().row - r == 1 &&
      abs_diff(getInfo().col, c) == 1)
    throw checkException(op, getInfo().row, getInfo().col, getInfo().rank);
}

vector<pair<int, int>> Pawn::generateMoves() {
  size_t r = getRow();
  size_t c = getCol();
  vector<pair<int, int>> ret;
  if (getFirst()) {
    if (getInfo().colour == Colour::White)
      ret.push_back({r + 2, c});
    else
      ret.push_back({r - 2, c});
  }
  if (getInfo().colour == Colour::White) {
    ret.push_back({r + 1, c});
    ret.push_back({r + 1, c - 1});
    ret.push_back({r + 1, c + 1});
  }
  else {
    ret.push_back({r - 1, c - 1});
    ret.push_back({r - 1, c + 1});
    ret.push_back({r - 1, c});
  }
  return ret;
}
