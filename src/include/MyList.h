#pragma once

#include "UserData.h"

class CMyList
{
public:
  CMyList(const char* pszFileName);
  ~CMyList(void);

protected:
  void ReleaseList(void);
  CUserData m_Head;
  const char* pszFileName;

public:
  CUserData* FindNode(const char* pszName);
  int AddNewNode(const char* pszName, const char* pszPhone);

  void PrintAll(void);

  int RemoveNode(const char* pszName);
};