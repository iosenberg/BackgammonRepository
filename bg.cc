#include "bg.h"

AI::AI() {}

//generates all possible moves for a single roll (returns stack of board instances)
BoardList* AI::generateMovesForSingleRoll(board* board1, int roll){
  //create stack for possibleBoards
  BoardList* possibleBoards = new BoardList();
  //check if any chips on bar
  if (board1->bar > 0){
    //check if chips can be taken off bar (slot is open)
    if(board1->boardArray[roll-1] > -1){
      //create new board where chip is taken off bar and into open slot
      board* possibleBoard = board1->copyBoard();
      possibleBoard->bar--;
      possibleBoard->boardArray[roll-1]++;
      //push possibleBoard onto BoardList
      possibleBoards->push(possibleBoard);
    }
  }
    //case for not on bar
  else {
    for (int i = 0; i < 24; i++){
      //check where your chips are
      if (board1->boardArray[i] > 0){
	//check if space roll away from that chip is open
	int moveindex = i+roll;
	if (moveindex < 24) {
	  if((board1->boardArray[moveindex] >= -1)&&(board1->boardArray[moveindex] <= 5)){
	    //add new possible board for each open piece and open slot
	    board* possibleBoard = board1->copyBoard();
	    possibleBoard->boardArray[moveindex]++;
	    possibleBoard->boardArray[i]--;
	    possibleBoards->push(possibleBoard);
	  }
	}
      }
    }
    if (board1->readyToBearOff()){
      if (board1->boardArray[24-roll] > 0) {
	board* possibleBoard = board1->copyBoard();
	possibleBoard->boardArray[24-roll]--;
	possibleBoards->push(possibleBoard);
      }
      else if (possibleBoards->isEmpty()) {
	for (int i = (24 - roll + 1); i < 24; i++) {
	  if (board1->boardArray[i] > 0) {
	    board* possibleBoard = board1->copyBoard();
	    possibleBoard->boardArray[i]--;
	    possibleBoards->push(possibleBoard);
	    break;
	  }
	}
      }
    }
  }
  return possibleBoards;
}

BoardList* AI::generateAllMoves(board* board1, RollsList* rolls, int numRolls){
  BoardList* returnLst = new BoardList();
  if (!rolls->isEmpty()) {
    int roll = rolls->first();
    BoardList* movesForRoll = generateMovesForSingleRoll(board1,roll);
    while (!movesForRoll->isEmpty()) {
      board* move = movesForRoll->pop();
      move->numRolls = numRolls;
      returnLst->push(move);
      returnLst->Merge(generateAllMoves(move, rolls->rest(), numRolls+1));
    }
  }
  else {
    board1->numRolls = numRolls-1;
    returnLst->push(board1);
  }
  return returnLst;
}

BoardList* AI::generateMoves(board* board1, RollsList* rolls){
  BoardList* possibleMoves = new BoardList();
  if(rolls->header == rolls->header->next){
    possibleMoves = generateAllMoves(board1, rolls, 1);
  }
  else{
    possibleMoves = generateAllMoves(board1, rolls, 1);
    rolls->reverse();
    possibleMoves->Merge(generateAllMoves(board1, rolls, 1));
  }
  int maxRolls = possibleMoves->findMax();
  BoardList* refinedMoves = new BoardList();
  BoardNode* current = possibleMoves->header;
  while(current!=NULL){
    if(current->boardData->numRolls == maxRolls){
      refinedMoves->push(current->boardData);
    }
    current = current->next;
  }
  refinedMoves->removeDuplicates();
  return refinedMoves;
}

//BoardList->BoardNode->boardData->boardArray,oppenentBar, etc
board* AI::bestMove(board* currentAIBoard, int roll1, int roll2){
  //need to free array and backward board
  RollsList* rolls = new RollsList(roll1,roll2);
  BoardList* refinedMoves = generateMoves(currentAIBoard, rolls);
  BoardNode* current = refinedMoves->header;
  bool check = true;
  while(current!=NULL){
    int sumNew = 0;
    int sumOriginal = 0;
    for(int i = 0; i<24; i++){
      if(current->boardData->boardArray[i] == 1){
	check = false;
      }
      if(current->boardData->boardArray[i] > 0){
	sumNew += current->boardData->boardArray[i];
      }
      if(currentAIBoard->boardArray[i] > 0){
	sumOriginal += currentAIBoard->boardArray[i];
      }
      
    }
    if(current->boardData->opponentBar > currentAIBoard->opponentBar){
	current->boardData->score++;
    }
    if (check){
      current->boardData->score++;
    }
    if(sumNew<sumOriginal){
      current->boardData->score++;
    }
    
    current = current->next;
  }
  current = refinedMoves->header;
  int maximumScore = -1;
  board* bestBoard;
  while(current != NULL){
    if(current->boardData->score > maximumScore){
      bestBoard = current->boardData;
      maximumScore = bestBoard->score;
    }
    current = current->next;
  }
  return bestBoard;
}

int* AI::AIMove(int* boardArray, int roll1, int roll2){
  board* currentBackwardBoard = new board();
  for(int i = 0; i<24; i++){
    currentBackwardBoard->boardArray[i] = boardArray[i];
  }
  currentBackwardBoard->bar = boardArray[25];
  currentBackwardBoard->opponentBar = boardArray[24];
  board* currentAIBoard;
  currentAIBoard = currentBackwardBoard->reverseBoard();
  board* bestBoard = bestMove(currentAIBoard, roll1, roll2);
  //in bestBoard - the player's bar is opponentBar and ai bar is bar
  //in bestBoardPlayerView = player's bar is bar and ai bar is opponentBar
  board* bestBoardPlayerView = bestBoard->reverseBoard();
  static int newBoardArray[26];
  for (int i = 0; i < 24; i++){
    newBoardArray[i] = bestBoardPlayerView->boardArray[i];
  }
  newBoardArray[24] = bestBoardPlayerView->opponentBar;
  newBoardArray[25] = bestBoardPlayerView->bar;
  return newBoardArray;
}


/*  
int AI::main(){
  int *p;
  int boardArray[26] = {0};
  p = AIMove(boardArray, 1, 2);
  for (int i = 0; i<26; i++){
    cout << p << " ";
  }
  cout << endl;
  return 0;
  }*/
  
