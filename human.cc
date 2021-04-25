#include <iostream>
#include "human.h"
#include "board.h"
// HUMAN PLAYER METHODS

class Board;

Human::Human(Board *gameboard, Colour colour): Player{gameboard, colour} {

}

Human::~Human(){

}

void Human::play(){
    char fromx;
    int fromy;
    char newx;
    int newy;
    //get user input
    //assumes that move command has already been read.
    while(true){
        std::cin >> fromx >> fromy >> newx >> newy;
        if(std::cin.fail()){
            if(std::cin.eof()){
                return ;
            }else{
                std::cin.clear();
                std::cin.ignore();
                std::cerr << "Incorrect Input Format. Try again!" << std::endl;
            }
        }else{
            break;
        }
    }
    gameboard->move(fromx, fromy, newx, newy, colour);
}
