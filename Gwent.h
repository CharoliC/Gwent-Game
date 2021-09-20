#ifndef _GWENT_H_
#define _GWENT_H_

#include "Gwent.h"
#include "graphics.h"
#include "extgraph.h"
#include "genlib.h"
#include "simpio.h"
#include "random.h"
#include "strlib.h"
#include "conio.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <windows.h>
#include <olectl.h>
#include <stdio.h>
#include <mmsystem.h>
#include <wingdi.h>
#include <ole2.h>
#include <ocidl.h>
#include <winuser.h>
#include <dos.h>
#include <math.h>
#include <string.h>
#include <time.h>
#pragma comment(lib,"Winmm.lib")

#define FALSE             0
#define TRUE              1
#define NORTHERN_REALMS   1//��������
#define NILFGAARD         2//�ḥ�ȵµ۹�
#define SCOIA             3//����
#define MONSTERS          4//����

typedef struct card
{
	int ID;//����id 
	char cname[40];//����������
	char ename[40];//����Ӣ����
	int type;//����(1-��ս��λ��2-Զ�̵�λ��3-���ǵ�λ��4-������5-����)
	int attack;//����
	int isHero;//�Ƿ�ΪӢ����
	int isSpecial;//����Ч����1-��� 2-���� 3-ͬ�� 4-�ټ� 5-���棩 

	
	int isWeatherControlled;//����������Ӱ�죬��0-�ޣ�1-��2-˪��3-�꣩ 
	int isInGameCardsStack;//�Ƿ�����Ϸ������
	int isSelected;//�Ƿ�ѡ��
	int isFielded;//�Ƿ���ս����
	int isGarbaged;//�Ƿ����Ĺ��
}card;

typedef struct des
{
	char x[100];
}des;
des intro[80];

card cards[100];//ȫ����
card Yourcards[25];//��Ŀ��� 
static int state;//ѡ���ƶ��Ǻ�
static int row;//ѡ���ƶ��Ǻţ��У� 
static int line;//ѡ���ƶ��Ǻţ��У� 
static int totalcards; 
static int totalcards1;
static int totalcards2;
static bool isSaved = FALSE; 
static int enemySide;//�Է���Ӫ
static int yourSide=0;//������Ӫ
static int selectedID=0;// �ѱ�ѡ�еĿ������ 
static int num[25];//����ѱ�ѡ�п��Ƶ�ID 
double gameWidth, gameHeight;//��Ϸ����Ŀ�ȣ��߶�


void DrawSword(double cx, double cy, double length);
void DrawBow(double cx, double cy, double length);
void DrawSiege(double cx, double cy, double length);
void DrawFrost(double cx, double cy, double length);
void DrawFog(double cx, double cy, double length);
void DrawRain(double cx, double cy, double size);
void DrawSun(double cx, double cy, double size);
void DrawBurn(double cx, double cy, double size);
void DrawHorn(double cx, double cy, double size);
void DrawSpy(double cx, double cy, double size);
void DrawMedic(double cx, double cy, double size);
void DrawBond(double cx, double cy, double size);
void DrawMuster(double cx, double cy, double size);
void DrawBoost(double cx, double cy, double length);

void DrawBox(double x, double y, double width, double height);
void DrawFrame(double x, double y, double width, double height);
void DrawTriangle_1(double x, double y, double waist);
void DrawTriangle_2(double x, double y, double waist);
void DrawTriangle_3(double x, double y, double waist);
void DrawGwent();
void DrawLogo();
void DrawCursor(double height, double halfLength);
void DrawViewCard();
void DrawSavedList();
void DrawIntroduction(int i,int j);
void DrawListCards(int row1, int line1);
void DrawPlayBoard();
void DrawBackground();
void DrawHandCards(double x, double y, int ID);
void DrawTriangleCursor(double x, double y, int isClear);
void DrawDetail(card a);
void KeyboardMenuProcess(int key, int event);
void KeyboardOptionProcess(int key, int event);
void KeyboardViewProcess(int key, int event);
void KeyboardSideProcess(int key, int event);
void KeyboardPlayProcess(int key, int event);
void KeyboardHelpProcess(int key,int event);
void KeyboardLanProcess(int key,int event);
void KeyboardAccountProcess(int key, int event);
void KeyboardRegisterProcess(int key, int event);
void KeyboardEventProcess(int key, int event);
void KeyboardoverProcess(int key, int event);
void CharEventProcess(char c);
void TimerEventProcess(int timerID);
void InitializePlay();
void GameOver();
void InitializeMenu();
void InitializeOption();
void InitializeView();
void InitializeSideSelect();
void InitializeCards();
void InitializeHelp();
void InitializeLan();
void InitializeAccounts();
void InitializeRegister();
void InitializeEvent(int state);
void LeadinSavedCards();
void SaveYourCards(int row1, int line1);
void ClearCards();
void ClearSavedList();
void ColorDefine();
void ClearCursor(int s);
void CheckYourCards();
void ClearField();
void UpdateGrave(int player);
void UpdateAttack(int row);
void JudgeWinner(int* pyourWin, int* penemyWin);
int AttackCalculate(card* ecard, int num);

#endif

