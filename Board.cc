#include "Board.h"

Board::Board(wxFrame *parent)
  : wxPanel(parent, wxID_ANY,wxDefaultPosition,
	    wxDefaultSize, wxBORDER_NONE)
{
  
  m_stsbar = parent->GetStatusBar();
  ClearBoard();

  Connect(wxEVT_PAINT, wxPaintEventHandler(Board::OnPaint));
  Connect(wxEVT_LEFT_DOWN, wxMouseEventHandler(Board::OnClick));
  /*connect other events*/
}

void Board::OnSetup()
{

}



void Board::OnPaint(wxPaintEvent& event)
{
  wxPaintDC dc(this);

  wxSize size = GetClientSize();
  int boardTop = size.Getheight() - BoardHeight * SquareHeight();

  for (int i=0; i < BoardHeigher; ++i) {
    dc.DrawLine(i,boardTop-1,i,0);
  }
  /*draw shapes*/

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
