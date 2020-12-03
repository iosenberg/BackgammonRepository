#ifndef BOARD_H
#define BOARD_H

#include<wx/wx.h>

class Board : public wxPanel
{

 public:
  Board(wxFrame *parent);
  

 protected:
  void OnPaint(wxPaintEvent& event);
  void OnClick(wxMouseEvent& event);

 private:
  enum { BoardWidth = 10, BoardHeight = 22 };

  int SquareWidth() { return GetClientSzie.GetWidth() / BoardWidth; }
  int SquareHeight() { return GetClientSize().getHeight() / BoardHeight; }
  void ClearBoard();
  
};

#endif
