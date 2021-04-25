#include "knight.h"
using namespace std;

Knight::Knight(size_t r, size_t c, Colour col) {
    getRow() = r;
    getCol() = c;
    getColour() = col;
    getRank() = Rank::n;
}

void Knight::move(size_t r, size_t c) {
    if ((abs_diff(getInfo().col, c) != 2 || abs_diff(getInfo().row, r) != 1) &&
        (abs_diff(getInfo().col, c) != 1 || abs_diff(getInfo().row, r) != 2))
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

void Knight::check(size_t r, size_t c) {
    Colour op = getInfo().colour == Colour::White ? Colour::Black : Colour::White;
    if (abs_diff(getInfo().col, c) == 2 && abs_diff(getInfo().row, r) == 1)
        throw checkException(op, getInfo().row, getInfo().col, getInfo().rank);

    if (abs_diff(getInfo().col, c) == 1 && abs_diff(getInfo().row, r) == 2)
        throw checkException(op, getInfo().row, getInfo().col, getInfo().rank);
}

vector<pair<int, int>> Knight::generateMoves() {
    size_t r = getRow();
    size_t c = getCol();
    vector<pair<int, int>> ret;
    if (r + 2 < 8) {
        if (c + 1 < 8)
            ret.push_back({r + 2, c + 1});
        if (c - 1 >= 0)
            ret.push_back({r + 2, c - 1});
    }
    if (r + 1 < 8) {
        if (c + 2 < 8)
            ret.push_back({r + 1, c + 2});
        if (c - 2 >= 0)
            ret.push_back({r + 1, c - 2});
    }
    if (r - 2 >= 0) {
        if (c + 1 < 8)
            ret.push_back({r - 2, c + 1});
        if (c - 1 >= 0)
            ret.push_back({r - 2, c - 1});
    }
    if (r - 1 >= 0) {
        if (c + 2 < 8)
            ret.push_back({r - 1, c + 2});
        if (c - 2 >= 0)
            ret.push_back({r - 1, c - 2});
    }
    return ret;
}
