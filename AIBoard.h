#include <iostream>
using namespace std;

#ifndef AIBOARD_H
#define AIBOARD_H

class board {
public:
  //initial board array (this gives a warning so maybe something wrong with this. still works though)
  int boardArray[24];
  int bar;
  int opponentBar;
  int numRolls;
  int score;

  board();
  void setInitialBoard();
  void setTestBoard();
  bool readyToBearOff();
  void printBoard();
  board* copyBoard();
  board* reverseBoard();
  bool boardEqualP(board*);
};

#endif

    
