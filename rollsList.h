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
  RollsList(int);
  RollsList(int,int);
  int isEmpty();
  int pop();
  int first();
  RollsList* rest();
  void print();
  void reverse();

};


#endif
