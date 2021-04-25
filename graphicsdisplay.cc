#include "graphicsdisplay.h"
using namespace std;

GraphicsDisplay::GraphicsDisplay(size_t dimension): gwindow{new Xwindow{static_cast<int>(dimension), static_cast<int>(dimension)}}, dx{dimension / 8} {
    for (int i = 0; i < 8; i++) {
        vector<string> row;
        for (int j = 0; j < 8; j++) {
            row.push_back("");
            row.push_back("");
        }
        OldDisplay.push_back(row);
        NewDisplay.push_back(row);
    }

    for (size_t x = 0; x < 8; x++) {
        for (size_t y = 0; y < 8; y++) {
            int fill = SquareColour(x, y);
            gwindow->fillRectangle(x*dx, y*dx, dx, dx, fill);
        }
    }
}

GraphicsDisplay::~GraphicsDisplay() {}

int GraphicsDisplay::SquareColour(size_t x, size_t y) const noexcept {
  if (x % 2 == 0) {
    if (y % 2 == 0) {
      return Xwindow::White;
    } else {
      return Xwindow::Black;
    }
  } else {
    if (y % 2 == 0) {
      return Xwindow::Black;
    } else { 
      return Xwindow::White;
    }
  }
}

string GraphicsDisplay::getIcon(Rank rank, Colour colour) const noexcept {
    if(rank == Rank::blank) {
        return "";
    } else if (colour == Colour::White) {
        if (rank == Rank::b) {
            return "BISHOP";
        } else if(rank == Rank::k) {
            return "KING";
        } else if(rank == Rank::n) {
            return "KNIGHT";
        } else if(rank == Rank::p) {
            return "PAWN";
        } else if(rank == Rank::q) {
            return "QUEEN";
        } else{
            return "ROOK";
        }
    } else {
        if (rank == Rank::b) {
            return "bishop";
        } else if (rank == Rank::k) {
            return "king";
        } else if (rank == Rank::n) {
            return "knight";
        } else if(rank == Rank::p) {
            return "pawn";
        } else if(rank == Rank::q) {
            return "queen";
        } else{
            return "rook";
        }
    }
}

void GraphicsDisplay::notify( Subject<Info, State> & whoNotified) {
    State fromState = whoNotified.getState();
    if (fromState.type == StateType::Standing) {
        int x = fromState.col;
        int y = 7 - fromState.row;
        string newicon = getIcon(fromState.rank, fromState.colour);
        NewDisplay[y][x] = newicon;
    }
}

void GraphicsDisplay::drawGraphics() noexcept {
    string oldicon;
    string newicon;
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            oldicon = OldDisplay[y][x];
            newicon = NewDisplay[y][x];
            if (oldicon != newicon) {
                //redraw this square
                int fill = SquareColour(x, y);
                gwindow->fillRectangle(x*dx, y*dx, dx, dx, fill);
                if (newicon != "") {
                    gwindow->drawString(x*dx + (dx / 2)-25, y*dx + (dx / 2), newicon);
                }
            }
        }
    }
    //finished drawing so set OldDisplay to NewDisplay
    OldDisplay = NewDisplay;
}
