#include "board.h"
#include "blank.h"
#include "rook.h"
#include "pawn.h"
#include "bishop.h"
#include "knight.h"
#include "queen.h"
#include "king.h"
using namespace std;

Board::Board(bool graphics): graphics{graphics} {}

void Board::init() {
	pieces.clear();
	moves.clear();
	td = make_shared<TextDisplay>();
    if (graphics) gd = make_shared<GraphicsDisplay>();
	for (size_t i = 0; i < 8; i++) {
		vector<shared_ptr<Piece>> row;
		for (size_t j = 0; j < 8; j++) {
			row.emplace_back(make_shared<Blank>(i, j));
		}
		pieces.push_back(row);
	}
	attachPieces();
}

void Board::play(Colour colour) {
    try {
        colour == Colour::White ? white->play() : black->play();
    } catch (InvalidMoveException) {
        throw;
    } catch (checkException &c) {
        throw;
    } catch (staleMateException) {
        throw;
    } catch (checkMateException &cm) {
        throw;
    }
}

void Board::initPlayers(unsigned seed) {
    string whitePlayer, blackPlayer;
	cin >> whitePlayer >> blackPlayer;

	if(whitePlayer == "human") white = make_shared<Human>(this, Colour::White); 
	else if(whitePlayer == "computer1") white = make_shared<Computer1>(this, Colour::White, seed);
	else if(whitePlayer == "computer2") white = make_shared<Computer2>(this, Colour::White, seed); 
	else if(whitePlayer == "computer3") white = make_shared<Computer3>(this, Colour::White, seed);
	if(blackPlayer == "human") black = make_shared<Human>(this, Colour::Black);
	else if(blackPlayer == "computer1") black = make_shared<Computer1>(this, Colour::Black, seed);
	else if(blackPlayer == "computer2") black = make_shared<Computer2>(this, Colour::Black, seed); 
	else if(blackPlayer == "computer3") black = make_shared<Computer3>(this, Colour::Black, seed);

	if (white && black) {
        for (size_t i = 0; i < 8; ++i) {
            for (size_t j = 0; j < 8; ++j) {
                if (pieces[i][j]->getInfo().rank == Rank::k) {
                    if (pieces[i][j]->getInfo().colour == Colour::White) {
                        wRow = i;
                        wCol = j;
                    } else {
                        bRow = i;
                        bCol = j;
                    }
                }
            }
        }
	    cout << *this;
        return;
	}
	throw InvalidPlayer{};
}

void Board::attachPieces(const int n) {
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			pieces[i][j]->attach(td.get());
			if (graphics) pieces[i][j]->attach(gd.get());
			for (int r = max((i - 1), 0); r <= min((i + 1), (n - 1)); ++r) {
				for (int c = max((j - 1), 0); c <= min((j + 1), (n - 1)); ++c) {
					if (!(r == i && c == j)) pieces[i][j]->attach(pieces[r][c].get());
				}
			}
		}
	}
}

void Board::detachPiece(Piece *p) {
	int i = p->getRow();
	int j = p->getCol();
	p->detach(td.get());
	if (graphics) p->detach(gd.get());
	for (int r = max((i - 1), 0); r <= min((i + 1), 7); r++) {
		for (int c = max((j - 1), 0); c <= min((j + 1), 7); c++) {
			if (!(r == i && c == j)) {
				pieces[r][c]->detach(p);
			    p->detach(pieces[r][c].get());
			}
		}
	}
}

void Board::attach(Piece *p) {
	int i = p->getRow();
	int j = p->getCol();
	p->attach(td.get());
	if (graphics) p->attach(gd.get());
	for (int r = max((i - 1), 0); r <= min((i + 1), 7); r++) {
		for (int c = max((j - 1), 0); c <= min((j + 1), 7); c++) {
			if (!(r == i && c == j)) {
				pieces[r][c]->attach(p);
				p->attach(pieces[r][c].get());
			}
		}
	}
}

void Board::setPiece(size_t r, size_t c, Rank rank, Colour colour) {
	if ((r > 7 || r < 0) || (c > 7 || c < 0) ||
		(rank == Rank::blank && pieces[r][c]->getInfo().rank == Rank::blank))
		throw InvalidMoveException{};

	detachPiece(pieces[r][c].get());

	if (rank == Rank::r)
		pieces[r][c] = make_shared<Rook>(r, c, colour); 
	else if (rank == Rank::p)
		pieces[r][c] = make_shared<Pawn>(r, c, colour);
	else if (rank == Rank::k)
		pieces[r][c] = make_shared<King>(r, c, colour);
	else if (rank == Rank::q)
		pieces[r][c] = make_shared<Queen>(r, c, colour);
	else if (rank == Rank::n)
		pieces[r][c] = make_shared<Knight>(r, c, colour);
	else if (rank == Rank::b)
		pieces[r][c] = make_shared<Bishop>(r, c, colour);
	else
		pieces[r][c] = make_shared<Blank>(r, c);
	
	if (r == passRow && c == passCol && rank == Rank::blank) 
	    pieces[passRow][passCol]->getPass() = true;

	attach(pieces[r][c].get());
	pieces[r][c]->setPiece(rank, colour, r, c);
}

bool Board::inCheckmate(size_t atRow, size_t atCol, Rank atRank, Colour atColour) {
	Colour myColour = atColour == Colour::White ? Colour::Black : Colour::White;
	size_t kRow = myColour == Colour::White ? wRow : bRow;
	size_t kCol = myColour == Colour::White ? wCol : bCol;
	size_t tempRow = kRow;
	size_t tempCol = kCol;

	for (auto & n : pieces) {
		for (auto p : n) {
			if (p->getColour() != myColour) continue;
			try {
				move(p->getInfo().col + 'a', p->getInfo().row + 1, atCol + 'a', atRow + 1, myColour);
				undo(myColour, true);
				myColour == Colour::White ? wRow = tempRow : bRow = tempRow;
	           	myColour == Colour::White ? wCol = tempCol : bCol = tempCol;
				return false;
			}
			catch (...) {
				myColour == Colour::White ? wRow = tempRow : bRow = tempRow;
	            myColour == Colour::White ? wCol = tempCol : bCol = tempCol;
				continue;
			}
		}
	}

	int lowCol = atCol < kCol ? atCol : kCol;
	int hiCol = atCol > kCol ? atCol : kCol;
	int lowRow = atRow < kRow  ? atRow : kRow;
	int hiRow = atRow > kRow ? atRow : kRow;


	if (atRank != Rank::n) {
		for (auto & n : pieces) {
			for (auto p : n) {
                if (p->getColour() != myColour)
                    continue;
                if (atRow == kRow) {
                    for (int l = lowCol + 1; l < hiCol; ++l) {
                        try {
                        move(p->getInfo().col + 'a', p->getInfo().row + 1, l + 'a', atRow + 1, myColour);
                        undo(myColour, true);
                        myColour == Colour::White ? wRow = tempRow : bRow = tempRow;
                        myColour == Colour::White ? wCol = tempCol : bCol = tempCol;
                        return false;
                        } catch(...) {
                            myColour == Colour::White ? wRow = tempRow : bRow = tempRow;
                            myColour == Colour::White ? wCol = tempCol : bCol = tempCol;
                            continue;
                        }
                    }
                }

                else if (atCol == kCol) {
                    for (int l = lowRow + 1; l < hiRow; ++l) {
                        try {
                        move( p->getInfo().col + 'a', p->getInfo().row + 1, atCol + 'a', l + 1, myColour);
                        myColour == Colour::White ? wRow = tempRow : bRow = tempRow;
                        myColour == Colour::White ? wCol = tempCol : bCol = tempCol;
                        undo(myColour, true);
                        return false;
                        } catch (...) {
                            myColour == Colour::White ? wRow = tempRow : bRow = tempRow;
                            myColour == Colour::White ? wCol = tempCol : bCol = tempCol;
                            continue;
                        }
                    }
                }
                int cc = 1;
                for (int l = lowRow + 1; l < hiRow; ++l) {
                    int col = lowCol + cc;
                    try {
                    move( p->getInfo().col + 'a', p->getInfo().row + 1, col + 'a', l + 1, myColour);
                    undo(myColour, true);
                    myColour == Colour::White ? wRow = tempRow : bRow = tempRow;
                    myColour == Colour::White ? wCol = tempCol : bCol = tempCol;
                    return false;
                    } catch (...) {
                        myColour == Colour::White ? wRow = tempRow : bRow = tempRow;
                        myColour == Colour::White ? wCol = tempCol : bCol = tempCol;
                        cc++;
                        continue;
                    }
                }
			}
		}
	}
	int intRow = kRow;
	int intCol = kCol;
	for (int r = max((intRow - 1), 0); r <= min((intRow + 1), 7); r++) {
		for (int c = max((intCol- 1), 0); c <= min((intCol + 1), 7); c++) {
			if (!(r == intRow && c == intCol))
				try {
					move(kCol + 'a', kRow + 1, c + 'a', r + 1, myColour);
					undo(myColour, true);
					myColour == Colour::White ? wRow = tempRow : bRow = tempRow;
	           		myColour == Colour::White ? wCol = tempCol : bCol = tempCol;
					return false;
				}
				catch (...)
				{
					myColour == Colour::White ? wRow = tempRow : bRow = tempRow;
	           		myColour == Colour::White ? wCol = tempCol : bCol = tempCol;
					continue;
				}
		}
	}
	return true;
}

bool Board::inStalemate(Colour colour) {
	if(colour == Colour::White && wCheck) return false;
	if(colour == Colour::Black && bCheck) return false;
    Info kingInfo {10, 10, Colour::NoColour, Rank::blank};
    for (const auto &n : pieces) {
        for (const auto &p : n) {
            if (p->getColour() == colour && p->getRank() == Rank::k) kingInfo = p->getInfo();
        }
    }
    if (kingInfo.colour == Colour::NoColour) return true;
    for (const auto &n : pieces) {
        for (const auto &p : n) {
            if (p->getColour() != colour) continue;
            vector<pair<int, int>> validmoves = p->generateMoves();
            for (const auto &i : validmoves) {
                if ((i.first > 7) || (i.first  < 0) || (i.second  > 7) || (i.second < 0)) continue;
                
                auto toInfo = pieces[i.first][i.second]->getInfo();
                auto fromInfo = p->getInfo();

                if (toInfo.colour == colour) continue;

                Rank rankTo = toInfo.rank;

                size_t fromRowAdj = static_cast<size_t>(fromInfo.row);
                size_t fromColAdj = static_cast<size_t>(fromInfo.col);
                size_t toRowAdj = static_cast<size_t>(i.first);
                size_t toColAdj = static_cast<size_t>(i.second);
		    
                if (toRowAdj == wRow && toColAdj == wCol) continue;
                if (toRowAdj == bRow && toColAdj == bCol) continue;

                size_t castleRow = 0, castleCol = 0;
                char moveType = 'd';

                try {
                    p->move(i.first, i.second);

                    //Castling logic
                    if (fromInfo.rank == Rank::k && abs_diff(fromColAdj, toColAdj) == 2) {
                        if ((colour == Colour::White && wCheck) || (colour == Colour::Black && bCheck))
                            throw InvalidMoveException{};

                        if (fromInfo.colour == Colour::White) castleRow = 0;
                        else castleRow = 7;
                        
                        if (fromColAdj > toColAdj) castleCol = 3;
                        else castleCol = 5;

                        if (castleCol == 3) {
                            if (pieces[castleRow][castleCol - 3]->getInfo().rank == Rank::blank || 
                                !(pieces[castleRow][castleCol - 3]->getFirst() && pieces[fromRowAdj][fromColAdj]->getFirst()))
                                throw InvalidMoveException{};
                        }
                        else {
                            if (pieces[castleRow][castleCol + 2]->getInfo().rank == Rank::blank || 
                                !(pieces[castleRow][castleCol + 2]->getFirst() && pieces[fromRowAdj][fromColAdj]->getFirst()))
                                throw InvalidMoveException{};
                        }
                        moveType = 'c';
                    }
                    //En passant add colour determined condition for col
		            if (pieces[fromRowAdj][fromColAdj]->getRank() == Rank::p && 
                        ((colour==Colour::White && toRowAdj == passRow && toColAdj == passCol) || 
                        (colour==Colour::Black && toRowAdj == passRow && toColAdj == passCol))) {
                            moveType = 'e';
                            rankTo = Rank::p;
                    }
                }
                catch (...) {
                    continue;
                } if (moveType == 'c') {
                    if (castleCol == 3) {
                        setPiece(castleRow, castleCol - 3, Rank::blank, Colour::NoColour);
                    }
                    else {
                        setPiece(castleRow, castleCol + 2, Rank::blank, Colour::NoColour);
                    }
                    setPiece(castleRow, castleCol, Rank::r, colour);
                }
                else if (moveType == 'e') {
                    if (colour == Colour::White)
                        setPiece(passRow - 1, passCol, Rank::blank, Colour::NoColour);
                    else
                        setPiece(passRow+1, passCol, Rank::blank, Colour::NoColour);
                }
                setPiece(fromInfo.row, fromInfo.col, Rank::blank, Colour::NoColour);
                setPiece(i.first, i.second, fromInfo.rank, colour);
                moves.emplace_back('a'+fromInfo.col, fromInfo.row+1, 'a'+i.second, i.first+1, pieces[i.first][i.second]->getFirst(), fromInfo.rank, rankTo, moveType);
                if (fromInfo.rank != Rank::k) {
                    try {
                        pieces[kingInfo.row][kingInfo.col]->move(kingInfo.row, kingInfo.col);
                        undo(colour, true);
                        return false;
                    } catch (checkException &c) {
                        undo(colour, true);
                        continue;
                    }
                } else {
                    try {
                        pieces[i.first][i.second]->move(i.first, i.second);
                        undo(colour, true);
                        return false;
                    } catch (checkException &c) {
                        undo(colour, true);
                        continue;
                    }
                }
            }
        }
    }
    return true;
}

void Board::move(char fromCol, size_t fromRow, char toCol, size_t toRow, Colour colour) {
	if ((fromRow > 8 || fromRow < 1) || (toRow > 8 || toRow < 1) ||
		((fromCol - 'a') > 7 || (fromCol - 'a' < 0)) || ((toCol - 'a') > 7 || (toCol - 'a' < 0)))
		throw InvalidMoveException{};

	auto toInfo = pieces[toRow - 1][toCol - 'a']->getInfo();
	auto fromInfo = pieces[fromRow - 1][fromCol - 'a']->getInfo();
	if ((toInfo.colour == colour) || (fromInfo.colour != colour) || (fromInfo.rank == Rank::blank))
		throw InvalidMoveException{};

	if (inStalemate(colour)) throw staleMateException{};

	Rank rankTo = toInfo.rank;
	Rank rankFrom = fromInfo.rank;
	
	size_t fromRowAdj = static_cast<size_t>(fromRow - 1);
	size_t fromColAdj = static_cast<size_t>(fromCol - 'a');
	size_t toRowAdj = static_cast<size_t>(toRow - 1);
	size_t toColAdj = static_cast<size_t>(toCol - 'a');

	size_t castleRow = 0, castleCol = 0;
    char moveType = 'd';

	try {
		//Enssure no one's attacking kings
		if (toRowAdj == wRow && toColAdj == wCol) throw InvalidMoveException{};
		if (toRowAdj == bRow && toColAdj == bCol) throw InvalidMoveException{};
		//Ensure move is possible
		pieces[fromRow - 1][fromCol - 'a']->move(toRow - 1, toCol - 'a');
		//Castling logic
		if (fromRowAdj == wRow && fromColAdj == wCol && abs_diff(fromCol, toCol) == 2) {
			if (wCheck) {
                throw InvalidMoveException{};
            }
			castleRow = 0;

			if (fromCol > toCol)
				castleCol = 3;
			else
				castleCol = 5;

			if (castleCol == 3) {
				if (pieces[castleRow][castleCol - 3]->getInfo().rank == Rank::blank || 
                    !(pieces[castleRow][castleCol - 3]->getFirst() && pieces[wRow][wCol]->getFirst()))
					throw InvalidMoveException{};
			}
			else {
				if (pieces[castleRow][castleCol + 2]->getInfo().rank == Rank::blank || 
                    !(pieces[castleRow][castleCol + 2]->getFirst() && pieces[wRow][wCol]->getFirst()))
					throw InvalidMoveException{};
			}
			pieces[wRow][wCol]->move(0, castleCol);
            moveType = 'c';
		}

		else if (fromRowAdj == bRow && fromColAdj == bCol && abs_diff(fromCol, toCol) == 2) {
            if (bCheck) {
                throw InvalidMoveException{};
            }
			castleRow = 7;
            
			if (fromCol > toCol)
				castleCol = 3;
			else
				castleCol = 5;

			if (castleCol == 3) {
				if (pieces[castleRow][castleCol - 3]->getInfo().rank == Rank::blank || 
                    !(pieces[castleRow][castleCol - 3]->getFirst() && pieces[bRow][bCol]->getFirst()))
					throw InvalidMoveException{};
			}
			else {
				if (pieces[castleRow][castleCol + 2]->getInfo().rank == Rank::blank || 
                    !(pieces[castleRow][castleCol + 2]->getFirst() && pieces[bRow][bCol]->getFirst()))
					throw InvalidMoveException{};
			}
			pieces[bRow][bCol]->move(7, castleCol);
            moveType = 'c';
		}

		// promotion logic
		if ((toRow == 8 || toRow == 1) && fromInfo.rank == Rank::p) {
			if ((colour == Colour::White && dynamic_cast<Human*>(white.get())) || 
                (colour == Colour::Black && dynamic_cast<Human*>(black.get()))) {
                    char promote;
                    cin >> promote;
                    if (promote == 'r' || promote == 'R')
                        rankFrom = Rank::r;
                    else if (promote == 'n' || promote == 'N')
                        rankFrom = Rank::n;
                    else if (promote == 'b' || promote == 'B')
                        rankFrom = Rank::b;
                    else if (promote == 'q' || promote == 'Q')
                        rankFrom = Rank::q;
                    else
                        throw InvalidMoveException{};
            }
            else rankFrom = Rank::q;

			moveType = 'p';
		}

		//En passant add colour determined condition for col
		if (pieces[fromRow - 1][fromCol - 'a']->getRank() == Rank::p && 
            ((colour==Colour::White && toRow-1 == passRow && toColAdj == passCol) || 
	     (colour==Colour::Black && toRow-1 == passRow && toColAdj == passCol))) {
			moveType = 'e';
			rankTo = Rank::p;
		}

		//Update kings positions
		if (fromRowAdj == wRow && fromColAdj == wCol) {
			wRow = toRow - 1;
			wCol = toCol - 'a';
		}
		if (fromRowAdj== bRow && fromColAdj == bCol) {
			bRow = toRow - 1;
			bCol = toCol - 'a';
		}
	}
	catch (...) {
		throw InvalidMoveException{};
	}
	if (moveType == 'c') {
		if (castleCol == 3) {
			setPiece(castleRow, castleCol - 3, Rank::blank, Colour::NoColour);
		}
		else {
			setPiece(castleRow, castleCol + 2, Rank::blank, Colour::NoColour);
		}
		setPiece(castleRow, castleCol, Rank::r, colour);
	}
	else if (moveType == 'e') {
		if (colour == Colour::White)
			setPiece(passRow - 1, passCol, Rank::blank, Colour::NoColour);
		else
			setPiece(passRow +1, passCol, Rank::blank, Colour::NoColour);
	}
	setPiece(toRow - 1, toCol - 'a', rankFrom, colour);
	setPiece(fromRow - 1, fromCol - 'a', Rank::blank, Colour::NoColour);

	moves.emplace_back(fromCol, fromRow, toCol, toRow, pieces[toRow - 1][toCol - 'a']->getFirst(), rankFrom, rankTo, moveType);
	pieces[toRow - 1][toCol - 'a']->getFirst() = false;
	
	//New pass is allowed
	if (rankFrom == Rank::p && abs_diff(toRow, fromRow) == 2) {
		 if (passCol >= 0 && passCol < 9) 
            pieces[passRow][passCol]->getPass() = false;
        
		if (colour == Colour::White) passRow = toRow - 2;
		else passRow = toRow;

		passCol = toCol - 'a';
        pieces[passRow][passCol]->getPass() = true;
	}
    
    size_t toRowPass = static_cast<size_t>(toRow - 2);
	//Reset old pass and move to impossible position
    if ((passCol > 0 && passCol < 9) && !((passRow == toRowPass || passRow == toRow ) && passCol == toColAdj)) {
        pieces[passRow][passCol]->getPass() = false;
        passRow = 10;
        passCol = 10;
    }
	try {
		if (wCheck) {
			pieces[wRow][wCol]->move(wRow, wCol);
			wCheck = false;
		} if (bCheck) {
			pieces[bRow][bCol]->move(bRow, bCol);
			bCheck = false;
		}
		if (colour == Colour::White) {
			pieces[wRow][wCol]->move(wRow, wCol);
			wCheck = false;
			pieces[bRow][bCol]->move(bRow, bCol);
			bCheck = false;
		} else {
			pieces[bRow][bCol]->move(bRow, bCol);
			bCheck = false;
			pieces[wRow][wCol]->move(wRow, wCol);
			wCheck = false;
		}
	}
	catch (checkException &c) {
		if (c.getColour() == colour) {
			undo(colour);
			throw;
		}
		else {
			colour == Colour::Black ? wCheck = true : bCheck = true;
			if (inCheckmate(c.getRow(), c.getCol(), c.getRank(), colour))
				throw checkMateException{};
			throw;
		}
	}
}

void Board::undo(Colour colour, bool staleMate) {
	if (moves.empty()) throw UndoException{};
	PlayerMove lastMove = moves.back();
	Position from = lastMove.getFrom();
	Position to = lastMove.getTo();
	char moveType = lastMove.getMoveType();
	Rank rankFrom = pieces[to.row - 1][to.col - 'a']->getInfo().rank;
	Colour capturedColour = colour == Colour::Black ? Colour::White : Colour::Black;

	size_t toRow = static_cast<size_t>(to.row - 1);
    size_t toCol = static_cast<size_t>(to.col - 'a');
    if (!staleMate) {
        if (toRow == wRow && toCol == wCol) {
            wRow = from.row - 1;
            wCol = from.col - 'a';
        }
        if (toRow == bRow && toCol == bCol) {
            bRow = from.row - 1;
            bCol = from.col - 'a';
        }
    }

	// default or promotion moves
	if (moveType == 'd' || moveType == 'p') {
		// default moves
		if (moveType == 'd') 
            setPiece(from.row - 1, from.col - 'a', rankFrom, colour);
		// promotion moves
		else if (moveType == 'p')
			setPiece(from.row - 1, from.col - 'a', Rank::p, colour);

        if (!staleMate) {
            // reset en passant
            if (passCol == toCol) {
                pieces[passRow][passCol]->getPass() = false;
                passCol = 10;
                passRow = 10;
            }
        }

		if (lastMove.getCaptured() == Rank::blank) 
            setPiece(to.row - 1, to.col - 'a', Rank::blank, Colour::NoColour);
		else 
            setPiece(to.row - 1, to.col - 'a', lastMove.getCaptured(), capturedColour);
	}
	else if (moveType == 'e') {
		setPiece(from.row - 1, from.col - 'a', rankFrom, colour);
		setPiece(to.row - 1, to.col - 'a', Rank::blank, Colour::NoColour);
		setPiece(from.row - 1, to.col - 'a', rankFrom, capturedColour);
		
		if (!staleMate) {
		    if (capturedColour == Colour::White)
			passRow = from.row - 2;
		    else
			passRow = from.row;
		    passCol = to.col - 'a';
		    pieces[passRow][passCol]->getPass() = true;
		}
	}
	else {
		setPiece(from.row - 1, from.col - 'a', rankFrom, colour);
		setPiece(to.row - 1, to.col - 'a', Rank::blank, Colour::NoColour);
		if (to.row == 1) {
			if (to.col == 'c') {
				// long
				setPiece(0, 0, Rank::r, colour);
				setPiece(0, 3, Rank::blank, Colour::NoColour);
				pieces[0][0]->getFirst() = true;
			}
			if (to.col == 'g') {
				// short
				setPiece(0, 7, Rank::r, colour);
				setPiece(0, 5, Rank::blank, Colour::NoColour);
				pieces[0][7]->getFirst() = true;
			}
		}
		else {
			// black castle
			if (to.col == 'c') {
				// long
				setPiece(7, 0, Rank::r, colour);
				setPiece(7, 3, Rank::blank, Colour::NoColour);
				pieces[7][0]->getFirst() = true;
			}
			if (to.col == 'g') {
				// short
				setPiece(7, 7, Rank::r, colour);
				setPiece(7, 5, Rank::blank, Colour::NoColour);
				pieces[7][7]->getFirst() = true;
			}
		}
	}
	if (lastMove.getFirst()) pieces[from.row - 1][from.col - 'a']->getFirst() = true;
	moves.pop_back();
	if (!staleMate) {
		try {
			if(wCheck) {
				pieces[wRow][wCol]->move(wRow, wCol);
				wCheck = false;
			}
			if(bCheck) {
				pieces[bRow][bCol]->move(bRow, bCol);
				bCheck = false;
			}
			pieces[bRow][bCol]->move(bRow, bCol);
			wCheck = false;
			pieces[wRow][wCol]->move(wRow, wCol);
			bCheck = false;
		}
		catch (checkException &c) {
			c.getColour() == Colour::White ? wCheck = true : bCheck = true;
			throw;
		}
	}
}

vector<vector<shared_ptr<Piece>>> Board::getPieces() const noexcept {
	return pieces;
}

bool Board::canLeaveSetup() const {
	bool whiteKing = false, blackKing = false;
	for (int i = 0; i < 8; ++i) {
		if ((pieces[0][i]->getInfo().rank == Rank::p) || (pieces[7][i]->getInfo().rank == Rank::p))
			return false;
		for (int j = 0; j < 8; j++) {
			if (pieces[i][j]->getInfo().rank == Rank::k) {
				if (pieces[i][j]->getInfo().colour == Colour::White) {
					whiteKing = true;
					try {
						pieces[i][j]->move(i, j);
					}
					catch (checkException &c) {
						return false;
					}
				}
				else {
					blackKing = true;
					try {
						pieces[i][j]->move(i, j);
					}
					catch (checkException &c) {
						return false;
					}
				}
			}
		}
	}
	if (!(whiteKing && blackKing)) return false;
	return true;
}

void Board::printHistory() const {
	if (moves.empty()) throw UndoException{};
	char type;
	cin >> type;
	string cur = "White";
	for (const auto &n : moves) {
        string col = "";
        char rankfrom = 0, rankto = 0;
		if (type == 'a') {
			cout << cur + " played: " << n.getFrom().col << n.getFrom().row << " to " << n.getTo().col << n.getTo().row;
		} else if (type == 'd') {
			cout << cur + " played: ";
			if (n.getMoveType() == 'c') {
				if (n.getFrom().col > n.getTo().col) {
                    cout << "O-O-O";
                } else cout << "O-O";
			} else if (n.getMoveType() == 'p') {
                col = cols.at(n.getTo().col-'a');
                cout << "P-" << col;
                if (cur == "White") cout << n.getTo().row;
                else cout << 9-n.getTo().row; 
                rankfrom = cnvrsn.at(n.getRankFrom());
                cout << '(' << rankfrom << ')';
            } else if (n.getCaptured() != Rank::blank) {
                rankfrom = cnvrsn.at(n.getRankFrom());
                rankto = cnvrsn.at(n.getCaptured());
                cout << rankfrom << 'x' << rankto;
            } else {
                col = cols.at(n.getTo().col-'a');
                cout << cnvrsn.at(n.getRankFrom()) << '-' << col;
                if (cur == "White") cout << n.getTo().row;
                else cout << 9-n.getTo().row; 
            }
		} else {
			cout << "Invalid printing type, enter a for algebraic or d for descriptive" << endl;
			return;
		}
		cur = cur == "White" ? "Black" : "White";
        if (n.getMoveType() == 'e' && type == 'd') cout << " e.p";
        cout << endl;
    }
}

ostream &operator<<(ostream &out, const Board &b) {
	if (b.td != nullptr)
		out << *b.td;
	if (b.graphics) {
        (b.gd)->drawGraphics();
    }
	return out;
}
