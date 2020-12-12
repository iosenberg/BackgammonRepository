#include <iostream>
#include "Board.h"
//#include "bg.h"

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
  myendslot = 0;
  opponentendslot = 0;
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
  if(i==24 || i==25)
    return 7;
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

  //Draws the triangles
  bool color = true; // true is white, false is brown
  dc.SetPen(wxPen(wxColor(115,77,38)));
  dc.SetBrush(wxBrush(wxColour(115,77,38)));
  for (int i = 1; i < BoardWidth - 2; ++i) {
    if(i!=BoardHeight/2 +1) {

      if(color) {
	dc.SetPen(wxPen(wxColor(210,166,121)));
	dc.SetBrush(wxBrush(wxColor(210,166,121)));
      }
      else {
	dc.SetPen(wxPen(wxColor(115,77,38)));
	dc.SetBrush(wxBrush(wxColor(115,77,38)));
      }
      
      for (int j=0;j<movesListSize;++j) {
	if (ToArray(i, 11) == movesList[j]) {
	  dc.SetPen(wxPen(wxColor(255,255,0)));
	  dc.SetBrush(wxBrush(wxColor(255,255,0)));
	}
      }
      
      
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

      for (int j=0;j<movesListSize;++j) {
	  if (ToArray(i, 1) == movesList[j]) {
	    dc.SetPen(wxPen(wxColor(255,255,0)));
	    dc.SetBrush(wxBrush(wxColor(255,255,0)));
	  }
	}
      
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

  //Draws the end slot for both teams, and populates it appropriately
  dc.SetPen(wxPen(wxColor(51,10,0)));
  dc.SetBrush(wxBrush(wxColor(128,10,0)));
  dc.DrawRectangle(14*SquareWidth(),SquareHeight()-1,SquareWidth(),4*SquareHeight()+2);
  dc.DrawRectangle(14*SquareWidth(),8*SquareHeight()-1,SquareWidth(),4*SquareHeight()+3);

  dc.SetBrush(wxBrush(wxColor(0,0,0)));
  for (int i=0;i<opponentendslot;i++) {
    dc.DrawRectangle(14*SquareWidth()+1,SquareHeight()+i*((4*SquareHeight()+2)/15),SquareWidth()-1,(4*SquareHeight()+2)/15);
  }
  dc.SetBrush(wxBrush(wxColor(255,255,255)));
  for (int i=0;i<myendslot;i++) {
    dc.DrawRectangle(14*SquareWidth()+1,(BoardHeight-1)*SquareHeight()-2-(i+0.5)*((4*SquareHeight()+3)/15),SquareWidth()-2,(4*SquareHeight()+3)/15);
  }  
  
  //Draws the pieces
  for(int i=0;i<26;++i) { 
    if(boardArray[i] != 0) {
      int n;
      int c;
      if (boardArray[i] < 0 || i == 25) {
	if(boardArray[i]<0)
	  n = -1*boardArray[i];
	else
	  n = boardArray[i];
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
	if(i<12 || i==24)
	  dc.DrawCircle(x,(j+1)*SquareHeight()+SquareHeight()/2,SquareWidth()/3);
	else
	  dc.DrawCircle(x,(BoardHeight-j-1)*SquareHeight()-SquareHeight()/2,SquareWidth()/3);
      }
    }
  }

  //Displays a "Thinking" banner when the AI is calculating moves.
  if(playersturn && rollsEmpty) {
    dc.SetTextForeground(wxColor(0,0,0));
    dc.SetFont(wxFont(SquareWidth()*2,wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL,
		      wxFONTWEIGHT_NORMAL,false));
    dc.DrawText("Thinking...",3*SquareWidth(),5*SquareHeight());
  }
}
	

void Board::OnClick(wxMouseEvent& event) //when the mouse is clicked within the window
{
  wxWindowDC dc(this);
  int x = event.GetLogicalPosition(dc).x/SquareWidth();
  int y = event.GetLogicalPosition(dc).y/SquareHeight();
    
  if (x == 14 && y > 4 && y < 8) { //they rolled the dice!
    if (!playersturn && rollsEmpty){
      roll1 = (rand() % 6) + 1;
      roll2 = (rand() % 6) + 1;
      if (roll1 == roll2) { // if they roll doubles
	for(int r=0; r<4; r++) currentRolls[r] = roll1;
      } else{
	currentRolls[0] = roll1;
	currentRolls[1] = roll2;
	currentRolls[2] = 0;
	currentRolls[3] = 0;
      }
      rollsEmpty = false;
      playersturn = true;
      pieceChosen = false;
      std::cout << "Successful Roll!" << std::endl;
      std::cout << "Rolls are: " << currentRolls[0] << ", " << currentRolls[1] << ", " << currentRolls[2] << ", and " << currentRolls[3] << std::endl;
    } 
  }
  
  int selectedsection = -1;
  
  // Collects mouse position
  if(x>0)  selectedsection = ToArray(x,y);
  /*if(selectedsection != -1){ 
    roll1 = 0;
    roll2 = 0;
    }*/
  
  selectedpiece = selectedsection;
                       
  if(playersturn && !rollsEmpty){
  
    if(pieceChosen){
      // Moves list section 1
      if(selectedsection == movesList[0]){
	endspace = movesList[0];
	std::cout << "Moving " << startspace << " to " << endspace << std::endl;
	// Capturing a piece
	if(boardArray[endspace] == -1) {
	  if(startspace > -1) boardArray[startspace] -= 1;
	  else boardArray[25] -=1;
	  boardArray[endspace] += 2;
	  boardArray[24] += 1; // Add one to brown's bar
	}
	// Moving into home
	else if(endspace > 23) {
	  if(startspace > -1) boardArray[startspace] -= 1;
          else boardArray[25] -=1;
	  myendslot += 1;
	}
	// Else, move the chip
	else {
	  if(startspace > -1) boardArray[startspace] -= 1;
          else boardArray[25] -=1;
	  boardArray[endspace] += 1;
	}
	movesList[0] = -1;
	if(movesList[1] == -1 && movesList[2] == -1 && movesList[3] == -1){
	  rollsEmpty = true;
	  pieceChosen = false;
	}
      }
      // Moves list section 2
      else if (selectedsection == movesList[1]){
	endspace = movesList[1];
	std::cout << "Moving " << startspace << " to " << endspace << std::endl;
        // Capturing a piece
        if(boardArray[endspace] == -1) {
          if(startspace > -1) boardArray[startspace] -= 1;
          else boardArray[25] -=1;	
          boardArray[endspace] += 2;
          boardArray[24] += 1; // Add one to brown's bar
        }
        // Moving into home        
        else if(endspace > 23) {
          if(startspace > -1) boardArray[startspace] -= 1;
          else boardArray[25] -=1;
          myendslot += 1;
        }
        // Else, move the chip
        else {
          if(startspace > -1) boardArray[startspace] -= 1;
          else boardArray[25] -=1;
          boardArray[endspace] += 1;
        }
	movesList[1] = -1;
	if(movesList[0] == -1 && movesList[2] == -1 && movesList[3] == -1){
	  rollsEmpty = true;
	  pieceChosen = false;
	}
      }
      // Moves list section 3 (doubles only)
      else if(selectedsection == movesList[2]){ 
	endspace = movesList[2];
	std::cout << "Moving " << startspace << " to " << endspace << std::endl;
        // Capturing a piece
        if(boardArray[endspace] == -1) {
          if(startspace > -1) boardArray[startspace] -= 1;
          else boardArray[25] -=1;	
          boardArray[endspace] += 2;
          boardArray[24] += 1; // Add one to brown's bar
        }
        // Moving into home
        else if(endspace > 23) {
          if(startspace > -1) boardArray[startspace] -= 1;
          else boardArray[25] -=1;
          myendslot += 1;
        }
        // Else, move the chip
        else {
          if(startspace > -1) boardArray[startspace] -= 1;
          else boardArray[25] -=1;
          boardArray[endspace] += 1;
        }                                                          
	movesList[2] = -1;
	if(movesList[0] == -1 && movesList[1] == -1 && movesList[3] == -1){
          rollsEmpty = true;
          pieceChosen = false;
        }
      }
      // Moves list section 4 (doubles only)
      else if (selectedsection == movesList[3]){
	endspace = movesList[3];
	std::cout << "Moving " << startspace << " to " << endspace << std::endl;
        // Capturing a piece
        if(boardArray[endspace] == -1) {
          if(startspace > -1) boardArray[startspace] -= 1;
          else boardArray[25] -=1;	
          boardArray[endspace] += 2;
          boardArray[24] += 1;
        }
        // Moving to home
        else if(endspace > 23) {
          if(startspace > -1) boardArray[startspace] -= 1;
          else boardArray[25] -=1;
          myendslot += 1;
        }
        // Else, move the chip
        else {
          if(startspace > -1) boardArray[startspace] -= 1;
          else boardArray[25] -=1;
          boardArray[endspace] += 1;
        }
        movesList[3] = -1;
        if(movesList[0] == -1 && movesList[1] == -1 && movesList[2] == -1){
          rollsEmpty = true;
          pieceChosen = false;
        }
      }
      // If a different piece is selected
      else {
      selectedpiece = selectedsection;
      if(0 < boardArray[25]) startspace = -1;
      else startspace = selectedpiece;
      }
    }
    
    if(!pieceChosen){
      if(boardArray[25] > 0) { // If white pieces on bar,
        startspace = -1; // Start on brown's "endslot"
        pieceChosen = true;
      } else {
        startspace = selectedpiece;
        pieceChosen = true;
      }
    }
    
    // Calculates the possible moves
    if(currentRolls[2] > 0){
      for(int counter=0;counter<4;counter++){            
	destination = startspace + currentRolls[counter];
        // If there are more than 2 brown or more than 4 white, skip.
        if(boardArray[destination] < -1 || boardArray[destination] > 4){
	  movesList[counter] = -1;
	  continue;
	}
        // If bearOff == false and destination > 23, skip
	else if(!isBearOff && destination > 23) {
	  movesList[counter] = -1;
	  continue;
	}
        // Else the space is available
        else movesList[counter] = destination;
      }
    }else {
      for(int counter=0;counter<2;counter++){
        destination = startspace + currentRolls[counter];
        // If there are more than 2 brown or more than 4 white, skip
        if(boardArray[destination] < -1 || boardArray[destination] > 4){
	  movesList[counter] = -1;
	  continue;
	}
        // If bearOff == false and destination > 23, skip
        else if(!isBearOff && destination > 23){
	  movesList[counter] = -1;
	  continue;
	}
        // Else the space is available
        else movesList[counter] = destination;
      }
    }
    std::cout << "Your possible moves are: " << movesList[0] << ", " << movesList[1] << ", " <<  movesList[2] << ", and " << movesList[3] << std::endl;
    
  } if(playersturn && rollsEmpty){
	  roll1 = (rand() % 6) + 1;
	  roll2 = (rand() % 6) + 1;
	  Refresh();
	  
	  playersturn = false;
	  pieceChosen = false;
	                                                
	  // Run AI code (Roll dice, calculate moves, etc.)
	  // boardArray = AIMove(&boardArray, AIroll1, AIroll2);
	  // Update board w/ AI's move
  }
                                                                                
  if(myendslot == 15 || opponentendslot == 15){                      
    //- Display an endscreen based on who won?                                    
    //- wait 60 seconds                                                           
    //- exit                                         
  }
  Refresh();
}
