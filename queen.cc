#include "queen.h"
using namespace std;

Queen::Queen(size_t r, size_t c, Colour col) {
    getRow() = r;
    getCol() = c;
    getColour() = col;
    getRank() = Rank::q;
}

void Queen::move(size_t r, size_t c) {
    if ((abs_diff(c, getInfo().col) != abs_diff(r, getInfo().row)) &&
        (getInfo().col != c && getInfo().row != r))
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

// Make sure no pieces in between
void Queen::check(size_t r, size_t c) {
    if (abs_diff(c, getInfo().col) != abs_diff(r, getInfo().row) &&
        getInfo().col != c && getInfo().row != r)
        return;
    Colour op = getInfo().colour == Colour::White ? Colour::Black : Colour::White;
    throw checkException(op, getInfo().row, getInfo().col, getInfo().rank);
}

vector<pair<int, int>> Queen::generateMoves() {
    size_t r = getRow();
    size_t c = getCol();
    vector<pair<int, int>> ret;
    for (int i = r + 1; i < 8; ++i) {
        if (r + c - i > 8)
            break;
        ret.push_back({i, i});
    }
    for (int i = r - 1; i >= 0; --i) {
        if (r + c - i > 0)
            break;
        ret.push_back({i, i});
    }
    int k = c + 1;
    for (int i = r + 1; i < 8; ++i) {
        if (k > 8)
            break;
        ret.push_back({i, k});
        k++;
    }
    int j = c - 1;
    for (int i = r + 1; i < 8; ++i) {
        if (j < 0)
            break;
        ret.push_back({i, j});
        j--;
    }
    for (int i = r + 1; i < 8; ++i) {
        ret.push_back({r, i});
    }
    for (int i = r - 1; i >= 0; --i) {
        ret.push_back({r, i});
    }
    for (int i = c + 1; i < 8; ++i) {
        ret.push_back({i, c});
    }
    for (int i = c - 1; i < 8; ++i) {
        ret.push_back({i, r});
    }
    return ret;
}
