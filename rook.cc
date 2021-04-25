#include "rook.h"
#include <iostream>

Rook::Rook(size_t r, size_t c, Colour col)
{
    getRow() = r;
    getCol() = c;
    getColour() = col;
    getRank() = Rank::r;
}

void Rook::move(size_t r, size_t c)
{
    if (getInfo().col != c && getInfo().row != r)
        throw InvalidMoveException();
    try
    {
        setState(State{StateType::Moving, getInfo().colour, r, c, getInfo().rank});
        notifyObservers();
    }
    catch (...)
    {
        setState(State{StateType::Standing, getInfo().colour, r, c, getInfo().rank});
        throw;
    }
}

void Rook::check(size_t r, size_t c)
{
    if (getInfo().col != c && getInfo().row != r)
        return;
    Colour op = getInfo().colour == Colour::White ? Colour::Black : Colour::White;
    throw checkException(op, getInfo().row, getInfo().col, getInfo().rank);
}

vector<pair<int, int>> Rook::generateMoves()
{
    size_t r = getRow();
    size_t c = getCol();
    vector<pair<int, int>> ret;
    for (int i = r + 1; i < 8; ++i)
    {
        ret.push_back({r, i});
    }
    for (int i = r - 1; i >= 0; --i)
    {
        ret.push_back({r, i});
    }
    for (int i = c + 1; i < 8; ++i)
    {
        ret.push_back({i, c});
    }
    for (int i = c - 1; i < 8; ++i)
    {
        ret.push_back({i, r});
    }
    return ret;
}
