#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define DATA_FILE_NAME "Address.data"

void ReleaseList();
typedef struct _USERDATA
{
  char szName[32]; // 이름
  char szPhone[32]; // 전화번호

  struct _USERDATA *pNext;
} USERDATA;

// 더미 헤드 노드 선언 및 정의
USERDATA g_Head = {0};

// 리스트에서 이름으로 특정 노드를 검색하는 함수
USERDATA *FindNode(char *pszName)
{
  USERDATA *pTmp = g_Head.pNext;
  while (pTmp != NULL)
  {
    if (strcmp(pTmp->szName, pszName) == 0)
      return pTmp;
    
    pTmp = pTmp->pNext;
  }

  return NULL;
}

// 리스트에 새로운 노드를 추가하는 함수
int AddNewNode(char *pszName, char *pszPhone)
{
  USERDATA *pNewUser = NULL;

  // 같은 이름이 이미 존재하는지 확인
  if (FindNode(pszName) != NULL)
  {
    printf("이미 존재하는 이름입니다.\n");
    return 0;
  }

  // 새로운 노드 메모리 할당
  pNewUser = (USERDATA *)malloc(sizeof(USERDATA));
  memset(pNewUser, 0, sizeof(USERDATA));

  // 메모리 값 지정
  sprintf_s(pNewUser->szName, sizeof(pNewUser->szName), "%s", pszName);
  sprintf_s(pNewUser->szPhone, sizeof(pNewUser->szPhone), "%s", pszPhone);
  pNewUser->pNext = NULL;

  pNewUser->pNext = g_Head.pNext;
  g_Head.pNext = pNewUser;

  return 1;
}

// 이름을 입력받아 리스트에 추가하는 함수
void Add()
{
  char szName[32] = {0};
  char szPhone[32] = {0};

  printf("이름을 입력하세요 : ");
  fflush(stdin);
  gets_s(szName, sizeof(szName));

  printf("전화번호를 입력하세요 : ");
  fflush(stdin);
  gets_s(szPhone, sizeof(szPhone));

  // 리스트에 추가
  AddNewNode(szName, szPhone);
}

// 특정 노드를 검색하는 함수
void Search()
{
  char szName[32] = {0};
  USERDATA *pNode = NULL;

  printf("검색할 이름을 입력하세요 : ");
  fflush(stdin);
  gets_s(szName, sizeof(szName));

  pNode = FindNode(szName);
  if (pNode != NULL)
  {
    printf("[%p] %s\t%s [%p]\n", 
      pNode,
      pNode->szName,
      pNode->szPhone,
      pNode->pNext
    );
  }
  else
  {
    printf("검색 결과가 없습니다. \n");
  }

  _getch();
}

// 리스트에 있는 모든 데이터를 출력하는 함수
void PrintAll()
{
  USERDATA *pTmp = g_Head.pNext;
  while (pTmp != NULL)
  {
    printf("[%p] %s\t%s [%p]\n", 
      pTmp,
      pTmp->szName,
      pTmp->szPhone,
      pTmp->pNext    
    );

    pTmp = pTmp->pNext;
  }

  _getch();
}

// 특정 노드를 검색하고 삭제하는 함수
int RemoveNode(char *pszName)
{
  USERDATA *pPrev = &g_Head;
  USERDATA *pDelete = NULL;
  
  while(pPrev->pNext != NULL)
  {
    pDelete = pPrev->pNext;

    if (strcmp(pDelete->szName, pszName) == 0)
    {
      pPrev->pNext = pDelete->pNext;
      free(pDelete);

      return 1;
    }

    pPrev = pPrev->pNext;
  }

  return 0;
}

// 이름을 입력받아 자료를 검색하고 삭제하는 함수
void Remove()
{
  char szName[32] = {0};

  printf("삭제할 이름을 입력하세요 : ");
  fflush(stdin);
  gets_s(szName, sizeof(szName));

  RemoveNode(szName);
}

// 메뉴를 출력하는 UI 함수
int PrintUI()
{
  int nInput = 0;
  
  system("cls");
  printf("[1] 추가\t [2] 검색\t [3] 전체출력\t [4] 삭제\t [0] 종료\n:");

  // 사용자가 선택한 메뉴의 값을 반환
  scanf_s("%d", &nInput);

  return nInput;
}

// 데이터 파일에서 노드들을 읽어와 리스트를 완성하는 함수
int LoadList(char *pszFileName)
{
  FILE *fp = NULL;
  USERDATA user = {0};

  fopen_s(&fp, pszFileName, "rb");

  if (fp == NULL)
  {
    printf("데이터 파일을 열 수 없습니다. \n");
    return 0;
  }

  ReleaseList();

  while(fread(&user, sizeof(USERDATA), 1, fp))
    AddNewNode(user.szName, user.szPhone);

  fclose(fp);

  return 0;
}

// 리스트 형태로 존재하는 정보를 파일에 저장하는 함수
int SaveList(char *pszFileName)
{
  FILE *fp = NULL;
  USERDATA *pTmp = g_Head.pNext;

  fopen_s(&fp, pszFileName, "wb");

  if (fp == NULL)
  {
    printf("데이터 파일을 열 수 없습니다. \n");
    _getch();

    return 0;
  }

  while(pTmp != NULL)
  {
    if (fwrite(pTmp, sizeof(USERDATA), 1, fp) != 1)
    {
      printf("%s에 대한 정보를 저장하는데 실패했습니다.\n", pTmp->szName);
    }

    pTmp = pTmp->pNext;
  }

  fclose(fp);

  return 1;
}

// 리스트의 모든 데이터를 삭제하는 함수
void ReleaseList()
{
  USERDATA *pTmp = g_Head.pNext;
  USERDATA *pDelete = NULL;

  while(pTmp != NULL)
  {
    pDelete = pTmp;
    pTmp = pTmp->pNext;

    free(pDelete);
  }

  memset(&g_Head, 0, sizeof(USERDATA));
}

int main(int argc, char** argv)
{
  SetConsoleOutputCP(CP_UTF8);
  SetConsoleCP(CP_UTF8);

  int nMenu = 0;
  LoadList(DATA_FILE_NAME);

  // 메인 이벤트 반복문
  while((nMenu = PrintUI()) != 0)
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
        PrintAll();
        break;

      case 4:
        Remove();
        break;
    }
  }    

  // 종료 전 파일로 저장 후 메모리 해제
  SaveList(DATA_FILE_NAME);
  ReleaseList();

  return 0;
}

