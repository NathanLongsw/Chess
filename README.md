# Chess

This project is a C++ implementation of game of Chess using OOP.


## About Chess

Chess is played on an 8x8 checkerboard, arranged so that there is a white square at the bottom right. Players take turns making one move at a time. The player controlling the white pieces makes the first move. There are six types of pieces:  
* King (K) Moves one square in any direction.  
* Queen (Q) Moves in any of the eight possible directions, any distance, but cannot move past any piece that blocks its path.  
* Bishop (B) Moves in any of the four diagonal directions, any distance, but cannot move past any piece that blocks its path.  
* Rook (R) Moves in any of the four vertical/horizontal directions, any distance, but cannot move past any piece that blocks its path.  
* Knight (N) If it sits on square (x,y), it can move to square (x±2,y±1) or (x±1,y±2). Can “jump over” any piece that blocks its path.  
* Pawn (P) Moves one square forward.  

A piece captures another piece by moving onto the square occupied by that piece. The captured piece is then permanently removed from the board. A piece that could capture another piece is said to attack that piece. A piece may only capture a piece of the opposite colour.
The objective of the game is to place your opponent’s king under attack, such that your op- ponent’s king cannot escape in one move. This is known as checkmate. An attack on the king, whether it can escape or not, is known as check.
The following additional rules govern the movement of pieces:  
* The pawn is the only piece whose standard move is different from its capturing move. A pawn moves only forward, but it captures on the forward diagonals (one square). Thus, on capturing, a pawn must move diagonally forward, one square, to take over a square occupied by another piece.  
* A pawn, on its first move, may move either one square forward or two squares forward.  
* If a pawn, by moving two squares forward, avoids capture by another pawn (i.e, if moving one square forward would have put it under attack by another pawn), the would-be attacking pawn may still capture it by moving one square diagonally forward to the square the other pawn skipped over. This is known as pawn capture en passant. This option is only available immediately following the two-square move by the opposing pawn. If you wait, you can’t do it.  
* A pawn, upon reaching the other end of the board is replaced by either a rook, knight, bishop, or queen (the player is free to choose).  
* A move known as castling helps to move the king to a safer square while simultaneously mobilizing a rook. To execute it, the king moves two squares towards one of the rooks, and that rook then occupies the square “skipped over” by the king. This happens in one move. For castling to be legal, the king and rook used must not previously have moved in the game; there must be no pieces between the king and rook used; and the king must not be in check on either its starting position, its final position, or the position in between (to be occupied by the rook).  
* It is not legal to make any move that puts your king in check.  
* If any player ever has no legal moves available, but is not in check, it is known as stalemate, and the game is a draw.  

## Implementation Details

My implementation of this game employs the Observer design pattern. Each piece is an observer of all of its neighbours
(that means that class Piece is its own observer). Thus, when the board calls notifyNeighbours on a given cell, that piece then calls the notify method on each of its neighbours (each piece is told who its neighbours are when the board is initialized). Moreover, the TextDisplay and GraphicsDisplay classes are observers of every piece (this is also set up when the board is initialized).

Additionally, this program utilizes the Strategy design pattern for the class Player. The Player is a base class with derived classes Human, Computer 1-3. The virtual method `play` is what invokes the design pattern; Humans get their moves from stdin and computers get their moves either from RNG (random number generation) or from a certain strategy (to be discussed later).

### Displays

As mentioned above, provided to the user are text and graphical displays of the chess board. In this display, capital letters denote white pieces, and lower case letters denote black pieces. Unoccupied squares are denoted by a blank space for white squares, and an underscore character for dark squares. The above board also represents the initial configuration of the game.

After every move, the board is be redisplayed. If one player or the other is in check, additionally display White is in check. or Black is in check., as appropriate. If one player has won the game, display Checkmate! White wins! or Checkmate! Black wins! If the game is stalemated, output Stalemate! If the game is resigned, output White wins! or Black wins!, as appropriate.

### Players

This program accommodates both human and computer players. In particular, human vs. human, human vs. computer, and computer vs. computer are all be possible. Computer players operate at one of three difficulty levels:  

* Level 1: random legal moves.  
* Level 2: prefers capturing moves and checks over other moves.  
* Level 3: prefers avoiding capture, capturing moves, and checks.  

### Scoring

A win awards one point to the winner and zero points to the loser. A draw awards half a point to each team. When the program ends (Ctrl-D is pressed), it should print the final score to the screen. For example:  

Final Score:  
White: 2  
Black: 1  

## Valid Commands

* `game white-player black-player` starts a new game. The parameters white-player and black-player can be either human or computer[1-3].  
* `resign` concedes the game to your opponent. This is the only way, outside of winning or drawing the game, to end a game.  
* `move start end` A move consists of the command move, followed by the starting and ending coordinates of the piece to be moved. For example: move e2 e4. Castling would specified by the two- square move for the king: move e1 g1 or move e1 c1 for white. Pawn promotion would additionally specify the piece type to which the pawn is promoted: move e7 e8 Q. In the case of a computer player, the command move (without arguments) makes the computer player make a move.   
* `undo` undoes the last move played. If there are no moves to undo a warning is displayed to the client.
* `history char` prints a history of the moves. When char equals 'a' the moves are printed in algebraic notation and 'd' displays the moves in descriptive notation.  
* `setup` enters setup mode, within which you can set up your own initial board configurations. This can only be done when a game is not currently running. Within setup mode, the following language is used:  
  * \+ K e1 places the piece K (i.e., white king in this case) on the square e1. If a piece is already on that square, it is replaced. The board should be redisplayed.  
  * \- e1 removes the piece from the square e1 and then redisplays the board. If there is no piece at that square, take no action.
  * \= colour makes it colour’s turn to go next.  
* `done` leaves setup mode.  
  
Upon completion of setup mode, you must verify that the board contains exactly one white king and exactly one black king; that no pawns are on the first or last row of the board; and that neither king is in check. The user cannot leave setup mode until these conditions are satisfied.  

### Command-line Interface

This program supports the following options on the command line:  
* `-text` runs the program in text-only mode. No graphics are displayed. The default behaviour
(no -text) is to show both text and graphics.  
* `-seed xxx` sets the random number generator’s seed to xxx. This is good for testing, but not
much fun. If you don’t set the seed, the program should use a different one each time.  

## Output

A sample text output from a short game is provided below. Italicized text is input.

*./chess -text*  

*game human human*
<div>
8 rnbqkbnr<br/>
7 pppppppp<br/>
6  - - - -<br/>
5 - - - - <br/>
4  - - - -<br/>
3 - - - - <br/>
2 PPPPPPPP<br/>
1 RNBQKBNR<br/>
  
  abcdefgh<br/>
</div>
  
*move e2 e4*
<div>
8 rnbqkbnr<br/>
7 pppppppp<br/>
6  - - - -<br/>
5 - - - - <br/>
4  - -P- -<br/>
3 - - - - <br/>
2 PPPP PPP<br/>
1 RNBQKBNR<br/>
  
  abcdefgh<br/>
</div>  

*move a7 a6*
<div>
8 rnbqkbnr<br/>
7 -ppppppp<br/>
6 p- - - -<br/>
5 - - - - <br/>
4  - -P- -<br/>
3 - - - - <br/>
2 PPPP PPP<br/>
1 RNBQKBNR<br/>
  
  abcdefgh<br/>
</div>  

*move d1 f3*
<div>
8 rnbqkbnr<br/>
7 -ppppppp<br/>
6 p- - - -<br/>
5 - - - - <br/>
4  - -P- -<br/>
3 - - -Q- <br/>
2 PPPP PPP<br/>
1 RNB KBNR<br/>
  
  abcdefgh<br/>
</div>  

*move a6 a5*
<div>
8 rnbqkbnr<br/>
7 -ppppppp<br/>
6  - - - -<br/>
5 p - - - <br/>
4  - -P- -<br/>
3 - - -Q- <br/>
2 PPPP PPP<br/>
1 RNB KBNR<br/>
  
  abcdefgh<br/>
</div>

*move f1 c4*
<div>
8 rnbqkbnr<br/>
7 -ppppppp<br/>
6  - - - -<br/>
5 p - - - <br/>
4  -B-P- -<br/>
3 - - -Q- <br/>
2 PPPP PPP<br/>
1 RNB K NR<br/>
  
  abcdefgh<br/>
</div>

*move a5 a4*
<div>
8 rnbqkbnr<br/>
7 -ppppppp<br/>
6  - - - -<br/>
5 - - - - <br/>
4 p-B-P- -<br/>
3 - - -Q- <br/>
2 PPPP PPP<br/>
1 RNB K NR<br/>
  
  abcdefgh<br/>
</div>

*move f3 f7*
<div>
8 rnbqkbnr<br/>
7 -ppppQpp<br/>
6  - - - -<br/>
5 - - - - <br/>
4 p-B-P- -<br/>
3 - - - - <br/>
2 PPPP PPP<br/>
1 RNB K NR<br/>
  
  abcdefgh<br/>
</div>

Checkmate! White wins!  
Final Score:  
White: 1  
Black: 0  

