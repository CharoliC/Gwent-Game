#include"Gwent.h"

extern int usernow;

void InitializeView()//��ʼ������ѡ����� 
{
	PlaySound(NULL,NULL,SND_FILENAME | SND_ASYNC | SND_LOOP);
	PlaySound("viewcards.wav",NULL,SND_FILENAME | SND_ASYNC | SND_LOOP);
	/*������*/
	InitializeCards();
    DrawBackground();
    DrawViewCard();
    DrawIntroduction(1,1);
    /*Ĭ��ѡ�����*/ 
    SetPenColor("Light_Green_1");
	DrawBox(0.5, gameHeight-1.3, 0.5, 0.8);
	CheckYourCards();
	LeadinSavedCards();
	DrawSavedList();
	
	registerKeyboardEvent(KeyboardViewProcess);
	row=1,line=1; 
}

void KeyboardViewProcess(int key, int event)//ѡ��������Ӧ���̲��� 
{
	int i;
	int isChosen;
	switch(event)
    {
        case KEY_DOWN:
            switch(key)
            {
				case VK_RIGHT://������� 
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
				case VK_LEFT://������� 
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
				case VK_DOWN://������� 
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
				case VK_UP://������� 
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
				case VK_RETURN://�س�ѡ��
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
						SaveYourCards(row, line);//��Ҫѡ�Ŀ�д�뱣�濨����ļ� 
				    	DrawListCards(row, line);//��ѡ���б�����ѡ�� 
				    	selectedID++;
					}
					break; 
				case VK_BACK://���˸������ѡ�����
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
*ע�⣬��������Ϊԭcards�ļ� 
*ע�⣬��������Ϊԭcards�ļ� 
*ע�⣬��������Ϊԭcards�ļ� 
*ע�⣬��������Ϊԭcards�ļ� 
 **********************************************************/

void InitializeCards() //������Ϣ���벢��ʼ�� 
{
	FILE *fp1;
	fp1=fopen("cardsinfo.txt","r");
	int i;
	for(i=0;i<100;i++){
		//���ļ��ж�ȡ������Ϣ 
		fscanf(fp1,"%d%s%s%d%d%d%d",
		&cards[i].ID,// ����id 
		cards[i].cname,//�������� 
		cards[i].ename,//Ӣ������ 
		&cards[i].type,//���� (1-��ս��λ��2-Զ�̵�λ��3-���ǵ�λ, 4-������5-����)
		&cards[i].attack,//���� 
		&cards[i].isHero,//�Ƿ���Ӣ���� 
		&cards[i].isSpecial);//����Ч����0-�� 1-��� 2-���� 3-ͬ�� 4-�Ž� 5-���棩 
		 
		cards[i].isWeatherControlled=0;//�Ƿ�����Ӱ�� ��0-�ޣ�1-��2-˪��3-�꣩
    //	cards[i].isInGameCardsStack=0;//�Ƿ�����Ϸ������ 
    	cards[i].isSelected=0;//�Ƿ�ѡ�� 
    	cards[i].isFielded=0;//�Ƿ���ս���� 
    	cards[i].isGarbaged=0;//�Ƿ����Ĺ�� 
    }
    fclose(fp1);
    
    FILE *fp2;
    fp2=fopen("cardsintro.txt","r");
    for(i=0;i<80;i++){
    	fgets(intro[i].x,100,fp2);
	}
	fclose(fp2);
}

void SaveYourCards(int row1, int line1)//д����ѡ��Ŀ���ѡһ��дһ�� 
{	
	extern int lan; 
	if((usernow == 0 && totalcards >= 25)||(usernow == 1 && totalcards1 >= 25)||(usernow == 2 && totalcards2 >= 25))
	{
		return;//���ڵ���25���򱣴�ʧ�� 
	}
	else
	{
		if(usernow == 0)
			totalcards++;//��ѡ�����п����������� 
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
			itoa(cards[10*row1+line1-11].ID, str, 10);//����ת�����ַ�10���� 
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

void LeadinSavedCards()//������ѱ��濨������ж��� 
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
			//���ļ��ж�ȡ�ѱ������Ϣ 
			fscanf(fp4, "%d %s %s %d %d %d %d",
			&Yourcards[i].ID,// ����id 
			Yourcards[i].ename,//Ӣ������
			Yourcards[i].cname,//��������
			&Yourcards[i].type,//���� (1-��ս��λ��2-Զ�̵�λ��3-���ǵ�λ, 4-������5-����)
			&Yourcards[i].attack,//���� 
			&Yourcards[i].isHero,//�Ƿ���Ӣ���� 
			&Yourcards[i].isSpecial);//����Ч����0-�� 1-��� 2-���� 3-ͬ�� 4-�Ž� 5-���棩 
			 
			Yourcards[i].isWeatherControlled = 0;//�Ƿ�����Ӱ�� ��0-�ޣ�1-��2-˪��3-�꣩
	    	Yourcards[i].isInGameCardsStack = 1;//�Ƿ�����Ϸ������ 
	    	Yourcards[i].isSelected = 0;//�Ƿ�ѡ�� 
	    	Yourcards[i].isFielded = 0;//�Ƿ���ս���� 
	    	Yourcards[i].isGarbaged = 0;//�Ƿ����Ĺ�� 
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
			&ID,// ����id 
			ename,//Ӣ������ 
			cname,//�������� 
			&type,//���� (1-��ս��λ��2-Զ�̵�λ��3-���ǵ�λ, 4-������5-����)
			&attack,//���� 
			&isHero,//�Ƿ���Ӣ���� 
			&isSpecial);//����Ч����0-�� 1-��� 2-���� 3-ͬ�� 4-�Ž� 5-���棩 
			
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

void DrawListCards(int row1, int line1)//ȫ�ֱ���totalcards��ȷ������λ�� 
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
	itoa(cards[10*row1+line1-11].ID, str, 10);//����ת�����ַ�10���� 
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
	DrawBox(6.5, 0.5, gameWidth-7, gameHeight-1); //����ѡ���б�(Card Group)
	MovePen(6.5, 6.3);
	SetPointSize(10);
	if(lan==0){
		DrawTextString("   Your Deck");
	}else{
		DrawTextString("   ����");
	}
	
	MovePen(6.5, 6.2);//�����б��·����� 
	DrawLine(gameWidth-7, 0);
//	MovePen(6.5, 2.2);
//	SetPenColor("White");
//	DrawLine(gameWidth-7,0);
	MovePen(6.5, 1.1);
	SetPenColor("Red");
	DrawLine(gameWidth-7, 0);
}
