#include "computer2.h"
#include "player.h"
#include "board.h"
#include <utility>
using namespace std;

Computer2::Computer2(Board *gameboard, Colour Colour, unsigned int seed) : Computer1{gameboard, Colour, seed} {
    pieces = gameboard->getPieces();
}

Computer2::~Computer2() {}


Colour Computer2::getEnemyColour() const noexcept {
    Colour col = Colour::NoColour;
    colour == Colour::White ? col = Colour::Black : col = Colour::White;
    return col;
}

void Computer2::playCapture() {
    Colour enemycolour = getEnemyColour();
    vector<pair<int, int>> enemyloc;

    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++) {
            if (pieces[r][c]->getColour() == enemycolour) {
                enemyloc.push_back(make_pair(r, c));
            }
        }
    }
    // now have vector of all enemy locations, for all my pieces, try capture an enemy
    for (const auto &v : pieces) {
        for (const auto &p : v) { 
            if (p->getColour() == colour) {
                //for each enemy loc try to move their
                for (auto &loc : enemyloc) {
                    try {
                        gameboard->move(p->getCol() + 97, p->getRow() + 1, loc.second + 97, loc.first + 1, colour);
                        return;
                    } catch (InvalidMoveException) {
                        continue;
                    } catch (checkException &c) {
                        // try another move if current move puts you in check
                        if (c.getColour() == colour) continue;
                        else {
                            throw;
                        }
                    } catch (checkMateException) {
                        throw;
                    }
                }
            }
        }
    }
    //couldnt capture for any piece so play random
    playRandom();
}

void Computer2::play(){
    pieces = gameboard->getPieces();
    playCapture();
}
