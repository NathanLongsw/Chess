#include "computer2.h"
#include "player.h"
#include "board.h"
#include <utility>
using namespace std;

Computer2::Computer2(Board *gameboard, Colour Colour, unsigned int seed) : Computer1{gameboard, Colour, seed} {
    pieces = gameboard->getPieces();
}

Computer2::~Computer2() {}


Colour Computer2::getEnemyColour(){
    icolour == Colour::White ? return Colour::Black : return Colour::White;
}

void Computer2::playCapture() {
    Colour enemycolour = getEnemyColour();
    vector<pair<int, int>> enemyloc;

    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++) {
            if (pieces[r][c]->getColour() == enemycolour) {
                enemyloc.push_back(std::make_pair(r, c));
            }
        }
    }
    //now have vector of all enemy locations, for all my pieces
    // try capture an enemy

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
                    } catch (checkException) {
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
