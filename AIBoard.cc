#include <iostream>
#include "AIBoard.h"
using namespace std;

board::board()
  {
    for (int i = 0; i<24; i++) {
      boardArray[i] = 0;
    }
    numRolls = 0;
  }

//function to set board to starting game baord
void board::setInitialBoard(){
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

void board::setTestBoard(){
  boardArray[16] = 3;
  boardArray[19] = 5;
  bar = 0;
  opponentBar = 0;
}

bool board::readyToBearOff(){
  int sum = 0;
  for (int i = 0; i < 18; i++){
    if(boardArray[i] > 0){
      sum+= boardArray[i];
    }
  }
  if ((sum > 0) || (bar > 0)){
    return false;
  }
  return true;
}

//function to print board for testing
void board::printBoard(){
  for(int i = 0; i < 24; i++){
    cout << boardArray[i] << " ";
  }
  cout << "bar " << bar << " ";
  cout << "opponent-bar " << opponentBar << " ";
  cout << "num-rolls " << numRolls << endl;
}

//function to copy board - need this to generate possible boards
board* board::copyBoard(){
  board* newBoard = new board();
  for (int i = 0; i <24; i++){
    newBoard->boardArray[i] = boardArray[i];
  }
  newBoard->bar = bar;
  newBoard->opponentBar = opponentBar;
  return newBoard;
}

//checkes if two boards are equal, this will delete boards in our list of possible boards that are duplicates, not necessary but saves some time/efficiency
bool board::boardEqualP(board* testboard){
  bool check = true;
  int index = 0;
  if(bar != testboard->bar){
    check = false;
  }
  if(opponentBar != testboard->opponentBar){
    check = false;
  }
  for(int i = 0; i <24; i++){
    if (boardArray[i] != testboard->boardArray[i]){
      check = false;
      return false;
    }
  }
  return check;
}
  
//does this make a copy and reverse? or just reverse the original? also there is a way to do this recursively but i dont know how to without saving start and end as function calls, this iterative way works though
//function that "reverses" board, it will reverse the array and change the sign for all elements in array
board* board::reverseBoard(){
  //creates copy of board that will be reversed
  board* newBoard = copyBoard();
  //switches the bars
  newBoard->opponentBar = bar;
  newBoard->bar = opponentBar;
  //reverses the array
  int start = 0;
  int end = 23;
  while (start < end){
    int temp = newBoard->boardArray[start];
    newBoard->boardArray[start] = newBoard->boardArray[end];
    newBoard->boardArray[end] = temp;
    start++;
    end--;
  }
  //changes sign of array elements
  for(int i = 0; i <24; i++){
    newBoard->boardArray[i] = -newBoard->boardArray[i];
  }
  return newBoard;
}
