#include <iostream>
using namespace std;

#ifndef ROLLSLIST_H
#define ROLLSLIST_H

class RollNode {
public:
  int roll;
  RollNode* next;
  RollNode(int);
};

class RollsList {
public:
  RollNode* header;

  RollsList();
  void setRolls(int, int);
  int isEmpty();
  int pop();
  int first();
  RollsList* rest();
  void print();
  void reverse();

};


#endif
