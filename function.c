#include "Gwent.h"

/********************************************************** 
 *  函数原型：void DrawBox(double x, double y, double width, double height)
 *  传入参数：左下点横纵坐标，方框宽，长
 *  返 回 值：无
 *  函数功能：画方框(用于填充)
 **********************************************************/
void DrawBox(double x, double y, double width, double height)
{
	SetPenSize(0.01);
	MovePen(x, y);
	DrawLine(0, height);
	DrawLine(width, 0);
	DrawLine(0, -height);
	DrawLine(-width, 0);
}
/********************************************************** 
 *  函数原型：void DrawFrame(double x, double y, double width, double height)
 *  传入参数：左下点横纵坐标，方框宽，长
 *  返 回 值：无
 *  函数功能：画方框（用于画框，在使用前可自行设置笔画大小）
 **********************************************************/
void DrawFrame(double x, double y, double width, double height)
{
	MovePen(x, y);
	DrawLine(0, height);
	DrawLine(width, 0);
	DrawLine(0, -height);
	DrawLine(-width, 0);
}
/********************************************************** 
 *  函数原型：void DrawTriangle_1(double x, double y, double waist)
 *  传入参数：左上角顶点横纵坐标，腰长
 *  返 回 值：无
 *  函数功能：画等腰直角三角形，直角顶点在左上角
 **********************************************************/
void DrawTriangle_1(double x, double y, double waist)
{
	SetPenSize(0.01);
	MovePen(x, y);
	DrawLine(0, -waist);
	DrawLine(waist, waist);
	DrawLine(-waist, 0);
}
/********************************************************** 
 *  函数原型：void DrawTriangle_2(double x, double y, double waist)
 *  传入参数：左下角顶点横纵坐标，腰长
 *  返 回 值：无
 *  函数功能：画等腰直角三角形，直角顶点在右下角
 **********************************************************/
void DrawTriangle_2(double x, double y, double waist)
{
	SetPenSize(0.01);
	MovePen(x, y);
	DrawLine(waist, 0);
	DrawLine(0, waist);
	DrawLine(-waist, -waist);
}
/********************************************************** 
 *  函数原型：void DrawTriangle_3(double x, double y, double waist)
 *  传入参数：左上角顶点横纵坐标，腰长
 *  返 回 值：无
 *  函数功能：画等腰直角三角形，直角顶点在右上角
 **********************************************************/
void DrawTriangle_3(double x, double y, double waist)
{
	SetPenSize(0.01);
	MovePen(x, y);
	DrawLine(waist, 0);
	DrawLine(0, -waist);
	DrawLine(-waist, waist);
}
/********************************************************** 
 *  函数原型：DrawGwent()
 *  传入参数：无
 *  返 回 值：无
 *  函数功能：画封面的"GWENT"
 **********************************************************/
void DrawGwent()
{
	/*G*/
	SetPenSize(2);
	SetPenColor("Light_Green_1");
	StartFilledRegion(1);
	MovePen(3.6,4.66);
	DrawLine(-1.1,0);
	DrawLine(-0.25,-0.25);
	DrawLine(0,-1.3);
	DrawLine(1,-0.55);
	DrawLine(0,1.35);
	DrawLine(-0.2,0);
	DrawLine(-0.25,-0.25);
    DrawLine(0.2,0);
    DrawLine(0,-0.71);
    DrawLine(-0.5,0.27);
    DrawLine(0,1.2);
    DrawLine(0.7,0);
    DrawLine(0,-0.2);
    DrawLine(0.4,0.44);
    EndFilledRegion();
    /*W*/
    SetPenColor("Light_Green_2");
    StartFilledRegion(1);
    MovePen(3.45,4.2);
    DrawLine(0,-0.8);
    DrawLine(0.06,-0.14);
    DrawLine(0.06,-0.08);
    DrawLine(0.06,-0.05);
    DrawLine(0.48,-0.25);
    DrawLine(0,0.3);
    DrawLine(0.56,-0.3);
    DrawLine(0,1.32);
    DrawLine(-0.22,0);
    DrawLine(0,-0.95);
    DrawLine(-0.3,0.16);
    DrawLine(0,0.79);
    DrawLine(-0.22,0);
    DrawLine(0,-0.95);
    DrawLine(-0.1,0.05);
    DrawLine(-0.1,0.1);
    DrawLine(-0.06,0.1);
    DrawLine(0,0.7);
    DrawLine(-0.22,0);
    EndFilledRegion();
    /*E*/
    SetPenColor("Mid_Green");
    StartFilledRegion(1);
    MovePen(4.9,4.2);
    DrawLine(0.75,0);
    DrawLine(0,-0.22);
    DrawLine(-0.63,0);
    DrawLine(0,-0.22);
    DrawLine(0.5,0);
    DrawLine(0,-0.2);
    DrawLine(-0.5,0);
    DrawLine(0.05,-0.14);
    DrawLine(0.05,-0.08);
    DrawLine(0.05,-0.04);
    DrawLine(0.45,-0.22);
    DrawLine(0,-0.25);
    DrawLine(-0.7,0.33);
    DrawLine(-0.05,0.04);
    DrawLine(-0.05,0.08);
    DrawLine(-0.05,0.14);
    DrawLine(0,0.65);
    DrawLine(0.13,0.13);
    EndFilledRegion();
    /*N*/
    SetPenColor("Mid_Green");
    StartFilledRegion(1);
    MovePen(5.8,4.2);
    DrawLine(0.22,0);
    DrawLine(0,-0.15);
    DrawLine(0.6,-0.55);
    DrawLine(0,0.7);
    DrawLine(0.22,0);
    DrawLine(0,-1.4);
    DrawLine(-0.22,0);
    DrawLine(-0.03,0.2);
    DrawLine(-0.06,0.15);
    DrawLine(-0.03,0.07);
    DrawLine(-0.52,0.52);
    DrawLine(0,-0.95);
    DrawLine(-0.22,0);
    DrawLine(0,1.42);
    EndFilledRegion();
    /*T*/
    SetPenColor("Dark_Green");
    StartFilledRegion(1);
    MovePen(6.4,4.6);
    DrawLine(1.3,0);
    DrawLine(0,-0.45);
    DrawLine(-0.22,-0.22);
    DrawLine(0,0.4);
    DrawLine(-0.24,0);
    DrawLine(0,-1.8);
    DrawLine(-0.22,-0.22);
    DrawLine(0,2.02);
    DrawLine(-0.38,0);
    DrawLine(-0.24,0.27);
    EndFilledRegion();
}
/********************************************************** 
 *  函数原型：DrawLogo()
 *  传入参数：无
 *  返 回 值：无
 *  函数功能：画封面的皇冠
 **********************************************************/
void DrawLogo()
{
	SetPenSize(2);
	SetPenColor("Gold_1");
	MovePen(4.45,4.3);
	StartFilledRegion(1);
	DrawLine(0.4,0);
	DrawLine(0.05,0.04);
	DrawLine(-0.4,0);
	DrawLine(-0.05,-0.04);
	EndFilledRegion();
	MovePen(4.45,4.38);
	StartFilledRegion(1);
	DrawLine(0.4,0);
	DrawLine(0.05,0.04);
	DrawLine(-0.4,0);
	DrawLine(-0.05,-0.04);
	EndFilledRegion();
	MovePen(4.96,4.3);
	StartFilledRegion(1);
	DrawLine(0.4,0);
	DrawLine(-0.05,0.04);
	DrawLine(-0.3,0);
	DrawLine(-0.05,-0.04);
	EndFilledRegion();
	MovePen(4.96,4.38);
	StartFilledRegion(1);
	DrawLine(0.4,0);
	DrawLine(-0.05,0.04);
	DrawLine(-0.3,0);
	DrawLine(-0.05,-0.04);
	EndFilledRegion();

    SetPenColor("Gold_2");
	MovePen(4.5,4.46);
	StartFilledRegion(1);
	DrawLine(0.2,0);
	DrawLine(-0.05,0.15);
	DrawLine(-0.03,-0.03);
	DrawLine(-0.02,0.1);
	DrawLine(0.03,0.03);
	DrawLine(-0.18,0.18);
	DrawLine(0,-0.32);
	DrawLine(0.05,-0.05);
	EndFilledRegion();
	MovePen(5.16,4.46);
	StartFilledRegion(1);
	DrawLine(0.2,0);
	DrawLine(0,0.07);
	DrawLine(0.05,0.05);
	DrawLine(0,0.32);
	DrawLine(-0.18,-0.18);
	DrawLine(0.03,-0.03);
	DrawLine(-0.02,-0.1);
	DrawLine(-0.03,0.03);
	DrawLine(-0.05,-0.16);
	EndFilledRegion();

	MovePen(4.74,4.46);
	StartFilledRegion(1);
	DrawLine(0.17,0);
	DrawLine(-0.17,0.17);
	DrawLine(0,-0.17);
	EndFilledRegion();
	MovePen(4.95,4.46);
	StartFilledRegion(1);
	DrawLine(0.17,0);
	DrawLine(0,0.17);
	DrawLine(-0.17,-0.17);
	EndFilledRegion();

    SetPenColor("Gold_2");
	MovePen(4.74,4.67);
	StartFilledRegion(1);
	DrawLine(0.2,0.2);
	DrawLine(0.05,-0.05);
	DrawLine(-0.05,0.35);
	DrawLine(-0.2,-0.2);
	DrawLine(0,-0.3);
	EndFilledRegion();
    MovePen(5.12,4.67);
    StartFilledRegion(1);
    DrawLine(0,0.3);
    DrawLine(-0.14,0.2);
    DrawLine(0.05,-0.37);
    DrawLine(0.09,-0.13);
    EndFilledRegion();

    SetPenColor("Gold_2");
    SetPenSize(3);
    MovePen(4.91,4.55);
    DrawLine(-0.1,0.1);
    DrawLine(0.12,0.12);
    MovePen(4.96,4.55);
    DrawLine(0.11,0.11);
    DrawLine(-0.08,0.09);
    SetPenSize(1);
    SetPenColor("Light_Blue");
    MovePen(4.91,4.58);
    StartFilledRegion(1);
    DrawLine(-0.07,0.07);
    DrawLine(0.07,0.07);
    DrawLine(0,-0.14);
    EndFilledRegion();
    SetPenColor("Light_Red");
    MovePen(4.95,4.58);
    StartFilledRegion(1);
    DrawLine(0.07,0.07);
    DrawLine(-0.07,0.07);
    DrawLine(0,-0.14);
    EndFilledRegion();
}
/********************************************************** 
 *  函数原型：void DrawCursor(double height, double halfLength)
 *  传入参数：对称光标的纵坐标，对称光标半长
 *  返 回 值：无
 *  函数功能：画对称光标
 **********************************************************/
void DrawCursor(double height, double halfLength)
{
	SetPenSize(0.01);
	StartFilledRegion(1);
    DrawBox(gameWidth/2-halfLength, height, 0.1, 0.1);
    EndFilledRegion();
    StartFilledRegion(1);
    DrawBox(gameWidth/2+halfLength, height, 0.1, 0.1);
    EndFilledRegion();
}
/********************************************************** 
 *  函数原型：void DrawBackground()
 *  传入参数：无 
 *  返 回 值：无
 *  函数功能：画背景 
 **********************************************************/
void DrawBackground()
{
    StartFilledRegion(1);
    SetPenColor("Dark_Brown");
    DrawBox(0, 0, gameWidth, gameHeight);
    EndFilledRegion();
    StartFilledRegion(1);
    SetPenColor("Light_Brown");
    DrawBox(0.4,0.4,gameWidth-0.8,gameHeight-0.8);
    EndFilledRegion();
}
/********************************************************** 
 *  函数原型：void DrawViewCard()
 *  传入参数：无 
 *  返 回 值：无
 *  函数功能：在卡牌选择界面画出所有的牌 
 **********************************************************/
void DrawViewCard()
{
	extern int lan; 
	int i, j;
	double ViewCardWidth = 0.5, ViewCardHeight = 0.8;
	//绘制卡牌框架 
	SetPointSize(20);
	for(i = 0; i < 10; i++)
		for(j = 0; j < 4; j++)	
		{
			char str[10];
			itoa(cards[10*(j+1)+i-10].attack, str, 10);
			StartFilledRegion(1);
			SetPenColor("White");
			DrawBox(0.5+0.6*i, gameHeight-1.3-j, ViewCardWidth, ViewCardHeight);
			EndFilledRegion();
			SetPenColor("Black");
			SetPointSize(10);
			if(cards[10*(j+1)+i-10].attack!=0){
				MovePen(0.55+0.6*i, gameHeight-0.66-j);
				DrawTextString(str);
			}
			if(cards[10*(j+1)+i-10].isSpecial==1){
				DrawSpy(0.82+0.6*i, gameHeight-1.1-j,0.3);
			}else if(cards[10*(j+1)+i-10].isSpecial==2){
				DrawMedic(0.82+0.6*i, gameHeight-1.1-j,0.2);
			}else if(cards[10*(j+1)+i-10].isSpecial==3){
				DrawBond(0.8+0.6*i, gameHeight-1.1-j,0.25);
			}else if(cards[10*(j+1)+i-10].isSpecial==4){
				DrawMuster(0.8+0.6*i, gameHeight-1.1-j,0.3);
			}else if(cards[10*(j+1)+i-10].isSpecial==5){
				DrawBoost(0.8+0.6*i, gameHeight-1.1-j,0.3);
			}
			if(cards[10*(j+1)+i-10].isSpecial==0){
				switch(cards[10*(j+1)+i-10].type){
					case 1:
						DrawSword(0.73+0.6*i, gameHeight-1-j,0.45);
						break;
					case 2:
						DrawBow(0.73+0.6*i, gameHeight-1-j,0.4);
						break;
					case 3:
						DrawSiege(0.78+0.6*i, gameHeight-1-j,0.4);
						break;
				}
			}else{
				switch(cards[10*(j+1)+i-10].type){
					case 1:
						DrawSword(0.7+0.6*i, gameHeight-0.85-j,0.35);
						break;
					case 2:
						DrawBow(0.7+0.6*i, gameHeight-0.85-j,0.3);
						break;
					case 3:
						DrawSiege(0.7+0.6*i, gameHeight-0.85-j,0.3);
						break;
			}
		}
		switch(cards[10*(j+1)+i-10].ID){
			case 28:case 29:
				DrawFrost(0.75+0.6*i, gameHeight-0.9-j,0.35);
				break;
			case 30:case 31:
				DrawFog(0.75+0.6*i, gameHeight-0.9-j,0.35);
				break;
			case 32:case 33:
				DrawRain(0.8+0.6*i, gameHeight-0.9-j,0.35);
				break;
			case 34:case 35:
				DrawSun(0.75+0.6*i, gameHeight-0.9-j,0.15);
				break;
			case 36:case 37:
				DrawHorn(0.78+0.6*i, gameHeight-0.9-j,0.4);
				break;
			case 38:case 39:case 40:
				DrawBurn(0.75+0.6*i, gameHeight-0.95-j,0.3);
				break;
		}
		if(cards[10*(j+1)+i-10].isHero==1){
			SetPenColor("Deep_Golden");
		}else{
			SetPenColor("Black");
		}
			SetPenSize(2);
			MovePen(0.52+0.6*i,gameHeight-1.28-j);
			DrawLine(0, ViewCardHeight-0.04);
			DrawLine(ViewCardWidth-0.04, 0);
			DrawLine(0, 0.04-ViewCardHeight);
			DrawLine(0.04-ViewCardWidth, 0);
	}
	//绘制下方卡牌说明区
	DrawBox(0.5, 0.5, gameWidth-4.1, gameHeight-5);//信息介绍框 
//	MovePen(0.5, gameHeight-4.8);
//	DrawLine(gameWidth-4.1, 0);
//	MovePen(0.5, gameHeight-4.7);
//	SetPointSize(10);
//	DrawTextString("  The Introduction of Selected Card"); 
	DrawBox(6.5, 0.5, gameWidth-7, gameHeight-1); //绘制选牌列表(Card Group)
	MovePen(6.5, 6.3);
	SetPointSize(10);
	SetPenColor("White");
	if(lan==0){
		DrawTextString("   Your Deck");
	}else{
		DrawTextString("   牌组");
	}
		if(lan==0){
		MovePen(6.5, 0.8);
		DrawTextString("   ( Press F5 to clear your deck，");
		MovePen(6.5, 0.6);
		DrawTextString("   Autosave when you choose 25 cards )");
	}else{
		MovePen(6.4, 0.6);
		DrawTextString("   （F5键可清空卡组，选够25张自动保存）");
	}
	MovePen(6.5, 6.2);//卡组列表下方坐标 
	DrawLine(gameWidth-7, 0);
//	MovePen(6.5, 2.2);
//	SetPenColor("White");
//	DrawLine(gameWidth-7, 0);
	MovePen(6.5, 1.1);
	SetPenColor("Red");
	DrawLine(gameWidth-7, 0);
}
/********************************************************** 
 *  函数原型：void DrawPlayBoard()
 *  传入参数：无
 *  返 回 值：无
 *  函数功能：画游戏界面（真正的游戏界面）
 **********************************************************/
void DrawPlayBoard()
{
/*背景*/
	StartFilledRegion(1);
	SetPenColor("Light_Brown");
	DrawBox(0,0,gameWidth,gameHeight);
	EndFilledRegion();
/*左侧框分割线*/
	SetPenSize(4);
	SetPenColor("Gray");
	MovePen(2,0);
	DrawLine(0,0.4);
	MovePen(2,1.3);
	DrawLine(0,gameHeight-1.1);
/*天气框*/
	StartFilledRegion(1);
	SetPenColor("White");
	DrawFrame(0.2,gameHeight/2-0.4,1.6,0.8);
	EndFilledRegion();
	SetPenColor("Light_Brown++");
	DrawFrame(0.2,gameHeight/2-0.4,1.6,0.8);
/*玩家信息框*/
	StartFilledRegion(1);
	SetPenColor("Dark_Brown");
	DrawBox(0,gameHeight/2-1.8,1.97,1);
	EndFilledRegion();
	StartFilledRegion(1);
	SetPenColor("Dark_Brown");
	DrawBox(0,gameHeight/2+0.8,1.97,1);
	EndFilledRegion();
/*点数显示*/
	SetPointSize(30);
	SetPenColor("Light Gray");
	MovePen(1.6,5);
	DrawTextString("0");
	MovePen(1.6,4.7);
	DrawTextString("0");
	MovePen(1.6,4.4);
	DrawTextString("0");
	MovePen(1.6,2.4);
	DrawTextString("0");
	MovePen(1.6,2.1);
	DrawTextString("0");
	MovePen(1.6,1.8);
	DrawTextString("0");
//领袖框（暂时不做）
/*己方手牌框*/
	SetPenSize(3);
	SetPenColor("Gold_2");
	DrawFrame(1.3,0.4,6.6,0.9);
/*战场*/
	SetPenSize(3);
	SetPenColor("Light_Brown++");
	DrawFrame(2.3,gameHeight-1,5.6,0.9);
    DrawFrame(2.3,gameHeight-1.92,5.6,0.9);
    DrawFrame(2.3,gameHeight-2.84,5.6,0.9);
    DrawFrame(2.3,gameHeight-3.8,5.6,0.9);
    DrawFrame(2.3,gameHeight-4.72,5.6,0.9);
    DrawFrame(2.3,gameHeight-5.64,5.6,0.9);
    SetPenColor("Gold_2");
    MovePen(2.25,gameHeight-2.86);
    DrawLine(5.7,0);
/*右侧框背景*/
    StartFilledRegion(1);
    SetPenColor("Light_Brown+");
    DrawBox(7.92,0,gameWidth-7.95,gameHeight);
    EndFilledRegion();
/*墓地*/
    StartFilledRegion(1);
    SetPenColor("Light_Brown");
    DrawBox(8.1,gameHeight-1.3,0.6,0.9);
    EndFilledRegion();
    StartFilledRegion(1);
    SetPenColor("Light_Brown");
    DrawBox(8.1,0.4,0.6,0.9);
    EndFilledRegion();
/*墓地初始卡牌数*/
    SetPointSize(40);
    SetPenColor("Light Gray");
    MovePen(8.3,gameHeight-1);
    DrawTextString("0");
    MovePen(8.3,0.7);
    DrawTextString("0");
/*牌堆*/
    StartFilledRegion(1);
    SetPenColor("Mid_Blue");
    DrawBox(9.1,gameHeight-1.3,0.6,0.9);
    EndFilledRegion();
    StartFilledRegion(1);
    SetPenColor("Mid_Blue");
    DrawBox(9.1,0.4,0.6,0.9);
    EndFilledRegion();
    SetPenColor("Gold_2");
    SetPointSize(75);
    MovePen(9.25,gameHeight-1.1);
    DrawTextString("?");
    MovePen(9.25,0.6);
    DrawTextString("?");
/*详细信息框*/
    SetPenColor("Light Gray");
    SetPenSize(3);
    DrawFrame(8.1,gameHeight/2-1.5,1.7,3);
}
/********************************************************** 
 *  函数原型：void ClearCursor(int s,double width)
 *  传入参数：state ,width
 *  返 回 值：无
 *  函数功能：去除光标残留 
 **********************************************************/
void ClearCursor(int s){
	SetPenColor("Light_Brown");
    SetPenSize(0.01);
	StartFilledRegion(1);
    DrawBox(gameWidth/2-1.2, 6.38-0.8*s, 0.12, 0.12);
    EndFilledRegion();
    StartFilledRegion(1);
    DrawBox(gameWidth/2+1.2, 6.38-0.8*s, 0.12, 0.12);
    EndFilledRegion();
}
/********************************************************** 
 *  函数原型：void DrawHandCards(double x, double y, int ID)
 *  传入参数：左下角横纵坐标，卡牌ID
 *  返 回 值：无
 *  函数功能：显示卡牌
 **********************************************************/
void DrawHandCards(double x, double y, int ID)
{
    /*底色&牌框*/
	SetPenSize(2);
	StartFilledRegion(1);
	SetPenColor("White");
	DrawFrame(x, y, 0.54, 0.88);
	EndFilledRegion();
	SetPenColor("Gray");
	DrawFrame(x, y, 0.54, 0.88);

	if(ID<=6)//金卡
	{
		StartFilledRegion(1);
		SetPenColor("Gold_2");
		DrawTriangle_1(x,y+0.9,0.2);
		EndFilledRegion();
	}
	/*显示点数*/
	SetPointSize(24);
	SetPenColor("Black");
	MovePen(x+0.08,y+0.65);
	switch(ID)
	{
		case 1: case 2:
		    DrawTextString("15");
		    break;
		case 3: case 59:
		    DrawTextString("7");
		    break;
		case 4: case 5: case 6:case 63: case 64:case 68:case 70:
		    DrawTextString("10");
		    break;
		case 58:
			DrawTextString("9");
		    break;
		case 7: case 19: case 21: case 27: case 48: case 49: case 50:
		case 51: case 52: case 53:
	        DrawTextString("6");
	        break;
	    case 8: case 13: case 20: case 22: case 25: case 47:
	    case 61: case 62:
	        DrawTextString("5");
	        break;
	    case 9: case 10: case 11: case 12: case 14: case 15:
	    case 41: case 42: case 43: case 44: case 45: case 46:
	        DrawTextString("4");
	        break;
	    case 16: case 17: case 18: case 54: case 55: case 56: case 57:
	    case 75:case 76: case 77:case 78:case 79:case 80:case 81:
	        DrawTextString("3");
	        break;
	    case 23: case 24:case 71:
	        DrawTextString("8");
	        break;
	    case 65: case 66: case 67:case 72:case 73: case 74:
	    	DrawTextString("2");
	        break;
	    case 26: case 60:case 69:
	        DrawTextString("1");
	        break;
	    default:
	        DrawTextString("- -");
	        break;
	}
    /*显示攻击类型图标*/
    SetPenColor("Black");
    switch(ID)
    {
    	case 1: case 2: case 7: case 8:case 72:
    	case 73:case 74:
    	    DrawSword(x+0.25,y+0.35,0.5);
    	    break;
    	case 9:case 10: case 11:case 54:case 55:
    	case 56:case 57:case 61:case 62:case 65:
    	case 66: case 67:
    	    DrawSword(x+0.15,y+0.45,0.3);
    	    DrawBond(x+0.35,y+0.25,0.3);
    	    break;
    	case 12: case 13:case 58:case 59:
    		DrawSword(x+0.15,y+0.45,0.3);
    		DrawSpy(x+0.35,y+0.25,0.3);
    	    break;
    	case 41:case 42:case 43:case 44:case 45:
    	case 46:case 47:case 48:case 49:case 50:
    		DrawSword(x+0.15,y+0.45,0.3);
    		DrawMuster(x+0.35,y+0.2,0.3);
    		break;
    	case 4: case 19: case 20:case 63:case 64:
    	case 75:case 76: case 77:case 78:case 79:case 80:case 81:
    	    DrawBow(x+0.25,y+0.32,0.35);
    	    break;
    	case 3:case 69:
    	    DrawBow(x+0.15,y+0.45,0.25);
    	    DrawMedic(x+0.38,y+0.25,0.2);
    	    break;
    	case 14: case 15: case 16:case 17: case 18:
    	    DrawBow(x+0.15,y+0.45,0.25);
    	    DrawMuster(x+0.35,y+0.2,0.3);
    	    break;
    	case 70:
    		DrawBow(x+0.15,y+0.45,0.25);
    		DrawBoost(x+0.35,y+0.2,0.3);
    	    break;
    	case 5: case 6: case 21: case 22:case 27:case 68:
    	case 71:
    	    DrawSiege(x+0.3,y+0.35,0.4);
    	    break;
    	case 23:case 24:
    	    DrawSiege(x+0.2,y+0.48,0.3);
    	    DrawBond(x+0.4,y+0.25,0.25);
    	    break;
    	case 25:case 60:
    	    DrawSiege(x+0.2,y+0.48,0.3);
    	    DrawMedic(x+0.38,y+0.25,0.2);
    	    break;
    	case 51:case 52:case 53:
    		DrawSiege(x+0.2,y+0.48,0.3);
    		DrawMuster(x+0.35,y+0.2,0.3);
    		break;
    	case 26:
    	    DrawSiege(x+0.2,y+0.48,0.3);
    	    DrawBoost(x+0.35,y+0.2,0.3);
    	    break;
    	case 28: case 29:
    	    DrawFrost(x+0.26,y+0.35,0.35);
    	    break;
    	case 30: case 31:
    	    DrawFog(x+0.27,y+0.35,0.35);
    	    break;
    	case 32: case 33:
    	    DrawRain(x+0.3,y+0.4,0.35);
    	    break;
    	case 34: case 35:
    	    DrawSun(x+0.27,y+0.36,0.15);
    	    break;
    	case 36: case 37:
    	    DrawHorn(x+0.27,y+0.36,0.45);
    	    break;
    	case 38: case 39: case 40:
    	    DrawBurn(x+0.27,y+0.35,0.35);
    	    break;
    }
}
/********************************************************** 
 *  函数原型：void DrawTriangleCursor(double x, double y, int isClear)
 *  传入参数：左下角横纵坐标，是否为擦除操作（是为1）
 *  返 回 值：无
 *  函数功能：画三角光标
 **********************************************************/
void DrawTriangleCursor(double x, double y, int isClear)
{
	if(isClear==1)
	{
		StartFilledRegion(1);
		SetPenColor("Light_Brown");
		DrawBox(x-0.01,y-0.01,0.1,0.11);
		EndFilledRegion();
	}
	else
	{
		MovePen(x, y);
	    SetPenSize(2);
	    SetPenColor("White");
	    DrawLine(0.04, 0.1);
	    DrawLine(0.04, -0.1);
	    DrawLine(-0.08, 0);
	}
}
/********************************************************** 
 *  函数原型：void DrawDetail(card a)
 *  传入参数：卡牌（结构体）
 *  返 回 值：无
 *  函数功能：画卡牌详细信息（右侧框）
 **********************************************************/
void DrawDetail(card a)
{
	/*擦去之前信息*/
	StartFilledRegion(1);
	SetPenColor("White");
	DrawBox(8.15,gameHeight/2-1.45,1.6,2.9);
	EndFilledRegion();
	/*显示名字*/
	SetPenColor("Black");
	SetPointSize(22);
	MovePen(8.95-TextStringWidth(a.ename)/2,2.4);
	DrawTextString(a.ename);
	/*显示点数*/
	SetPenColor("Black");
	SetPointSize(50);
	MovePen(8.25,4.5);
	switch(a.attack)
	{
		case 1:
		    DrawTextString("1");
		    break;
		case 3:
		    DrawTextString("3");
		    break;
		case 4:
		    DrawTextString("4");
		    break;
		case 5:
		    DrawTextString("5");
		    break;
		case 6:
		    DrawTextString("6");
		    break;
		case 7:
		    DrawTextString("7");
		    break;
		case 8:
		    DrawTextString("8");
		    break;
		case 10:
		    DrawTextString("10");
		    break;
		case 15:
		    DrawTextString("15");
		    break;
		default:
		    DrawTextString("- -");
	}
	/*显示图标（类型）*/
	switch(a.type)
	{
		case 1:
		    DrawSword(9.4,4.65,0.5);
		    break;
		case 2:
		    DrawBow(9.45,4.65,0.4);
		    break;
		case 3:
		    DrawSiege(9.4,4.7,0.5);
		    break;
		case 4:
		    switch(a.ID)
		    {
		    	case 28: case 29:
    	            DrawFrost(8.95,3.6,1);
    	            break;
    	        case 30: case 31:
    	            DrawFog(8.95,3.6,1);
    	            break;
    	        case 32: case 33:
    	            DrawRain(9.05,3.7,1);
    	            break;
    	        case 34: case 35:
    	            DrawSun(8.95,3.6,0.5);
    	            break;
		    }
		    break;
		case 5:
		    switch(a.ID)
		    {
		    	case 36: case 37:
		    	    DrawHorn(8.95,3.6,1.2);
		    	    break;
		    	case 38: case 39: case 40:
		    	    DrawBurn(8.95,3.45,1);
		    	    break;
		    }
		    break;
	}
	/*显示图标（特殊效果）*/
	switch(a.isSpecial)
	{
		case 1:
		    DrawSpy(8.95,3.6,1.1);
		    break;
	    case 2:
	        DrawMedic(8.95,3.6,1.1);
	        break;
	    case 3:
	        DrawBond(8.8,3.5,1.1);
	        break;
	    case 4:
	        DrawMuster(8.95,3.5,1.3);
	        break;
	    case 5:
	        DrawBoost(8.95,3.5,1.1);
	        break;
	    case 0:
	        if(a.ID<=27)
	        {
	        	SetPenColor("Black");
	        	SetPointSize(100);
	        	MovePen(8.65,3.35);
	        	DrawTextString("- -");
	        }
	        break;
	}
}
/********************************************************** 
 *  函数原型：void ClearField()
 *  传入参数：无
 *  返 回 值：无
 *  函数功能：擦除战场上的卡牌
 **********************************************************/
void ClearField()
{
	StartFilledRegion(1);
	SetPenColor("Light_Brown"); 
	DrawBox(2.25,gameHeight-5.69,5.65,6);
	EndFilledRegion();
	
	SetPenSize(3);
	SetPenColor("Light_Brown++");
	DrawFrame(2.3,gameHeight-1,5.6,0.9);
    DrawFrame(2.3,gameHeight-1.92,5.6,0.9);
    DrawFrame(2.3,gameHeight-2.84,5.6,0.9);
    DrawFrame(2.3,gameHeight-3.8,5.6,0.9);
    DrawFrame(2.3,gameHeight-4.72,5.6,0.9);
    DrawFrame(2.3,gameHeight-5.64,5.6,0.9);
    SetPenColor("Gold_2");
    MovePen(2.25,gameHeight-2.86);
    DrawLine(5.7,0);
}
