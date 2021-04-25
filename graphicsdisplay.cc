#include "graphicsdisplay.h"
#include "piece.h"


// constructor
GraphicsDisplay::GraphicsDisplay(size_t dimension):gwindow{new Xwindow{static_cast<int>(dimension), static_cast<int>(dimension)}}, dx{dimension / 8}{
    for(int i = 0; i < 8; i++){
        std::vector<std::string> row;
        for(int j = 0; j < 8; j++){
            row.push_back("");
            row.push_back("");
        }
        OldDisplay.push_back(row);
        NewDisplay.push_back(row);
    }

    for(size_t x = 0; x < 8; x++){
        for(size_t y = 0; y < 8; y++){
            int fill = SquareColour(x, y);
            gwindow->fillRectangle(x*dx, y*dx, dx, dx, fill);
        }
    }
    // for(size_t r = 0; r < 8; r++){
    //     for(size_t c = 0; c < 8; c++){
    //         int fill = SquareColour(r, c);
    //         gwindow->fillRectangle(r*dx, c*dx, dx, dx, fill);
    //     }
    // }
}


//destructor
GraphicsDisplay::~GraphicsDisplay() {
}






int GraphicsDisplay::SquareColour(size_t x, size_t y) const{
  if(x % 2 == 0){
    if(y % 2 == 0){
      return Xwindow::White;
    }else{
      return Xwindow::Black;
    }
  }else{
    if(y % 2 == 0){
      return Xwindow::Black;
    }else{
      return Xwindow::White;
    }
  }
}


std::string GraphicsDisplay::getIcon(Rank rank, Colour colour) const{
    if(rank == Rank::blank){
        return "";
    }else if(colour == Colour::White){
        if(rank == Rank::b){
            return "BISHOP";
        }else if(rank == Rank::k){
            return "KING";
        }else if(rank == Rank::n){
            return "KNIGHT";
        }else if(rank == Rank::p){
            return "PAWN";
        }else if(rank == Rank::q){
            return "QUEEN";
        }else{
            return "ROOK";
        }
    }else{
        if(rank == Rank::b){
            return "bishop";
        }else if(rank == Rank::k){
            return "king";
        }else if(rank == Rank::n){
            return "knight";
        }else if(rank == Rank::p){
            return "pawn";
        }else if(rank == Rank::q){
            return "queen";
        }else{
            return "rook";
        }
    }
}



void GraphicsDisplay::notify( Subject<Info, State> & whoNotified ){
    State fromState = whoNotified.getState();
    if(fromState.type == StateType::Standing){
        int x = fromState.col;
        int y = 7 - fromState.row;
        std::string newicon = getIcon(fromState.rank, fromState.colour);
        NewDisplay[y][x] = newicon;
    }
}



//         if(Display[y][x] != newicon){
//             Display[y][x] = newicon;
//             int fill = SquareColour(x, y);
//             gwindow->fillRectangle(x*dx, y*dx, dx, dx, fill);
//             if(newicon != ""){
//                 gwindow->drawString(x*dx + (dx / 2)-25, y*dx + (dx / 2), newicon);
//             }
//         }
//     }
// }

//   if(fromState.type == StateType::Standing){
//     int newrow = fromState.row;
//     int newcol = fromState.col;
//     Rank newrank = fromState.rank;
//     Colour newColour = fromState.colour;
//     std::string newicon = getIcon(newrank, newColour);
//     std::string oldicon = Display[newcol][7-newrow];
//     if(oldicon != newicon){
//         Display[newcol][7-newrow] = newicon;
//         int x = 7 - newrow;
//         int y = newcol;
//         int fill = SquareColour(newrow, newcol);
//         //paint over old square
//         gwindow->fillRectangle(x*dx, y*dx, dx, dx fill);
//         if(newicon != ""){
//             gwindow->drawString(x*dx + (dx / 2)-25, y*dx + (dx / 2), newicon);
//         }
//     }
//   }

// //     //check if oldicon == newicon
// //     if(oldicon != toprint){
// //         int fill = SquareColour(newrow, newcol);
// //         int r = newcol;
// //         int c = 7 - newrow;
// //         gwindow->fillRectangle(r*dx, c*dx, dx, dx, fill);
// //         if(toprint != ""){
// //             gwindow->drawString(r*dx + (dx / 2)-25, c*dx + (dx / 2), toprint);
// //         }
// //     }
// //     Display[newcol][7-newrow] = toprint;
// //   }
// }







void GraphicsDisplay::drawGraphics(){
    std::string oldicon;
    std::string newicon;
    for(int y = 0; y < 8; y++){
        for(int x = 0; x < 8; x++){
            oldicon = OldDisplay[y][x];
            newicon = NewDisplay[y][x];
            if(oldicon != newicon){
                //redraw this square
                int fill = SquareColour(x, y);
                gwindow->fillRectangle(x*dx, y*dx, dx, dx, fill);
                if(newicon != ""){
                    gwindow->drawString(x*dx + (dx / 2)-25, y*dx + (dx / 2), newicon);
                }
            }
        }
    }
    
    //finished drawing so set OldDisplay to NewDisplay
    OldDisplay = NewDisplay;
}
