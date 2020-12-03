#include "main.h"
#include "Backgammon.h"

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
  srand(time(NULL));
  Backgammon *backgammon = new Backgammon(wxT("Backgammon"));
  backgammon->Centre();
  backgammon->Show(true);

  return true;
}
