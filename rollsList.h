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
  
  RollsList(int, int);
  int isEmpty();
  int pop();
  void print();

};


#endif
