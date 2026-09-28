#include "MyList.h"
#include <conio.h>
#include <cstdio>
#include <cstring>
#include <iostream>

CMyList::CMyList(CMyNode *pHead)
{
  m_pHead = pHead;
  
  return;
}

CMyList::~CMyList()
{
  ReleaseList();

  return;
}

int CMyList::AddNewNode(CMyNode *pNewNode)
{
  if (FindNode(pNewNode->GetKey()) != nullptr)
  {
    delete pNewNode;
    return 0;
  }
    
  pNewNode->pNext = m_pHead->pNext;
  m_pHead->pNext = pNewNode;
  
  return 1;
}

void CMyList::PrintAll()
{
  CMyNode* pNode = m_pHead->pNext;

  while (pNode != nullptr)
  {
    pNode->PrintNode();
    pNode = pNode->GetNext();
  }
}

CMyNode* CMyList::FindNode(const char* pszKey)
{
  CMyNode *pNode = m_pHead->pNext;
  while(pNode != nullptr)
  {
    if (strcmp(pNode->GetKey(), pszKey) == 0)
      return pNode;

    pNode = pNode->GetNext();
  }

  return nullptr;
}

int CMyList::RemoveNode(const char* pszName)
{
  CMyNode *pPrevNode = m_pHead;
  CMyNode *pNode = m_pHead->pNext;

  while(pNode != nullptr)
  {
    if (strcmp(pNode->GetKey(), pszName) == 0)
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
  CMyNode* pNode = m_pHead->pNext;

  while (pNode != nullptr)
  {
    CMyNode* pDelete = pNode;
    pNode = pNode->GetNext();

    delete pDelete;
  }

  m_pHead->pNext = nullptr;
}