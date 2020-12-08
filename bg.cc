#include <iostream>
#include "boardList.h"
#include "rollsList.h"
using namespace std;

//generates all possible moves for a single roll (returns stack of board instances)
BoardList* generateMovesForSingleRoll(board* board1, int roll){
  //create stack for possibleBoards
  BoardList* possibleBoards = new BoardList();
  //check if any chips on bar
  if (board1->bar > 0){
    //check if chips can be taken off bar (slot is open)
    if(board1->boardArray[roll-1] > -1){
      //create new board where chip is taken off bar and into open slot
      board* possibleBoard = board1->copyBoard();
      possibleBoard->bar--;
      possibleBoard->boardArray[roll-1]++;
      //push possibleBoard onto BoardList
      possibleBoards->push(possibleBoard);
    }
  }
    //case for not on bar
  else {
    for (int i = 0; i < 24; i++){
      //check where your chips are
      if (board1->boardArray[i] > 0){
	//check if space roll away from that chip is open
	int moveindex = i+roll;
	if (moveindex < 24) {
	  if(board1->boardArray[moveindex] >= -1){
	    //add new possible board for each open piece and open slot
	    board* possibleBoard = board1->copyBoard();
	    possibleBoard->boardArray[moveindex]++;
	    possibleBoard->boardArray[i]--;
	    possibleBoards->push(possibleBoard);
	  }
	}
      }
    }
    if (board1->readyToBearOff()){
      if (board1->boardArray[24-roll] > 0) {
	board* possibleBoard = board1->copyBoard();
	possibleBoard->boardArray[24-roll]--;
	possibleBoards->push(possibleBoard);
      }
      else if (possibleBoards->isEmpty()) {
	for (int i = (24 - roll + 1); i < 24; i++) {
	  if (board1->boardArray[i] > 0) {
	    board* possibleBoard = board1->copyBoard();
	    possibleBoard->boardArray[i]--;
	    possibleBoards->push(possibleBoard);
	    break;
	  }
	}
      }
    }
  }
  return possibleBoards;
}

BoardList* generateAllMoves(board* board1, RollsList* rolls, int numRolls){
  BoardList* returnLst = new BoardList();
  if (!rolls->isEmpty()) {
    int roll = rolls->first();
    BoardList* movesForRoll = generateMovesForSingleRoll(board1,roll);
    while (!movesForRoll->isEmpty()) {
      board* move = movesForRoll->pop();
      move->numRolls = numRolls;
      returnLst->push(move);
      returnLst->Merge(generateAllMoves(move, rolls->rest(), numRolls+1));
    }
  }
  else {
    board1->numRolls = numRolls-1;
    returnLst->push(board1);
  }
  return returnLst;
}


//function for testing
int main(){
  board board1;
  board1.setInitialBoard();
  board1.printBoard();
  board* board2;
  board2 = board1.reverseBoard();
  board2->printBoard();
  if(board1.boardEqualP(board2)){
    cout << "True" << endl;
  }
  else{
    cout << "False" << endl;
  }
  board* board3 = board1.copyBoard();
  BoardList boardlist;
  boardlist.push(&board1);
  boardlist.push(board2);
  boardlist.push(board3);
  cout << "Printing List After Pushes" << endl;
  boardlist.print();
  boardlist.pop();
  cout << "Printing List After Pop" << endl;
  boardlist.print();
  boardlist.push(board3);
  boardlist.removeDuplicates();
  cout << "Printing List Removing Duplicates" << endl;
  boardlist.print();
  BoardList* moves = generateMovesForSingleRoll(&board1,6);
  cout << "Printing Original Board" << endl;
  board1.printBoard();
  cout << "Printing Moves" << endl;
  moves->print();
  RollsList* rolls = new RollsList(1,2);
  rolls->print();
  cout << "rolls" << endl;
  board board4;
  board4.setTestBoard();
  board4.printBoard();
  BoardList* moremoves = generateAllMoves(&board4, rolls, 1);
  moremoves->print();
  
  return 0;
}
