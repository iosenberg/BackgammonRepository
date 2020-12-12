#include <iostream>
#include "boardList.h"
#include "rollsList.h"
#include "Board.h"
using namespace std;

#ifndef BG_H
#define BG_H

BoardList* generateMovesForSingleRoll(board* board1, int roll);

BoardList* generateAllMoves(board* board1, RollsList* rolls, int numRolls);

BoardList* generateMoves(board* board1, RollsList* rolls);

board* bestMove(board* currentAIBoard, int roll1, int roll2);

int* AIMove(int* boardArray, int roll1, int roll2);

#endif

