#ifndef BOARD_H
#define BOARD_H

#include <wx/wx.h>
#include <iostream>
#include <list>
#include <ctime>
#include <cstdlib>
#include "bg.h"

class Board : public wxPanel
{
 public:
  Board(wxFrame *parent);
  int boardArray[26] = {0};
  int myendslot;
  int opponentendslot;
  int selectedpiece = -1; //generally selected piece (as opposed to piece selected by mouse)
  int movesList[4] = {-1,-1,-1,-1}; //do whatever you want with this, @Veronica
  int movesListSize = sizeof(movesList)/sizeof(movesList[0]); //Same with this. This is just here so I could code the triangles
  int roll1 = 0;
  int roll2 = 0;
  int currentRolls[4] = {-1,-1,-1,-1}; // -1 means no roll present
  bool rollsEmpty = true;
  bool playersturn = false;
  bool pieceChosen = false;
  bool isBearOff = false;
  int startspace = -1;
  int destination = -1;
  int endspace = -1;
  
 protected:
  void OnPaint(wxPaintEvent& event);
  void OnClick(wxMouseEvent& event);
  
 private:
  int ToArray(int x, int y);
  int ToBoard(int i);
  
  enum { BoardWidth = 16, BoardHeight = 13 };

  int SquareWidth() { return GetClientSize().GetWidth() / BoardWidth; }
  int SquareHeight() { return GetClientSize().GetHeight() / BoardHeight; }
  wxStatusBar *m_stsbar;
  
  AI *gameAI;
};

#endif
