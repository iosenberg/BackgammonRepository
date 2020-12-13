#include "Board.h"
using namespace std;

Board::Board(wxFrame *parent)
  : wxPanel(parent, wxID_ANY,wxDefaultPosition,
	    wxDefaultSize, wxBORDER_NONE)
{
  m_stsbar = parent->GetStatusBar();

  srand(time(0));
  
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

  gameAI = new AI();
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
    if (i<6) x++;
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
      if (boardArray[i] < 0 || i == 24) {
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
	if(i<12 || i==25)
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
      cout << "Successful Roll!" << endl;
      //cout << "Rolls are: " << currentRolls[0] << ", " << currentRolls[1] << ", " << currentRolls[2] << ", and " << currentRolls[3] << endl;
    } 
  }
  
  int selectedsection = -1;
  
  // Collects mouse position
  if (x > 0) selectedsection = ToArray(x,y);
                       
  if(playersturn && !rollsEmpty){
  
    if(pieceChosen){
      // Run through the 4 moves list indices
      for (int i=0;i<4;i++) {
	// If -1 is selected, don't do anything
	if(selectedsection == -1) continue;
	if(selectedsection == movesList[i] && pieceChosen){
	  endspace = movesList[i];
	  //cout << "Moving " << startspace << " to " << endspace << endl;
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
	  // Sets the roll in currentRolls used to 0.
	  currentRolls[i] = 0;
	  // If all the rolls are empty, rollsEmpty = true
	  if(currentRolls[0] == 0 && currentRolls[1] == 0 && currentRolls[2] == 0 && currentRolls[3] == 0){
	    rollsEmpty = true;
	    cout << "Out of moves!" << endl;
	  }
	  // Resets movesList and deselects piece
	  movesList[i] = -1;
	  selectedpiece = -1;
	  pieceChosen = false;
	}
	// Also part of reseting movesList. Makes everything -1.
	else movesList[i] = -1;
      }

      // If a piece is already selected and another piece is selected      
      if(pieceChosen && selectedsection > -1 && selectedsection < 24 && boardArray[selectedsection] > 0){
	// If there are brown pieces on that spot, don't select it.
	//if(boardArray[selectedsection] < 0) 1 == 1;
	if(boardArray[25] > 0) { // If white pieces on bar,
	  selectedpiece = 25;
	  startspace = -1; // Start on brown's "endslot"
	}
	else {
	  selectedpiece = selectedsection;
	  startspace = selectedpiece;
	}
	pieceChosen = true;
      }
    }
    // No piece is already selected, and a piece is selected
    else if(selectedsection > -1 && selectedsection < 24 && boardArray[selectedsection] > 0){
      // If there are brown pieces on that spot, don't select it.
      //if(boardArray[selectedsection] < 0) ;
      if(boardArray[25] > 0) { // If white pieces on bar,
	selectedpiece = 25;
        startspace = -1; // Start on brown's "endslot"
      } else {
	selectedpiece = selectedsection;
        startspace = selectedpiece;
      }
      pieceChosen = true;
    }
    else { // If no piece is already selected, and a slot with no piece is selected, reset
      selectedpiece = -1;
      pieceChosen = false;
    }

    // If a new piece is selected, calculates possible moves
    if(pieceChosen && selectedpiece != -1) {
      for(int counter=0;counter<4;counter++){
	if(currentRolls[counter] != 0) {
	  destination = startspace + currentRolls[counter];
	  // If bearOff == false and destination > 23, skip
	  if(!isBearOff && destination > 23) {
	    //cout << startspace << " to " << destination << " no good, not bear-off yet." << endl;
	    movesList[counter] = -1;
	  }
	  // If bearOff == true and destination > 23, set destination to 24
	  else if(isBearOff && destination > 23) {
	    movesList[counter] = 24;
	  }
	  // If there are more than 2 brown or 4 white, skip
	  else if(boardArray[destination] < -1 || boardArray[destination] > 4){
            movesList[counter] = -1;
            //cout << startspace << " to " << destination << " no good, there are " << boardArray[destination] << " chips." << endl;
          }
	  // Else the space is available
	  else movesList[counter] = destination;
	}
     }
      
      //cout << "Your possible moves are: " << movesList[0] << ", " << movesList[1] << ", " <<  movesList[2] << ", and " << movesList[3] << endl;
    }
  }

  // If it's the AI's turn
  if(playersturn && rollsEmpty){
    cout << "AI's turn." << endl;
    // Rolls for the AI (displays the rolls on the dice)
    // And displays "Thinking"
    roll1 = (rand() % 6) + 1;
    roll2 = (rand() % 6) + 1;
    Refresh();
    Update();

    sleep(3);
    
    playersturn = false;
    pieceChosen = false;

    //Run AI code
    gameAI = new AI();
    int* boardPointer = gameAI->AIMove(boardArray,roll1,roll2);
    for (int i=0;i<26;i++)
      boardArray[i] = *(boardPointer + i);
    roll1=0;
    roll2=0;
    cout << "Player's turn." << endl;
  }

  // Check if the player can bear-off
  int chip_sum = 0;
  for (int index=0; index < 18; index++){
    if(boardArray[index] > 0) chip_sum += boardArray[index];
  }
  chip_sum += boardArray[25];
  if(0 == chip_sum) isBearOff = true;
  else isBearOff = false;
    
  if(myendslot == 15 || opponentendslot == 15){                      
    //- Display an endscreen based on who won?
    if (myendslot == 15) cout << "Congrats! Player won!" << endl;
    else if (opponentendslot == 15) cout << "Too bad, the AI won." << endl;
    //- wait 60 seconds                                                           
    sleep(60);
    //- exit
    exit(0);
  }
  
  Refresh();
}
