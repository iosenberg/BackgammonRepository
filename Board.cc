#include <iostream>
#include "Board.h"
#include "rollsList.h"

Board::Board(wxFrame *parent)
  : wxPanel(parent, wxID_ANY,wxDefaultPosition,
	    wxDefaultSize, wxBORDER_NONE)
{
  m_stsbar = parent->GetStatusBar();
 
  Connect(wxEVT_PAINT, wxPaintEventHandler(Board::OnPaint));
  Connect(wxEVT_LEFT_DOWN, wxMouseEventHandler(Board::OnClick));

  boardArray[0] = 2;
  boardArray[5] = -5;
  boardArray[8] = -3;
  boardArray[11] = 5;
  boardArray[12] = -5;
  boardArray[15] = 3;
  boardArray[18] = 5;
  boardArray[23] = -2;
  mybar = 0;
  opponentbar = 0;
}

void Board::OnPaint(wxPaintEvent& WXUNUSED(event))
{  
  wxPaintDC dc(this);

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
	wxPen pen(wxColor(210,166,121));
	dc.SetPen(pen);
	dc.SetBrush(wxBrush(wxColor(210,166,121)));
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

  for(int i=0;i<24;++i) {
    if(boardArray[i] != 0) {
      int n;
      int c;
      if (boardArray[i] < 0) {
	n = -1*boardArray[i];
	c = 0;
      } else {
	n = boardArray[i];
	c = 255;
      }
      wxPen pen(wxColor(c,c,c));
      dc.SetPen(pen);
      dc.SetBrush(wxBrush(wxColor(c,c,c)));
      for(int j=0;j<n;++j) {
	if(selectedpiece == i && j == n-1) {
	  wxPen pen(wxColor(255,255,0));
	  dc.SetPen(pen);
	  dc.SetBrush(wxBrush(wxColor(255,255,0)));
	}
	if(i>11)
	  dc.DrawCircle((i-10)*SquareWidth()+SquareWidth()/2-1,
			(BoardHeight-j-1)*SquareHeight()-SquareHeight()/2,
			SquareWidth()/3);
	else
	  dc.DrawCircle((BoardWidth-i-2)*SquareWidth()-SquareWidth()/2-1,
			(j+1)*SquareHeight()+SquareHeight()/2,
			SquareWidth()/3);
      }
    }
  }

}

void Board::OnClick(wxMouseEvent& event) //when the mouse is clicked within the window
{
  wxWindowDC dc(this);
  int selectedsection;

  //takes the mouse position and calculates which section of the board is selected
  if(event.GetLogicalPosition(dc).y/SquareHeight() < 7)
    selectedsection = 13 - event.GetLogicalPosition(dc).x/SquareWidth();
  else
    selectedsection = event.GetLogicalPosition(dc).x/SquareWidth() + 10;
  //selectedsection is the index of the piece selected by the mouse click
  
  if(selectedpiece > -1 && selectedpiece < 25) {
    // 0 is bar, 25 is white endspace, 26 is brown endspace
    // White is positive, brown is negative
    int startspace;
    if (selectedpiece == 0){
      if (color == true) startspace = 26;
      else if (color == false) startspace = 25;
    } else startspace = selectedpiece;
  }
  
    if(//selectedsection is in list of possible moves
       ) {
      //make move
      selectedpiece = -1; //resets what piece is selected to none
    }
    else {
      selectedpiece = selectedsection;
      //list of possible moves = get moves list function
    }
  }
  else { //it also has to go down here
    selectedpiece = selectedsection;
    //list of possible moves = get moves list function
  }
  
  Refresh();
}
