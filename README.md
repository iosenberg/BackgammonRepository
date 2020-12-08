# BackgammonRepository

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
