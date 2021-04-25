#include "textdisplay.h"
#include "piece.h"

// Blank board
TextDisplay::TextDisplay(){
  for(int r = 0; r < 8; ++r){
    std::vector<char> row;
    for(int c = 0; c < 8; c++){
      char print = squareChar(r, c);
      row.push_back(print);
    }
    theDisplay.push_back(row);
  }
}


// returns char representing either black or white board
char TextDisplay::squareChar(int row, int col) const{
  if(row % 2 == 0){
    if(col % 2 == 0){
      return '-';
    }else{
      return ' ';
    }
  } else {
    if(col % 2 == 0){
      return ' ';
    }else{
      return '-';
    }
  }
}


// returns display icon for piece of colour and rank
char TextDisplay::getIcon(Colour colour, Rank rank) const{
  char toprint;
  if(rank == Rank::p){
    toprint = 'p';
  }else if(rank == Rank::n){
    toprint = 'n';
  }else if(rank == Rank::q){
    toprint = 'q';
  }else if(rank == Rank::r){
    toprint = 'r';
  }else if(rank == Rank::b){
    toprint = 'b';
  }else if(rank == Rank::k){
    toprint = 'k';
  }else{
    //Blank rank
    toprint = ' ';
  }
  if(toprint != ' ' && colour == Colour::White){
    toprint -= 32; // convert to uppcase char
  }
  return toprint;
}



void TextDisplay::notify( Subject<Info, State> & whoNotified ){
  State fromState = whoNotified.getState();
  if(fromState.type == StateType::Standing){
    size_t newrow = fromState.row;
    size_t newcol = fromState.col;
    Rank newrank = fromState.rank;
    Colour newColour = fromState.colour;
    
    char toprint;
    if(newrank == Rank::blank){
      toprint = squareChar(newrow, newcol);
    } else {
      toprint = getIcon(newColour, newrank);
    }
    theDisplay[newrow][newcol] = toprint;
  }
}


std::ostream & operator<<(std::ostream &out, const TextDisplay &td) {
    int R = 8;
    for (auto it = td.theDisplay.end() - 1; it >= td.theDisplay.begin(); it--){
        out << R << " ";
        for (int i = 0; i < 8; i++)
            out << (*it)[i];
        out << std::endl;
        --R;
    }
    out << std::endl;
    out << "  abcdefgh" << std::endl;
    return out;
}
