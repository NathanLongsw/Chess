#include <iostream>
#include <string>
#include <stdexcept>
#include <chrono>
#include "controller.h"
using namespace std;

int main(int argc, char *argv[]) {
    cin.exceptions(ios::eofbit | ios::failbit);
    string cmd;
    bool inProgress = false;
    bool setupStarted = false;
    
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    bool graphics = true;

    if ( argc > 1 ) {
        for (int i = 1; i < argc; i++) {
            if (string{argv[i]} == "-text") {
                graphics = false;
            } 
            if (string{argv[i]} == "-seed" && (i + 1 < argc)) {
                try {
                    seed = stoi( string{ argv[i+1] } );
                } catch ( invalid_argument & e ) {
                    cerr << e.what() << endl;
                    return 1;
                } catch( out_of_range & e ) {
                    cerr << e.what() << endl;
                    return -1;
                }
            }
        }
    }
    
    Controller ctr{graphics};
    Colour whoseMove = Colour::NoColour;
    
    while (true) {
        try {
            cin >> cmd;
            if (cmd == "game") {
                if (setupStarted) {
                    try {
                        ctr.initPlayers(seed);
                    } catch (InvalidPlayer) {
                        continue;
                    }
                } else {
                    try {
                        ctr.startGame(seed);
                    } catch (InvalidPlayer) {
                        continue;
                    } 
                }
                setupStarted = false;
                inProgress = true;
                if(whoseMove == Colour::NoColour) whoseMove = Colour::White; 
            }
            else if (cmd == "setup") {
                if (inProgress) {
                    cerr << "Cannot enter setup mode while a game is in progress." << endl;
                    continue;
                }
                if (setupStarted) {
                    ctr.setup(whoseMove);
                } else {
                    setupStarted = true;
                    ctr.init();
                    ctr.setup(whoseMove);
                }
            }
            else if (!inProgress) {
                cerr << "Can't call this command while there is no game in progess." << endl;
            }
            else if (cmd == "move") {
                try {
                    ctr.move(whoseMove); 
                }
                catch (checkMateException &cm) {
                    inProgress = false;
                } 
                catch (staleMateException) {
                    inProgress = false;
                }
                catch (...) {
                    cerr << "Invalid Move! Try again." << endl;
                    continue;
                }
                whoseMove = whoseMove == Colour::Black ? Colour::White : Colour::Black;
            }
            else if (cmd == "undo") {
                try {
                    ctr.undo(whoseMove);
                    whoseMove = whoseMove == Colour::Black ? Colour::White : Colour::Black;
                } catch (UndoException) {
                    cerr << "No moves to undo!" << endl;
                }
            }
            else if (cmd == "history") {
                try {
                    ctr.printHistory(); 
                } catch (UndoException) {
                    cerr << "No move history to print!" << endl;
                }
            }
            else if (cmd == "resign") {
                ctr.resign(whoseMove);
                inProgress = false;
                whoseMove = Colour::NoColour;
            }
            else {
                cerr << "Invalid command, try again." << endl;
            }
        }
        catch (ios::failure &) {
            if (cin.eof()) {
                ctr.gameOver();
                return 0;
            }
            cin.clear();
            cin.ignore();
        }
    }
}
