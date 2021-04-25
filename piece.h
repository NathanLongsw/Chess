#ifndef PIECE_H_
#define PIECE_H_
#include <cstddef>
#include <vector>
#include "info.h"
#include "observer.h"
#include "state.h"
#include "subject.h"

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
    std::vector<std::pair<int, int>> moves;
    bool inBetween(size_t, size_t, size_t, size_t, size_t, size_t) const noexcept;

public:
    Piece() {};
    Piece(size_t r, size_t c);
    Piece(size_t r, size_t c, Rank R, Colour col);
    virtual void move(size_t r, size_t c) = 0;
    virtual void check(size_t r, size_t c) = 0;
    virtual std::vector<std::pair<int, int>> generateMoves() noexcept = 0;
    void setPiece(Rank t, Colour colour, size_t r, size_t c);
    virtual void notify(Subject<Info, State> &whoFrom) override; 
    Info getInfo() const noexcept override;
    size_t &getRow() noexcept;
    size_t &getCol() noexcept;
    bool &getFirst() noexcept;
    bool &getPass() noexcept;
    Rank &getRank() noexcept;
    Colour &getColour() noexcept;
};

class InvalidMoveException {};

class checkException{
    Colour colour;
    size_t row, col;
    Rank rank;

public:
    checkException(Colour c, size_t r, size_t co, Rank ra): colour{c}, row{r}, col{co}, rank{ra} {}
    Colour getColour() const noexcept {return colour; }
    Rank getRank() const noexcept { return rank; }
    size_t getRow() const noexcept { return row; }
    size_t getCol() const noexcept { return col; }
};

#endif
