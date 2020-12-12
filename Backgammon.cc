#include "Backgammon.h"
#include "Board.h"

Backgammon::Backgammon(const wxString& title)
  : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(700,400))
{
  wxStatusBar *sb = CreateStatusBar();
  sb->SetStatusText(wxT("0"));
  Board *board = new Board(this);
  board->SetFocus();
}
