#ifndef CONTROLLER_H_
#define CONTROLLER_H_
#include <iostream>
#include <memory>
#include <string>
#include "state.h"
#include "piece.h"
#include "board.h"

class Controller {
    std::shared_ptr<Board> b;
    double whiteScore = 0, blackScore = 0;

public:
    Controller(bool graphics);
    void startGame(unsigned seed);
    void init();
    void initPlayers(unsigned seed);
    void move(Colour colour);
    void resign(Colour colour) noexcept;
    void checkmate(Colour colour) noexcept;
    void draw() noexcept;
    void setup(Colour &colour);
    void undo(Colour colour);
    void gameOver() const noexcept;
    void printHistory() const;
    void print() const;
};

#endif
