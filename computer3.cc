#include "computer3.h"
#include "board.h"
#include <algorithm>
using namespace std;

Computer3::Computer3(Board *gameboard, Colour colour, unsigned int seed): Computer2{gameboard, colour, seed} {}

Computer3::~Computer3() {}

bool Computer3::positionatRisk(int row, int col) noexcept {
    Colour enemy = getEnemyColour();
    for (const auto &v: pieces) {
        for (const auto &p : v) {
            if (p->getColour() != enemy) continue;
            pair<int, int> mypos = make_pair(row, col);
            vector<pair<int, int>> moves = p->generateMoves();
            if(find(moves.begin(), moves.end(), mypos) != moves.end()) {
                return true;
            }
        }
    }
    return false;
}

void Computer3::play() {
    gameboard->getPieces();

    vector<pair<int, int>> threat;
    //check if any of my pieces are in threat
    for (int r = 0; r < 8; r++) {
        for (int c = 0; c  < 8; c++) {
            if( positionatRisk(r, c)) {
                threat.push_back(make_pair(r, c));
            }
        }
    }

    //for my pieces that are threatened try to make a legal move if not at risk
    for (const auto &p : threat) {
        shared_ptr<Piece> mypiece = pieces[p.first][p.second];
        vector<pair<int, int>> moves = mypiece->generateMoves();
        for (const auto &m : moves) {
            //for each move if not at risk then try to move
            if (!positionatRisk(m.first, m.second)) {
                try {
                    gameboard->move(p.second + 97, p.first + 1, m.second + 97, m.first + 1, colour);
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
    //could not get out of the way so play capture like computer2
    playCapture();
}
