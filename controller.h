#ifndef CONTROLLER_H_
#define CONTROLLER_H_
#include <iostream>
#include <memory>
#include <string>
#include "board.h"

class Controller {
    // Pointer to the Board
    std::shared_ptr<Board> b;

    // Keeps track of the score
    double whiteScore = 0, blackScore = 0;

public:
    Controller(bool graphics);

    // Initializes board
    void init();

    // Initializes board, set default starting piece layout and set players
    void startGame(unsigned seed);

    // Initializes players
    void initPlayers(unsigned seed);

    // Call player's move method 
    void move(Colour colour);

    // Resigns the game
    void resign(Colour colour) noexcept;

    // Called when checkmate occurs
    void checkmate(Colour colour) noexcept;

    // Draws the game
    void draw() noexcept;

    // Executes set up mode
    void setup(Colour &colour);

    // Undo the last move 
    void undo(Colour colour);

    // Game over output
    void gameOver() const noexcept;

    // Print a history of moves
    void printHistory() const;

    // Prints board
    void print() const;
};

#endif
