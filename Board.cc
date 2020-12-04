#include "Board.h"

Board::Board(wxFrame *parent)
  : wxPanel(parent, wxID_ANY,wxDefaultPosition,
	    wxDefaultSize, wxBORDER_NONE)
{
  // timer = new wxTimer(this,1);
  
  m_stsbar = parent->GetStatusBar();
  //ClearBoard();

  Connect(wxEVT_PAINT, wxPaintEventHandler(Board::OnPaint));
  Connect(wxEVT_LEFT_DOWN, wxMouseEventHandler(Board::OnClick));
  //Connect(wxEVT_TIMER, wxCommandEventHandler(Board::OnTimer));
  /*connect other events*/
  //timecolor = 115;
  std::cout << "Hello!!\n";
}

/*void Board::Start()
{
  timer->Start();
  }*/

void Board::OnPaint(wxPaintEvent& WXUNUSED(event))
{  
  wxPaintDC dc(this);

  //wxSize size = GetClientSize();
  // int boardTop = size.GetHeight() - BoardHeight * SquareHeight();
  //i==x,j==y
  for (int i = 0; i < BoardWidth; ++i) {
    for (int j = 0; j < BoardHeight; ++j) {
      if (i==0 || j == 0 || i == BoardWidth/2 -1 || i >= BoardWidth-2 || j == BoardHeight-1) {
	wxPen pen(wxColour(153,51,0));
	pen.SetCap(wxCAP_PROJECTING);
	dc.SetPen(pen);
	dc.SetBrush(wxBrush(wxColour(153,51,0)));
      }
      else {
	wxPen pen(wxColour(198,140,83));
	pen.SetCap(wxCAP_PROJECTING);
	dc.SetPen(pen);
	dc.SetBrush(wxBrush(wxColour(198,140,83)));
      }
      dc.DrawRectangle(i*SquareWidth(),j*SquareHeight(),SquareWidth(),SquareHeight());
    }
  }

  bool color = true; // true is white, false is brown
  wxPen pen(wxColor(115,77,38));
  pen.SetCap(wxCAP_PROJECTING);
  dc.SetPen(pen);
  dc.SetBrush(wxBrush(wxColour(115,77,38)));
  for (int i = 1; i < BoardWidth - 2; ++i) {
    if(i!=BoardHeight/2 +1) {     
      wxPoint points1[] = {wxPoint(i*SquareWidth(), (BoardHeight-1)*SquareHeight()),
			   wxPoint((i+1)*SquareWidth()-1, (BoardHeight-1)*SquareHeight()),
			   wxPoint(i*SquareWidth()+SquareWidth()/2,(BoardHeight-6)*SquareHeight())};
      dc.DrawPolygon(3,points1,0,0,wxODDEVEN_RULE);
      
      if(color) {
	wxPen pen(wxColor(249,242,236));
	dc.SetPen(pen);
	dc.SetBrush(wxBrush(wxColor(249,242,236)));
      }
      else {
	wxPen pen(wxColor(115,77,38));
	dc.SetPen(pen);
	dc.SetBrush(wxBrush(wxColor(115,77,38)));
      }
      color = !color;
      
      wxPoint points2[] = {wxPoint(i*SquareWidth(), SquareHeight()),
			   wxPoint((i+1)*SquareWidth()-1, SquareHeight()),
			   wxPoint(i*SquareWidth()+SquareWidth()/2,6*SquareHeight())};
    dc.DrawPolygon(3,points2,0,0,wxODDEVEN_RULE);
    }
  }
    //  dc.DrawCircle(SquareHeight()*BoardHeight/2,SquareWidth()*BoardWidth/2,SquareWidth());
      /* for (int i=0; i < size.GetHeight(); ++i) {
    //std::cout << timecolor + "\n";
    wxPen pen(wxColour(color1%255,color2%255,(color1*color2)%255));
    pen.SetCap(wxCAP_PROJECTING);
    dc.SetPen(pen);
    dc.DrawLine(0,i,size.GetWidth()-1,i);
    }*/
  /*draw shapes*/

}

void Board::OnClick(wxMouseEvent& WXUNUSED(event))
{
  wxWindowDC dc(this);
  //wxPoint position = event.GetLogicalPosition(dc);
  //  color1 = position.x;
  //color2 = position.y;
  //wxLogMessage("Hewwo? %d,%d\n",position.x,position.y);
  Refresh();
}
/*
void Board::OnTimer(wxCommandEvent& WXUNUSED(event))
{
  //  timecolor = (timecolor + 1) % 255;
  //  std::cout << timecolor;
  //Refresh();
  }*/
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
