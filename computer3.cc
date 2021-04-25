#include "computer3.h"
#include "board.h"
#include <map>
#include <algorithm>

Computer3::Computer3(Board *gameboard, Colour colour, unsigned int seed): Computer2{gameboard, colour, seed} {

}

Computer3::~Computer3(){

}



bool Computer3::positionatRisk(int row, int col){
    Colour enemy = getEnemyColour();
    for(auto &v: pieces){
        for(auto &p : v){
            if (p->getColour() != enemy) continue;
            std::pair<int, int> mypos = std::make_pair(row, col);
            std::vector<std::pair<int, int>> moves = p->generateMoves();
            if(std::find(moves.begin(), moves.end(), mypos) != moves.end()){
                return true;
            }
        }
    }
    return false;
}

void Computer3::play(){
    gameboard->getPieces();


    std::vector<std::pair<int, int>> threat;
    //check if any of my pieces are in threat
    for(int r = 0; r < 8; r++){
        for(int c = 0; c  < 8; c++){
            if(positionatRisk(r, c)){
                threat.push_back(std::make_pair(r, c));
            }
        }
    }
    

    //for my pieces that are threatened try to make a legal move if not at risk
    for(auto &p : threat){
        std::shared_ptr<Piece> mypiece = pieces[p.first][p.second];
        std::vector<std::pair<int, int>> moves = mypiece->generateMoves();
        for(auto &m : moves){
            //for each move if not at risk then try to move
            if(positionatRisk(m.first, m.second) == false){
                try{
                    gameboard->move(p.second + 97, p.first + 1, m.second + 97, m.first + 1, colour);
                    return ;
                } catch (InvalidMoveException) {
                            //invalid move so move on to next one
                        continue;
                } catch (checkException) {
                    // try another move if current move puts you in check
                    continue;
                } catch (checkMateException) {
                    throw;
                }
            }
        }
    }
    //could not get out of the way so play capture like computer2
    playCapture();
}
