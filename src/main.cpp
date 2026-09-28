#include "include/UserInterface.h"
#include "include/MyList.h"

int main(int argc, char** argv)
{
  CMyList DB("address.dat");
  CUserInterface UI(DB);
  UI.Run();

  return 0;
}