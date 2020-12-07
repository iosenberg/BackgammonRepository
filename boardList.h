#include <iostream>
#include "AIBoard.h"
using namespace std;

#ifndef BOARDLIST_H
#define BOARDLIST_H

class BoardNode {
public:
  board *boardData;
  BoardNode* next;
  
  BoardNode(board*);
};

class BoardList {
public:
  BoardNode* header;
  
  BoardList();
  int isEmpty();
  void push(board*);
  board* pop();
  void print();
  void removeDuplicates();
  void Merge(BoardList*);

};


#endif
