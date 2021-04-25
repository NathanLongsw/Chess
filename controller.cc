#include "controller.h"
using namespace std;

Controller::Controller(bool graphics): b{make_shared<Board>(graphics)} {}

// Initializes board
void Controller::init() {
    b->init();
}
// Initializes board, set default starting piece layout and set players
void Controller::startGame(unsigned seed) {
    init();
    b->setPiece(0, 0, Rank::r, Colour::White);
    b->setPiece(0, 7, Rank::r, Colour::White);
    b->setPiece(0, 1, Rank::n, Colour::White);
    b->setPiece(0, 6, Rank::n, Colour::White);
    b->setPiece(0, 2, Rank::b, Colour::White);
    b->setPiece(0, 5, Rank::b, Colour::White);
    b->setPiece(0, 3, Rank::q, Colour::White);
    b->setPiece(0, 4, Rank::k, Colour::White);
    for (size_t i = 0; i < 8; ++i)
        b->setPiece(1, i, Rank::p, Colour::White);
    for (size_t l = 0; l < 8; ++l)
        b->setPiece(6, l, Rank::p, Colour::Black);
    b->setPiece(7, 0, Rank::r, Colour::Black);
    b->setPiece(7, 7, Rank::r, Colour::Black);
    b->setPiece(7, 1, Rank::n, Colour::Black);
    b->setPiece(7, 6, Rank::n, Colour::Black);
    b->setPiece(7, 2, Rank::b, Colour::Black);
    b->setPiece(7, 5, Rank::b, Colour::Black);
    b->setPiece(7, 3, Rank::q, Colour::Black);
    b->setPiece(7, 4, Rank::k, Colour::Black);
    b->attachPieces();
    initPlayers(seed);
}

// Initializes players
void Controller::initPlayers(unsigned seed) {
    try {
        b->initPlayers(seed);

    } catch (InvalidPlayer) {
        cerr << "Invalid player initialization, try again." << endl;
        throw;
    }
}

// Call player's move method 
void Controller::move(Colour colour) {
    try {
        b->play(colour);
        print();
    } catch (InvalidMoveException) {
        throw;
    } catch (checkException &c) {
        if (c.getColour() == colour) {
            throw;
        } else {
            print();
            colour == Colour::Black ? cout << "White" : cout << "Black";
			cout << " is in check." << endl;
        }
    } catch (staleMateException) {
        print();
        draw();
        throw;
    }
    catch (checkMateException &cm) {
        print();
        checkmate(colour);
        throw;
    }
}

// Resigns game
void Controller::resign(Colour colour) noexcept {  
   // b->resign(colour);  
    if (colour == Colour::White) {
        cout << "Black";
        ++blackScore;;
    } else {
        cout << "White";
        ++whiteScore;
    }
    cout << " wins!" << endl;
}

// Called when checkmate occurs
void Controller::checkmate(Colour colour) {
    //b->checkmate(colour);
    cout << "Checkmate! ";
    if (colour == Colour::Black) {
	cout << "Black";
        ++blackScore; 
    } else {
	cout << "White";
        ++whiteScore;
    }
    cout << " wins!" << endl;
}

// Draws game
void Controller::draw() noexcept {
     cout << "Stalemate!" << endl;
     whiteScore += 0.5; 
     blackScore += 0.5;
}

// Executes set up mode
void Controller::setup(Colour &colour) {
    while (true) {
        string op;
        char piece, col;
        int row;
        string colourIn;
        cin >> op;
        if (op == "+") {
            cin >> piece >> col >> row;
            Rank rank;
            if (piece == 'p' || piece ==  'P')
                rank = Rank::p;
            else if (piece == 'r' || piece == 'R' )
                rank = Rank::r;
            else if (piece == 'n' || piece == 'N')
                rank = Rank::n;
            else if (piece == 'b' || piece == 'B')
                rank = Rank::b;
            else if (piece == 'q' || piece == 'Q')
                rank = Rank::q;
            else if (piece == 'k' || piece == 'K')
                rank = Rank::k;
            else {
                cerr << "Invalid piece, try again." << endl;
                continue;
            }
            if (piece > 'Z') {
                try {
                    b->setPiece(row-1, col-'a', rank, Colour::Black);
                } catch (InvalidMoveException) {
                    cerr << "Invalid placement, try again." << endl;
                    continue;
                }
            } else {
                try {
                    b->setPiece(row-1, col-'a', rank, Colour::White);
                } catch (InvalidMoveException) {
                    cerr << "Invalid placement, try again." << endl;
                    continue;
                }
            }
            print();
        }
        else if (op == "-") {
            cin >> col >> row;
            try {
                b->setPiece(row-1, col-'a', Rank::blank, Colour::NoColour);
                print();
            } catch (InvalidMoveException) {
                cerr << "Invalid placement, try again." << endl;
                continue;
            }
        }
        else if (op == "=") {
            cin >> colourIn;
            colour = colourIn == "black" ? Colour::Black : Colour::White;
        }
        else if (op == "done") {
            if (b->canLeaveSetup()) return;
            cerr << "Invalid board setup." << endl;
        }
        else {
            cerr << "Invalid command, type 'done' to leave setup mode." << endl;
        }
    }
}

// Undo last move 
void Controller::undo(Colour colour) {
    try {
        // Get colour of who played the last move
        Colour col = colour == Colour::White ? Colour::Black : Colour::White;
        b->undo(col);
        print();
    } catch (UndoException) {
        throw;
    }
}

// Game over output
void Controller::gameOver() const noexcept {
    cout << "Final Score:" << endl;
    cout << "White: " << whiteScore << endl << "Black: " << blackScore << endl;
}

// Print history of moves
void Controller::printHistory() const {
    try {
        b->printHistory();
    } catch (UndoException) {
        throw;
    }
}

// Prints board
void Controller::print() const {
    cout << *b;
}
