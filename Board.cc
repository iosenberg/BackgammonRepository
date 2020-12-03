#include "Board.h"

Board::Board(wxFrame *parent)
  : wxPanel(parent, wxID_ANY,wxDefaultPosition,
	    wxDefaultSize, wxBORDER_NONE)
{
  /*declaration of variables?
    want bool isplayersturn*/

  ClearBoard();

  Connect(wxEVT_PAINT, wxPaintEventHandler(Board::OnPaint));
  /*connect other events*/
}

void Board::OnInit(wxPaintEvent& event)
{
  
}

void Board::OnPaint(wxPaintEvent& event)
{
  wxPaintDC dc(this);

  wxSize size = GetClientSize();
  int boardTop = size.Getheight() - BoardHeight * SquareHeight();

  /*draw shapes*/

}

void Board::ClearBoard()
{
  /*maybe*/
}

void Board::Draw()
{
  /*i'm actually not gonna use this.
    Note for late coding:
    on init (in construction or in separate event), paint the board and background
    then on every turn, or update (probably timer update), paint all the pieces
  */
}
