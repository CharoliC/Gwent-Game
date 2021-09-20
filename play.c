#include "Gwent.h"

card allocatedCards[12];//��������
card remainedCards[13];//����������δ���ֵ������е�������
card yourMelee[12], yourRange[12], yourSiege[12];//����ս���ϵĿ���
card enemyMelee[12], enemyRange[12], enemySiege[12];//�Է�ս���ϵĿ���
card weatherCards[3];
card GraveCards[25];//����Ĺ��
card eGraveCards[25];//�з�Ĺ�� 

char numDisplay[4];

bool isYourTurn;//�Ƿ�Ϊ�����غ�
bool isYouGiveUp=FALSE;//�����Ƿ��������
bool isEnemyGiveUp=FALSE;//�з��Ƿ��������
bool isGameFinished=FALSE;//������Ϸ�Ƿ����
bool isOperated=FALSE;//�����غ��Ƿ������Ч�ĳ��Ʋ���
bool isSpy;

int randomNum[12],remainedNum[13];//�����ţ����ڷ���
int cardState=1;//�����ƶ����ǹ����г���
int yourField_1=1, yourField_2=1, yourField_3=1;//���ڵ��ڿ�����ս���ϵķ���λ�ã�������
int enemyField_1=1, enemyField_2=1, enemyField_3=1;//���ڵ��ڿ�����ս���ϵķ���λ�ã��Է���
int weatherField=1;//���ڵ�������ͼ��λ��
int yourGrave=0, enemyGrave=0;//�����͵з�Ĺ�صĿ�����
int gameStage=1;//��ǰ��Ϸ���ڵ�С����
int yourWin=0, *pyourWin=&yourWin;//����ʤ����С����, ָ��û��Ҫ���������ø�
int enemyWin=0, *penemyWin=&enemyWin;//�Է�ʤ����С����
int yourAttack[3], enemyAttack[3];//�����ͶԷ�����ս���ĵ�����0-��ս��1-Զ�̣�2-����
int yourAttacks, enemyAttacks;//�����ͶԷ����ܵ���
int winner;//0-ƽ�֣�1-������2-�Է�
int isFrost=FALSE, isFog=FALSE, isRain=FALSE;
int enemyHandcards=12;//����������
char enemyhandcards[10]; 
card yourRecentcard;//��ҳ������һ���� 

void EnemyPlaying();
void EnemyLogic(card ecard);
void CardLogic(card ecard);

void InitializePlay()
{
    yourGrave=0;
    enemyGrave=0;
	yourWin=0;
	enemyWin=0;
	gameStage=1;
	enemyHandcards=12;
	cardState=1;
    LeadinSavedCards();//���뱣��Ŀ���
    enemySide=RandomInteger(1, 4);//��������з���Ӫ
    DrawPlayBoard();//���ƶԾֽ���
    SetPenColor("White");
	SetPointSize(30);
	sprintf(enemyhandcards,"%d",enemyHandcards);
	MovePen(0.6,4.8);
	DrawTextString(enemyhandcards);

/*�����������ַ�*/
    if(yourSide==SCOIA && enemySide==SCOIA && RandomChance(0.5) ||
       yourSide!=SCOIA && enemySide!=SCOIA && RandomChance(0.5) ||
       yourSide==SCOIA && enemySide!=SCOIA)
    {
        isYourTurn=TRUE;
    }
    else
    {
        isYourTurn=FALSE;
    }

/*ȷ���������к�*/
    int i,j,k=0;
    int isEqual;//���ڰ�randomNum������ѡ��
    for(i=0;i<25;i++)
    {
        if(i-j==13)
        {
            randomNum[j]=i;
            j++;
        }
        else
        {
            if(rand()%25+1<=12)
            {
                randomNum[j]=i;
                j++;
            }
            if(j==12)
            {
                break;
            }
        }
    }
/*ȷ��ʣ��13�������к�*/
    for(i=0;i<25;i++)
    {
        isEqual=0;
        for(j=0;j<12;j++)
        {
            if(randomNum[j]==i)
            {
                isEqual=1;
                break;
            }
        }
        if(isEqual==0)
        {
            remainedNum[k]=i;
            k++;
        }
    }
/*�������кŷֱ������ƺ�ʣ���Ƶ���Ϣ*/
    for(i=0;i<12;i++)
    {
        allocatedCards[i]=Yourcards[randomNum[i]];
    }
    for(i=0;i<13;i++)
    {
        remainedCards[i]=Yourcards[remainedNum[i]];
    }
/*��ʾ��Ӫ��Ϣ*/
    SetPenColor("White");
    SetPointSize(20);
    MovePen(0.3,gameHeight/2-1.6);
    extern int lan;
    if(lan==0)
    {
        switch(yourSide)
        {
            case NORTHERN_REALMS:
                DrawTextString("Northern Realms");
                break;
            case NILFGAARD:
                DrawTextString("Nilfgaard");
                break;
            case SCOIA:
                DrawTextString("Scoia' Tael");
                break;
            case MONSTERS:    
                DrawTextString("Monsters");
                break;
        }
        MovePen(0.3,gameHeight/2+1);
        switch(enemySide)
        {
            case NORTHERN_REALMS:
                DrawTextString("Northern Realms");
                break;
            case NILFGAARD:
                DrawTextString("Nilfgaard");
                break;
            case SCOIA:
                DrawTextString("Scoia' Tael");
                break;
            case MONSTERS:    
                DrawTextString("Monsters");
                break;
        }
    }
    else
    {
        switch(yourSide)
        {
            case NORTHERN_REALMS:
                DrawTextString("��������");
                break;
            case NILFGAARD:
                DrawTextString("�ḥ�ȵµ۹�");
                break;
            case SCOIA:
                DrawTextString("����");
                break;
            case MONSTERS:    
                DrawTextString("����");
                break;
        }
        MovePen(0.5,gameHeight/2+1);
            switch(enemySide)
        {
            case NORTHERN_REALMS:
                DrawTextString("��������");
               break;
            case NILFGAARD:
                DrawTextString("�ḥ�ȵµ۹�");
                break;
            case SCOIA:
                DrawTextString("����");
                break;
            case MONSTERS:    
                DrawTextString("����");
                break;
        }
    }

/*��ʾ����*/
    for(i=0;i<12;i++)
    {
        DrawHandCards(1.3+0.55*i, 0.4, allocatedCards[i].ID);
    }

/*��ʼ��꣨���ǣ�*/
    DrawTriangleCursor(1.53,0.27,0);

/*��ʼ��ϸ��Ϣ���Ҳ��*/
    DrawDetail(allocatedCards[0]);

/*��ʾ�Ƿ�Ϊ�����غϣ���һС������Ȩ��*/
    while(isYourTurn==TRUE)
    {
        if(lan==0)
        {
            SetPointSize(30);
            SetPenColor("Red");
            MovePen(0.4,gameHeight/2-2.05);
            DrawTextString("Your Turn!");
        }
        else
        {
            SetPointSize(25);
            SetPenColor("Red");
            MovePen(0.4,gameHeight/2-2.05);
            DrawTextString("��Ļغϣ�");
        }
        break;
    }
    PlaySound(NULL,NULL,SND_FILENAME);
	if(enemySide==NORTHERN_REALMS){
		PlaySound("northern.wav",NULL,SND_FILENAME | SND_ASYNC | SND_LOOP);
	}else if(enemySide==NILFGAARD){
		PlaySound("nilfgaard.wav",NULL,SND_FILENAME | SND_ASYNC | SND_LOOP);
	}else if(enemySide==SCOIA){
		PlaySound("scoia.wav",NULL,SND_FILENAME | SND_ASYNC | SND_LOOP);
	}else if(enemySide==MONSTERS){
		PlaySound("monsters.wav",NULL,SND_FILENAME | SND_ASYNC | SND_LOOP);
	}

    registerKeyboardEvent(KeyboardPlayProcess);//������Ϣ�ص�����
}


void InitializeSideSelect()
{
	PlaySound(NULL,NULL,SND_FILENAME);
	PlaySound("select.wav",NULL,SND_FILENAME | SND_ASYNC | SND_LOOP);
    DrawBackground();
    extern int lan;
/*��Ӫѡ��*/
    if(lan==0){
        SetPointSize(35);
        MovePen(gameWidth/2-TextStringWidth("Choose  Your  Side")/2,5.5);
        SetPenColor("White");
        DrawTextString("Choose  Your  Side");
        SetPointSize(30);
        MovePen(gameWidth/2-TextStringWidth("Northern  Realms")/2,4.5);
        DrawTextString("Northern  Realms");
        MovePen(gameWidth/2-TextStringWidth("The  Nilfgaardian  Empire")/2,3.5);
        DrawTextString("The  Nilfgaardian  Empire");
        MovePen(gameWidth/2-TextStringWidth("Scoia' Tael")/2,2.5);
        DrawTextString("Scoia' Tael");
        MovePen(gameWidth/2-TextStringWidth("Monsters")/2,1.5);
        DrawTextString("Monsters");
    }else{
        SetPointSize(35);
        MovePen(gameWidth/2-TextStringWidth("ѡ �� �� Ӫ")/2-0.16,5.5);
        SetPenColor("White");
        DrawTextString("ѡ �� �� Ӫ");
        SetPointSize(30);
        MovePen(gameWidth/2-TextStringWidth("�� �� �� ��")/2,4.5);
        DrawTextString("�� �� �� ��");
        MovePen(gameWidth/2-TextStringWidth("�� �� �� �� �� ��")/2,3.5);
        DrawTextString("�� �� �� �� �� ��");
        MovePen(gameWidth/2-TextStringWidth("�� �� ��")/2,2.5);
        DrawTextString("�� �� ��");
        MovePen(gameWidth/2-TextStringWidth("�� ��")/2,1.5);
        DrawTextString("�� ��");
    }
    
    extern int lan;
/*��ʼ���*/
    SetPenColor("Gold_1");
    if(lan==0){
        MovePen(gameWidth/2-TextStringWidth("Northern  Realms")/2,4.5);
        DrawTextString("Northern  Realms");
        SetPenColor("Gray");
        MovePen(gameWidth/2-TextStringWidth("Draw a card from your deck whnever you win a round")/2,4.2);
        DrawTextString("Draw a card from your deck whnever you win a round");
    }else{
        MovePen(gameWidth/2-TextStringWidth("�� �� �� ��")/2,4.5);
        DrawTextString("�� �� �� ��");
        SetPenColor("Gray");
        SetPointSize(20); 
        MovePen(gameWidth/2-TextStringWidth("Ӯ��һ�غϺ�ɳ�һ����")/2,4.2);
        DrawTextString("Ӯ��һ�غϺ�ɳ�һ����");
    }
    SetPointSize(30); 
    state=1;
    registerKeyboardEvent(KeyboardSideProcess);//������Ϣ�ص�����
}

void KeyboardSideProcess(int key, int event)//������Ϣ�ص���������Ӫѡ��
{
    extern int lan; 
        switch(event)
    {
        case KEY_DOWN:
            if(lan==0){//Ӣ�� 
                switch(key)
            {
                case VK_DOWN:
                    if(state<4)
                    {
                        switch(state)
                        {
                            case 1:
                                SetPenColor("White");
                                MovePen(gameWidth/2-TextStringWidth("Northern  Realms")/2,4.5);
                                DrawTextString("Northern  Realms");
                                SetPenColor("Light_Brown");
                                StartFilledRegion(1);
                                DrawBox(1,4.1,8,0.32);
                                EndFilledRegion();

                                SetPenColor("Gold_1");
                                MovePen(gameWidth/2-TextStringWidth("The  Nilfgaardian  Empire")/2,3.5);
                                DrawTextString("The  Nilfgaardian  Empire");
                                SetPenColor("Gray");
                                MovePen(gameWidth/2-TextStringWidth("If draw, you win")/2,3.2);
                                DrawTextString("If draw, you win");
                                state++;
                                break;
                            case 2:
                                SetPenColor("White");
                                MovePen(gameWidth/2-TextStringWidth("The  Nilfgaardian  Empire")/2,3.5);
                                DrawTextString("The  Nilfgaardian  Empire");
                                SetPenColor("Light_Brown");
                                MovePen(gameWidth/2-TextStringWidth("If draw, you win")/2,3.2);
                                DrawTextString("If draw, you win");

                                SetPenColor("Gold_1");
                                MovePen(gameWidth/2-TextStringWidth("Scoia' Tael")/2,2.5);
                                DrawTextString("Scoia' Tael");
                                SetPenColor("Gray");
                                MovePen(gameWidth/2-TextStringWidth("You always put cards first")/2,2.2);
                                DrawTextString("You always put cards first");
                                state++;
                                break;
                            case 3:
                                SetPenColor("White");
                                MovePen(gameWidth/2-TextStringWidth("Scoia' Tael")/2,2.5);
                                DrawTextString("Scoia' Tael");
                                SetPenColor("Light_Brown");
                                MovePen(gameWidth/2-TextStringWidth("You always put cards first")/2,2.2);
                                DrawTextString("You always put cards first");

                                SetPenColor("Gold_1");
                                MovePen(gameWidth/2-TextStringWidth("Monsters")/2,1.5);
                                DrawTextString("Monsters");
                                SetPenColor("Gray");
                                MovePen(gameWidth/2-TextStringWidth("At the end of a round, ")/2,1.2);
                                DrawTextString("At the end of a round, ");
                                MovePen(gameWidth/2-TextStringWidth("a random unit card will stay on the playboard")/2,0.9);
                                DrawTextString("a random unit card will stay on the playboard");
                                state++;
                                break;
                        }
                    }
                    break;

                case VK_UP:
                    if(state>1)
                    {
                        switch(state)
                        {
                            
                            case 2:
                                SetPenColor("White");
                                MovePen(gameWidth/2-TextStringWidth("The  Nilfgaardian  Empire")/2,3.5);
                                DrawTextString("The  Nilfgaardian  Empire");
                                SetPenColor("Light_Brown");
                                MovePen(gameWidth/2-TextStringWidth("If draw, you win")/2,3.2);
                                DrawTextString("If draw, you win");

                                SetPenColor("Gold_1");
                                MovePen(gameWidth/2-TextStringWidth("Northern  Realms")/2,4.5);
                                DrawTextString("Northern  Realms");
                                SetPenColor("Gray");
                                MovePen(gameWidth/2-TextStringWidth("Draw a card from your deck whnever you win a round")/2,4.2);
                                DrawTextString("Draw a card from your deck whnever you win a round");
                                state--;
                                break;
                            case 3:
                                SetPenColor("White");
                                MovePen(gameWidth/2-TextStringWidth("Scoia' Tael")/2,2.5);
                                DrawTextString("Scoia' Tael");
                                SetPenColor("Light_Brown");
                                MovePen(gameWidth/2-TextStringWidth("You always put cards first")/2,2.2);
                                DrawTextString("You always put cards first");

                                SetPenColor("Gold_1");
                                MovePen(gameWidth/2-TextStringWidth("The  Nilfgaardian  Empire")/2,3.5);
                                DrawTextString("The  Nilfgaardian  Empire");
                                SetPenColor("Gray");
                                MovePen(gameWidth/2-TextStringWidth("If draw, you win")/2,3.2);
                                DrawTextString("If draw, you win");
                                state--;
                                break;
                            case 4:
                                SetPenColor("White");
                                MovePen(gameWidth/2-TextStringWidth("Monsters")/2,1.5);
                                DrawTextString("Monsters");
                                SetPenColor("Light_Brown");
                                MovePen(gameWidth/2-TextStringWidth("At the end of a round, ")/2,1.2);
                                DrawTextString("At the end of a round, ");
                                MovePen(gameWidth/2-TextStringWidth("a random unit card will stay on the playboard")/2,0.9);
                                DrawTextString("a random unit card will stay on the playboard");

                                SetPenColor("Gold_1");
                                MovePen(gameWidth/2-TextStringWidth("Scoia' Tael")/2,2.5);
                                DrawTextString("Scoia' Tael");
                                SetPenColor("Gray");
                                MovePen(gameWidth/2-TextStringWidth("You always put cards first")/2,2.2);
                                DrawTextString("You always put cards first");
                                state--;
                                break;
                        }
                    }
                    break;
                
                case VK_RETURN:
                    switch(state)
                    {
                        case 1:
                            yourSide=1;
                            break;
                        case 2: 
                            yourSide=2;
                            break;
                        case 3:
                            yourSide=3;
                            break;
                        case 4:
                            yourSide=4;
                            break;
                    }
                    InitializePlay();
                    break;
                case VK_BACK:
                    InitializeOption();
                    break;
            }
            break;
            }
            else{//���� 
                switch(key)
            {
                case VK_DOWN:
                    if(state<4)
                    {
                        switch(state)
                        {
                            case 1:
                                SetPointSize(30); 
                                SetPenColor("White");
                                MovePen(gameWidth/2-TextStringWidth("�� �� �� ��")/2,4.5);
                                DrawTextString("�� �� �� ��");
                                SetPenColor("Light_Brown");
                                StartFilledRegion(1);
                                DrawBox(2.5,4.1,6,0.32);
                                EndFilledRegion();

                                SetPointSize(30); 
                                SetPenColor("Gold_1");
                                MovePen(gameWidth/2-TextStringWidth("�� �� �� �� �� ��")/2,3.5);
                                DrawTextString("�� �� �� �� �� ��");
                                SetPenColor("Gray");
                                SetPointSize(20); 
                                MovePen(gameWidth/2-TextStringWidth("ƽ��ʱ�ɻ��ʤ��")/2,3.2);
                                DrawTextString("ƽ��ʱ�ɻ��ʤ��");
                                state++;
                                break;
                            case 2:
                                SetPointSize(30); 
                                SetPenColor("White");
                                MovePen(gameWidth/2-TextStringWidth("�� �� �� �� �� ��")/2,3.5);
                                DrawTextString("�� �� �� �� �� ��");
                                SetPenColor("Light_Brown");
                                SetPointSize(20); 
                                MovePen(gameWidth/2-TextStringWidth("ƽ��ʱ�ɻ��ʤ��")/2,3.2);
                                DrawTextString("ƽ��ʱ�ɻ��ʤ��");

                                SetPointSize(30); 
                                SetPenColor("Gold_1");
                                MovePen(gameWidth/2-TextStringWidth("�� �� ��")/2,2.5);
                                DrawTextString("�� �� ��");
                                SetPenColor("Gray");
                                SetPointSize(20); 
                                MovePen(gameWidth/2-TextStringWidth("�������ȳ���")/2,2.2);
                                DrawTextString("�������ȳ���");
                                state++;
                                break;
                            case 3:
                                SetPointSize(30); 
                                SetPenColor("White");
                                MovePen(gameWidth/2-TextStringWidth("�� �� ��")/2,2.5);
                                DrawTextString("�� �� ��");
                                SetPenColor("Light_Brown");
                                SetPointSize(20); 
                                MovePen(gameWidth/2-TextStringWidth("�������ȳ���")/2,2.2);
                                DrawTextString("�������ȳ���");

                                SetPointSize(30); 
                                SetPenColor("Gold_1");
                                MovePen(gameWidth/2-TextStringWidth("�� ��")/2,1.5);
                                DrawTextString("�� ��");
                                SetPenColor("Gray");
                                SetPointSize(20); 
                                MovePen(gameWidth/2-TextStringWidth("�غϽ���ʱ����ѡ�񼺷�ս����һ���Ʋ�ʹ�䱣��")/2,1.2);
                                DrawTextString("�غϽ���ʱ����ѡ�񼺷�ս����һ���Ʋ�ʹ�䱣��");
                                state++;
                                break;
                        }
                    }
                    break;

                case VK_UP:
                    if(state>1)
                    {
                        switch(state)
                        {
                            
                            case 2:
                                SetPointSize(30); 
                                SetPenColor("White");
                                MovePen(gameWidth/2-TextStringWidth("�� �� �� �� �� ��")/2,3.5);
                                DrawTextString("�� �� �� �� �� ��");
                                SetPenColor("Light_Brown");
                                SetPointSize(20); 
                                MovePen(gameWidth/2-TextStringWidth("ƽ��ʱ�ɻ��ʤ��")/2,3.2);
                                DrawTextString("ƽ��ʱ�ɻ��ʤ��");

                                SetPointSize(30); 
                                SetPenColor("Gold_1");
                                MovePen(gameWidth/2-TextStringWidth("�� �� �� ��")/2,4.5);
                                DrawTextString("�� �� �� ��");
                                SetPenColor("Gray");
                                SetPointSize(20); 
                                MovePen(gameWidth/2-TextStringWidth("Ӯ��һ�غϺ�ɳ�һ����")/2,4.2);
                                DrawTextString("Ӯ��һ�غϺ�ɳ�һ����");
                                state--;
                                break;
                            case 3:
                                
                                SetPointSize(30); SetPenColor("White");
                                MovePen(gameWidth/2-TextStringWidth("�� �� ��")/2,2.5);
                                DrawTextString("�� �� ��");
                                SetPenColor("Light_Brown");
                                SetPointSize(20); 
                                MovePen(gameWidth/2-TextStringWidth("�������ȳ���")/2,2.2);
                                DrawTextString("�������ȳ���");

                                
                                SetPointSize(30); 
                                SetPenColor("Gold_1");
                                MovePen(gameWidth/2-TextStringWidth("�� �� �� �� �� ��")/2,3.5);
                                DrawTextString("�� �� �� �� �� ��");
                                SetPenColor("Gray");
                                SetPointSize(20); 
                                MovePen(gameWidth/2-TextStringWidth("ƽ��ʱ�ɻ��ʤ��")/2,3.2);
                                DrawTextString("ƽ��ʱ�ɻ��ʤ��");
                                state--;
                                break;
                            case 4:
                                SetPointSize(30); 
                                SetPenColor("White");
                                MovePen(gameWidth/2-TextStringWidth("�� ��")/2,1.5);
                                DrawTextString("�� ��");
                                SetPenColor("Light_Brown");
                                SetPointSize(20); 
                                MovePen(gameWidth/2-TextStringWidth("�غϽ���ʱ����ѡ�񼺷�ս����һ���Ʋ�ʹ�䱣��")/2,1.2);
                                DrawTextString("�غϽ���ʱ����ѡ�񼺷�ս����һ���Ʋ�ʹ�䱣��");

                                SetPointSize(30); 
                                SetPenColor("Gold_1");
                                MovePen(gameWidth/2-TextStringWidth("�� �� ��")/2,2.5);
                                DrawTextString("�� �� ��");
                                SetPenColor("Gray");
                                SetPointSize(20); 
                                MovePen(gameWidth/2-TextStringWidth("�������ȳ���")/2,2.2);
                                DrawTextString("�������ȳ���");
                                state--;
                                break;
                        }
                    }
                    break;
                
                case VK_RETURN:
                    switch(state)
                    {
                        case 1:
                            yourSide=1;
                            break;
                        case 2: 
                            yourSide=2;
                            break;
                        case 3:
                            yourSide=3;
                            break;
                        case 4:
                            yourSide=4;
                            break;
                    }
                    InitializePlay();
                    break;
                case VK_BACK:
                    InitializeOption();
                    break;
            }
        break;
            }
            
    }    
    
}

void KeyboardPlayProcess(int key, int event)
{
    int i;//��ѭ����ʹ��
    int preWin;
    card aliveCard;
    switch(event)
    {
        case KEY_DOWN:
            switch(key)
            {
                case VK_NUMPAD1:
                    DrawHandCards(2.3,gameHeight-3.8,37);
                    DrawHandCards(2.3,gameHeight-4.72,37);
                    DrawHandCards(2.3,gameHeight-5.64,37);
                    yourMelee[11].type=5;
                    yourRange[11].type=5;
                    yourSiege[11].type=5;
                    yourAttack[0]=AttackCalculate(yourMelee, yourField_1-1);
                    yourAttack[1]=AttackCalculate(yourRange, yourField_2-1);
                    yourAttack[2]=AttackCalculate(yourRange, yourField_3-1);
                    UpdateAttack(4);
                    UpdateAttack(5);
                    UpdateAttack(6);
                    break;
                case VK_NUMPAD2:
                    if(yourField_1<10)
                    {
                        DrawHandCards(2.3+0.55*yourField_1,gameHeight-3.8,9);
                        yourMelee[yourField_1-1]=cards[10];
                        yourField_1++;
                        yourAttack[0]=AttackCalculate(yourMelee, yourField_1-1);
                        UpdateAttack(4);
                    }
                    break;
                case VK_NUMPAD3:
                    for(i=1;i<10;i++)
                    {
                        DrawHandCards(2.3+0.55*i,gameHeight-3.8,1);
                        DrawHandCards(2.3+0.55*i,gameHeight-4.72,4);
                        DrawHandCards(2.3+0.55*i,gameHeight-5.64,5);
                        yourMelee[i-1].attack=15;
                        yourRange[i-1].attack=10;
                        yourSiege[i-1].attack=10;
                        yourField_1=10;
                        yourField_2=10;
                        yourField_3=10;
                    }
                    yourAttack[0]=AttackCalculate(yourMelee, yourField_1-1);
                    yourAttack[1]=AttackCalculate(yourRange, yourField_2-1);
                    yourAttack[2]=AttackCalculate(yourRange, yourField_3-1);
                    UpdateAttack(4);
                    UpdateAttack(5);
                    UpdateAttack(6);
                    break;
                case VK_NUMPAD4:
                    yourWin=2;
                    GameOver();
                    break;
                case VK_F1:
                    yourWin=2;
                    enemyWin=0;
                    GameOver();
                    break;
                case VK_F2:
                    yourWin=0;
                    enemyWin=2;
                    GameOver();
                    break;
                case VK_F3:
                    yourWin=0;
                    enemyWin=0;
                    GameOver();
                    break;
                /*F12��������*/
                case VK_F12:	
            		StartFilledRegion(1);
            		SetPenColor("Light_Brown");
            		DrawBox(0.35,gameHeight/2-2.1, 1.6, 0.3);
            		EndFilledRegion();
                    //if(isYouGiveUp==FALSE)
                    //{
                        isYouGiveUp=TRUE;
                        isYourTurn=FALSE;//�������ƺ󣬼����غ���������
                        if(isEnemyGiveUp==TRUE)//������Ȩ�����ж�С���Ƿ����
                        {
                            preWin=yourWin;
                            /*С��ʤ������*/
                            JudgeWinner(pyourWin, penemyWin);
                            /*���ս��*/
                            yourAttack[0]=0;
                            yourAttack[1]=0;
                            yourAttack[2]=0;
                            enemyAttack[0]=0;
                            enemyAttack[1]=0;
                            enemyAttack[2]=0;
                            for(i=1;i<=6;i++)
                            {
                                UpdateAttack(i);
                            }
                            for(i=0;i<12;i++)
                            {
                                if(allocatedCards[i].isFielded && allocatedCards[i].type!=4)
                                {
                                    allocatedCards[i].isFielded=0;//���ƴ�ս����ȥ��
                                    allocatedCards[i].isGarbaged=1;//���ƽ���Ĺ��
                                    yourGrave++;
                                }
                            }
                            for(i=0;i<13;i++)
                            {
                                if(remainedCards[i].isFielded)
                                {
                                    remainedCards[i].isFielded=0;
                                    remainedCards[i].isGarbaged=1;
                                    yourGrave++;
                                }
                            }
                            yourMelee[11].type=-1;
                            yourRange[11].type=-1;
                            yourSiege[11].type=-1;
                            enemyMelee[11].type=-1;
                            enemyRange[11].type=-1;
                            enemySiege[11].type=-1;
                            UpdateGrave(1);
                            ClearField();
                            /*��һС�ֿ�ʼ*/
                            if(yourWin==2||enemyWin==2)
                            {
                                /*��Ϸ����*/
                                GameOver();
                            }
                            else
                            {
                                EnemyLogic(cards[34]); 
                                enemyHandcards++;
                                gameStage++;
                            }
                        }
                        else//�Է�δ����
                        {
                            EnemyPlaying();
                        }
                        break;
                    //}

                /*�˸�ص���һ���棨��ͣ�ã�*/
                case VK_BACK:
                    //InitializeSideSelect();
                    break;

                /*���ƹ��*/
                case VK_RIGHT:
                    if(cardState<=11)
                    {
                        DrawTriangleCursor(0.98+0.55*cardState,0.27,1);
                        DrawTriangleCursor(1.53+0.55*cardState,0.27,0);
                        cardState++;
                    }
                    DrawDetail(allocatedCards[cardState-1]);//������ϸ��Ϣ
                    break;

                /*���ƹ��*/
                case VK_LEFT:
                    if(cardState>=2)
                    {
                        DrawTriangleCursor(0.98+0.55*cardState,0.27,1);
                        DrawTriangleCursor(0.43+0.55*cardState,0.27,0);
                        cardState--;
                    }
                    DrawDetail(allocatedCards[cardState-1]);//������ϸ��Ϣ
                    break;

                /*�س��������ǰ���ָ�������*/
                case VK_RETURN:
                    if(isYourTurn==TRUE)//�����غ�
                    {    
                        if(allocatedCards[cardState-1].isFielded==0 &&
                           allocatedCards[cardState-1].isGarbaged==0)//����δ������ſɴ��
                        {                
                        	/*����your turn*/
                        	StartFilledRegion(1);
                        	SetPenColor("Light_Brown");
                        	DrawBox(0.35,gameHeight/2-2.1, 1.6, 0.3);
                        	EndFilledRegion();
                            /*��ȥ�����ƣ����ƿ��ڣ�*/
                            StartFilledRegion(1);
                            SetPenColor("Light_Brown");
                            DrawBox(0.75+0.55*cardState, 0.4, 0.55, 0.9);
                            EndFilledRegion();

                            /*����Ч��+������ʾ*/
                            CardLogic(allocatedCards[cardState-1]);
                            yourRecentcard=allocatedCards[cardState-1];

                            /*���������Ϸ��Ϣ*/
                            for(i=1;i<=6;i++)
                            {
                                UpdateAttack(i);
                            }
                            UpdateGrave(1);
                            isOperated=TRUE;//������Ч
                            if(isSpy==FALSE)//��ֹ�����õ��Ʋ��ܴ��
                            {
                                allocatedCards[cardState-1].isFielded=1;//�ÿ��ƽ���ս��
                            }
                            if(isEnemyGiveUp==FALSE && isOperated==TRUE)//�������ҵз�δ�������ƣ�����ĻغϽ���
                            {
                                isYourTurn=FALSE;
                            }
                        }
                    }
                    else//�Է��غ�
                    {
                    	/*д��your turn*/
                        SetPointSize(30);
            			SetPenColor("Red");
           				MovePen(0.4,gameHeight/2-2.05);
            			DrawTextString("Your Turn!");
            			if(isYouGiveUp==TRUE){
            				StartFilledRegion(1);
            				SetPenColor("Light_Brown");
            				DrawBox(0.35,gameHeight/2-2.1, 1.6, 0.3);
            				EndFilledRegion();
        				}
            				
                    	enemyAttacks=enemyAttack[0]+enemyAttack[1]+enemyAttack[2];
                    	yourAttacks=yourAttack[0]+yourAttack[1]+yourAttack[2];
						EnemyPlaying();
						for(i=1;i<=6;i++)
                        {
                            UpdateAttack(i);
                    	}
                        if(isEnemyGiveUp==TRUE)
                        {
                            if(isYouGiveUp==TRUE)//�Է���Ȩ�����ж�С���Ƿ����
                            {
                                /*С��ʤ������*/
                                JudgeWinner(pyourWin, penemyWin);
                                /*���ս��*/
                                yourAttack[0]=0;
                                yourAttack[1]=0;
                                yourAttack[2]=0;
                                enemyAttack[0]=0;
                                enemyAttack[1]=0;
                                enemyAttack[2]=0;
                                for(i=1;i<=6;i++)
                                {
                                    UpdateAttack(i);
                                }
                                for(i=0;i<12;i++)
                                {
                                    if(allocatedCards[i].isFielded && allocatedCards[i].type!=4)
                                    {
                                        allocatedCards[i].isFielded=0;
                                        allocatedCards[i].isGarbaged=1;
                                        yourGrave++;
                                    }
                                }
                                for(i=0;i<13;i++)
                                {
                                    if(remainedCards[i].isFielded)
                                    {
                                        remainedCards[i].isFielded=0;
                                        remainedCards[i].isGarbaged=1;
                                        yourGrave++;
                                    }
                                }
                                yourMelee[11].type=-1;
                                yourRange[11].type=-1;
                                yourSiege[11].type=-1;
                                enemyMelee[11].type=-1;
                                enemyRange[11].type=-1;
                                enemySiege[11].type=-1;
                                UpdateGrave(1);
                                ClearField();
                                /*��һС��*/
                                if(yourWin==2||enemyWin==2||gameStage==3)
                                {
                                	/*��Ϸ����*/
                                	GameOver();
								}
                                else
                                {
									EnemyLogic(cards[34]);
									enemyHandcards++; 
									gameStage++;
								}
                            }
                        }

                        if(isYouGiveUp==FALSE)
                        {
                            isYourTurn=TRUE;
                            isOperated=FALSE;
                        }

                    }
                    break;
				
            }
        break;
    }
}

void JudgeWinner(int* pyourWin, int* penemyWin)//�ж�С��ʤ��
{
	extern int lan;
    if(yourAttack[0]+yourAttack[1]+yourAttack[2] > enemyAttack[0]+enemyAttack[1]+enemyAttack[2] ||
       yourAttack[0]+yourAttack[1]+yourAttack[2] == enemyAttack[0]+enemyAttack[1]+enemyAttack[2] && yourSide==NILFGAARD && enemySide!=NILFGAARD)
    {
        (*pyourWin)++;
    }
    if(yourAttack[0]+yourAttack[1]+yourAttack[2] < enemyAttack[0]+enemyAttack[1]+enemyAttack[2] ||
       yourAttack[0]+yourAttack[1]+yourAttack[2] == enemyAttack[0]+enemyAttack[1]+enemyAttack[2] && enemySide==NILFGAARD && yourSide!=NILFGAARD)
    {
        (*penemyWin)++;
    }
    isEnemyGiveUp=FALSE;
    isYouGiveUp=FALSE;
    yourField_1=1;
    yourField_2=1;
    yourField_3=1;
    enemyField_1=1;
    enemyField_2=1;
    enemyField_3=1;
    SetPenColor("Light_Brown");
	MovePen(0.15,6);
	if(lan==0){
		SetPointSize(20);
		DrawTextString("Enemy Give Up");
	}else{
		SetPointSize(20);
		DrawTextString("���������غ�");
	}
}

void UpdateGrave(int player)//ˢ��Ĺ����Ϣ,1-������2-�Է�
{
    int i,k=0;
    switch(player)
    {
        case 1:
            StartFilledRegion(1);
            SetPenColor("Light_Brown");
            DrawBox(8.1,0.4,0.6,0.9);
            EndFilledRegion();
            SetPointSize(40);
            SetPenColor("Light Gray");
            MovePen(8.3,0.7);
            itoa(yourGrave,numDisplay,10);
            DrawTextString(numDisplay);

            for(i=0;i<12;i++)
            {
                if(allocatedCards[i].isGarbaged==1)
                {
                    GraveCards[k]=allocatedCards[i];
                    k++;
                }
            }
            for(i=0;i<13;i++)
            {
                if(remainedCards[i].isGarbaged==1)
                {
                    GraveCards[k]=remainedCards[i];
                    k++;
                }
            }
            break;
        case 2:
            StartFilledRegion(1);
            SetPenColor("Light_Brown");
            DrawBox(8.1,gameHeight-1.3,0.6,0.9);
            EndFilledRegion();
            SetPointSize(40);
            SetPenColor("Light Gray");
            MovePen(8.3,gameHeight-1);
            itoa(enemyGrave,numDisplay,10);
            DrawTextString(numDisplay);
            break;
    }
}

void UpdateAttack(int row)//1-�з����ǣ�2-�з�Զ�̣�3-�з���ս��4-������ս��5-����Զ�̣�6-��������
{
    StartFilledRegion(1);
    SetPenColor("Dark_Brown");
    row<4 ? DrawBox(1.58,4.98-0.3*(row-1),0.4,0.28) : DrawBox(1.58,2.38-0.3*(row-4),0.4,0.28);
    EndFilledRegion();
    SetPenColor("Light Gray");
    SetPointSize(30);
    switch(row)
    {
        case 1:
            itoa(enemyAttack[2],numDisplay,10);
            MovePen(1.6,5);
            DrawTextString(numDisplay);
            break;
        case 2:
            itoa(enemyAttack[1],numDisplay,10);
            MovePen(1.6,4.7);
            DrawTextString(numDisplay);
            break;
        case 3:
            itoa(enemyAttack[0],numDisplay,10);
            MovePen(1.6,4.4);
            DrawTextString(numDisplay);
            break;
        case 4:
            itoa(yourAttack[0],numDisplay,10);
            MovePen(1.6,2.4);
            DrawTextString(numDisplay);
            break;
        case 5:
            itoa(yourAttack[1],numDisplay,10);
            MovePen(1.6,2.1);
            DrawTextString(numDisplay);
            break;
        case 6:
            itoa(yourAttack[2],numDisplay,10);
            MovePen(1.6,1.8);
            DrawTextString(numDisplay);
            break;            
    }
}

void CardLogic(card ecard)//�������ڶԷ�����!!!
{
    int i, j;//����ѭ��
    int dead;//�����ƵĿ���
    int hornPlace;//�Ž������λ��,1-��ս,2-Զ��,3-����
    int burnPlace;
    int newCardPos[2];//�»���ƵĲ���λ��
    int emptyPos=0;//�ɲ���λ�õ�����
    int newCardNum[2];//�»������remainedNum��������
    time_t randSeed;
    card temp;//��������λ��
    isSpy=FALSE;
    switch(ecard.type)
    {
        case 1://��ս
            switch(ecard.isSpecial)
            {
                case 1://���
                    isSpy=TRUE;
                    enemyMelee[enemyField_1-1]=ecard;
                    DrawHandCards(2.3+0.55*enemyField_1,gameHeight-2.84,ecard.ID);
                    enemyField_1++;
                    allocatedCards[cardState-1].isFielded=1;
                    for(i=0;i<12;i++)
                    {
                        if(allocatedCards[i].isFielded==1 || allocatedCards[i].isGarbaged==1)
                        {
                            newCardPos[emptyPos]=i;
                            emptyPos++;
                            if(emptyPos==2)
                            {
                                break;
                            }
                        }
                    }
                    srand((unsigned) time(&randSeed));
                    while(1)//ѡ��δ�������Ϊֹ
                    {
                        if(emptyPos==1)
                        {
                            newCardNum[0]=rand()%12;
                            if(remainedCards[newCardNum[0]].isFielded==0 &&
                               remainedCards[newCardNum[0]].isGarbaged==0)
                                break;
                        }
                        if(emptyPos==2)
                        {
                            newCardNum[0]=rand()%12;
                            newCardNum[1]=rand()%12;
                            if(remainedCards[newCardNum[0]].isFielded==0  &&
                               remainedCards[newCardNum[0]].isGarbaged==0 &&
                               remainedCards[newCardNum[1]].isFielded==0  &&
                               remainedCards[newCardNum[1]].isGarbaged==0 &&
                               newCardNum[0]!=newCardNum[1])
                                break;
                        }
                    }
                    temp=allocatedCards[newCardPos[0]];
                    allocatedCards[newCardPos[0]]=remainedCards[newCardNum[0]];
                    remainedCards[newCardNum[0]]=temp;//����������remainedCards��allocatedCards��λ��
                    DrawHandCards(1.3+0.55*newCardPos[0],0.4,allocatedCards[newCardPos[0]].ID);
                    if(emptyPos==2)
                    {
                        temp=allocatedCards[newCardPos[1]];
                        allocatedCards[newCardPos[1]]=remainedCards[newCardNum[1]];
                        remainedCards[newCardNum[1]]=temp;//����������remainedCards��allocatedCards��λ��
                        DrawHandCards(1.3+0.55*newCardPos[1],0.4,allocatedCards[newCardPos[1]].ID);                        
                    }
                    break;
                case 3://ͬ��
                    yourMelee[yourField_1-1]=ecard;
                    DrawHandCards(2.3+0.55*yourField_1,gameHeight-3.8,ecard.ID);
                    yourField_1++;
                    break;
                default://��սû�����ƣ��ټ�������
                    yourMelee[yourField_1-1]=ecard;
                    DrawHandCards(2.3+0.55*yourField_1,gameHeight-3.8,ecard.ID);
                    yourField_1++;
                    break;
            }
            /*for(i=0;i<yourField_1-1;i++)
            {
                yourAttack[0]=yourAttack[0]+yourMelee[i].attack;
            }
            for(i=0;i<enemyField_1-1;i++)//��Ϊ�м������Ҫˢ��һ�¶Է��ĵ���
            {
                enemyAttack[0]=enemyAttack[0]+enemyMelee[i].attack;
            }*/
            break;
        case 2://Զ��
            switch(ecard.isSpecial)
            {
                case 2://����
                    yourRange[yourField_2-1]=ecard;
                    DrawHandCards(2.3+0.55*yourField_2,gameHeight-4.72,ecard.ID);
                    yourField_2++;
                    dead=rand()%3;
                    switch(dead)
                    {
                        case 0://��ս
                            yourMelee[yourField_1-1]=cards[6];
                            DrawHandCards(2.3+0.55*yourField_1,gameHeight-3.8,7);
                            yourField_1++;
                            break;
                        case 1://Զ��
                            yourRange[yourField_2-1]=cards[18];
                            DrawHandCards(2.3+0.55*yourField_2,gameHeight-4.72,19);
                            yourField_2++;
                            break;
                        case 2://����
                            yourSiege[yourField_3-1]=cards[20];
                            DrawHandCards(2.3+0.55*yourField_3,gameHeight-5.64,21);
                            yourField_3++;
                            break;
                    }
                    break;
                case 4://�ټ�
                    yourRange[yourField_2-1]=ecard;
                    DrawHandCards(2.3+0.55*yourField_2,gameHeight-4.72,ecard.ID);
                    yourField_2++;
                    if(ecard.ID==14 || ecard.ID==15)//partition 1
                    {
                        for(i=0;i<12;i++)
                        {
                            if((allocatedCards[i].ID==14 || allocatedCards[i].ID==15) &&
                                allocatedCards[i].ID!=ecard.ID)
                            {
                                StartFilledRegion(1);
                                SetPenColor("Light_Brown");
                                DrawBox(1.3+0.55*i, 0.4, 0.55, 0.9);
                                EndFilledRegion();

                                yourRange[yourField_2-1]=allocatedCards[i];
                                DrawHandCards(2.3+0.55*yourField_2,gameHeight-4.72,14);
                                yourField_2++;
                                allocatedCards[i].isFielded=1;
                            }
                        }
                        for(i=0;i<13;i++)
                        {
                            if((remainedCards[i].ID==14 || remainedCards[i].ID==15) &&
                                remainedCards[i].ID!=ecard.ID)
                            {
                                yourRange[yourField_2-1]=remainedCards[i];
                                DrawHandCards(2.3+0.55*yourField_2,gameHeight-4.72,14);
                                yourField_2++;
                                remainedCards[i].isFielded=1;
                            }
                        }
                    }
                    if(ecard.ID==16 || ecard.ID==17 || ecard.ID==18)//partition 2
                    {
                        for(i=0;i<12;i++)
                        {
                            if((allocatedCards[i].ID==16 || allocatedCards[i].ID==17 || allocatedCards[i].ID==18) &&
                                allocatedCards[i].ID!=ecard.ID)
                            {
                                StartFilledRegion(1);
                                SetPenColor("Light_Brown");
                                DrawBox(1.3+0.55*i, 0.4, 0.55, 0.9);
                                EndFilledRegion();

                                yourRange[yourField_2-1]=allocatedCards[i];
                                DrawHandCards(2.3+0.55*yourField_2,gameHeight-4.72,16);
                                yourField_2++;
                                allocatedCards[i].isFielded=1;
                            }
                        }
                        for(i=0;i<13;i++)
                        {
                            if((remainedCards[i].ID==16 || remainedCards[i].ID==17 || remainedCards[i].ID==18) &&
                                remainedCards[i].ID!=ecard.ID)
                            {
                                yourRange[yourField_2-1]=remainedCards[i];
                                DrawHandCards(2.3+0.55*yourField_2,gameHeight-4.72,16);
                                yourField_2++;
                                remainedCards[i].isFielded=1;
                            }
                        }
                    }
                    break;
                default://Զ��ֻ���ټ�
                    yourRange[yourField_2-1]=ecard;
                    DrawHandCards(2.3+0.55*yourField_2,gameHeight-4.72,ecard.ID);
                    yourField_2++;
                    break;                
            }
            /*for(i=0;i<yourField_2-1;i++)
            {
                yourAttack[1]=yourAttack[1]+yourRange[i].attack;
            }*/
            break;
        case 3://����
            switch(ecard.isSpecial)
            {
                case 2://����
                    yourSiege[yourField_3-1]=ecard;
                    DrawHandCards(2.3+0.55*yourField_3,gameHeight-5.64,ecard.ID);
                    yourField_3++;
                    dead=rand()%3;
                    switch(dead)
                    {
                        case 0://��ս
                            yourMelee[yourField_1-1]=cards[6];
                            DrawHandCards(2.3+0.55*yourField_1,gameHeight-3.8,7);
                            yourField_1++;
                            break;
                        case 1://Զ��
                            yourRange[yourField_2-1]=cards[18];
                            DrawHandCards(2.3+0.55*yourField_2,gameHeight-4.72,19);
                            yourField_2++;
                            break;
                        case 2://����
                            yourSiege[yourField_3-1]=cards[20];
                            DrawHandCards(2.3+0.55*yourField_3,gameHeight-5.64,21);
                            yourField_3++;
                            break;
                    }
                    break;
                case 3://ͬ��
                    yourSiege[yourField_3-1]=ecard;
                    DrawHandCards(2.3+0.55*yourField_3,gameHeight-5.64,ecard.ID);
                    yourField_3++;
                    break;
                case 5://����
                    yourSiege[yourField_3-1]=ecard;
                    DrawHandCards(2.3+0.55*yourField_3,gameHeight-5.64,ecard.ID);
                    yourField_3++;
                    break;
                default:
                    yourSiege[yourField_3-1]=ecard;
                    DrawHandCards(2.3+0.55*yourField_3,gameHeight-5.64,ecard.ID);
                    yourField_3++;
                    break;        
            }
            /*for(i=0;i<yourField_3-1;i++)
            {
                yourAttack[2]=yourAttack[2]+yourSiege[i].attack;
            }*/
            break;
        case 4://����
            for(i=0;i<weatherField-1;i++)//���Ŀǰ��Ч����
            {
                if(weatherCards[i].ID==28 || weatherCards[i].ID==29)
                    isFrost=TRUE;
                if(weatherCards[i].ID==30 || weatherCards[i].ID==31)
                    isFog=TRUE;
                if(weatherCards[i].ID==32 || weatherCards[i].ID==33)
                    isRain=TRUE;
            }
            switch(ecard.ID)
            {
                case 28: case 29:
                    if(isFrost==FALSE)
                    {
                        weatherCards[weatherField-1]=ecard;
                        DrawFrost(0.2+0.4*weatherField,3.5,0.3);
                        weatherField++;
                        isFrost=TRUE;
                        mciSendString(TEXT("play frost.wav"),NULL,0,NULL);
                    }
                    break;
                case 30: case 31:
                    if(isFog==FALSE)
                    {
                        weatherCards[weatherField-1]=ecard;
                        DrawFog(0.2+0.4*weatherField,3.5,0.3);
                        weatherField++;
                        isFog=TRUE;
						mciSendString(TEXT("play fog.wav"),NULL,0,NULL);                       
                    }
                    break;
                case 32: case 33:
                    if(isRain==FALSE)
                    {
                        weatherCards[weatherField-1]=ecard;
                        DrawRain(0.2+0.4*weatherField,3.53,0.3);
                        weatherField++;
                        isRain=TRUE;
                        mciSendString(TEXT("play rain.wav"),NULL,0,NULL);
                    }
                    break;
                case 34: case 35:
                    /*���������*/
                    StartFilledRegion(1);
                    SetPenColor("White");
                    DrawFrame(0.2,gameHeight/2-0.4,1.6,0.8);
                    EndFilledRegion();
                    SetPenColor("Light_Brown++");
                    DrawFrame(0.2,gameHeight/2-0.4,1.6,0.8);
                    isFrost=FALSE;
                    isFog=FALSE;
                    isRain=FALSE;
                    weatherField=1;
                    weatherCards[0].ID=0;//����ID,��ʹ���Ʋ��ٱ��ж�Ϊ����
                    weatherCards[1].ID=0;
                    weatherCards[2].ID=0;
                    mciSendString(TEXT("play clear.wav"),NULL,0,NULL);
                    break;
            }
            break;
        case 5://����
            switch(ecard.ID)
            {
                case 36: case 37://�Ž�
                    srand((unsigned) time(&randSeed));
                    while(1)
                    {
                        hornPlace=rand()%3+1;
                        if(hornPlace==1 && yourMelee[11].type!=5 ||
                           hornPlace==2 && yourRange[11].type!=5 ||
                           hornPlace==3 && yourSiege[11].type!=5 ||
                           yourMelee[11].type==5 && yourRange[11].type==5 && yourSiege[11].type==5)
                        {
                            break;
                        }
                    }
                    DrawHandCards(2.3,gameHeight-2.88-0.92*hornPlace,36);
                    switch(hornPlace)
                    {
                        case 1:
                            yourMelee[11]=ecard;
                            break;
                        case 2:
                            yourRange[11]=ecard;
                            break;
                        case 3:
                            yourSiege[11]=ecard;
                            break;
                    }
                    mciSendString(TEXT("play horn.wav"),NULL,0,NULL);
                    break;
                case 38: case 39: case 40://ȼ��
                    srand((unsigned) time(&randSeed));
                    burnPlace=rand()%3+1;
                    switch(burnPlace)
                    {
                        case 1:
                            enemyMelee[0].attack=enemyMelee[0].attack-8;
                            break;
                        case 2:
                            enemyRange[0].attack=enemyRange[0].attack-8;
                            break;
                        case 3:
                            enemySiege[0].attack=enemySiege[0].attack-8;
                            break;
                    }
                    mciSendString(TEXT("play burn.wav"),NULL,0,NULL);
                    break;
            }
    }
/*����Ӱ�츲��*/
    for(i=0;i<yourField_1-1;i++)
        yourMelee[i].isWeatherControlled=isFrost;
    for(i=0;i<enemyField_1-1;i++)
        enemyMelee[i].isWeatherControlled=isFrost;
    for(i=0;i<yourField_2-1;i++)
        yourRange[i].isWeatherControlled=isFog;
    for(i=0;i<enemyField_2-1;i++)
        enemyRange[i].isWeatherControlled=isFog;
    for(i=0;i<yourField_3-1;i++)
        yourSiege[i].isWeatherControlled=isRain;
    for(i=0;i<enemyField_3-1;i++)
        enemySiege[i].isWeatherControlled=isRain;
/*���ս������*/
    yourAttack[0]=AttackCalculate(yourMelee, yourField_1-1);
    yourAttack[1]=AttackCalculate(yourRange, yourField_2-1);
    yourAttack[2]=AttackCalculate(yourSiege, yourField_3-1);
    enemyAttack[0]=AttackCalculate(enemyMelee, enemyField_1-1);
    enemyAttack[1]=AttackCalculate(enemyRange, enemyField_2-1);
    enemyAttack[2]=AttackCalculate(enemySiege, enemyField_3-1);
}

int AttackCalculate(card* ecard, int num)
{
    int i,j;
    int bondNum1=0,bondNum2=0,bondNum3=0,bondNum4=0,bondNum5=0;
    int finalAttack=0;
    int isBoost=0;
    int isHorn=0;
    card tcard[12];
    /*����*/
    for(i=0;i<num;i++)
    {
        tcard[i]=ecard[i];
    }
    tcard[11]=ecard[11];
    /*ͳ��ͬ��*/
    for(i=0;i<num;i++)
    {
        if(tcard[i].isSpecial==3)
        {
        	if(tcard[i].ID>=9&&tcard[i].ID<=11){
        		bondNum1++;//���� 
			}else if(tcard[i].ID>=23&&tcard[i].ID<=24){
				bondNum2++;//Ͷʯ��
			}else if(tcard[i].ID>=54&&tcard[i].ID<=57){
				bondNum3++;//������ 
			}else if(tcard[i].ID>=61&&tcard[i].ID<=62){
				bondNum4++;//��ʹ 
			}else if(tcard[i].ID>=65&&tcard[i].ID<=67){
				bondNum5++;//����������� 
			}	 
        }
    }
    /*�ж�����*/
    for(i=0;i<num;i++)
    {
        if(tcard[i].isSpecial==5)
        {
            isBoost=1;
        }
    }
    /*�жϺŽ�*/
    if(tcard[11].type==5)
    {
        isHorn=1;
    }
    /*���ս���˳����������*/
    for(i=0;i<num;i++)
    {
        /*��һ������������*/
        if(tcard[i].isWeatherControlled==1&&tcard[i].isHero==0)
        {
            tcard[i].attack=1;
        }
        /*�ڶ���������ͬ��*/
        if(tcard[i].isSpecial==3)
        {
        	if(tcard[i].ID>=9&&tcard[i].ID<=11){
        		tcard[i].attack=bondNum1*tcard[i].attack;//���� 
			}else if(tcard[i].ID>=23&&tcard[i].ID<=24){
				tcard[i].attack=bondNum2*tcard[i].attack;//Ͷʯ��
			}else if(tcard[i].ID>=54&&tcard[i].ID<=57){
				tcard[i].attack=bondNum3*tcard[i].attack;//������ 
			}else if(tcard[i].ID>=61&&tcard[i].ID<=62){
				tcard[i].attack=bondNum4*tcard[i].attack;//��ʹ 
			}else if(tcard[i].ID>=65&&tcard[i].ID<=67){
				tcard[i].attack=bondNum5*tcard[i].attack;//����������� 
			}	 
        }
        /*����������������*/
        if(isBoost==1)
        {
            tcard[i].attack=tcard[i].attack+1;
        }
        /*���Ĳ�������Ž�*/
        if(isHorn==1)
        {
            tcard[i].attack=2*tcard[i].attack;
        }
    }
    /*�����յ����������*/
    for(i=0;i<num;i++)
    {
        finalAttack=finalAttack+tcard[i].attack;
    }
    return finalAttack;
}

void EnemyLogic(card ecard){
	int i,j;//����ѭ��
    int dead;//�����ƵĿ��ƺ�
    int hornPlace;//�Ž������λ��,1-��ս,2-Զ��,3-����
    int burnPlace;
    time_t randSeed;
    switch(ecard.type)
    {
        case 1://��ս
            switch(ecard.isSpecial)
            {
                case 1://���
                    yourMelee[yourField_1-1]=ecard;
                    DrawHandCards(2.3+0.55*yourField_1,gameHeight-3.8,ecard.ID);
                    yourField_1++;
                    enemyHandcards++;
                    break;
                case 3://ͬ��
                    enemyMelee[enemyField_1-1]=ecard;
                    DrawHandCards(2.3+0.55*enemyField_1,gameHeight-2.84,ecard.ID);
                    enemyField_1++;
                    enemyHandcards--;
                    break;
                case 4://�ټ�
                    if(ecard.ID>=41&&ecard.ID<=47)//partition 1
                    {
						for(i=41;i<47;i++){
							enemyMelee[enemyField_1-1]=cards[i-1];
							DrawHandCards(2.3+0.55*enemyField_1,gameHeight-2.84,41);
                        	enemyField_1++;
						}
						DrawHandCards(2.3+0.55*enemyField_1,gameHeight-2.84,47);
                        enemyField_1++;
                        if(enemyHandcards>=3){
                        	enemyHandcards-=3;
						}else{
							enemyHandcards=0;
						}
                    }
                    if(ecard.ID==48||ecard.ID==49||ecard.ID==50)//partition 2
                    {
                        for(i=48;i<=50;i++){
							enemyMelee[enemyField_1-1]=cards[i-1];
							DrawHandCards(2.3+0.55*enemyField_1,gameHeight-2.84,48);
                        	enemyField_1++;
						}
                        enemyHandcards--;
                    }
                    break;
                default://��սû������,����
                    enemyMelee[enemyField_1-1]=ecard;
                    DrawHandCards(2.3+0.55*enemyField_1,gameHeight-2.84,ecard.ID);
                    enemyField_1++;
                    enemyHandcards--;
                    break;
            }
            break;
        case 2://Զ��
            switch(ecard.isSpecial)
            {
            /*	case 2://����
            		enemyRange[enemyField_2-1]=ecard;
                    DrawHandCards(2.3+0.55*enemyField_2,gameHeight-1.92,ecard.ID);
                    enemyField_2++;
                    if(enemyGrave>0)
                    {
                        dead=rand()%(enemyGrave-1);
                        CardLogic(eGraveCards[dead]);
                    }
                    enemyHandcards--;
                    break;		*/
                case 4://�ټ�
                    if(ecard.ID==14 || ecard.ID==15)//partition 1
                    {
                        for(i=14;i<=15;i++)
                        {
                            enemyRange[enemyField_2-1]=cards[i-1];
                            DrawHandCards(2.3+0.55*enemyField_2,gameHeight-1.92,14);
                            enemyField_2++;
                        }
                        enemyHandcards--;
                
                    }
                    if(ecard.ID==16 || ecard.ID==17 || ecard.ID==18)//partition 2
                    {
                        for(i=16;i<=18;i++)
                        {
                            enemyRange[enemyField_2-1]=cards[i-1];
                            DrawHandCards(2.3+0.55*enemyField_2,gameHeight-1.92,16);
                            enemyField_2++;
                        }
                        enemyHandcards-=2;
                    }
                    break;
                case 5://ʿ��
                	enemyRange[enemyField_2-1]=ecard;
                    DrawHandCards(2.3+0.55*enemyField_2,gameHeight-1.92,ecard.ID);
                    enemyField_2++;
                    enemyHandcards--;
                    break;
                default://Զ���޼����ͬ�� 
                    enemyRange[enemyField_2-1]=ecard;
                    DrawHandCards(2.3+0.55*enemyField_2,gameHeight-1.92,ecard.ID);
                    enemyField_2++;
                    enemyHandcards--;
                    break;                
            }
            break;
        case 3://����
            switch(ecard.isSpecial)
            {
				/*	case 2://����
                    enemySiege[enemyField_3-1]=ecard;
                    DrawHandCards(2.3+0.55*enemyField_3,gameHeight-1,ecard.ID);
                    enemyField_3++;
                    if(enemyGrave>0)
                    {
                        dead=rand()%(enemyGrave-1);
                        CardLogic(eGraveCards[dead]);
                    }
                    enemyHandcards--;
                    break;		*/
                case 3://ͬ��
                    enemySiege[enemyField_3-1]=ecard;
                    DrawHandCards(2.3+0.55*enemyField_3,gameHeight-1,ecard.ID);
                    enemyField_3++;
                    enemyHandcards--;
                    break;
                case 4://�ټ�
                    if(ecard.ID==51||ecard.ID==52||ecard.ID==53)
                    {
                        for(i=51;i<=53;i++)
                        {
                            enemySiege[enemyField_3-1]=cards[i-1];
                            DrawHandCards(2.3+0.55*enemyField_3,gameHeight-1,51);
                            enemyField_3++;
                        }
                        if(enemyHandcards>=2){
                        	enemyHandcards-=2;
						}else{
							enemyHandcards=0;
						}
                    }
                    break;
                case 5://����
                    enemySiege[enemyField_3-1]=ecard;
                    DrawHandCards(2.3+0.55*enemyField_3,gameHeight-1,ecard.ID);
                    enemyField_3++;
                    enemyHandcards--;
                    break;
                default:
                    enemySiege[enemyField_3-1]=ecard;
                    DrawHandCards(2.3+0.55*enemyField_3,gameHeight-1,ecard.ID);
                    enemyField_3++;
                    enemyHandcards--;
                    break;        
            }
            break;
        case 4://����
        	enemyHandcards--;
            for(i=0;i<weatherField-1;i++)//���Ŀǰ��Ч����
            {
                if(weatherCards[i].ID==28 || weatherCards[i].ID==29)
                    isFrost=TRUE;
                if(weatherCards[i].ID==30 || weatherCards[i].ID==31)
                    isFog=TRUE;
                if(weatherCards[i].ID==32 || weatherCards[i].ID==33)
                    isRain=TRUE;
            }
            switch(ecard.ID)
            {
                case 28: case 29:
                    if(isFrost==FALSE)
                    {
                        weatherCards[weatherField-1]=ecard;
                        DrawFrost(0.2+0.4*weatherField,3.5,0.3);
                        weatherField++;
                        isFrost=TRUE;
                    }
                    mciSendString(TEXT("play frost.wav"),NULL,0,NULL);
                    break;
                case 30: case 31:
                    if(isFog==FALSE)
                    {
                        weatherCards[weatherField-1]=ecard;
                        DrawFog(0.2+0.4*weatherField,3.5,0.3);
                        weatherField++;
                        isFog=TRUE;
						mciSendString(TEXT("play fog.wav"),NULL,0,NULL);                       
                    }
                    break;
                case 32: case 33:
                    if(isRain==FALSE)
                    {
                        weatherCards[weatherField-1]=ecard;
                        DrawRain(0.2+0.4*weatherField,3.53,0.3);
                        weatherField++;
                        isRain=TRUE;
                        mciSendString(TEXT("play rain.wav"),NULL,0,NULL);
                    }
                    break;
                case 34: case 35:
                    /*���������*/
                    StartFilledRegion(1);
                    SetPenColor("White");
                    DrawFrame(0.2,gameHeight/2-0.4,1.6,0.8);
                    EndFilledRegion();
                    SetPenColor("Light_Brown++");
                    DrawFrame(0.2,gameHeight/2-0.4,1.6,0.8);
                    isFrost=FALSE;
                    isFog=FALSE;
                    isRain=FALSE;
                    weatherField=1;
                    weatherCards[0].ID=0;//����ID,��ʹ���Ʋ��ٱ��ж�Ϊ����
                    weatherCards[1].ID=0;
                    weatherCards[2].ID=0;
                    mciSendString(TEXT("play clear.wav"),NULL,0,NULL);
                    break;
            }
            break;
        case 5://����
        	enemyHandcards--;
            switch(ecard.ID)
            {
                case 36: case 37://�Ž�
                    srand((unsigned) time(&randSeed));
                    while(1)
                    {
                        hornPlace=rand()%3+1;
                        if(hornPlace==1 && enemyMelee[11].type!=5 ||
                           hornPlace==2 && enemyRange[11].type!=5 ||
                           hornPlace==3 && enemySiege[11].type!=5 ||
                           enemyMelee[11].type==5 && enemyRange[11].type==5 && enemySiege[11].type==5)
                        {
                            break;
                        }
                    }
                    DrawHandCards(2.3,gameHeight-3.76+0.92*hornPlace,36);
                    switch(hornPlace)
                    {
                        case 1:
                            enemyMelee[11]=ecard;
                            break;
                        case 2:
                            enemyRange[11]=ecard;
                            break;
                        case 3:
                            enemySiege[11]=ecard;
                            break;
                    }
                    break;
                    mciSendString(TEXT("play horn.wav"),NULL,0,NULL);
                case 38: case 39: case 40://ȼ��
                	srand((unsigned) time(&randSeed));
                    burnPlace=rand()%3+1;
                    switch(burnPlace)
                    {
                        case 1:
                            yourMelee[0].attack=yourMelee[0].attack-8;
                            break;
                        case 2:
                            yourRange[0].attack=yourRange[0].attack-8;
                            break;
                        case 3:
                            yourSiege[0].attack=yourSiege[0].attack-8;
                            break;
                    }
                    mciSendString(TEXT("play burn.wav"),NULL,0,NULL);
                    break;
            }
    }
/*����Ӱ�츲��*/
    for(i=0;i<yourField_1-1;i++)
        yourMelee[i].isWeatherControlled=isFrost;
    for(i=0;i<enemyField_1-1;i++)
        enemyMelee[i].isWeatherControlled=isFrost;
    for(i=0;i<yourField_2-1;i++)
        yourRange[i].isWeatherControlled=isFog;
    for(i=0;i<enemyField_2-1;i++)
        enemyRange[i].isWeatherControlled=isFog;
    for(i=0;i<yourField_3-1;i++)
        yourSiege[i].isWeatherControlled=isRain;
    for(i=0;i<enemyField_3-1;i++)
        enemySiege[i].isWeatherControlled=isRain;
/*���ս������*/
    yourAttack[0]=AttackCalculate(yourMelee, yourField_1-1);
    yourAttack[1]=AttackCalculate(yourRange, yourField_2-1);
    yourAttack[2]=AttackCalculate(yourSiege, yourField_3-1);
    enemyAttack[0]=AttackCalculate(enemyMelee, enemyField_1-1);
    enemyAttack[1]=AttackCalculate(enemyRange, enemyField_2-1);
    enemyAttack[2]=AttackCalculate(enemySiege, enemyField_3-1);
}

void EnemyPlaying(){
	extern int lan; 
	if(isEnemyGiveUp==FALSE){
		if(enemyHandcards<=0){
			isEnemyGiveUp=TRUE;//û�ƾ�����
		}else if(gameStage==3&&enemyHandcards>0){
			isEnemyGiveUp=FALSE;
		}else if((gameStage==1||gameStage==2&&enemyWin==1)&&fabs(yourAttacks-enemyAttacks)>=25){
			isEnemyGiveUp=TRUE;//�����㣬attack��೬��25���������
		
		}else if(isYouGiveUp==TRUE&&(enemyAttacks>yourAttacks&&(enemySide!=2||enemySide==2&&yourSide==2)||enemyAttacks>=yourAttacks&&enemySide==2&&yourSide!=2)){
			isEnemyGiveUp=TRUE;//������ˣ����ֵ������������������ 
		}else if(gameStage==1&&enemyHandcards<=6){
			isEnemyGiveUp=TRUE;
		}else{
			isEnemyGiveUp=FALSE;
		}
	}
	if(isEnemyGiveUp==FALSE){
		int hero1=0,hero2=0,hero3=0;//����ͳ�����ÿһ�е�Ӣ��������
		int pureattack1=yourAttack[0],pureattack2=yourAttack[1],pureattack3=yourAttack[2];//����ͳ��������в���Ӣ�۵��ܵ��� 
		int altnum;
		for(altnum=0;altnum<12;altnum++){
			if(yourMelee[altnum].isHero==1){
				hero1++;
				pureattack1=pureattack1-yourMelee[altnum].attack;
			}
			if(yourRange[altnum].isHero==1){
				hero2++;
				pureattack2=pureattack2-yourRange[altnum].attack;
			}
			if(yourSiege[altnum].isHero==1){
				hero3++;
				pureattack3=pureattack3-yourSiege[altnum].attack;
			}
		}
		//��ͬ���Ʒ��
		extern bool newplay;
		static int commando,catapult,spynum,isBurnt,isHorned,isCleared,poor,BlackArcher,NilSpy,
					Emissary,Brigade,Rider,HaveKar,Dwarven;
		static bool isFogged,isFrosted,isRained,isDeth,isFire,isHFire,isTech,isDun,isHealer,
					isMilva,isSchirru,isVampire,isCrone,isArachas,isRipper;
		if(newplay==TRUE){
			newplay=FALSE;
			commando=0;
			catapult=0;
			spynum=0;
			isBurnt=0;
			isHorned=0;
			isCleared=0;
			poor=0;
			BlackArcher=0;
			Emissary=0;
			Brigade=0;
			Rider=0;
			NilSpy=0;
			HaveKar=0;
			Dwarven=0;
			isFogged=FALSE;
			isFrosted=FALSE;
			isRained=FALSE;
			isDeth=FALSE;
			isFire=FALSE;
			isHFire=FALSE;
			isTech==FALSE;
			isDun=FALSE;
			isHealer=FALSE;
			isMilva=FALSE;
			isSchirru=FALSE;
			isVampire=FALSE;
			isCrone=FALSE;
			isArachas=FALSE;
			isRipper=FALSE;
		}
		switch(enemySide){
			case NORTHERN_REALMS://���������д���ͬ��֮�飬�Լ������͵ļ����
					if(rand()%99<40&&yourRecentcard.type==4&&(isCleared==0||isCleared==1&&gameStage!=1)){
						EnemyLogic(cards[34]);
						isCleared++;
					}else if(isDeth==FALSE&&rand()%100<=49){
						EnemyLogic(cards[18]);
						isDeth=TRUE;
					}else if(gameStage==2&&isDun==FALSE){
						isDun=TRUE;
						EnemyLogic(cards[24]);
					}else if(rand()%3==0&&spynum==0||rand()%5==0&&spynum==1){
						EnemyLogic(cards[11]);
						spynum++;
					}else if(rand()%3==3&&spynum==0||rand()%5==0&&spynum==1){
						EnemyLogic(cards[12]);
						spynum++;
					}else if(commando==0&&rand()%2==0&&(catapult==0||catapult==2)){
						EnemyLogic(cards[8]);
						commando++;
					}else if(commando==1){
						EnemyLogic(cards[9]);
						commando++;
					}else if(commando==2){
						EnemyLogic(cards[10]);
						commando++;
					}else if(catapult==0){
						EnemyLogic(cards[22]);
						catapult++;
					}else if(catapult==1){
						EnemyLogic(cards[23]);
						catapult++;
					}else if(((pureattack2-yourField_2+1+hero2)>(enemyAttack[1]-enemyField_2+1))&&isFogged==FALSE){
						EnemyLogic(cards[29]);
						isFogged=TRUE;
					}else if((((pureattack1-yourField_1+1+hero1)>(enemyAttack[0]-enemyField_1+1))
							&&((pureattack3-yourField_3+1+hero3)>(enemyAttack[2]-enemyField_3+1)))
							&&isFrosted==FALSE&&isRained==FALSE&&rand()%2==0){
						if(rand()%2==0){
							EnemyLogic(cards[27]);
							isFrosted=TRUE;
						}else{
							EnemyLogic(cards[31]);
							isRained=TRUE;
						}
					}else if(isHorned!=1){
						EnemyLogic(cards[35]);
						isHorned++;
					}else if(enemyField_2<=7&&poor==0){
						EnemyLogic(cards[74]);
						poor++;
					}else if(enemyField_2<=7&&poor==1){
						EnemyLogic(cards[75]);
						poor++;
					}else if(enemyField_2<=7&&poor==2){
						EnemyLogic(cards[76]);
						poor++;
					}else if(isHorned!=2){
						EnemyLogic(cards[35]);
						isHorned++;
					}else if(enemyField_1<=7&&poor==3){
						EnemyLogic(cards[71]);
						poor++;
					}else if(enemyField_1<=7&&poor==4){
						EnemyLogic(cards[72]);
						poor++;
					}else if(enemyField_1<=7&&poor==5){
						EnemyLogic(cards[73]);
						poor++;
					}else if(enemyField_2<=7&&poor==6){
						EnemyLogic(cards[77]);
						poor++;
					}else if(enemyField_2<=7&&poor==7){
						EnemyLogic(cards[78]);
						poor++;
					}else if(enemyField_2<=7&&poor==8){
						EnemyLogic(cards[79]);
						poor++;
					}else if(enemyField_2<=7&&poor==9){
						EnemyLogic(cards[80]);
						poor++;
					}else{
						isEnemyGiveUp=TRUE;
					}
				break;	
			case NILFGAARD://�ḥ�ȵµ۹���ǿ��ĵ����ƣ��ҷֲ��ڶ��ţ��н϶�ҽ���ƣ�������Ƶ����ձ����
					if(gameStage==2&&enemyWin==1&&NilSpy==0){
						NilSpy++;
						EnemyLogic(cards[57]);
					}else if(gameStage==2&&enemyWin==1&&NilSpy==1){
						NilSpy++;
						EnemyLogic(cards[58]);
					}else if(gameStage==2&&enemyWin==1&&NilSpy==2){
						isEnemyGiveUp=TRUE;
					}else if(rand()%99<40&&yourRecentcard.type==4&&(isCleared==0||isCleared==1&&gameStage!=1)){
						EnemyLogic(cards[34]);
						isCleared++;
					}else if((BlackArcher==0)
							&&(Emissary==0||Emissary==2)
							&&(Rider==0||Rider==3)
							&&(Brigade==0||Brigade==4)
							&&rand()%6==0){
						EnemyLogic(cards[62]);
						BlackArcher++;
					}else if(BlackArcher==1){
						EnemyLogic(cards[63]);
						BlackArcher++;
					}else if((BlackArcher==0||BlackArcher==2)
							&&(Emissary==0||Emissary==2)
							&&(Rider==0||Rider==3)
							&&(Brigade==0)
							&&rand()%5==0){
						EnemyLogic(cards[53]);
						Brigade++;
					}else if(Brigade==1&&rand()%2==0){
						EnemyLogic(cards[54]);
						Brigade++;
					}else if(Brigade==2){
						EnemyLogic(cards[55]);
						Brigade++;
					}else if(Brigade==3&&rand()%4==0){
						EnemyLogic(cards[56]);
						Brigade++;
					}else if((BlackArcher==0||BlackArcher==2)
							&&(Emissary==0)
							&&(Rider==0||Rider==3)
							&&(Brigade==0||Brigade==4)
							&&rand()%4==0){
						EnemyLogic(cards[60]);
						Emissary++;
					}else if(Emissary==1){
						EnemyLogic(cards[61]);
						Emissary++;
					}else if((BlackArcher==0||BlackArcher==2)
							&&(Emissary==0||Emissary==2)
							&&(Rider==0)
							&&(Brigade==0||Brigade==4)
							&&rand()%3==0){
						EnemyLogic(cards[64]);
						Rider++;
					}else if(Rider==1){
						EnemyLogic(cards[65]);
						Rider++;
					}else if(Rider==2&&rand()%4==0){
						EnemyLogic(cards[66]);
						Rider++;
					}else if(gameStage!=1&&isFire==FALSE){
						isFire=TRUE;
						EnemyLogic(cards[21]);
					}else if(gameStage!=1&&isHFire==FALSE){
						isHFire=TRUE;
						EnemyLogic(cards[67]);
					}else if((isFire==TRUE||isHFire==TRUE)&&isTech==FALSE){
						isTech==TRUE;
						EnemyLogic(cards[59]);
					}else if(((pureattack1-yourField_1+1+hero1)>(enemyAttack[0]-enemyField_1+1))
						&&isFrosted==FALSE&&rand()%3!=0){
						EnemyLogic(cards[27]);
						isFrosted=TRUE;
					}else if(((pureattack2-yourField_2+1+hero2)>(enemyAttack[1]-enemyField_2+1))
						&&isFogged==FALSE&&rand()%3!=0){
						EnemyLogic(cards[29]);
						isFogged=TRUE;
					}else if(((pureattack3-yourField_3+1+hero3)>(enemyAttack[2]-enemyField_3+1))
						&&isRained==FALSE&&rand()%3!=0){
						EnemyLogic(cards[31]);
						isRained=TRUE;
					}else if(isHorned!=1){
						EnemyLogic(cards[35]);
						isHorned++;
					}else if(enemyField_2<=7&&poor==0){
						EnemyLogic(cards[74]);
						poor++;
					}else if(enemyField_2<=7&&poor==1){
						EnemyLogic(cards[75]);
						poor++;
					}else if(enemyField_2<=7&&poor==2){
						EnemyLogic(cards[76]);
						poor++;
					}else if(isHorned!=2){
						EnemyLogic(cards[35]);
						isHorned++;
					}else if(enemyField_1<=7&&poor==3){
						EnemyLogic(cards[71]);
						poor++;
					}else if(enemyField_1<=7&&poor==4){
						EnemyLogic(cards[72]);
						poor++;
					}else if(enemyField_1<=7&&poor==5){
						EnemyLogic(cards[73]);
						poor++;
					}else if(enemyField_2<=7&&poor==6){
						EnemyLogic(cards[77]);
						poor++;
					}else if(enemyField_2<=7&&poor==7){
						EnemyLogic(cards[78]);
						poor++;
					}else if(enemyField_2<=7&&poor==8){
						EnemyLogic(cards[79]);
						poor++;
					}else if(enemyField_2<=7&&poor==9){
						EnemyLogic(cards[80]);
						poor++;
					}else{
						isEnemyGiveUp=TRUE;
					}
				break;
			case SCOIA://�����д��������ƺ�ҽ���ƣ���ȱ�ٹ��ǵ�λ�������Ƶ����ϵ�
				if(rand()%99<40&&yourRecentcard.type==4&&(isCleared==0||isCleared==1&&gameStage!=1)){
						EnemyLogic(cards[34]);
						isCleared++;
					}else if(rand()%2==0&&HaveKar==0&&Dwarven==0){
						EnemyLogic(cards[13]);
						HaveKar++;
					}else if(rand()%2==0&&Dwarven==0&&HaveKar==0){
						EnemyLogic(cards[15]);
						Dwarven++;
					}else if(gameStage!=1&&isHealer==FALSE){
						isHealer=TRUE;
						EnemyLogic(cards[68]);
					}else if(enemyField_2>=5&&isMilva==FALSE){
						isMilva=TRUE;
						EnemyLogic(cards[69]);
					}else if(gameStage!=1&&isSchirru==FALSE){
						isSchirru=TRUE;
						EnemyLogic(cards[70]);
					}else if(((pureattack1-yourField_1+1+hero1)>(enemyAttack[0]-enemyField_1+1))
						&&isFrosted==FALSE&&rand()%3!=0){
						EnemyLogic(cards[27]);
						isFrosted=TRUE;
					}else if(((pureattack2-yourField_2+1+hero2)>(enemyAttack[1]-enemyField_2+1))
						&&isFogged==FALSE&&rand()%3!=0){
						EnemyLogic(cards[29]);
						isFogged=TRUE;
					}else if(((pureattack3-yourField_3+1+hero3)>(enemyAttack[2]-enemyField_3+1))
						&&isRained==FALSE&&rand()%3!=0){
						EnemyLogic(cards[31]);
						isRained=TRUE;
					}else if(isHorned<2&&gameStage==1){
						EnemyLogic(cards[35]);
						isHorned++;
					}else if(isHorned<4&&gameStage!=1){
						EnemyLogic(cards[35]);
						isHorned++;
					}else if(enemyField_2<=7&&poor==0){
						EnemyLogic(cards[74]);
						poor++;
					}else if(enemyField_2<=7&&poor==1){
						EnemyLogic(cards[75]);
						poor++;
					}else if(enemyField_2<=7&&poor==2){
						EnemyLogic(cards[76]);
						poor++;
					}else if(enemyField_1<=7&&poor==3){
						EnemyLogic(cards[71]);
						poor++;
					}else if(enemyField_1<=7&&poor==4){
						EnemyLogic(cards[72]);
						poor++;
					}else if(enemyField_1<=7&&poor==5){
						EnemyLogic(cards[73]);
						poor++;
					}else if(enemyField_2<=7&&poor==6){
						EnemyLogic(cards[77]);
						poor++;
					}else if(enemyField_2<=7&&poor==7){
						EnemyLogic(cards[78]);
						poor++;
					}else if(enemyField_2<=7&&poor==8){
						EnemyLogic(cards[79]);
						poor++;
					}else if(enemyField_2<=7&&poor==9){
						EnemyLogic(cards[80]);
						poor++;
					}else{
						isEnemyGiveUp=TRUE;
					}
				break;
			case MONSTERS://ӵ�д��������ƣ��ҵ����ܸߣ��������ڽ�ս��λ�У���ȱ�������ҽ�� 
				if(rand()%99<40&&yourRecentcard.type==4&&(isCleared==0||isCleared==1&&gameStage!=1)){
						EnemyLogic(cards[34]);
						isCleared++;
					}else if(rand()%2==0&&isVampire==FALSE&&(isCrone==FALSE||gameStage!=1)&&isArachas==FALSE){
						EnemyLogic(cards[40]);
						isVampire=TRUE;
					}else if(rand()%2==0&&(isVampire==FALSE||gameStage!=1)&&isVampire==FALSE&&isCrone==FALSE&&isArachas==FALSE){
						EnemyLogic(cards[47]);
						isCrone=TRUE;
					}else if(rand()%6==0&&isArachas==FALSE){
						EnemyLogic(cards[50]);
						isArachas=TRUE;
					}else if(gameStage!=1&&isArachas==FALSE&&isRipper==FALSE){
						EnemyLogic(cards[26]);
						isRipper=TRUE;
					}else if(isHorned<2&&gameStage==1){
						EnemyLogic(cards[35]);
						isHorned++;
					}else if(isHorned<3&&gameStage!=1){
						EnemyLogic(cards[35]);
						isHorned++;
					}else if(((pureattack1-yourField_1+1+hero1)>(enemyAttack[0]-enemyField_1+1))
						&&isFrosted==FALSE&&rand()%3!=0){
						EnemyLogic(cards[27]);
						isFrosted=TRUE;
					}else if(((pureattack2-yourField_2+1+hero2)>(enemyAttack[1]-enemyField_2+1))
						&&isFogged==FALSE&&rand()%3!=0){
						EnemyLogic(cards[29]);
						isFogged=TRUE;
					}else if(((pureattack3-yourField_3+1+hero3)>(enemyAttack[2]-enemyField_3+1))
						&&isRained==FALSE&&rand()%3!=0){
						EnemyLogic(cards[31]);
						isRained=TRUE;
					}else if(enemyField_2<=7&&poor==0){
						EnemyLogic(cards[74]);
						poor++;
					}else if(enemyField_2<=7&&poor==1){
						EnemyLogic(cards[75]);
						poor++;
					}else if(enemyField_2<=7&&poor==2){
						EnemyLogic(cards[76]);
						poor++;
					}else if(enemyField_1<=7&&poor==3){
						EnemyLogic(cards[71]);
						poor++;
					}else if(enemyField_1<=7&&poor==4){
						EnemyLogic(cards[72]);
						poor++;
					}else if(enemyField_1<=7&&poor==5){
						EnemyLogic(cards[73]);
						poor++;
					}else if(enemyField_2<=7&&poor==6){
						EnemyLogic(cards[77]);
						poor++;
					}else if(enemyField_2<=7&&poor==7){
						EnemyLogic(cards[78]);
						poor++;
					}else if(enemyField_2<=7&&poor==8){
						EnemyLogic(cards[79]);
						poor++;
					}else if(enemyField_2<=7&&poor==9){
						EnemyLogic(cards[80]);
						poor++;
					}else{
						isEnemyGiveUp=TRUE;
					}
				break;
		}
			SetPenColor("Dark_Brown");
			StartFilledRegion(1);
			DrawBox(0.55,4.75,0.5,0.4);
			EndFilledRegion();
			SetPenColor("White");
			SetPointSize(30);
			sprintf(enemyhandcards,"%d",enemyHandcards);
			MovePen(0.6,4.8);
			if(enemyHandcards>0){
				DrawTextString(enemyhandcards);
			}else{
				DrawTextString("0");
			}
			
			
		}
		if(isEnemyGiveUp==TRUE){
			SetPenColor("Red");
			MovePen(0.15,6);
			if(lan==0){
				SetPointSize(20);
				DrawTextString("Enemy Give Up");
			}else{
				SetPointSize(20);
				DrawTextString("���������غ�");
			}
		}
}
