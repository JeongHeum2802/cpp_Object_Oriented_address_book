#include "MyList.h"
#include <conio.h>
#include <cstdio>
#include <cstring>
#include <iostream>

CMyList::CMyList(const char* pszFileNameParam) : pszFileName(pszFileNameParam)
{
  FILE *fp = nullptr;
  
  fopen_s(&fp, pszFileName, "rb");

  if (fp == nullptr)
    return;

  ReleaseList();

  CUserData user;
  while(fread(&user, sizeof(CUserData), 1, fp))
    AddNewNode(user.szName, user.szPhone);
  
  fclose(fp);

  return;
}

CMyList::~CMyList()
{
  FILE *fp = nullptr;
  CUserData *pNode = m_Head.pNext;

  fopen_s(&fp, pszFileName, "wb");

  if (fp != nullptr)
  {
    CUserData* pNode = m_Head.pNext;

    while (pNode != nullptr)
    {
      fwrite(pNode, sizeof(CUserData), 1, fp);
      pNode = pNode->GetNext();
    }

    fclose(fp);
  }

  ReleaseList();

  return;
}

int CMyList::AddNewNode(const char* pszName, const char* pszPhone)
{
  if (FindNode(pszName) != nullptr)
    return 0;
    
  CUserData *pNewNode = new CUserData();
  strcpy_s(pNewNode->szName, sizeof(pNewNode->szName), pszName);
  strcpy_s(pNewNode->szPhone, sizeof(pNewNode->szPhone), pszPhone);

  pNewNode->pNext = m_Head.pNext;
  m_Head.pNext = pNewNode;

  return 1;
}

void CMyList::PrintAll()
{
  CUserData *pNode = m_Head.pNext;

  while (pNode != nullptr)
  {
    std::cout << "이름: " << pNode->GetName() << ", 전화번호: " << pNode->GetPhone() << std::endl;
    pNode = pNode->GetNext();
  }
}

CUserData* CMyList::FindNode(const char* pszName)
{
  CUserData *pNode = m_Head.pNext;
  while(pNode != nullptr)
  {
    if (strcmp(pNode->GetName(), pszName) == 0)
      return pNode;

    pNode = pNode->GetNext();
  }

  return nullptr;
}

int CMyList::RemoveNode(const char* pszName)
{
  CUserData *pPrevNode = &m_Head;
  CUserData *pNode = m_Head.pNext;

  while(pNode != nullptr)
  {
    if (strcmp(pNode->GetName(), pszName) == 0)
    {
      pPrevNode->pNext = pNode->pNext;
      delete pNode;
      return 1; 
    }

    pPrevNode = pNode;
    pNode = pNode->GetNext();
  }

  return 0;
}

void CMyList::ReleaseList()
{
  CUserData *pNode = m_Head.pNext;
  while(pNode != nullptr)
  {
    CUserData *pTemp = pNode;
    pNode = pNode->GetNext();
    delete pTemp;
  }

  m_Head.pNext = nullptr;
}