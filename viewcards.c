#include"Gwent.h"

extern int usernow;

void InitializeView()//初始化卡牌选择界面 
{
	PlaySound(NULL,NULL,SND_FILENAME | SND_ASYNC | SND_LOOP);
	PlaySound("viewcards.wav",NULL,SND_FILENAME | SND_ASYNC | SND_LOOP);
	/*画背景*/
	InitializeCards();
    DrawBackground();
    DrawViewCard();
    DrawIntroduction(1,1);
    /*默认选卡光标*/ 
    SetPenColor("Light_Green_1");
	DrawBox(0.5, gameHeight-1.3, 0.5, 0.8);
	CheckYourCards();
	LeadinSavedCards();
	DrawSavedList();
	
	registerKeyboardEvent(KeyboardViewProcess);
	row=1,line=1; 
}

void KeyboardViewProcess(int key, int event)//选卡界面相应键盘操作 
{
	int i;
	int isChosen;
	switch(event)
    {
        case KEY_DOWN:
            switch(key)
            {
				case VK_RIGHT://光标右移 
				    if(line<10)
					{
					    SetPenColor("White");
					    DrawBox(-0.1+0.6*line, gameHeight-0.3-row, 0.5, 0.8);
					    line++; 
					    SetPenColor("Light_Green_1");
					    DrawBox(-0.1+0.6*line, gameHeight-0.3-row, 0.5, 0.8);
					    DrawIntroduction(line,row); 
				    }
					else if(line==10&&row<4)
					{
						SetPenColor("White");
						DrawBox(-0.1+0.6*line, gameHeight-0.3-row, 0.5, 0.8);
						line=1; 
						row++;
						SetPenColor("Light_Green_1");
						DrawBox(-0.1+0.6*line, gameHeight-0.3-row, 0.5, 0.8);
						DrawIntroduction(line,row); 
				    }
				    break;
				case VK_LEFT://光标左移 
					if(line>1)
					{
						SetPenColor("White");
						DrawBox(-0.1+0.6*line, gameHeight-0.3-row, 0.5, 0.8);
						line--; 
						SetPenColor("Light_Green_1");
						DrawBox(-0.1+0.6*line, gameHeight-0.3-row, 0.5, 0.8);
						DrawIntroduction(line,row); 
					}
					else if(line==1&&row>1)
					{
						SetPenColor("White");
						DrawBox(-0.1+0.6*line, gameHeight-0.3-row, 0.5, 0.8);
						line=10; 
						row--;
						SetPenColor("Light_Green_1");
						DrawBox(-0.1+0.6*line, gameHeight-0.3-row, 0.5, 0.8);
						DrawIntroduction(line,row); 
					}
					break;
				case VK_DOWN://光标下移 
					if(row<4)
					{
						SetPenColor("White");
						DrawBox(-0.1+0.6*line, gameHeight-0.3-row, 0.5, 0.8);
						row++; 
						SetPenColor("Light_Green_1");
						DrawBox(-0.1+0.6*line, gameHeight-0.3-row, 0.5, 0.8);
						DrawIntroduction(line,row); 
					}
					else if(row==4&&line<10)
					{
						SetPenColor("White");
						DrawBox(-0.1+0.6*line, gameHeight-0.3-row, 0.5, 0.8);
						row=1; 
						line++;
						SetPenColor("Light_Green_1");
						DrawBox(-0.1+0.6*line, gameHeight-0.3-row, 0.5, 0.8);
						DrawIntroduction(line,row); 
					}
					break;
				case VK_UP://光标上移 
					if(row>1)
					{
						SetPenColor("White");
						DrawBox(-0.1+0.6*line, gameHeight-0.3-row, 0.5, 0.8);
						row--; 
						SetPenColor("Light_Green_1");
						DrawBox(-0.1+0.6*line, gameHeight-0.3-row, 0.5, 0.8);
						DrawIntroduction(line,row); 
					}
					else if(row==1&&line>1)
					{
						SetPenColor("White");
						DrawBox(-0.1+0.6*line, gameHeight-0.3-row, 0.5, 0.8);
						row=4;
						line--; 
						SetPenColor("Light_Green_1");
						DrawBox(-0.1+0.6*line, gameHeight-0.3-row, 0.5, 0.8);
						DrawIntroduction(line,row); 
					}
					break;
				case VK_RETURN://回车选卡
					for(i=0;i<25;i++){
						if(cards[10*row+line-11].ID==num[i]){
							isChosen=1;
							break;
						}else{
							isChosen=0;
						}
					} 
					if(isChosen==0){
						num[selectedID]=cards[10*row+line-11].ID;
						SaveYourCards(row, line);//将要选的卡写入保存卡组的文件 
				    	DrawListCards(row, line);//在选卡列表画出已选卡 
				    	selectedID++;
					}
					break; 
				case VK_BACK://按退格键进入选择界面
					if((usernow == 0 && totalcards < 25) || (usernow == 1 && totalcards1 < 25) || (usernow == 2&&totalcards2 < 25))
					{
						ClearSavedList();
						ClearCards();
					}
                    InitializeOption();
                    break;
                case VK_F5:
                	ClearSavedList();
                	ClearCards();
                	break;
            }
            break;
    }
}

/********************************************************** 
*注意，以下内容为原cards文件 
*注意，以下内容为原cards文件 
*注意，以下内容为原cards文件 
*注意，以下内容为原cards文件 
 **********************************************************/

void InitializeCards() //卡牌信息导入并初始化 
{
	FILE *fp1;
	fp1=fopen("cardsinfo.txt","r");
	int i;
	for(i=0;i<100;i++){
		//从文件中读取卡牌信息 
		fscanf(fp1,"%d%s%s%d%d%d%d",
		&cards[i].ID,// 卡牌id 
		cards[i].cname,//中文名称 
		cards[i].ename,//英文名称 
		&cards[i].type,//类型 (1-近战单位，2-远程单位，3-攻城单位, 4-天气，5-法术)
		&cards[i].attack,//点数 
		&cards[i].isHero,//是否是英雄牌 
		&cards[i].isSpecial);//特殊效果（0-无 1-间谍 2-治疗 3-同袍 4-团结 5-增益） 
		 
		cards[i].isWeatherControlled=0;//是否被天气影响 （0-无，1-雾，2-霜，3-雨）
    //	cards[i].isInGameCardsStack=0;//是否在游戏牌组内 
    	cards[i].isSelected=0;//是否被选中 
    	cards[i].isFielded=0;//是否在战场上 
    	cards[i].isGarbaged=0;//是否进入墓地 
    }
    fclose(fp1);
    
    FILE *fp2;
    fp2=fopen("cardsintro.txt","r");
    for(i=0;i<80;i++){
    	fgets(intro[i].x,100,fp2);
	}
	fclose(fp2);
}

void SaveYourCards(int row1, int line1)//写入已选择的卡，选一次写一次 
{	
	extern int lan; 
	if((usernow == 0 && totalcards >= 25)||(usernow == 1 && totalcards1 >= 25)||(usernow == 2 && totalcards2 >= 25))
	{
		return;//大于等于25张则保存失败 
	}
	else
	{
		if(usernow == 0)
			totalcards++;//自选卡组中卡牌总数增加 
		else if(usernow == 1)
			totalcards1++;
		else if(usernow == 2)
			totalcards2++;
		if((usernow == 0&&totalcards == 25)||(usernow == 1 && totalcards1 == 25)||(usernow == 2 && totalcards2 == 25))
		{
			char str[10];
			string name;
			if(lan==0){
				name = cards[10*row1+line1-11].ename;
			}else{
				name = cards[10*row1+line1-11].cname;
			}
			itoa(cards[10*row1+line1-11].ID, str, 10);//数字转换成字符10进制 
			SetPenColor("White");
			if(usernow == 0)
				MovePen(6.5, 6.2-totalcards*0.2);
			else if(usernow == 1)
				MovePen(6.5, 6.2-totalcards1*0.2);
			else if(usernow == 2)
				MovePen(6.5, 6.2-totalcards2*0.2);
			DrawTextString("  ");
			DrawTextString(str);
			DrawTextString("  ");
			DrawTextString(name);
		}
	}
	
	FILE *fp3;
	if(usernow == 0)
	{
		fp3 = fopen("savedcards.txt", "a");
	}
	else if(usernow == 1)
	{
		fp3 = fopen("savedcards1.txt", "a");
	}
	else if(usernow == 2)
	{
		fp3 = fopen("savedcards2.txt", "a");
	}
			fprintf(fp3, "%d %s %s %d %d %d %d\n", 
					cards[10*row1+line1-11].ID, cards[10*row1+line1-11].ename, cards[10*row1+line1-11].cname,cards[10*row1+line1-11].type, cards[10*row1+line1-11].attack,
					cards[10*row1+line1-11].isHero, cards[10*row1+line1-11].isSpecial);

	fclose(fp3);
} 

void CheckYourCards()
{
	FILE *fp;
	if(usernow == 0)
	{
		fp = fopen("savedcards.txt", "r");
	}
	else if(usernow == 1)
	{
		fp = fopen("savedcards1.txt", "r");
	}
	else if(usernow == 2)
	{
		fp = fopen("savedcards2.txt", "r");
	}
	int i, ID, type, attack, isHero, isSpecial;
	char ename[40], cname[40];
	fseek(fp, 0L, SEEK_END);
	int len = ftell(fp);
	if(len != 0)
	{
		fseek(fp, 0L, SEEK_SET);
		for(i = 0; ; i++)
		{
			fscanf(fp, "%d %s %s %d %d %d %d", &ID, ename, cname, &type, &attack, &isHero, &isSpecial);
			if(feof(fp))
			{
				if(i == 25)
				{
					
					break;
				}
				else
				{
					ClearCards();
					break;
				}
			}
		}
	}
}

void LeadinSavedCards()//如果有已保存卡组则进行读入 
{
	extern int lan;
	FILE *fp4;
	if(usernow == 0)
	{
		fp4 = fopen("savedcards.txt", "r");
	}
	else if(usernow == 1)
	{
		fp4 = fopen("savedcards1.txt", "r");
	}
	else if(usernow == 2)
	{
		fp4 = fopen("savedcards2.txt", "r");
	}
	fseek(fp4, 0L, SEEK_END);
	int len = ftell(fp4);
	if(len != 0)
	{
		fseek(fp4, 0L, SEEK_SET);
		int i;
			for(i = 0; i < 25; i++)
		{
			//从文件中读取已保存的信息 
			fscanf(fp4, "%d %s %s %d %d %d %d",
			&Yourcards[i].ID,// 卡牌id 
			Yourcards[i].ename,//英文名称
			Yourcards[i].cname,//中文名称
			&Yourcards[i].type,//类型 (1-近战单位，2-远程单位，3-攻城单位, 4-天气，5-法术)
			&Yourcards[i].attack,//点数 
			&Yourcards[i].isHero,//是否是英雄牌 
			&Yourcards[i].isSpecial);//特殊效果（0-无 1-间谍 2-治疗 3-同袍 4-团结 5-增益） 
			 
			Yourcards[i].isWeatherControlled = 0;//是否被天气影响 （0-无，1-雾，2-霜，3-雨）
	    	Yourcards[i].isInGameCardsStack = 1;//是否在游戏牌组内 
	    	Yourcards[i].isSelected = 0;//是否被选中 
	    	Yourcards[i].isFielded = 0;//是否在战场上 
	    	Yourcards[i].isGarbaged = 0;//是否进入墓地 
	    }
	    if(usernow == 0) totalcards = 25;
	    else if(usernow == 1) totalcards1 = 25;
	    else if(usernow == 2) totalcards2 = 25;
	}
	fclose(fp4);
}

void DrawSavedList()
{
	extern int lan;
	FILE *fp5;
	if(usernow == 0)
	{
		fp5 = fopen("savedcards.txt", "r");
	}
	else if(usernow == 1)
	{
		fp5 = fopen("savedcards1.txt", "r");
	}
	else if(usernow == 2)
	{
		fp5 = fopen("savedcards2.txt", "r");
	}
	fseek(fp5, 0L, SEEK_END);
	int len = ftell(fp5);	
	if(len != 0)
	{
		SetPenColor("White");
		fseek(fp5, 0L, SEEK_SET);
		int i, ID, type, attack, isHero, isSpecial;
		char ename[40];
		char cname[40];
		for(i = 1; i <= 25; i++)
		{
			char str[10];
			fscanf(fp5, "%d %s %s %d %d %d %d",
			&ID,// 卡牌id 
			ename,//英文名称 
			cname,//中文名称 
			&type,//类型 (1-近战单位，2-远程单位，3-攻城单位, 4-天气，5-法术)
			&attack,//点数 
			&isHero,//是否是英雄牌 
			&isSpecial);//特殊效果（0-无 1-间谍 2-治疗 3-同袍 4-团结 5-增益） 
			
			itoa(ID, str, 10);
			MovePen(6.5, 6.2-i*0.2);
			DrawTextString("  ");
			DrawTextString(str);
			DrawTextString("  ");
			if(lan==0){
				DrawTextString(ename);
			} else{
				DrawTextString(cname);
			}
			
	    }
	}
	fclose(fp5);
}

void DrawListCards(int row1, int line1)//全局变量totalcards可确定画的位置 
{
	extern int lan;
	if((usernow == 0 && totalcards >= 25)||(usernow == 1 && totalcards1 >= 25)||(usernow == 2 && totalcards2 >= 25)) return;
	char str[10];
	string name;
	if(lan==0){
		name = cards[10*row1+line1-11].ename;
	}else{
		name = cards[10*row1+line1-11].cname;
	}
	itoa(cards[10*row1+line1-11].ID, str, 10);//数字转换成字符10进制 
	SetPenColor("White");
	if(usernow == 0)
		MovePen(6.5, 6.2-totalcards*0.2);
	else if(usernow == 1)
		MovePen(6.5, 6.2-totalcards1*0.2);
	else if(usernow == 2)
		MovePen(6.5, 6.2-totalcards2*0.2);
	DrawTextString("  ");
	DrawTextString(str);
	DrawTextString("  ");
	DrawTextString(name);
	
}

void ClearCards()
{
	int i;
	FILE *fp6;
	if(usernow == 0)
	{
		fp6 = fopen("savedcards.txt", "w+");
		totalcards = 0;
	}
	else if(usernow == 1)
	{
		fp6 = fopen("savedcards1.txt", "w+");
		totalcards1 = 0;
	}
	else if(usernow == 2)
	{
		fp6 = fopen("savedcards2.txt", "w+");
		totalcards2 = 0;
	}
	fclose(fp6);
	selectedID = 0;
	for(i=0;i<25;i++)
	{
		num[i]=0;
	}
}

void ClearSavedList()
{
	extern int lan;
	StartFilledRegion(1);
    SetPenColor("Light_Brown");
	DrawBox(6.45, 0.5, gameWidth-7.2, gameHeight-1);
	EndFilledRegion();
	SetPenColor("White");
	DrawBox(6.5, 0.5, gameWidth-7, gameHeight-1); //绘制选牌列表(Card Group)
	MovePen(6.5, 6.3);
	SetPointSize(10);
	if(lan==0){
		DrawTextString("   Your Deck");
	}else{
		DrawTextString("   牌组");
	}
	
	MovePen(6.5, 6.2);//卡组列表下方坐标 
	DrawLine(gameWidth-7, 0);
//	MovePen(6.5, 2.2);
//	SetPenColor("White");
//	DrawLine(gameWidth-7,0);
	MovePen(6.5, 1.1);
	SetPenColor("Red");
	DrawLine(gameWidth-7, 0);
}
