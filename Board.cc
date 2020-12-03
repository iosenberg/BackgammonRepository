#include "Board.h"

Board::Board(wxFrame *parent)
  : wxPanel(parent, wxID_ANY,wxDefaultPosition,
	    wxDefaultSize, wxBORDER_NONE)
{
  timer = new wxTimer(this,1);
  
  m_stsbar = parent->GetStatusBar();
  //ClearBoard();

  Connect(wxEVT_PAINT, wxPaintEventHandler(Board::OnPaint));
  Connect(wxEVT_LEFT_DOWN, wxMouseEventHandler(Board::OnClick));
  Connect(wxEVT_TIMER, wxCommandEventHandler(Board::OnTimer));
  /*connect other events*/
  timer = new wxTimer(this,1);
  timer->Start();
  timecolor = 115;
  std::cout << "Hello!!\n";
}

void Board::OnPaint(__attribute__((unused)) wxPaintEvent& event)
{
  std::cout << "Paintin Time\n";
  
  wxPaintDC dc(this);

  wxSize size = GetClientSize();
  // int boardTop = size.GetHeight() - BoardHeight * SquareHeight();

  for (int i=0; i < size.GetHeight(); ++i) {
    std::cout << timecolor + "\n";
    wxPen pen(wxColour(i%255,i%255,i%255));
    pen.SetCap(wxCAP_PROJECTING);
    dc.SetPen(pen);
    dc.DrawLine(i,size.GetWidth()-1,i,0);
  }
  /*draw shapes*/

}

void Board::OnClick(__attribute__((unused)) wxMouseEvent& event)
{
  wxLogMessage("Hewwo? %d\n",timer->GetInterval());
}

void Board::OnTimer(__attribute__((unused)) wxCommandEvent& event)
{
  timecolor = (timecolor + 1) % 255;
  //  std::cout << timecolor;
  Refresh();
}
/*void Board::ClearBoard()
{
  maybe
}

void Board::Draw()
{
  i'm actually not gonna use this.
    Note for late coding:
    on init (in construction or in separate event), paint the board and background
    then on every turn, or update (probably timer update), paint all the pieces
  
}
*/
