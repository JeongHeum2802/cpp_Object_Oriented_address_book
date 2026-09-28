#pragma once

class CMyNode
{
  friend class CMyList;

public:
  CMyNode();
  virtual ~CMyNode();

  CMyNode* GetNext() const { return pNext; }

  // 관리를 위해 꼭 필요한 인터페이스 함수들을 순수 가살 함수로 선언
  virtual const char* GetKey() const = 0;
  virtual void PrintNode(void) = 0;

private:
  CMyNode* pNext;
};