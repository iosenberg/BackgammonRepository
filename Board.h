#ifndef BOARD_H
#define BOARD_H

#include <wx/wx.h>
#include <list>

class Board : public wxPanel
{
 public:
  Board(wxFrame *parent);
  void Start();
  int boardArray[26] = {0};
  int mybar;
  int opponentbar;
  int selectedpiece = -1; //generally selected piece (as opposed to piece selected by mouse)
  int movesList[3] = {2,4,19}; //do whatever you want with this, @Veronica
  int movesListSize = sizeof(movesList)/sizeof(movesList[0]); //Same with this. This is just here so I could code the triangles
  int roll1 = 0;
  int roll2 = 0;

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
};

#endif
