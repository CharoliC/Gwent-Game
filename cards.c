#include"Gwent.h"

void InitializeCards() //卡牌信息导入并初始化 
{
	FILE *fp1;
	fp1=fopen("cardsinfo.txt","r");
	int i;
	for(i=0;i<40;i++)
	{
		//从文件中读取卡牌信息 
		fscanf(fp1,"%d%s%d%d%d%d",
		&cards[i].ID,// 卡牌id 
		cards[i].name,//名称 
		&cards[i].type,//类型 (1-近战单位，2-远程单位，3-攻城单位, 4-天气，5-法术)
		&cards[i].attack,//点数 
		&cards[i].isHero,//是否是英雄牌 
		&cards[i].isSpecial);//特殊效果（0-无 1-间谍 2-治疗 3-同袍 4-团结 5-增益） 
		 
		cards[i].isWeatherControlled=0;//是否被天气影响 （0-无，1-雾，2-霜，3-雨）
    	cards[i].isInGameCardsStack=0;//是否在游戏牌组内 
    	cards[i].isSelected=0;//是否被选中 
    	cards[i].isFielded=0;//是否在战场上 
    	cards[i].isGarbaged=0;//是否进入墓地 
    }
    fclose(fp1);
    
    FILE *fp2;
    fp2 = fopen("cardsintro.txt","r");
    for(i=0;i<80;i++)
	{
    	fgets(intro[i].x, 100, fp2);
	}
	fclose(fp2);
}

void SaveYourCards(int row1, int line1)//写入已选择的卡，选一次写一次 
{	
	if(totalcards >= 25)
	{
		return;//大于等于25张则保存失败 
	}
	else
	{
		totalcards++;//自选卡组中卡牌总数增加 
	}
	
	FILE *fp3;
	fp3 = fopen("savedcards.txt", "a");
	fprintf(fp3, "%d %s %d %d %d %d\n", 
	cards[10*row1+line1-11].ID, cards[10*row1+line1-11].name, cards[10*row1+line1-11].type, cards[10*row1+line1-11].attack,
	cards[10*row1+line1-11].isHero, cards[10*row1+line1-11].isSpecial);
	fclose(fp3);
} 

void LeadinSavedCards()//如果有已保存卡组则进行读入 
{
	FILE *fp4;
	fp4 = fopen("savedcards.txt", "r");
	fseek(fp4, 0L, SEEK_END);
	int len = ftell(fp4);	
	if(len != 0)
	{
		fseek(fp4, 0L, SEEK_SET);
		int i;
		for(i = 0; i < 25; i++)
		{
			//从文件中读取已保存的信息 
			fscanf(fp4, "%d %s %d %d %d %d",
			&Yourcards[i].ID,// 卡牌id 
			Yourcards[i].name,//名称 
			&Yourcards[i].type,//类型 (1-近战单位，2-远程单位，3-攻城单位, 4-天气，5-法术)
			&Yourcards[i].attack,//点数 
			&Yourcards[i].isHero,//是否是英雄牌 
			&Yourcards[i].isSpecial);//特殊效果（0-无 1-间谍 2-治疗 3-同袍 4-团结 5-增益） 
			 
			Yourcards[i].isWeatherControlled = 0;//是否被天气影响 （0-无，1-雾，2-霜，3-雨）
	    	Yourcards[i].isInGameCardsStack = 1;//是否在游戏牌组内 
	    	Yourcards[i].isSelected = 0;//是否被选中 
	    	Yourcards[i].isFielded = 0;//是否在战场上 
	    	Yourcards[i].isGarbaged = 0;//是否进入墓地 
	    	
	    	if(feof(fp4)) 
			{
				totalcards = i + 1;
				break;
			}//卡组下限20张，上限25张
	    }
	}
	fclose(fp4);
}

void DrawSavedList()
{
	FILE *fp5;
	fp5 = fopen("savedcards.txt", "r");
	fseek(fp5, 0L, SEEK_END);
	int len = ftell(fp5);	
	if(len != 0)
	{
		SetPenColor("White");
		fseek(fp5, 0L, SEEK_SET);
		int i, ID, type, attack, isHero, isSpecial;
		char name[40];
		for(i = 1; i <= totalcards; i++)
		{
			char str[10];
			fscanf(fp5, "%d %s %d %d %d %d",
			&ID,// 卡牌id 
			name,//名称 
			&type,//类型 (1-近战单位，2-远程单位，3-攻城单位, 4-天气，5-法术)
			&attack,//点数 
			&isHero,//是否是英雄牌 
			&isSpecial);//特殊效果（0-无 1-间谍 2-治疗 3-同袍 4-团结 5-增益） 
			itoa(ID, str, 10);
			MovePen(6.5, 6.2-i*0.2);
			DrawTextString("  ");
			DrawTextString(str);
			DrawTextString("  ");
			DrawTextString(name);
	    }
	}
	fclose(fp5);
}

void DrawListCards(int row1, int line1)//全局变量totalcards可确定画的位置 
{
	if(totalcards > 25) return;
	char str[10];
	string name = cards[10*row1+line1-11].name;
	itoa(cards[10*row1+line1-11].ID, str, 10);//数字转换成字符10进制 
	SetPenColor("White");
	MovePen(6.5, 6.2-totalcards*0.2);
	DrawTextString("  ");
	DrawTextString(str);
	DrawTextString("  ");
	DrawTextString(name);
}

void ClearCards()
{
	FILE *fp6;
	fp6 = fopen("savedcards.txt", "w+");
	fclose(fp6);
	totalcards = 0;
}

void ClearSavedList()
{
	StartFilledRegion(1);
    SetPenColor("Light_Brown");
	DrawBox(6.45, 0.5, gameWidth-7.2, gameHeight-1);
	EndFilledRegion();
	SetPenColor("White");
	DrawBox(6.5, 0.5, gameWidth-7, gameHeight-1); //绘制选牌列表(Card Group)
	MovePen(6.5, 6.3);
	SetPointSize(10);
	DrawTextString("   Your Card Group");
	MovePen(6.5, 6.2);//卡组列表下方坐标 
	DrawLine(gameWidth-7, 0);
	MovePen(6.5, 2.2);
	SetPenColor("White");
	DrawLine(gameWidth-7, 0);
	MovePen(6.5, 1.2);
	SetPenColor("Red");
	DrawLine(gameWidth-7, 0);
}


