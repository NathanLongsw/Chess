#include "bishop.h"
using namespace std;

Bishop::Bishop(size_t r, size_t c, Colour col) {
    getRow() = r;
    getCol() = c;
    getColour() = col;
    getRank() = Rank::b;
}

void Bishop::move(size_t r, size_t c) {
    if (abs_diff(c, getInfo().col) != abs_diff(r, getInfo().row))
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

void Bishop::check(size_t r, size_t c) {
    if (abs_diff(c, getInfo().col) != abs_diff(r, getInfo().row))
        return;
    Colour op = getInfo().colour == Colour::White ? Colour::Black : Colour::White;
    throw checkException(op, getInfo().row, getInfo().col, getInfo().rank);
}

vector<pair<int, int>> Bishop::generateMoves() noexcept {
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
    return ret;
}
