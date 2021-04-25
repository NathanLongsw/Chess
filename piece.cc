#include "piece.h"

Piece::Piece(size_t r, size_t c) : row{r}, col{c}, colour{Colour::NoColour}, rank{Rank::blank} {}

Piece::Piece(size_t r, size_t c, Rank R, Colour col) : row{r}, col{c}, colour{col}, rank{R} {}

void Piece::setPiece(Rank t, Colour colour, size_t r, size_t c) {
    setState(State{StateType::Standing, colour, r, c, t});
    notifyObservers();
    moves = generateMoves();
}

bool inBetween(size_t row, size_t col, size_t fromRow, size_t fromCol, size_t toRow, size_t toCol) const noexcept {
    bool hor = ((row < toRow && row > fromRow) || (row > toRow && row < fromRow));

    bool ver = ((col < toCol && col > fromCol) || (col > toCol && col < fromCol));

    if (hor && (col == toCol) && (col == fromCol))
        return true;

    if (ver && (row == toRow) && (row == fromRow))
        return true;

    // Must ensure piece is in between to and from as before
    if (col != fromCol && fromCol != toCol) {
        size_t slope = abs_diff(row, fromRow) / abs_diff(col, fromCol);
        size_t moveSlope = abs_diff(toRow, fromRow) / abs_diff(toCol, fromCol);
        if ((ver && hor) && (slope == moveSlope))
            return true;
    }
    return false;
}

// Ensures valid move and checks (No blocks, diff colour, &c)
void Piece::notify(Subject<Info, State> &whoFrom) {
    if (whoFrom.getState().type == StateType::Standing ||
        whoFrom.getState().type == StateType::NewPiece)
        return;

    if (row == whoFrom.getState().row && col == whoFrom.getState().col && rank == Rank::k) return;

    //Ensures no piece in the way
    if (whoFrom.getState().rank != Rank::n && rank != Rank::blank && whoFrom.getState().type != StateType::Check)
        if (inBetween(row, col, whoFrom.getInfo().row, whoFrom.getInfo().col, whoFrom.getState().row, whoFrom.getState().col))
            throw InvalidMoveException{};
    

    if (whoFrom.getState().type == StateType::Castling) {
        if (getInfo().row == whoFrom.getState().row) {
            if (!inBetween(row, col, whoFrom.getInfo().row, whoFrom.getInfo().col, whoFrom.getState().row, whoFrom.getState().col))
                return;
            if (rank != Rank::blank)
                throw InvalidMoveException{};
            if (rank == Rank::r) {
                if (!getFirst())
                    throw InvalidMoveException{};
                if (colour != whoFrom.getState().colour)
                    throw InvalidMoveException{};
                return;
            }
            if ((col == 8 || col == 0) && rank != Rank::r)
                throw InvalidMoveException{};
             try {
                setState(State{whoFrom.getState().type, whoFrom.getState().colour, row, col, rank});
                notifyObservers();
            } catch(...) {
                setState(State{StateType::Standing, colour, row, col, rank});
                throw;
            }
            setState(State{StateType::Standing, colour, row, col, rank});
            return;
        }
        else return;
    }
    
    if (whoFrom.getState().type == StateType::Check && whoFrom.getState().colour != colour && colour != Colour::NoColour && 
        (whoFrom.getInfo().rank == Rank::blank || whoFrom.getInfo().rank == Rank::k || rank == Rank::n) && 
        (inBetween(whoFrom.getInfo().row, whoFrom.getInfo().col, row, col, whoFrom.getState().row, whoFrom.getState().col) || 
        whoFrom.getInfo().rank == Rank::k || rank == Rank::n) && (row != whoFrom.getState().row || col != whoFrom.getState().col)) {
        check(whoFrom.getState().row, whoFrom.getState().col);
    }

    if (row == whoFrom.getState().row && col == whoFrom.getState().col && whoFrom.getState().type != StateType::Check) {
        
        //Ensures pawn doesn't capture piece in front
        if (whoFrom.getState().rank == Rank::p) {
            if (whoFrom.getState().col == whoFrom.getInfo().col && rank != Rank::blank)
                throw InvalidMoveException{};
            if (whoFrom.getState().col != whoFrom.getInfo().col && rank == Rank::blank && !pass)
                throw InvalidMoveException{}; 
        }
        //Ensure piece doesn't capture same team
        if (colour == whoFrom.getState().colour) 
            throw InvalidMoveException{};
             
        return;
    }

    //If a blank square send message along
    if (rank == Rank::blank && whoFrom.getState().rank != Rank::n && getState().type != whoFrom.getState().type) {
        if (inBetween(row, col, whoFrom.getInfo().row, whoFrom.getInfo().col, whoFrom.getState().row, whoFrom.getState().col)) {
            //If I'm blank and in-between relay the message
            setState(State{whoFrom.getState().type, whoFrom.getState().colour, whoFrom.getState().row, whoFrom.getState().col, whoFrom.getState().rank});
            try {
                notifyObservers();
            } catch (...) {
                setState(State{StateType::Standing, Colour::NoColour, row, col, Rank::blank});
                throw;
            }
            setState(State{StateType::Standing, Colour::NoColour, row, col, Rank::blank});
            return;
        }
        else if (whoFrom.getState().type == StateType::Check && inBetween(whoFrom.getInfo().row, whoFrom.getInfo().col, row, col, whoFrom.getState().row, whoFrom.getState().col) && whoFrom.getInfo().rank == Rank::blank) {
            setState(State{whoFrom.getState().type, whoFrom.getState().colour, whoFrom.getState().row, whoFrom.getState().col, whoFrom.getState().rank});
            try {
                notifyObservers();
            } catch (...) {
                setState(State{StateType::Standing, Colour::NoColour, row, col, Rank::blank});
                throw;
            }
            setState(State{StateType::Standing, Colour::NoColour, row, col, Rank::blank});
            return;
        }
    }

    //Knight is specific
    if (whoFrom.getInfo().rank == Rank::n && whoFrom.getState().type != StateType::Check) {
        if (whoFrom.getState().row == row && whoFrom.getState().col != col) {
            try {
                setState(State{whoFrom.getState().type, whoFrom.getState().colour, whoFrom.getState().row, whoFrom.getState().col, whoFrom.getInfo().rank});
                notifyObservers();
            } catch(...) {
                setState(State{StateType::Standing, colour, row, col, rank});
                throw;
            }
            setState(State{StateType::Standing, colour, row, col, rank});
            return;
        }

        else if (whoFrom.getState().col == col && whoFrom.getState().row != row) {
            try {
                setState(State{whoFrom.getState().type, whoFrom.getState().colour, whoFrom.getState().row, whoFrom.getState().col, whoFrom.getInfo().rank});
                notifyObservers();
            } catch(...) {
                setState(State{StateType::Standing, colour, row, col, rank});
                throw;
            }
            setState(State{StateType::Standing, colour, row, col, rank});
            return;
        }
    }

    //Used to tell knight 1 piece away
   if (whoFrom.getInfo().rank == Rank::k && whoFrom.getState().type == StateType::Check) {
         try {
            setState(State{whoFrom.getState().type, whoFrom.getState().colour, whoFrom.getState().row, whoFrom.getState().col, whoFrom.getInfo().rank});
            notifyObservers();
        } catch(...) {
            setState(State{StateType::Standing, colour, row, col, rank});
            throw;
        }
        setState(State{StateType::Standing, colour, row, col, rank});
        return;
    }
}

Info Piece::getInfo() const noexcept {
    return Info{row, col, colour, rank};
}

size_t &getRow() noexcept {
    return row;
}

size_t &getCol() noexcept {
    return col;
}

bool &getFirst() noexcept {
    return first;
}

bool &getPass() noexcept {
    return pass;
}

Rank &getRank() noexcept {
    return rank;
}

Colour &getColour() noexcept {
    return colour;
}
