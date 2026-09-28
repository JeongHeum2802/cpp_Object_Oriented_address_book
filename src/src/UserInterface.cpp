#include "UserInterface.h"
#include "MyList.h"
#include "UserData.h"
#include <iostream>

CUserInterface::CUserInterface(CMyList &rList) : m_List(rList)
{
}

CUserInterface::~CUserInterface()
{
}

void CUserInterface::Add()
{
  char szName[32] = {0};
  char szPhone[32] = {0};

  std::cout << "이름을 입력하세요: ";
  std::cin >> szName;
  std::cout << "전화번호를 입력하세요: ";
  std::cin >> szPhone;

  m_List.AddNewNode(new CUserData(szName, szPhone));
}

int CUserInterface::PrintUI()
{
  int nMenu = 0;

  std::cout << "1. 추가" << std::endl;
  std::cout << "2. 검색" << std::endl;
  std::cout << "3. 전체 출력" << std::endl;
  std::cout << "4. 삭제" << std::endl;
  std::cout << "0. 종료" << std::endl;
  std::cout << "메뉴를 선택하세요: ";
  std::cin >> nMenu;

  return nMenu;
}

void CUserInterface::Search()
{
  char szName[32] = {0};

  std::cout << "검색할 이름을 입력하세요: ";
  std::cin >> szName;

  CMyNode *pNode = m_List.FindNode(szName);

  if (pNode != nullptr)
  {
    pNode->PrintNode();
  }
  else
  {
    std::cout << "검색 결과가 없습니다." << std::endl;
  }
}

void CUserInterface::Remove()
{
  char szName[32] = {0};

  std::cout << "삭제할 이름을 입력하세요: ";
  std::cin >> szName;

  if (m_List.RemoveNode(szName))
  {
    std::cout << "삭제되었습니다." << std::endl;
  }
  else
  {
    std::cout << "삭제할 항목이 없습니다." << std::endl;
  }
}

int CUserInterface::Run(void)
{
  int nMenu = 0;

  // 메인 이벤트 반복문
  while ((nMenu = PrintUI()) != 0)
  {
    switch(nMenu)
    {
      case 1:
        Add();
        break;
      
      case 2:
        Search();
        break;

      case 3:
        m_List.PrintAll();
        break;

      case 4:
        Remove();
        break;
    }
  }

  return 0;
}