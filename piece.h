#ifndef PIECE_H_
#define PIECE_H_
#include <cstddef>
#include <vector>
#include "info.h"
#include "observer.h"
#include "state.h"
#include "subject.h"

/* Derived class which inhertis from Subject and Observer */

class Piece : public Subject<Info, State>, public Observer<Info, State> {
    size_t row, col;
    Colour colour = Colour::NoColour;
    Rank rank = Rank::blank;

    // Vector of possible moves for a piece
    std::vector<std::pair<int, int>> moves;

    // Bool to determine if the king has played its first move
    bool first = true;

    // Bool to determine if a pawn can be taken en passant
    bool pass = false;

    // Used to determine if a piece is blocking another piece's move
    bool inBetween(size_t, size_t, size_t, size_t, size_t, size_t) const noexcept;

public:
    Piece();
    Piece(size_t r, size_t c);
    Piece(size_t r, size_t c, Rank R, Colour col);

    // Moves this piece
    virtual void move(size_t r, size_t c) = 0;

    // Determines if this piece puts the king in check
    virtual void check(size_t r, size_t c) = 0;

    // Generates all valid moves for this piece
    virtual std::vector<std::pair<int, int>> generateMoves() noexcept = 0;

    // Set this piece at row r and column c
    void setPiece(Rank t, Colour colour, size_t r, size_t c);

    // Ensures valid move and checks (No blocks, diff colour, &c)
    virtual void notify(Subject<Info, State> &whoFrom) override;

    // Getters to access this piece's fields
    Info getInfo() const noexcept override;

    // Getters to return by reference in order for class Board to modify them
    size_t &getRow() noexcept;
    size_t &getCol() noexcept;
    bool &getFirst() noexcept;
    bool &getPass() noexcept;
    Rank &getRank() noexcept;
    Colour &getColour() noexcept;
};

// Class to indicate invalid moves
class InvalidMoveException {};

// Class to indicate checks
class checkException {
    Colour colour;
    size_t row, col;
    Rank rank;

public:
    checkException(Colour c, size_t r, size_t co, Rank ra): colour{c}, row{r}, col{co}, rank{ra} {}

    // Getters to access the checkException's fields
    Colour getColour() const noexcept {return colour; }
    Rank getRank() const noexcept { return rank; }
    size_t getRow() const noexcept { return row; }
    size_t getCol() const noexcept { return col; }
};

// Template function to get the absolute difference between a and b
template<typename T>
T abs_diff(T a, T b) {
    return a > b ? a - b : b - a;
}

#endif
