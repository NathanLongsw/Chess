#ifndef BOARD_H
#define BOARD_H
#include <cstddef>
#include <iostream>
#include <vector>
#include <utility>
#include <memory>
#include <map>
#include "human.h"
#include "computer1.h"
#include "computer2.h"
#include "computer3.h"
#include "piece.h"
#include "playermove.h"
#include "textdisplay.h"
#include "graphicsdisplay.h"

template <typename InfoType, typename StateType> class Observer;

/*  This class handles the collection of pieces on the board, the 
    players and the displays.  */

class Board {
    // The actual board
    std::vector<std::vector<std::shared_ptr<Piece>>> pieces;

    // Pointers to Players
    std::shared_ptr<Player> white = nullptr, black = nullptr;

    // The text display
    std::shared_ptr<TextDisplay> td = nullptr;

    // The graphical display
    std::shared_ptr<GraphicsDisplay> gd = nullptr;

    // Vector of previous moves
    std::vector<PlayerMove> moves;

    // Bool for graphics
    bool graphics;
    
    // Maps for algebraic to descriptive conversions
    const std::map<Rank, char> cnvrsn = {{Rank::r,'R'},{Rank::n,'N'},{Rank::q,'Q'},{Rank::k,'K'},
                                        {Rank::b,'b'}, {Rank::p,'P'}, {Rank::blank,' '}};
    const std::map<int, std::string> cols = {{0,"QR"},{1,"QN"},{2,"QB"},{3,"Q"}, {4,"K"}, {5,"KB"},
                                        {6,"KN"}, {7,"KR"}};
    
    // Data regarding king position and check status
    size_t wRow, wCol;
    size_t bRow = 10, bCol = 10;
    bool wCheck = false, bCheck = false;

    // The current en passant position
    size_t passRow = 10, passCol = 10;
    
    // Detaches a Piece from observers
    void detachPiece(Piece* p);

    // Attaches a Piece from observers
    void attach(Piece* p);

    // Returns true if the Player in check is in checkmate
    bool inCheckmate(size_t atRow, size_t atCol, Rank atRank, Colour atColour);

    // Returns true if the current Player is in stalemate
    bool inStalemate(Colour colour);
    
public:
    Board(bool graphics);

    // Sets up the board.  Clears old board, if necessary.
    void init();

    // Plays a move
    void play(Colour colour);

    // Initializes players
    void initPlayers(unsigned seed);

    // Attaches pieces to initialize observer design pattern
    void attachPieces(const int n = 8);
    
    // Places piece at row r, col c.
    void setPiece(size_t row, size_t col, Rank rank, Colour colour);

    // Moves piece at fromRow-1, fromCol-'a' to toRow-1, toCol-'a'
    void move(char fromCol, size_t fromRow, char toCol, size_t toRow, Colour colour); 

    // Undo last move
    void undo(Colour colour, bool staleMate = false);

    // Returns copy of the board
    std::vector<std::vector<std::shared_ptr<Piece>>> getPieces() const noexcept;

    // Determines if the user can leave setup mode
    bool canLeaveSetup() const;

    // Prints a history of moves
    void printHistory() const;

    // Prints the Board
    friend std::ostream &operator<<(std::ostream &out, const Board &b);
};

#endif

/*  Class thrown if an invalid undo is encountered. */
class UndoException {};

/*  Class thrown if a stalemate occurs. */
class staleMateException {};

/*  Class thrown if a checkmate occurs. */
class checkMateException {};

/*  Class thrown if an invalid player initialization occurs. */
class InvalidPlayer {};
