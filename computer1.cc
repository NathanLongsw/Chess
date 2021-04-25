#include "computer1.h"
#include "board.h"
#include <utility>
#include <map>
#include <iostream>
#include <algorithm>
#include <random>

Computer1::Computer1(Board *gameboard, Colour colour, unsigned int seed): Player{gameboard, colour}, seed{seed} {
    pieces = gameboard->getPieces();
}

Computer1::~Computer1() {}



// returns all my pieces
std::vector<std::shared_ptr<Piece>> Computer1::getMyPieces() const{
    std::vector<std::shared_ptr<Piece>> mypieces;
    for(auto &v : pieces){
        for(auto &p : v){
            if(p->getColour() == colour){
                mypieces.push_back(p);
            }
        }
    }
    return mypieces;
}


void Computer1::playRandom() {
    pieces = gameboard->getPieces();

    std::vector<std::shared_ptr<Piece>> mypieces = getMyPieces();
    
    std::shared_ptr<Piece> cpiece{nullptr};
    
    std::default_random_engine rng{seed};

    int count = 0;
    
    while(count <= 1000) {

        int randidx = 0;
        // shuffle vector 100 times to improve randomess
        for(int z = 0; z < 200; z++){
            std::shuffle(mypieces.begin(), mypieces.end(), rng);
        }
        cpiece = mypieces[randidx];
        //return valid moves for this piece
        std::vector<std::pair<int, int>> validmoves = cpiece->generateMoves();
        //shuffle moves
        for(int z = 0; z < 10; z++){
            std::shuffle(validmoves.begin(), validmoves.end(), rng);
        }
        //index not already seen, so try to play move
        for(auto &p : validmoves){
        //for each move try to play it
            char mycol = 0, tocol = 0;
            int myrow = 0, torow = 0;
            try{
                mycol = cpiece->getInfo().col + 97;
                myrow = cpiece->getInfo().row + 1;
                tocol = p.second + 97;
                torow = p.first + 1;
                gameboard->move(mycol, myrow, tocol, torow, colour);
                std::cout << "Computer Played... " << mycol << myrow << "->" << tocol << torow << std::endl;
                return ;
            } catch (InvalidMoveException) {
                //invalid move so move on to next one
               continue;
            } catch (checkException &c) {
                if (c.getColour() == colour) continue;
                else {
                    std::cout << "Computer Played... " << mycol << myrow << "->" << tocol << torow << std::endl;
                    throw;
                }
                // try another move if current move puts you in check
            } catch (checkMateException) {
                throw;
            } 
        }   
        ++count;
    }
    std::cout << "NO MOVE" << std::endl;
}


void Computer1::play(){
    playRandom();
}
