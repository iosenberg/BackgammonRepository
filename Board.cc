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
  boardArray[7] = -3;
  boardArray[11] = 5;
  boardArray[12] = -5;
  boardArray[16] = 3;
  boardArray[18] = 5;
  boardArray[23] = -2;
  mybar = 0;
  opponentbar = 0;
}

int Board::ToArray(int x, int y)
{
  int n;
  if(y<7) {
    n = 13 - x;
    if (x<7) n--;
  }
  else {
    n = x + 10;
    if (x<7) n++;
  }
  return n;
  
}

int Board::ToBoard(int i)
{
  int x;
  if(i>11) {
    x = i-11;
    if (i>17) x++;
  }
  else {
    x = BoardWidth-i-4;
    if (i<7) x++;
  }
  return x;    
}

void Board::OnPaint(wxPaintEvent& WXUNUSED(event))
{  
  wxPaintDC dc(this);


  //Draws the base board
  dc.SetPen(wxPen(wxColor(153,38,0))); //Outer, red section
  dc.SetBrush(wxBrush(wxColor(153,38,0)));
  dc.DrawRectangle(0,0,BoardWidth*SquareWidth(),BoardHeight*SquareHeight());

  dc.SetPen(wxPen(wxColor(51,10,83))); //two inner, brown sections
  dc.SetBrush(wxBrush(wxColor(198,140,83)));  //51, 10, 0 - for frame!!
  dc.DrawRectangle(SquareWidth()-1,SquareHeight()-1,6*SquareWidth()+2,11*SquareHeight()+3);
  dc.DrawRectangle(8*SquareWidth()-1,SquareHeight()-1,6*SquareWidth()+2,11*SquareHeight()+3);
  /*
  for (int i = 0;i < BoardWidth; ++i) {
    for (int j = 0; j < BoardHeight; ++j) {
      if (i==0 || j == 0 || i == BoardWidth/2 -1 || i >= BoardWidth-2 || j == BoardHeight-1) {
	dc.SetPen(wxPen(wxColor(153,38,0)));//51
	dc.SetBrush(wxBrush(wxColour(153,38,0)));
      }
      else {
	dc.SetPen(wxPen(wxColor(198,140,83)));
	dc.SetBrush(wxBrush(wxColour(198,140,83)));
      }
      dc.DrawRectangle(i*SquareWidth(),j*SquareHeight(),SquareWidth(),SquareHeight());
    }
  }
  */

  //Draws the triangles
  bool color = true; // true is white, false is brown
  dc.SetPen(wxPen(wxColor(115,77,38)));
  dc.SetBrush(wxBrush(wxColour(115,77,38)));
  for (int i = 1; i < BoardWidth - 2; ++i) {
    if(i!=BoardHeight/2 +1) {     
      wxPoint points1[] = {wxPoint(i*SquareWidth(), (BoardHeight-1)*SquareHeight()),
			   wxPoint((i+1)*SquareWidth()-1, (BoardHeight-1)*SquareHeight()),
			   wxPoint(i*SquareWidth()+SquareWidth()/2,(BoardHeight-6)*SquareHeight())};
      
      dc.DrawPolygon(3,points1,0,0,wxODDEVEN_RULE);
      
      if(color) {
	dc.SetPen(wxPen(wxColor(210,166,121)));
	dc.SetBrush(wxBrush(wxColor(210,166,121)));
      }
      else {
	dc.SetPen(wxPen(wxColor(115,77,38)));
	dc.SetBrush(wxBrush(wxColor(115,77,38)));
      }
      color = !color;
      
      wxPoint points2[] = {wxPoint(i*SquareWidth(), SquareHeight()),
			   wxPoint((i+1)*SquareWidth()-1, SquareHeight()),
			   wxPoint(i*SquareWidth()+SquareWidth()/2,6*SquareHeight())};
      
      dc.DrawPolygon(3,points2,0,0,wxODDEVEN_RULE);
    }
  }

    
  //Draws the dice
  dc.SetPen(wxPen(wxColor(51,10,0)));
  dc.SetBrush(wxBrush(wxColor(128,10,0)));
  dc.DrawRectangle(14*SquareWidth(),5*SquareHeight(),SquareWidth(),3*SquareHeight()+1);
  if (roll1*roll2 == 0) {
    dc.SetTextForeground(wxColor(255,255,0));
    dc.SetFont(wxFont(SquareHeight()*6/5, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL,
		      wxFONTWEIGHT_NORMAL,false));
    dc.DrawRotatedText(wxString("Roll!"),14.9*SquareWidth()+1,5.15*SquareHeight(),270);
  }
  else
    for (int i=0;i<2;++i) {
      double x = 14.1*SquareWidth();
      double y = 5.2*SquareHeight() + i*1.4*SquareHeight();
      double width = SquareWidth()*4/5;
      dc.SetPen(wxPen(wxColor(255,255,255)));
      dc.SetBrush(wxBrush(wxColor(255,255,255)));
      dc.DrawRectangle(x,y,width,width);
      
      width /= 4;
      
      dc.SetPen(wxPen(wxColor(0,0,0)));
      dc.SetBrush(wxBrush(wxColor(0,0,0)));
      switch(i ? roll1 : roll2) {
      case 1:
	dc.DrawCircle(x+2*width,y+2*width,width/3);
	break;
      case 2:
	dc.DrawCircle(x+3*width,y+width,width/3);
	dc.DrawCircle(x+width,y+3*width,width/3);
	break;
      case 3:
	dc.DrawCircle(x+3*width,y+width,width/3);
	dc.DrawCircle(x+2*width,y+2*width,width/3);
	dc.DrawCircle(x+width,y+3*width,width/3);
	break;
      case 4:
	dc.DrawCircle(x+width,y+width,width/3);
	dc.DrawCircle(x+3*width,y+width,width/3);
	dc.DrawCircle(x+width,y+3*width,width/3);
	dc.DrawCircle(x+3*width,y+3*width,width/3);
	break;
      case 5:
	dc.DrawCircle(x+width,y+width,width/3);
	dc.DrawCircle(x+3*width,y+width,width/3);
	dc.DrawCircle(x+width,y+3*width,width/3);
	dc.DrawCircle(x+3*width,y+3*width,width/3);
	dc.DrawCircle(x+2*width,y+2*width,width/3);
	break;
      case 6:
	dc.DrawCircle(x+width,y+width,width/3);
	dc.DrawCircle(x+width,y+2*width,width/3);
	dc.DrawCircle(x+width,y+3*width,width/3);
	dc.DrawCircle(x+3*width,y+width,width/3);
	dc.DrawCircle(x+3*width,y+2*width,width/3);
	dc.DrawCircle(x+3*width,y+3*width,width/3);
      }
    }

  //Draws the bar for both teams, and populates it appropriately
  dc.SetPen(wxPen(wxColor(51,10,0)));
  dc.SetBrush(wxBrush(wxColor(128,10,0)));
  dc.DrawRectangle(14*SquareWidth(),SquareHeight()-1,SquareWidth(),4*SquareHeight()+2);
  dc.DrawRectangle(14*SquareWidth(),8*SquareHeight()-1,SquareWidth(),4*SquareHeight()+3);
  
  //Draws the pieces
  for(int i=0;i<26;++i) { 
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
      dc.SetPen(wxColor(c,c,c));
      dc.SetBrush(wxBrush(wxColor(c,c,c)));
      for(int j=0;j<n;++j) {
	if(selectedpiece == i && j == n-1) {
	  dc.SetPen(wxPen(wxColor(255,255,0)));
	  dc.SetBrush(wxBrush(wxColor(255,255,0)));
	}
	int x = ToBoard(i) * SquareWidth() + SquareWidth()/2 - 1;
	if(i<12)
	  dc.DrawCircle(x,(j+1)*SquareHeight()+SquareHeight()/2,SquareWidth()/3);
	else if (i<24) 
	  dc.DrawCircle(x,(BoardHeight-j-1)*SquareHeight()-SquareHeight()/2,SquareWidth()/3);
	else if (i==25){}
	else {}
      }
    }
  }
}
	

void Board::OnClick(wxMouseEvent& event) //when the mouse is clicked within the window
{
  wxWindowDC dc(this);
  int x = event.GetLogicalPosition(dc).x/SquareWidth();
  int y = event.GetLogicalPosition(dc).y/SquareHeight();

  if (x == 14 && y > 4 && y < 8) { //they rolled the dice!
    if(roll1*roll2 == 0) {
      roll1 = (rand() % 6) + 1;
      roll2 = (rand() % 6) + 1;
    }
  }
  
  int selectedsection = -1;
  
  //takes the mouse position and calculates which section of the board is selected
  if(x>0)  selectedsection = ToArray(x,y);
  if(selectedsection != -1){
    roll1 = 0;
    roll2 = 0;
  }

  selectedpiece = selectedsection;
  //selectedsection is the index of the piece selected by the mouse click
  printf("%d,%d: %d\n",x,y,selectedsection);
  

 /* HERES THE FIRST COMMENT BRACKET. Sorry for commenting out all your code lol
 
  if(selectedpiece > -1 && selectedpiece < 25) {
    // 25 is white endspace, 24 is brown endspace
    // White is positive, brown is negative
    int startspace;
    int currentroll;
    int counter = 0;
    // Set start space
    //NOTE: we need code that prevents the player/AI from selecting anything off the bar if they have pieces on the bar.
    if (color == true && mybar != 0) startspace = 24;
    else if (color == false && opponentbar != 0) startspace = 0; // This is zero so if they roll a 1, the available spot is 1.
    else startspace = selectedpiece;
    // For each roll:
    while(counter != 2){ // Even if someone rolls doubles, the possible moves are going to be the same
      currentroll = currentRolls->RollsList::first();
      if(color == true) currentroll *= -1;
      int destination = startspace + currentroll;
      // Set a boolean for if a player has all their pieces in their side of the board?
      if(destination > 25) destination = 25;
      if(destination < 1) destination = 26;
      // Check if the spots on the board are available
      if(boardArray[destination] < -1 || boardArray[] > 1) continue;
      else movesList[counter] = destination;
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

  HERE'S THE LAST COMMENT BRACKET
  */


  //Player Moves
  //Change boardArray;
  //Refresh()
  //AI moves
  //Change boardArray;

  
  Refresh();
}
