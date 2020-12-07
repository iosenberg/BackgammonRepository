#include <iostream>
using namespace std;

#ifndef BOARD_H
#define BOARD_H

class board {
public:
  //initial board array (this gives a warning so maybe something wrong with this. still works though)
  int boardArray[24];
  int bar;
  int opponentBar;
  int numRolls;

  board();
  void setInitialBoard();
  bool readyToBearOff();
  void printBoard();
  board* copyBoard();
  board* reverseBoard();
  bool boardEqualP(board*);
};

#endif

    
