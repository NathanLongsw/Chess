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

My implementation of this game employs the Observer design pattern. Each cell of the grid is an observer of all of its neighbours
(that means that class Cell is its own observer). Thus, when the grid calls notifyNeighbours on a given cell, that cell then calls the notify method on each of its neighbours (each cell is told who its neighbours are when the grid is initialized). Moreover, the TextDisplay class is an observer of every cell (this is also set up when the grid is initialized).

In order to construct a complete solution using this design pattern, I was required to specify the types of notifcations a cell can send. A notification can either be a notification of a new piece, a relay of that new piece message, or a reply to that new piece being found. A cell that receives a new piece notifies its observers (adjacent cells) that it has received a new piece of a certain colour. The cells notified of a new piece by their neighbour relays that message along the line. When a message is received by a cell that contains the same colour piece as the new piece, it replies back in a similar fashion. Hence, when a piece matching the colour of the new piece is reached, the message stops relaying and instead replies back. Similarly if there are no pieces in a cell to relay a message then it should stop. Since the observer pattern doesn’t distinguish what observers are in the collection the cell receiving a new piece can’t send out specific information about the direction of each line to its appropriate neighbours. However, when a neighbour receives a notification of a new piece they check the information passed along and determine what direction they are from the original piece, and relay that information along. For more information on these messages see the state.h file.


## Valid Commands

* `new n` : Creates a new n × n grid, where n ≥ 4 ∧ n ≡ 0(mod2). If there was already an active grid,that grid is destroyed and replaced with the new one. When setting up the new grid the program intializes the middle 4 squares following the Black-White-Black-White pattern.

* `play r c` : Within a game, plays a piece at row r, column c of the colour corresponding to the player who’s move it is. If the row and column entered correspond to a cell that already has a piece, or a position outside the grid, then the input is ignored and nothing is done.

## Output

When the game is over, if the black player wins the program displays "Black wins!" and if the white player wins it displays "White wins!"; otherwise it displays "Tie!". If input was exhausted before the game was won or lost, it displays nothing.

A sample output from a game is provided below. Italicized text is input.



*new 8*
<div>
--------<br/>
--------<br/>
--------<br/>
---BW---<br/>
---WB---<br/>
--------<br/>
--------<br/>
--------<br/>
</div>
  
*play 3 5*
<div>
--------<br/>
--------<br/>
--------<br/>
---BBB--<br/>
---WB---<br/>
--------<br/>
--------<br/>
--------<br/>
</div>  

*play 3 6*
<div>
--------<br/> 
--------<br/> 
--------<br/> 
---BBBW-<br/> 
---WB---<br/> 
--------<br/> 
--------<br/> 
--------<br/> 
</div>  

*play 3 2*
<div>
--------<br/> 
--------<br/> 
--------<br/> 
--BBBBW-<br/> 
---WB---<br/> 
--------<br/> 
--------<br/> 
--------<br/> 
</div>  

*play 2 3*
<div>
--------<br/> 
--------<br/> 
---W----<br/> 
--BWBBW-<br/> 
---WB---<br/> 
--------<br/> 
--------<br/> 
--------<br/> 
</div>

*play 0 0*
<div>
B-------<br/> 
--------<br/> 
---W----<br/> 
--BWBBW-<br/> 
---WB---<br/> 
--------<br/> 
--------<br/> 
--------<br/> 
</div>

*play 3 1*
<div>
B-------<br/> 
--------<br/> 
---W----<br/> 
-WWWBBW-<br/> 
---WB---<br/> 
--------<br/> 
--------<br/> 
--------<br/> 
</div>

*play 7 7*
<div>
B-------<br/> 
--------<br/> 
---W----<br/> 
-WWWBBW-<br/> 
---WB---<br/> 
--------<br/> 
--------<br/> 
-------B<br/>
</div>

*ˆD*

