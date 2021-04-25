#ifndef PIECE_H_
#define PIECE_H_
#include <cstddef>
#include "info.h"
#include "observer.h"
#include "state.h"
#include "subject.h"
#include <vector>

using std::vector;
using std::pair;
using std::size_t;


template<typename T>
T abs_diff(T a, T b) {
    return a > b ? a - b : b - a;
}

class Piece : public Subject<Info, State>, public Observer<Info, State> {
    size_t row, col;
    Colour colour = Colour::NoColour;
    Rank rank = Rank::blank;
    bool first = true;
    bool pass = false;
    vector<pair<int, int>> moves;

public:
    Piece() {};
    Piece(size_t r, size_t c);
    Piece(size_t r, size_t c, Rank R, Colour col);
    virtual void move(size_t r, size_t c) = 0;
    virtual void check(size_t r, size_t c) = 0;
    virtual vector<pair<int, int>> generateMoves() = 0;
  //  void undo(size_t r, size_t c); //Invariants should allow piece to just move there
    void setPiece(Rank t, Colour colour, size_t r, size_t c); // Place a piece of given colour here.

    // Any piece that moves will call this overriden for king so he know if in check
    virtual void notify(Subject<Info, State> &whoFrom) override; 
    Info getInfo() const override;
    size_t &getRow() { return row; }
    size_t &getCol() { return col; }
    bool &getFirst() { return first; }
    bool &getPass() { return pass; }
    Rank &getRank() { return rank; }
    Colour &getColour() { return colour; }
};

class InvalidMoveException {};

//Row and Col
class checkException{
    Colour colour;
    size_t row, col;
    Rank rank;
    public:
    checkException(Colour c, size_t r, size_t co, Rank ra) : colour{c}, row{r}, col{co}, rank{ra} {}
    Colour getColour() const {return colour; }
    Rank getRank() const { return rank; }
    size_t getRow() const { return row; }
    size_t getCol() const { return col; }
};

#endif
