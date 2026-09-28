#pragma once
#include "MyNode.h"

class CUserData : public CMyNode
{
public:
  CUserData();
  CUserData(const char *pszName, const char *pszPhone);
  ~CUserData();

  const char* GetName() const { return szName; }
  const char* etPhone() const { return szPhone; }

protected:
  char szName[32];
  char szPhone[32];

  static int nUserDataCounter;

public:
  const char* GetKey() const override;
  void PrintNode() override;
};