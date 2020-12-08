# BackgammonRepository

## Notes
- There are two colors; white (the player) and brown/black (the AI/opponent)
- White is ready to bear off when its pieces are in spaces 0-5
- Brown/black is ready to bear pff when its pieces are in spaces 18-23

## Common Variables

### In Board.h
- boardArray[24] | *int, contains the board spaces from 1-24 (0-23)*
- mybar |  *int, holds the number of 
- opponentbar | *int, holds the number of chips in the AI's end space*
- selectedpiece | *int, the index of the selected piece (-1 is no piece is chosen)*
- movesList[2] | *int, holds the valid moves of a chip and two dice rolls (-1 if no move is valid)*

### In AIBoard.h
- boardArray[24] | *int, contains the board spaces from 1-24 (0-23)*
- bar | *int, *
- oppenentBar | *int, *
- numRolls | *int, *

### In boardList.h
- \*boardData | *board, *
- \*next | *BoardNode, *

### In rollsList.h
- roll | *int, holds the die roll number*
- \*next | *RollNode, holds the next node in the list*
- isEmpty() | *checks if RollNode header is NULL or not*
- first() | *returns the value of RollNode header*
- rest() | *returns a new list with the first RollNode removed*

## Functions within Programs

### Board.cc - includes Board.h, rollsList.h
- Board::Board(wxFrame *parent) | **
- void Board::OnPaint(wxPaintEvent& WXUNUSED(event)) | *Draws the board?*
- void Board::OnClick(wxMouseEvent& event) | *Calculates the possible moves of a selected piece*

### AIBoard.cc - includes AIBoard.h
- board::board() | **
- void board::setInitialBoard() | *Sets the board to a starting game board*
- bool board::readyToBearOff() | *Checks if someone is ready to start adding their pieces to their end area*
- void board::printBoard() | **
- board* board::copyBoard() | **
- bool board::boardEqualP(board* testboard) | **
- board* board::reverseBoard() | **

### AIFunctions.cc

### boardList.cc

### rollsList.cc

### bg.cc

### Backgammon.cc

### main.cc
