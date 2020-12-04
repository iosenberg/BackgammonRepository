#ifndef BOARD_H
#define BOARD_H

#include<wx/wx.h>

class Board : public wxPanel
{

 public:
  Board(wxFrame *parent);
  void Start();
  int boardArray[24] = {0};
  int mybar;
  int opponentbar;
  int selectedpiece = -1;

 protected:
  void OnPaint(wxPaintEvent& event);
  void OnClick(wxMouseEvent& event);
  //  void OnTimer(wxCommandEvent& event);
  
 private:
  enum { BoardWidth = 16, BoardHeight = 13 };

  int SquareWidth() { return GetClientSize().GetWidth() / BoardWidth; }
  int SquareHeight() { return GetClientSize().GetHeight() / BoardHeight; }
  wxStatusBar *m_stsbar;
  // wxTimer *timer;
  //int timecolor;
};

#endif
