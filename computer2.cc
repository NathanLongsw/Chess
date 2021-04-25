#include "computer2.h"
#include "player.h"
#include "board.h"
#include <utility>
#include <map>


Computer2::Computer2(Board *gameboard, Colour Colour, unsigned int seed) : Computer1{gameboard, Colour, seed} {
    pieces = gameboard->getPieces();
}

Computer2::~Computer2(){

}


Colour Computer2::getEnemyColour(){
    if(colour == Colour::White){
        return Colour::Black;
    }else{
        return Colour::White;
    }
}


void Computer2::playCapture(){
    Colour enemycolour = getEnemyColour();
    
    std::vector<std::pair<int, int>> enemyloc;

    for(int r = 0; r < 8; r++){
        for(int c = 0; c < 8; c++){
            if(pieces[r][c]->getColour() == enemycolour){
                enemyloc.push_back(std::make_pair(r, c));
            }
        }
    }


    //now have vector of all enemy locations, for all my pieces
    // try capture an enemy

    for(auto &v : pieces){
        for(auto &p : v){
            if(p->getColour() == colour){
                //for each enemy loc try to move their
                for(auto &loc : enemyloc){
                    try{
                        gameboard->move(p->getCol() + 97, p->getRow() + 1, loc.second + 97, loc.first + 1, colour);
                        return;
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
    }

    //couldnt capture for any piece so play random
    playRandom();
}


void Computer2::play(){
    pieces = gameboard->getPieces();
    playCapture();
}
