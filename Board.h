#ifndef BOARD_H
#define BOARD_H

#include<wx/wx.h>

class Board : public wxPanel
{

 public:
  Board(wxFrame *parent);
  void Setup();  

 protected:
  void OnPaint(wxPaintEvent& event);
  void OnClick(wxMouseEvent& event);

 private:
  enum { BoardWidth = 10, BoardHeight = 22 };

  int SquareWidth() { return GetClientSize().GetWidth() / BoardWidth; }
  int SquareHeight() { return GetClientSize().GetHeight() / BoardHeight; }
  void ClearBoard();
  
};

#endif
