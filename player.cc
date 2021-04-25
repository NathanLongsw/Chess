#include "player.h"
#include "board.h"

Player::Player(Board *Board, Colour colour): colour{colour}, gameboard{Board} {}

Player::~Player() {}
