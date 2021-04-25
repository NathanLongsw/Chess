#include <iostream>
#include "human.h"
#include "board.h"
using namespace std;

Human::Human(Board *gameboard, Colour colour): Player{gameboard, colour} {}

Human::~Human() {}

void Human::play() {
    char fromx, newx;
    int fromy, newy;
    
    while (true) {
        cin >> fromx >> fromy >> newx >> newy;
        if (cin.fail()) {
            if (cin.eof()) {
                return ;
            } else {
                cin.clear();
                cin.ignore();
                cerr << "Incorrect Input Format. Try again!" << endl;
            }
        } else {
            break;
        }
    }
    gameboard->move(fromx, fromy, newx, newy, colour);
}
