#ifndef BOARD_H
#define BOARD_H
#include <cstddef>
#include <iostream>
#include <vector>
#include <utility>
#include <memory>
#include <map>
#include "player.h"
#include "human.h"
#include "computer1.h"
#include "computer2.h"
#include "computer3.h"
#include "piece.h"
#include "playermove.h"

class GraphicsDisplay;
class TextDisplay;

template <typename InfoType, typename StateType> class Observer;

class UndoException {};
class staleMateException{};
class checkMateException{};
class InvalidPlayer{};

class Board {
    std::vector<std::vector<std::shared_ptr<Piece>>> pieces; // the actual board
    std::shared_ptr<Player> white = nullptr, black = nullptr; // players
    std::shared_ptr<TextDisplay> td = nullptr; // The text display
    std::shared_ptr<GraphicsDisplay> gd = nullptr;// The graphics display

    std::vector<PlayerMove> moves; // vector of previous moves
    bool graphics; // bool for graphics
    
    const std::map<Rank, char> cnvrsn = {{Rank::r,'R'},{Rank::n,'N'},{Rank::q,'Q'},{Rank::k,'K'},
                                        {Rank::b,'b'}, {Rank::p,'P'}, {Rank::blank,' '}};
    const std::map<int, std::string> cols = {{0,"QR"},{1,"QN"},{2,"QB"},{3,"Q"}, {4,"K"}, {5,"KB"},
                                        {6,"KN"}, {7,"KR"}};
    
    size_t wRow, wCol;
    size_t bRow = 10, bCol = 10;
    size_t passRow = 10, passCol = 10;
    bool wCheck = false, bCheck = false;
    
    void detachPiece(Piece* p);
    void attach(Piece* p);
    bool inCheckmate(size_t atRow, size_t atCol, Rank atRank, Colour atColour);
    bool inStalemate(Colour colour);
public:
    Board(bool graphics);
    void init();
    void play(Colour colour);
    void initPlayers(unsigned seed);
    void attachPieces(const int n = 8);
    void setPiece(size_t row, size_t col, Rank rank, Colour colour);
    void move(char fromCol, size_t fromRow, char toCol, size_t toRow, Colour colour); 
    std::vector<std::vector<std::shared_ptr<Piece>>> getPieces() const noexcept;
    void undo(Colour colour, bool staleMate = false);
    void printHistory() const;
    bool canLeaveSetup() const;
    friend std::ostream &operator<<(std::ostream &out, const Board &b);
};

#endif
