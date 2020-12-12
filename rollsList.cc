#include <iostream>
#include "rollsList.h"
using namespace std;

RollNode::RollNode(int rollVal){
  this->roll = rollVal;
  this->next = NULL;
}

RollsList::RollsList() {
  header = NULL;
}

RollsList::RollsList(int roll1, int roll2) {
  header = new RollNode(roll1);
  RollNode* temp = new RollNode(roll2);
  header->next = temp;
  if (roll1 == roll2){
    RollNode* temp2 = new RollNode(roll2);
    temp->next = temp2;
    temp = new RollNode(roll2);
    temp2->next = temp;
  } 
}


int RollsList::isEmpty(){
  return !header;
}

//need to return like empty board and idk what that would look like.  i dont even use pop for this list so its ok
int RollsList::pop(){
  if (!header){
    return -1;
  }
  RollNode* temp = header;
  int val;
  header = header->next;
  val = temp->roll;
  delete temp;
  return val;
}

int RollsList::first() {
  if (!header){
    return -1;
  }
  else {
    return header->roll;
  }
}

RollsList* RollsList::rest() {
  RollsList* newlst = new RollsList();
  if (header != NULL) {
    newlst->header = header->next;
  }
  return newlst;
}

void RollsList::print(){
  RollNode* current = header;
  while (current != NULL) {
    cout << current->roll << " ";
    current = current->next;
  }
  cout << endl;
}

void RollsList::reverse(){
  RollNode* current = header;
  RollNode *prev = NULL, *next = NULL;
  while (current != NULL){
    next = current->next;
    current->next = prev;
    prev = current;
    current = next;
  }
  header = prev;
}
