#include"Gwent.h"

void InitializeCards() //������Ϣ���벢��ʼ�� 
{
	FILE *fp1;
	fp1=fopen("cardsinfo.txt","r");
	int i;
	for(i=0;i<40;i++)
	{
		//���ļ��ж�ȡ������Ϣ 
		fscanf(fp1,"%d%s%d%d%d%d",
		&cards[i].ID,// ����id 
		cards[i].name,//���� 
		&cards[i].type,//���� (1-��ս��λ��2-Զ�̵�λ��3-���ǵ�λ, 4-������5-����)
		&cards[i].attack,//���� 
		&cards[i].isHero,//�Ƿ���Ӣ���� 
		&cards[i].isSpecial);//����Ч����0-�� 1-��� 2-���� 3-ͬ�� 4-�Ž� 5-���棩 
		 
		cards[i].isWeatherControlled=0;//�Ƿ�����Ӱ�� ��0-�ޣ�1-��2-˪��3-�꣩
    	cards[i].isInGameCardsStack=0;//�Ƿ�����Ϸ������ 
    	cards[i].isSelected=0;//�Ƿ�ѡ�� 
    	cards[i].isFielded=0;//�Ƿ���ս���� 
    	cards[i].isGarbaged=0;//�Ƿ����Ĺ�� 
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

void SaveYourCards(int row1, int line1)//д����ѡ��Ŀ���ѡһ��дһ�� 
{	
	if(totalcards >= 25)
	{
		return;//���ڵ���25���򱣴�ʧ�� 
	}
	else
	{
		totalcards++;//��ѡ�����п����������� 
	}
	
	FILE *fp3;
	fp3 = fopen("savedcards.txt", "a");
	fprintf(fp3, "%d %s %d %d %d %d\n", 
	cards[10*row1+line1-11].ID, cards[10*row1+line1-11].name, cards[10*row1+line1-11].type, cards[10*row1+line1-11].attack,
	cards[10*row1+line1-11].isHero, cards[10*row1+line1-11].isSpecial);
	fclose(fp3);
} 

void LeadinSavedCards()//������ѱ��濨������ж��� 
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
			//���ļ��ж�ȡ�ѱ������Ϣ 
			fscanf(fp4, "%d %s %d %d %d %d",
			&Yourcards[i].ID,// ����id 
			Yourcards[i].name,//���� 
			&Yourcards[i].type,//���� (1-��ս��λ��2-Զ�̵�λ��3-���ǵ�λ, 4-������5-����)
			&Yourcards[i].attack,//���� 
			&Yourcards[i].isHero,//�Ƿ���Ӣ���� 
			&Yourcards[i].isSpecial);//����Ч����0-�� 1-��� 2-���� 3-ͬ�� 4-�Ž� 5-���棩 
			 
			Yourcards[i].isWeatherControlled = 0;//�Ƿ�����Ӱ�� ��0-�ޣ�1-��2-˪��3-�꣩
	    	Yourcards[i].isInGameCardsStack = 1;//�Ƿ�����Ϸ������ 
	    	Yourcards[i].isSelected = 0;//�Ƿ�ѡ�� 
	    	Yourcards[i].isFielded = 0;//�Ƿ���ս���� 
	    	Yourcards[i].isGarbaged = 0;//�Ƿ����Ĺ�� 
	    	
	    	if(feof(fp4)) 
			{
				totalcards = i + 1;
				break;
			}//��������20�ţ�����25��
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
			&ID,// ����id 
			name,//���� 
			&type,//���� (1-��ս��λ��2-Զ�̵�λ��3-���ǵ�λ, 4-������5-����)
			&attack,//���� 
			&isHero,//�Ƿ���Ӣ���� 
			&isSpecial);//����Ч����0-�� 1-��� 2-���� 3-ͬ�� 4-�Ž� 5-���棩 
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

void DrawListCards(int row1, int line1)//ȫ�ֱ���totalcards��ȷ������λ�� 
{
	if(totalcards > 25) return;
	char str[10];
	string name = cards[10*row1+line1-11].name;
	itoa(cards[10*row1+line1-11].ID, str, 10);//����ת�����ַ�10���� 
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
	DrawBox(6.5, 0.5, gameWidth-7, gameHeight-1); //����ѡ���б�(Card Group)
	MovePen(6.5, 6.3);
	SetPointSize(10);
	DrawTextString("   Your Card Group");
	MovePen(6.5, 6.2);//�����б��·����� 
	DrawLine(gameWidth-7, 0);
	MovePen(6.5, 2.2);
	SetPenColor("White");
	DrawLine(gameWidth-7, 0);
	MovePen(6.5, 1.2);
	SetPenColor("Red");
	DrawLine(gameWidth-7, 0);
}


