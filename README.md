# Reversi
Northwestern CS 211: Reversi Board Game

## Description:
Reversi is a strategy board game for two players played on an 8 x 8 uncheckered board

## Instructions:
Game is divided into two stages (beginning stage and main stage) and designed for two players (dark and light)

### Beginning Stage
- First four moves must be placed in the center four squares of the board with Dark player going first 
- No pieces are captured or reversed

### Main Stage
- Each piece played must be laid adjacent to an opponent's piece so that the opponent's piece or a row of opponent's pieces is flanked by the new piece and another piece of the player's color
- Legal moves mark the board red while illegal moves display a small player color piece over the board
- All of the opponent's pieces between these two pieces are 'captured' and turned over to match the player's color
- It can happen that a piece is played so that pieces or rows of pieces in more than one direction are trapped between the new piece played and other pieces of the same color (in this case, all the pieces in all viable directions are turned over)
- If the player has no legal moves for the turn, the opponent has the right to place a piece
- The game is over when neither player has a legal move or when the board is full
- All pieces belonging to the loosing player will turn grey
