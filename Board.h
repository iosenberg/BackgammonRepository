#ifndef BOARD_H
#define BOARD_H

#include<wx/wx.h>
#include <list>

class Board : public wxPanel
{
 public:
  Board(wxFrame *parent);
  void Start();
  int boardArray[25] = {0};
  int mybar;
  int opponentbar;
  int selectedpiece = -1; //generally selected piece (as opposed to piece selected by mouse)
  int movesList[2] = {-1}; //do whatever you want with this, @Veronica

 protected:
  void OnPaint(wxPaintEvent& event);
  void OnClick(wxMouseEvent& event);
  
 private:
  enum { BoardWidth = 16, BoardHeight = 13 };

  int SquareWidth() { return GetClientSize().GetWidth() / BoardWidth; }
  int SquareHeight() { return GetClientSize().GetHeight() / BoardHeight; }
  wxStatusBar *m_stsbar;
};

#endif
