# BackgammonRepository

## Notes
- There are two colors; white (the player) and brown/black (the AI/opponent)
- White is ready to bear off when its pieces are in spaces 18-23
- Brown/black is ready to bear pff when its pieces are in spaces 0-5

## Common Variables

### In Board.h
- boardArray[24] | *int, contains the board spaces from 1-24 (0-23)*
- mybar |  *int, holds the number of the player's chips on the middle bar*
- opponentbar | *int, holds the number of the AI/opponent's chips on the middle bar*
- selectedpiece | *int, the index of the selected piece (-1 is no piece is chosen)*
- movesList[2] | *int, holds the valid moves of a chip and two dice rolls (-1 if no move is valid)*

### In AIBoard.h
- boardArray[24] | *int, contains the board spaces from 1-24 (0-23)*
- bar | *int, AI's bar
- oppenentBar | *int, human player's bar
- numRolls | *int, holds the number of rolls needed to get to a particular roll (this helps for deleting interim rolls like in the case where you can do 2 rolls you must do 2)
- score | *int, holds the score given to a particular move (AI uses this to choose best move)

### In boardList.h
- \*boardData | *board, this holds a board object (board object contains variables in AIBoard.h)
- \*next | *BoardNode, holds the next thing in the list (just a part of the linked list of boards)

### In rollsList.h
- roll | *int, holds the die roll number*
- \*next | *RollNode, holds the next node in the list*

## Functions within Programs

### Board.cc - includes Board.h, rollsList.h
- Board::Board(wxFrame \*parent) | **
- void Board::OnPaint(wxPaintEvent& WXUNUSED(event)) | *Draws the board?*
- void Board::OnClick(wxMouseEvent& event) | *Calculates the possible moves of a selected piece*

### AIBoard.cc - includes AIBoard.h
- board::board() | *constructor for board class, just initializes variables in board object*
- void board::setInitialBoard() | *Sets the board to a starting game board*
- bool board::readyToBearOff() | *Checks if someone is ready to start adding their pieces to their end area, specific to AI*
- void board::printBoard() | *prints all variables in board class (boardArray, opponentBar, bar, score, and numRolls)*
- board\* board::copyBoard() | *copies board object*
- bool board::boardEqualP(board* testboard) | *just creates a board for testing, not relevant to anything but debugging*
- board\* board::reverseBoard() | *reverses board to show players view of the board (reverses array and switches the signs in the board array and on the bars)*

### boardList.cc
- BoardNode(board* BoardNode(board* board) | *BoardNode constructor just initializing linked list*
- BoardList() | *BoardList constructor just initializes linked list
- int isEmpty() | *checks if list is empty*
- void push(board* board) | *adds a board to the top of the linked list*
- board* pop() | *takes off and returns the top board on the boardList*
- board* first() | *returns first board in the list*
- BoardList* rest() | *creates new list that removes header from list*
- void print() | *prints the boardList dad*
- void removeDuplicates() | *removes duplicates on the boardlist*
- void Merge(BoardList* lst) | *appends lst to your BoardList*
- int findMax() | *finds maximum numRolls to remove interim moves*
 
### rollsList.cc
- isEmpty() | *checks if RollNode header is NULL or not, allow you to loop through rolls*
- pop() | *removes the last added RollNode in the list and returns the value of it*
- first() | *returns the value of RollNode header*
- rest() | *returns a new list with the first RollNode removed, just used in recursive function for AI*
- print() | *prints each RollsNode in RollsList*
-reverse() | *reverses the RollsList*

### bg.cc
- BoardList* generateMovesForSingleRoll(board* board1, int roll) | *generates all possible moves for single roll and stores board objects for possible moves in BoardList*
- BoardList* generateAllMoves(board* board1, RollsList* rolls, int numRolls) | *generates all possible moves for combined rolls and saves the numRolls needed to get to resulting board*
- BoardList* generateMoves(board* board1, RollsList* rolls) | *takes list of all possible moves and removes ones that dont use the maximum number of rolls available and removes duplicates*
- board* bestMove(board* currentBoard) | *from a current board, gives the best move for the AI*

### Backgammon.cc

### main.cc
