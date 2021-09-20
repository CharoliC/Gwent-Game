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
#define NORTHERN_REALMS   1//北方领域
#define NILFGAARD         2//尼弗迦德帝国
#define SCOIA             3//松鼠党
#define MONSTERS          4//怪物

typedef struct card
{
	int ID;//卡牌id 
	char cname[40];//卡牌中文名
	char ename[40];//卡牌英文名
	int type;//种类(1-近战单位，2-远程单位，3-攻城单位，4-天气，5-法术)
	int attack;//点数
	int isHero;//是否为英雄牌
	int isSpecial;//特殊效果（1-间谍 2-治疗 3-同袍 4-召集 5-增益） 

	
	int isWeatherControlled;//卡牌受天气影响，（0-无，1-雾，2-霜，3-雨） 
	int isInGameCardsStack;//是否在游戏牌组中
	int isSelected;//是否被选择
	int isFielded;//是否在战场上
	int isGarbaged;//是否进入墓地
}card;

typedef struct des
{
	char x[100];
}des;
des intro[80];

card cards[100];//全卡组
card Yourcards[25];//你的卡组 
static int state;//选项移动记号
static int row;//选卡移动记号（行） 
static int line;//选卡移动记号（列） 
static int totalcards; 
static int totalcards1;
static int totalcards2;
static bool isSaved = FALSE; 
static int enemySide;//对方阵营
static int yourSide=0;//己方阵营
static int selectedID=0;// 已被选中的卡牌序号 
static int num[25];//存放已被选中卡牌的ID 
double gameWidth, gameHeight;//游戏界面的宽度，高度


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

