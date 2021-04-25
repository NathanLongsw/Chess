#include "player.h"
#include "board.h"


// ABSTRACT BASE CLASS METHODS
Player::Player(Board *Board, Colour colour): colour{colour}, gameboard{Board} {}

Player::~Player(){}



// END ABSTRACT BASE CLASS METHODS
