#include <iostream>
using namespace std;

// dice class - creates two rolls and their frequency
class dice {
public:
  int roll1;
  int roll2;
  int frequency1 = 0;
  int frequency2 = 0;
  dice() {
    //constructor calls roll() function
    roll();
  }
  void roll(){
    //sets random values 1-6 to both rolls
    roll1 = rand()%6+1;
    roll2 = rand()%6+1;
    if(roll1 == roll2){
      //how do i delete the value in roll2? do i need to?
      //sets frequency to 4 if doubles
      frequency1 = 4;
    }
    else{
      //sets frequency to 1 if not doubles
      frequency1 = 1;
      frequency2 = 1;
    }
  }
  //function to print roll for testing
  void printRoll(){
    cout << "roll1 " << roll1; 
    cout << "roll2 " << roll2;
    cout << "f1 " << frequency1;
    cout << "f2 " << frequency2;
  }
};

class board {
public:
  //initial board array (this gives a warning so maybe something wrong with this. still works though)
  int boardArray[24] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  int bar;
  int opponentBar;

  //function to set board to starting game baord
  void setInitialBoard(){
    boardArray[0] = 2;
    boardArray[5] = -5;
    boardArray[7] = -3;
    boardArray[11] = 5;
    boardArray[12] = -5;
    boardArray[16] = 3;
    boardArray[19] = 5;
    boardArray[23] = -2;
    bar = 0;
    opponentBar = 0;
  }

  //function to print board for testing
  void printBoard(){
    for(int i = 0; i < 24; i++){
      cout << boardArray[i] << " ";
    }
    cout << bar << " ";
    cout << opponentBar << endl;
  }

  //function to copy board - need this to generate possible boards
  board copyBoard(board originalBoard){
    board newBoard;
    for (int i = 0; i <24; i++){
      newBoard.boardArray[i] = originalBoard.boardArray[i];
    }
    newBoard.bar = originalBoard.bar;
    newBoard.opponentBar = originalBoard.opponentBar;
    return newBoard;
  }

  //checkes if two boards are equal, this will delete boards in our list of possible boards that are duplicates, not necessary but saves some time/efficiency
  bool boardEqualP(board board1, board board2){
    bool check = true;
    int index = 0;
    if(board1.bar != board2.bar){
      check = false;
    }
    if(board1.opponentBar != board2.opponentBar){
      check = false;
    }
    for(int i = 0; i <24; i++){
      if (board1.boardArray[i] != board2.boardArray[i]){
	check = false;
	return false;
      }
    }
    return check;
  }
  
  //does this make a copy and reverse? or just reverse the original? also there is a way to do this recursively but i dont know how to without saving start and end as function calls, this iterative way works though
  //function that "reverses" board, it will reverse the array and change the sign for all elements in array
  board reverseBoard(board board1){
    //creates copy of board that will be reversed
    board newBoard = board1.copyBoard(board1);
    //switches the bars
    int temp = newBoard.opponentBar;
    newBoard.opponentBar = newBoard.bar;
    newBoard.bar = temp;
    //reverses the array
    int start = 0;
    int end = 23;
    while (start < end){
      int temp = newBoard.boardArray[start];
      newBoard.boardArray[start] = newBoard.boardArray[end];
      newBoard.boardArray[end] = temp;
      start++;
      end--;
    }
    //changes sign of array elements
    for(int i = 0; i <24; i++){
      newBoard.boardArray[i] = -newBoard.boardArray[i];
    }
    return newBoard;
  }
         
};

//class stack to hold the list of possible boards
class StackNode {
public:
  board data;
  StackNode* next;
};

StackNode* newNode(board data){
  StackNode* stackNode = new StackNode();
  stackNode->data = data;
  stackNode->next = NULL;
  return stackNode;
}

int isEmpty(StackNode* root){
  return !root;
}

void push(StackNode** root, board data){
  StackNode* stackNode = newNode(data);
  stackNode->next = *root;
  *root = stackNode;
  data.printBoard();
  cout << " pushed to stack\n";
}

//need to return like empty board and idk what that would look like.  i dont even use pop for this list so its ok
//board pop(StackNode** root){
//  if (isEmpty(*root)){
//    return NULL?;
//  }
//  StackNode* temp = *root;
//  *root = (*root)->next;
//  board popped = temp->data;
//  free(temp);
//  return popped;
//}



//generates all possible moves for a single roll (returns stack of board instances)
StackNode* generateMovesForSingleRoll(board board1, int roll){
  //create stack for possibleBoards
  StackNode* possibleBoards = NULL;
  //check if any chips on bar
  if (board1.bar > 0){
    //check if chips can be taken off bar (slot is open)
    if(board1.boardArray[roll-1] > -1){
      //create new board where chip is taken off bar and into open slot
      board possibleBoard = board1.copyBoard(board1);
      possibleBoard.bar--;
      possibleBoard.boardArray[roll-1]++;
      //push possibleBoard onto stack
      push(&possibleBoards, possibleBoard);
    }
  }
  //case for not on bar
  else {
    for (int i = 0; i < 24; i++){
      //check if where your chips are
      if (board1.boardArray[i] > 0){
	//check if space roll away from that chip is open
	if(board1.boardArray[i+roll] >= -1){
	  //add new possible board for each open piece and open slot
	  board possibleBoard = board1.copyBoard(board1);
	  possibleBoard.boardArray[i+roll]++; //= board1.boardArray[i+roll]+1;
	  possibleBoard.boardArray[i]--;//=board1.boardArray[i]-1;
	  push(&possibleBoards, possibleBoard);
	}
      }
    }
  }
  return possibleBoards;
}
    


//function for testing
int main(){
  board board1;
  board1.setInitialBoard();
  board1.printBoard();
  board board2;
  board2 = board1.copyBoard(board1);
  board2.printBoard();
  board board3;
  board3 = board2.reverseBoard(board2);
  board3.printBoard();
  if(board1.boardEqualP(board1, board2)){
    cout << "True" << endl;
  }
  else{
    cout << "False" << endl;
  }
  board barBoard;
  barBoard.bar = 1;
  barBoard.boardArray[0] = -2;
  generateMovesForSingleRoll(barBoard, 1);
  return 0;
}
    






//using board as an array

//print board - function to print board for testing

//delete_all_boards - function delete all boards - this needs to happen so that in our generate all legal board moves function, we can delete options (ie: sometimes we save the move of a single dice roll if that is the only legal move, but other times we want to delete the saved single roll moves because there are legal moves for both rolls

//board_equal_p - function to check if two boards are equal

//reverse_board - function reverse board --> this will reverse the values of the pieces on the board. this makes it so that we can have two computers play each other pretty easily.  essentially just lets you switch players.   (if array index 3 has value -1, it will be switched to 1

//copy array - function to copy array 

//roll - function for roll - we should make this return the number and the frequency -- that way when we get double 3's we can have it return (3, 4) and therefore know to generate possible moves where you can move 3 four times.

//functions for bearing off:
//no_checkers_in_range_p(board, start, end) 
//bearing_off_p(board)
//no_checkers_outside_of_roll_p(board, roll)
//no_checkers_on_board_p (board) 

//generate_boards_for_roll(board, roll) - this will generate all possible moves for a particular board and a given roll - this means a SINGLE roll, give all legal moves

//generate_moves (initial board, rolls) - this will generate all legal moves for multiple rolls and it will call the above generate_boards_for_roll function
