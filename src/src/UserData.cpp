#include "UserData.h"
#include <cstring>
#include <iostream>

int CUserData::nUserDataCounter = 0;

CUserData::CUserData()
{
  memset(szName, 0, sizeof(szName));
  memset(szPhone, 0, sizeof(szPhone));

  nUserDataCounter++;
}

CUserData::CUserData(const char* pszName, const char* pszPhone)
{
  memset(szName, 0, sizeof(szName));
  memset(szPhone, 0, sizeof(szPhone));

  strcpy_s(szName, sizeof(szName), pszName);
  strcpy_s(szPhone, sizeof(szPhone), pszPhone);

  nUserDataCounter++;
}

CUserData::~CUserData()
{
  nUserDataCounter--;
}

const char* CUserData::GetKey() const
{
  return szName;
}

void CUserData::PrintNode()
{
  std::cout << "이름: " << szName << ", 전화번호: " << szPhone << std::endl;

}