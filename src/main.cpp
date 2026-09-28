#include "include/UserInterface.h"
#include "include/MyList.h"
#include "include/UserData.h"

int main(int argc, char** argv)
{
  CUserData Head;
  CMyList DB(&Head);
  CUserInterface UI(DB);
  UI.Run();

  return 0;
}