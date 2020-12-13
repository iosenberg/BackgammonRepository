#include "boardList.h"

BoardNode::BoardNode(board* board){
  this->boardData = board;
  this->next = NULL;
}

BoardList::BoardList() {
  header = NULL;
}

int BoardList::isEmpty(){
  return !header;
}

void BoardList::push(board* board){
  BoardNode* boardNode = new BoardNode(board);
  boardNode->next = header;
  header = boardNode;
}

//need to return like empty board and idk what that would look like.  i dont even use pop for this list so its ok
board* BoardList::pop(){
  if (!header){
    return NULL;
  }
  BoardNode* temp = header;
  board* val;
  header = header->next;
  val = temp->boardData;
  free(temp);
  return val;
}

board* BoardList::first() {
  if (!header){
    return NULL;
  }
  else {
    return header->boardData;
  }
}

BoardList* BoardList::rest() {
  BoardList* newlst = new BoardList();
  if (header != NULL) {
    newlst->header = header->next;
  }
  return newlst;
}

void BoardList::print(){
  BoardNode* current = header;
  while (current != NULL) {
    current->boardData->printBoard();
    current = current->next;
  }
}

void BoardList::removeDuplicates(){
  BoardNode* currentNode = header;
  while (currentNode != NULL) {
    board* currentBoard = currentNode->boardData;
    BoardNode* next = currentNode->next;
    BoardNode* prev = currentNode;
    while (next != NULL) {
      if (currentBoard->boardEqualP(next->boardData)) {
	prev->next = next->next;
      }
      else {
	prev = next;
      }
      next = next->next;
    }
    currentNode = currentNode->next;
  }
}

void BoardList::Merge(BoardList* lst){
  BoardNode* current = header;
  BoardNode* temp;
  if (header == NULL) {
    header = lst->header;
  }
  else {
    while(current != NULL){
      temp = current;
      current = current->next;
    }
    temp->next = lst->header;
  }
}

int BoardList::findMax(){
  int max = 0;
  BoardNode* current = header;
  while(current !=NULL){
    if(current->boardData->numRolls > max){
      max = current->boardData->numRolls;
    }
    current = current->next;
  }
  return max;
}



  
  
  
