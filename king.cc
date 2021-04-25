#include <cstdlib>
#include <iostream>
#include "king.h"

King::King(size_t r, size_t c, Colour col)
{
    getRow() = r;
    getCol() = c;
    getColour() = col;
    getRank() = Rank::k;
}

void King::move(size_t r, size_t c)
{
    try
    {
        if (r == getInfo().row && c == getInfo().col)
        {

            setState(State{StateType::Check, getInfo().colour, r, c, getInfo().rank});
            notifyObservers();
            setState(State{StateType::Standing, getInfo().colour, r, c, getInfo().rank});
            return;
        }

        else if ((first && abs_diff(getInfo().col, c) == 2 && getInfo().row - r == 0) &&
                 ((getColour() == Colour::White && getRow() == 0) ||
                  (getColour() == Colour::Black && getRow() == 7)))
        {
            setState(State{StateType::Castling, getInfo().colour, r, c, getInfo().rank});
            notifyObservers();
        }
        else
        {
            if (abs_diff(getInfo().col, c) > 1 || abs_diff(getInfo().row, r) > 1)
                throw InvalidMoveException();
            setState(State{StateType::Moving, getInfo().colour, r, c, getInfo().rank});
            notifyObservers();
            
            setState(State{StateType::Check, getInfo().colour, r, c, getInfo().rank});
            notifyObservers();
        }
    }
    catch (...)
    {
        setState(State{StateType::Standing, getInfo().colour, r, c, getInfo().rank});
        throw;
    }
}

void King::check(size_t r, size_t c)
{
    Colour op = getInfo().colour == Colour::White ? Colour::Black : Colour::White;
    if (abs_diff(r, getInfo().row) <= 1 && abs_diff(c, getInfo().col) <= 1)
        throw checkException(op, getInfo().row, getInfo().col, getInfo().rank);
}

vector<pair<int, int>> King::generateMoves()
{
    size_t r = getRow();
    size_t c = getCol();
    vector<pair<int, int>> ret;
    if (r + 1 < 8 && c + 1 < 8)
        ret.push_back({r + 1, c + 1});
    if (r + 1 < 8 && c - 1 >= 0)
        ret.push_back({r + 1, c - 1});
    if (r - 1 >= 0 && c + 1 < 8)
        ret.push_back({r - 1, c + 1});
    if (r - 1 >= 0 && c - 1 >= 0)
        ret.push_back({r - 1, c - 1});
    if (r + 1 < 8)
        ret.push_back({r + 1, c});
    if (r - 1 >= 0)
        ret.push_back({r - 1, c});
    if (c + 1 < 8)
        ret.push_back({r, c + 1});
    if (c - 1 >= 0)
        ret.push_back({r, c - 1});
    if (first && ((r == 0 || r == 7) && c == 4))
    {
        ret.push_back({r, c + 2});
        ret.push_back({r, c - 2});
    }
    return ret;
}
