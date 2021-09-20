#include "Gwent.h"

card allocatedCards[12];//己方手牌
card remainedCards[13];//己方牌组中未被分到手牌中的所有牌
card yourMelee[12], yourRange[12], yourSiege[12];//己方战场上的卡牌
card enemyMelee[12], enemyRange[12], enemySiege[12];//对方战场上的卡牌
card weatherCards[3];
card GraveCards[25];//己方墓地
card eGraveCards[25];//敌方墓地 

char numDisplay[4];

bool isYourTurn;//是否为己方回合
bool isYouGiveUp=FALSE;//己方是否放弃跟牌
bool isEnemyGiveUp=FALSE;//敌方是否放弃跟牌
bool isGameFinished=FALSE;//整局游戏是否结束
bool isOperated=FALSE;//己方回合是否存在有效的出牌操作
bool isSpy;

int randomNum[12],remainedNum[13];//随机编号，用于发牌
int cardState=1;//用于移动三角光标进行出牌
int yourField_1=1, yourField_2=1, yourField_3=1;//用于调节卡牌在战场上的放置位置（己方）
int enemyField_1=1, enemyField_2=1, enemyField_3=1;//用于调节卡牌在战场上的放置位置（对方）
int weatherField=1;//用于调节天气图标位置
int yourGrave=0, enemyGrave=0;//己方和敌方墓地的卡牌数
int gameStage=1;//当前游戏处于的小局数
int yourWin=0, *pyourWin=&yourWin;//己方胜利的小局数, 指针没必要，但我懒得改
int enemyWin=0, *penemyWin=&enemyWin;//对方胜利的小局数
int yourAttack[3], enemyAttack[3];//己方和对方三排战场的点数，0-近战，1-远程，2-攻城
int yourAttacks, enemyAttacks;//己方和对方的总点数
int winner;//0-平局，1-己方，2-对方
int isFrost=FALSE, isFog=FALSE, isRain=FALSE;
int enemyHandcards=12;//对手手牌数
char enemyhandcards[10]; 
card yourRecentcard;//玩家出的最后一张牌 

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
    LeadinSavedCards();//读入保存的卡牌
    enemySide=RandomInteger(1, 4);//随机决定敌方阵营
    DrawPlayBoard();//绘制对局界面
    SetPenColor("White");
	SetPointSize(30);
	sprintf(enemyhandcards,"%d",enemyHandcards);
	MovePen(0.6,4.8);
	DrawTextString(enemyhandcards);

/*决定出牌先手方*/
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

/*确定手牌序列号*/
    int i,j,k=0;
    int isEqual;//用于把randomNum外的序号选出
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
/*确定剩余13张牌序列号*/
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
/*根据序列号分别导入手牌和剩余牌的信息*/
    for(i=0;i<12;i++)
    {
        allocatedCards[i]=Yourcards[randomNum[i]];
    }
    for(i=0;i<13;i++)
    {
        remainedCards[i]=Yourcards[remainedNum[i]];
    }
/*显示阵营信息*/
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
                DrawTextString("北方领域");
                break;
            case NILFGAARD:
                DrawTextString("尼弗迦德帝国");
                break;
            case SCOIA:
                DrawTextString("松鼠党");
                break;
            case MONSTERS:    
                DrawTextString("怪物");
                break;
        }
        MovePen(0.5,gameHeight/2+1);
            switch(enemySide)
        {
            case NORTHERN_REALMS:
                DrawTextString("北方领域");
               break;
            case NILFGAARD:
                DrawTextString("尼弗迦德帝国");
                break;
            case SCOIA:
                DrawTextString("松鼠党");
                break;
            case MONSTERS:    
                DrawTextString("怪物");
                break;
        }
    }

/*显示手牌*/
    for(i=0;i<12;i++)
    {
        DrawHandCards(1.3+0.55*i, 0.4, allocatedCards[i].ID);
    }

/*初始光标（三角）*/
    DrawTriangleCursor(1.53,0.27,0);

/*初始详细信息（右侧框）*/
    DrawDetail(allocatedCards[0]);

/*显示是否为己方回合（第一小局先手权）*/
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
            DrawTextString("你的回合！");
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

    registerKeyboardEvent(KeyboardPlayProcess);//键盘消息回调函数
}


void InitializeSideSelect()
{
	PlaySound(NULL,NULL,SND_FILENAME);
	PlaySound("select.wav",NULL,SND_FILENAME | SND_ASYNC | SND_LOOP);
    DrawBackground();
    extern int lan;
/*阵营选项*/
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
        MovePen(gameWidth/2-TextStringWidth("选 择 阵 营")/2-0.16,5.5);
        SetPenColor("White");
        DrawTextString("选 择 阵 营");
        SetPointSize(30);
        MovePen(gameWidth/2-TextStringWidth("北 方 领 域")/2,4.5);
        DrawTextString("北 方 领 域");
        MovePen(gameWidth/2-TextStringWidth("尼 弗 迦 德 帝 国")/2,3.5);
        DrawTextString("尼 弗 迦 德 帝 国");
        MovePen(gameWidth/2-TextStringWidth("松 鼠 党")/2,2.5);
        DrawTextString("松 鼠 党");
        MovePen(gameWidth/2-TextStringWidth("怪 物")/2,1.5);
        DrawTextString("怪 物");
    }
    
    extern int lan;
/*初始光标*/
    SetPenColor("Gold_1");
    if(lan==0){
        MovePen(gameWidth/2-TextStringWidth("Northern  Realms")/2,4.5);
        DrawTextString("Northern  Realms");
        SetPenColor("Gray");
        MovePen(gameWidth/2-TextStringWidth("Draw a card from your deck whnever you win a round")/2,4.2);
        DrawTextString("Draw a card from your deck whnever you win a round");
    }else{
        MovePen(gameWidth/2-TextStringWidth("北 方 领 域")/2,4.5);
        DrawTextString("北 方 领 域");
        SetPenColor("Gray");
        SetPointSize(20); 
        MovePen(gameWidth/2-TextStringWidth("赢得一回合后可抽一张牌")/2,4.2);
        DrawTextString("赢得一回合后可抽一张牌");
    }
    SetPointSize(30); 
    state=1;
    registerKeyboardEvent(KeyboardSideProcess);//键盘消息回调函数
}

void KeyboardSideProcess(int key, int event)//键盘消息回调函数（阵营选择）
{
    extern int lan; 
        switch(event)
    {
        case KEY_DOWN:
            if(lan==0){//英文 
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
            else{//中文 
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
                                MovePen(gameWidth/2-TextStringWidth("北 方 领 域")/2,4.5);
                                DrawTextString("北 方 领 域");
                                SetPenColor("Light_Brown");
                                StartFilledRegion(1);
                                DrawBox(2.5,4.1,6,0.32);
                                EndFilledRegion();

                                SetPointSize(30); 
                                SetPenColor("Gold_1");
                                MovePen(gameWidth/2-TextStringWidth("尼 弗 迦 德 帝 国")/2,3.5);
                                DrawTextString("尼 弗 迦 德 帝 国");
                                SetPenColor("Gray");
                                SetPointSize(20); 
                                MovePen(gameWidth/2-TextStringWidth("平局时可获得胜利")/2,3.2);
                                DrawTextString("平局时可获得胜利");
                                state++;
                                break;
                            case 2:
                                SetPointSize(30); 
                                SetPenColor("White");
                                MovePen(gameWidth/2-TextStringWidth("尼 弗 迦 德 帝 国")/2,3.5);
                                DrawTextString("尼 弗 迦 德 帝 国");
                                SetPenColor("Light_Brown");
                                SetPointSize(20); 
                                MovePen(gameWidth/2-TextStringWidth("平局时可获得胜利")/2,3.2);
                                DrawTextString("平局时可获得胜利");

                                SetPointSize(30); 
                                SetPenColor("Gold_1");
                                MovePen(gameWidth/2-TextStringWidth("松 鼠 党")/2,2.5);
                                DrawTextString("松 鼠 党");
                                SetPenColor("Gray");
                                SetPointSize(20); 
                                MovePen(gameWidth/2-TextStringWidth("你总是先出牌")/2,2.2);
                                DrawTextString("你总是先出牌");
                                state++;
                                break;
                            case 3:
                                SetPointSize(30); 
                                SetPenColor("White");
                                MovePen(gameWidth/2-TextStringWidth("松 鼠 党")/2,2.5);
                                DrawTextString("松 鼠 党");
                                SetPenColor("Light_Brown");
                                SetPointSize(20); 
                                MovePen(gameWidth/2-TextStringWidth("你总是先出牌")/2,2.2);
                                DrawTextString("你总是先出牌");

                                SetPointSize(30); 
                                SetPenColor("Gold_1");
                                MovePen(gameWidth/2-TextStringWidth("怪 物")/2,1.5);
                                DrawTextString("怪 物");
                                SetPenColor("Gray");
                                SetPointSize(20); 
                                MovePen(gameWidth/2-TextStringWidth("回合结束时，可选择己方战场上一张牌并使其保留")/2,1.2);
                                DrawTextString("回合结束时，可选择己方战场上一张牌并使其保留");
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
                                MovePen(gameWidth/2-TextStringWidth("尼 弗 迦 德 帝 国")/2,3.5);
                                DrawTextString("尼 弗 迦 德 帝 国");
                                SetPenColor("Light_Brown");
                                SetPointSize(20); 
                                MovePen(gameWidth/2-TextStringWidth("平局时可获得胜利")/2,3.2);
                                DrawTextString("平局时可获得胜利");

                                SetPointSize(30); 
                                SetPenColor("Gold_1");
                                MovePen(gameWidth/2-TextStringWidth("北 方 领 域")/2,4.5);
                                DrawTextString("北 方 领 域");
                                SetPenColor("Gray");
                                SetPointSize(20); 
                                MovePen(gameWidth/2-TextStringWidth("赢得一回合后可抽一张牌")/2,4.2);
                                DrawTextString("赢得一回合后可抽一张牌");
                                state--;
                                break;
                            case 3:
                                
                                SetPointSize(30); SetPenColor("White");
                                MovePen(gameWidth/2-TextStringWidth("松 鼠 党")/2,2.5);
                                DrawTextString("松 鼠 党");
                                SetPenColor("Light_Brown");
                                SetPointSize(20); 
                                MovePen(gameWidth/2-TextStringWidth("你总是先出牌")/2,2.2);
                                DrawTextString("你总是先出牌");

                                
                                SetPointSize(30); 
                                SetPenColor("Gold_1");
                                MovePen(gameWidth/2-TextStringWidth("尼 弗 迦 德 帝 国")/2,3.5);
                                DrawTextString("尼 弗 迦 德 帝 国");
                                SetPenColor("Gray");
                                SetPointSize(20); 
                                MovePen(gameWidth/2-TextStringWidth("平局时可获得胜利")/2,3.2);
                                DrawTextString("平局时可获得胜利");
                                state--;
                                break;
                            case 4:
                                SetPointSize(30); 
                                SetPenColor("White");
                                MovePen(gameWidth/2-TextStringWidth("怪 物")/2,1.5);
                                DrawTextString("怪 物");
                                SetPenColor("Light_Brown");
                                SetPointSize(20); 
                                MovePen(gameWidth/2-TextStringWidth("回合结束时，可选择己方战场上一张牌并使其保留")/2,1.2);
                                DrawTextString("回合结束时，可选择己方战场上一张牌并使其保留");

                                SetPointSize(30); 
                                SetPenColor("Gold_1");
                                MovePen(gameWidth/2-TextStringWidth("松 鼠 党")/2,2.5);
                                DrawTextString("松 鼠 党");
                                SetPenColor("Gray");
                                SetPointSize(20); 
                                MovePen(gameWidth/2-TextStringWidth("你总是先出牌")/2,2.2);
                                DrawTextString("你总是先出牌");
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
    int i;//供循环体使用
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
                /*F12放弃跟牌*/
                case VK_F12:	
            		StartFilledRegion(1);
            		SetPenColor("Light_Brown");
            		DrawBox(0.35,gameHeight/2-2.1, 1.6, 0.3);
            		EndFilledRegion();
                    //if(isYouGiveUp==FALSE)
                    //{
                        isYouGiveUp=TRUE;
                        isYourTurn=FALSE;//放弃跟牌后，己方回合立即结束
                        if(isEnemyGiveUp==TRUE)//己方弃权后，需判断小局是否结束
                        {
                            preWin=yourWin;
                            /*小局胜负结算*/
                            JudgeWinner(pyourWin, penemyWin);
                            /*清空战场*/
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
                                    allocatedCards[i].isFielded=0;//卡牌从战场上去除
                                    allocatedCards[i].isGarbaged=1;//卡牌进入墓地
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
                            /*下一小局开始*/
                            if(yourWin==2||enemyWin==2)
                            {
                                /*游戏结束*/
                                GameOver();
                            }
                            else
                            {
                                EnemyLogic(cards[34]); 
                                enemyHandcards++;
                                gameStage++;
                            }
                        }
                        else//对方未放弃
                        {
                            EnemyPlaying();
                        }
                        break;
                    //}

                /*退格回到上一界面（已停用）*/
                case VK_BACK:
                    //InitializeSideSelect();
                    break;

                /*右移光标*/
                case VK_RIGHT:
                    if(cardState<=11)
                    {
                        DrawTriangleCursor(0.98+0.55*cardState,0.27,1);
                        DrawTriangleCursor(1.53+0.55*cardState,0.27,0);
                        cardState++;
                    }
                    DrawDetail(allocatedCards[cardState-1]);//更新详细信息
                    break;

                /*左移光标*/
                case VK_LEFT:
                    if(cardState>=2)
                    {
                        DrawTriangleCursor(0.98+0.55*cardState,0.27,1);
                        DrawTriangleCursor(0.43+0.55*cardState,0.27,0);
                        cardState--;
                    }
                    DrawDetail(allocatedCards[cardState-1]);//更新详细信息
                    break;

                /*回车键打出当前光标指向的手牌*/
                case VK_RETURN:
                    if(isYourTurn==TRUE)//己方回合
                    {    
                        if(allocatedCards[cardState-1].isFielded==0 &&
                           allocatedCards[cardState-1].isGarbaged==0)//卡牌未被打出才可打出
                        {                
                        	/*擦掉your turn*/
                        	StartFilledRegion(1);
                        	SetPenColor("Light_Brown");
                        	DrawBox(0.35,gameHeight/2-2.1, 1.6, 0.3);
                        	EndFilledRegion();
                            /*擦去该手牌（手牌框内）*/
                            StartFilledRegion(1);
                            SetPenColor("Light_Brown");
                            DrawBox(0.75+0.55*cardState, 0.4, 0.55, 0.9);
                            EndFilledRegion();

                            /*卡牌效果+卡牌显示*/
                            CardLogic(allocatedCards[cardState-1]);
                            yourRecentcard=allocatedCards[cardState-1];

                            /*更新相关游戏信息*/
                            for(i=1;i<=6;i++)
                            {
                                UpdateAttack(i);
                            }
                            UpdateGrave(1);
                            isOperated=TRUE;//出牌有效
                            if(isSpy==FALSE)//防止间谍获得的牌不能打出
                            {
                                allocatedCards[cardState-1].isFielded=1;//该卡牌进入战场
                            }
                            if(isEnemyGiveUp==FALSE && isOperated==TRUE)//出过牌且敌方未放弃跟牌，则你的回合结束
                            {
                                isYourTurn=FALSE;
                            }
                        }
                    }
                    else//对方回合
                    {
                    	/*写上your turn*/
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
                            if(isYouGiveUp==TRUE)//对方弃权后，需判断小局是否结束
                            {
                                /*小局胜负结算*/
                                JudgeWinner(pyourWin, penemyWin);
                                /*清空战场*/
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
                                /*下一小局*/
                                if(yourWin==2||enemyWin==2||gameStage==3)
                                {
                                	/*游戏结束*/
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

void JudgeWinner(int* pyourWin, int* penemyWin)//判断小局胜利
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
		DrawTextString("对手跳过回合");
	}
}

void UpdateGrave(int player)//刷新墓地信息,1-己方，2-对方
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

void UpdateAttack(int row)//1-敌方攻城，2-敌方远程，3-敌方近战，4-己方近战，5-己方远程，6-己方攻城
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

void CardLogic(card ecard)//不可用于对方出牌!!!
{
    int i, j;//用于循环
    int dead;//被治疗的卡牌
    int hornPlace;//号角增益的位置,1-近战,2-远程,3-攻城
    int burnPlace;
    int newCardPos[2];//新获得牌的插入位置
    int emptyPos=0;//可插排位置的数量
    int newCardNum[2];//新获得牌在remainedNum的数组编号
    time_t randSeed;
    card temp;//交换手牌位置
    isSpy=FALSE;
    switch(ecard.type)
    {
        case 1://近战
            switch(ecard.isSpecial)
            {
                case 1://间谍
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
                    while(1)//选到未打出的牌为止
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
                    remainedCards[newCardNum[0]]=temp;//交换两牌在remainedCards和allocatedCards的位置
                    DrawHandCards(1.3+0.55*newCardPos[0],0.4,allocatedCards[newCardPos[0]].ID);
                    if(emptyPos==2)
                    {
                        temp=allocatedCards[newCardPos[1]];
                        allocatedCards[newCardPos[1]]=remainedCards[newCardNum[1]];
                        remainedCards[newCardNum[1]]=temp;//交换两牌在remainedCards和allocatedCards的位置
                        DrawHandCards(1.3+0.55*newCardPos[1],0.4,allocatedCards[newCardPos[1]].ID);                        
                    }
                    break;
                case 3://同袍
                    yourMelee[yourField_1-1]=ecard;
                    DrawHandCards(2.3+0.55*yourField_1,gameHeight-3.8,ecard.ID);
                    yourField_1++;
                    break;
                default://近战没有治疗，召集，增益
                    yourMelee[yourField_1-1]=ecard;
                    DrawHandCards(2.3+0.55*yourField_1,gameHeight-3.8,ecard.ID);
                    yourField_1++;
                    break;
            }
            /*for(i=0;i<yourField_1-1;i++)
            {
                yourAttack[0]=yourAttack[0]+yourMelee[i].attack;
            }
            for(i=0;i<enemyField_1-1;i++)//因为有间谍，需要刷新一下对方的点数
            {
                enemyAttack[0]=enemyAttack[0]+enemyMelee[i].attack;
            }*/
            break;
        case 2://远程
            switch(ecard.isSpecial)
            {
                case 2://治疗
                    yourRange[yourField_2-1]=ecard;
                    DrawHandCards(2.3+0.55*yourField_2,gameHeight-4.72,ecard.ID);
                    yourField_2++;
                    dead=rand()%3;
                    switch(dead)
                    {
                        case 0://近战
                            yourMelee[yourField_1-1]=cards[6];
                            DrawHandCards(2.3+0.55*yourField_1,gameHeight-3.8,7);
                            yourField_1++;
                            break;
                        case 1://远程
                            yourRange[yourField_2-1]=cards[18];
                            DrawHandCards(2.3+0.55*yourField_2,gameHeight-4.72,19);
                            yourField_2++;
                            break;
                        case 2://攻城
                            yourSiege[yourField_3-1]=cards[20];
                            DrawHandCards(2.3+0.55*yourField_3,gameHeight-5.64,21);
                            yourField_3++;
                            break;
                    }
                    break;
                case 4://召集
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
                default://远程只有召集
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
        case 3://攻城
            switch(ecard.isSpecial)
            {
                case 2://治疗
                    yourSiege[yourField_3-1]=ecard;
                    DrawHandCards(2.3+0.55*yourField_3,gameHeight-5.64,ecard.ID);
                    yourField_3++;
                    dead=rand()%3;
                    switch(dead)
                    {
                        case 0://近战
                            yourMelee[yourField_1-1]=cards[6];
                            DrawHandCards(2.3+0.55*yourField_1,gameHeight-3.8,7);
                            yourField_1++;
                            break;
                        case 1://远程
                            yourRange[yourField_2-1]=cards[18];
                            DrawHandCards(2.3+0.55*yourField_2,gameHeight-4.72,19);
                            yourField_2++;
                            break;
                        case 2://攻城
                            yourSiege[yourField_3-1]=cards[20];
                            DrawHandCards(2.3+0.55*yourField_3,gameHeight-5.64,21);
                            yourField_3++;
                            break;
                    }
                    break;
                case 3://同袍
                    yourSiege[yourField_3-1]=ecard;
                    DrawHandCards(2.3+0.55*yourField_3,gameHeight-5.64,ecard.ID);
                    yourField_3++;
                    break;
                case 5://增益
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
        case 4://天气
            for(i=0;i<weatherField-1;i++)//检测目前生效天气
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
                    /*清空天气框*/
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
                    weatherCards[0].ID=0;//更改ID,可使该牌不再被判定为天气
                    weatherCards[1].ID=0;
                    weatherCards[2].ID=0;
                    mciSendString(TEXT("play clear.wav"),NULL,0,NULL);
                    break;
            }
            break;
        case 5://法术
            switch(ecard.ID)
            {
                case 36: case 37://号角
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
                case 38: case 39: case 40://燃烧
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
/*天气影响覆盖*/
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
/*最终结算点数*/
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
    /*备份*/
    for(i=0;i<num;i++)
    {
        tcard[i]=ecard[i];
    }
    tcard[11]=ecard[11];
    /*统计同袍*/
    for(i=0;i<num;i++)
    {
        if(tcard[i].isSpecial==3)
        {
        	if(tcard[i].ID>=9&&tcard[i].ID<=11){
        		bondNum1++;//蓝衣 
			}else if(tcard[i].ID>=23&&tcard[i].ID<=24){
				bondNum2++;//投石车
			}else if(tcard[i].ID>=54&&tcard[i].ID<=57){
				bondNum3++;//近卫军 
			}else if(tcard[i].ID>=61&&tcard[i].ID<=62){
				bondNum4++;//特使 
			}else if(tcard[i].ID>=65&&tcard[i].ID<=67){
				bondNum5++;//那乌西卡骑兵 
			}	 
        }
    }
    /*判断增益*/
    for(i=0;i<num;i++)
    {
        if(tcard[i].isSpecial==5)
        {
            isBoost=1;
        }
    }
    /*判断号角*/
    if(tcard[11].type==5)
    {
        isHorn=1;
    }
    /*按照结算顺序修正点数*/
    for(i=0;i<num;i++)
    {
        /*第一步，结算天气*/
        if(tcard[i].isWeatherControlled==1&&tcard[i].isHero==0)
        {
            tcard[i].attack=1;
        }
        /*第二步，结算同袍*/
        if(tcard[i].isSpecial==3)
        {
        	if(tcard[i].ID>=9&&tcard[i].ID<=11){
        		tcard[i].attack=bondNum1*tcard[i].attack;//蓝衣 
			}else if(tcard[i].ID>=23&&tcard[i].ID<=24){
				tcard[i].attack=bondNum2*tcard[i].attack;//投石车
			}else if(tcard[i].ID>=54&&tcard[i].ID<=57){
				tcard[i].attack=bondNum3*tcard[i].attack;//近卫军 
			}else if(tcard[i].ID>=61&&tcard[i].ID<=62){
				tcard[i].attack=bondNum4*tcard[i].attack;//特使 
			}else if(tcard[i].ID>=65&&tcard[i].ID<=67){
				tcard[i].attack=bondNum5*tcard[i].attack;//那乌西卡骑兵 
			}	 
        }
        /*第三步，结算增益*/
        if(isBoost==1)
        {
            tcard[i].attack=tcard[i].attack+1;
        }
        /*第四步，结算号角*/
        if(isHorn==1)
        {
            tcard[i].attack=2*tcard[i].attack;
        }
    }
    /*对最终点数进行求和*/
    for(i=0;i<num;i++)
    {
        finalAttack=finalAttack+tcard[i].attack;
    }
    return finalAttack;
}

void EnemyLogic(card ecard){
	int i,j;//用于循环
    int dead;//被治疗的卡牌号
    int hornPlace;//号角增益的位置,1-近战,2-远程,3-攻城
    int burnPlace;
    time_t randSeed;
    switch(ecard.type)
    {
        case 1://近战
            switch(ecard.isSpecial)
            {
                case 1://间谍
                    yourMelee[yourField_1-1]=ecard;
                    DrawHandCards(2.3+0.55*yourField_1,gameHeight-3.8,ecard.ID);
                    yourField_1++;
                    enemyHandcards++;
                    break;
                case 3://同袍
                    enemyMelee[enemyField_1-1]=ecard;
                    DrawHandCards(2.3+0.55*enemyField_1,gameHeight-2.84,ecard.ID);
                    enemyField_1++;
                    enemyHandcards--;
                    break;
                case 4://召集
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
                default://近战没有治疗,增益
                    enemyMelee[enemyField_1-1]=ecard;
                    DrawHandCards(2.3+0.55*enemyField_1,gameHeight-2.84,ecard.ID);
                    enemyField_1++;
                    enemyHandcards--;
                    break;
            }
            break;
        case 2://远程
            switch(ecard.isSpecial)
            {
            /*	case 2://治疗
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
                case 4://召集
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
                case 5://士气
                	enemyRange[enemyField_2-1]=ecard;
                    DrawHandCards(2.3+0.55*enemyField_2,gameHeight-1.92,ecard.ID);
                    enemyField_2++;
                    enemyHandcards--;
                    break;
                default://远程无间谍、同袍 
                    enemyRange[enemyField_2-1]=ecard;
                    DrawHandCards(2.3+0.55*enemyField_2,gameHeight-1.92,ecard.ID);
                    enemyField_2++;
                    enemyHandcards--;
                    break;                
            }
            break;
        case 3://攻城
            switch(ecard.isSpecial)
            {
				/*	case 2://治疗
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
                case 3://同袍
                    enemySiege[enemyField_3-1]=ecard;
                    DrawHandCards(2.3+0.55*enemyField_3,gameHeight-1,ecard.ID);
                    enemyField_3++;
                    enemyHandcards--;
                    break;
                case 4://召集
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
                case 5://增益
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
        case 4://天气
        	enemyHandcards--;
            for(i=0;i<weatherField-1;i++)//检测目前生效天气
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
                    /*清空天气框*/
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
                    weatherCards[0].ID=0;//更改ID,可使该牌不再被判定为天气
                    weatherCards[1].ID=0;
                    weatherCards[2].ID=0;
                    mciSendString(TEXT("play clear.wav"),NULL,0,NULL);
                    break;
            }
            break;
        case 5://法术
        	enemyHandcards--;
            switch(ecard.ID)
            {
                case 36: case 37://号角
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
                case 38: case 39: case 40://燃烧
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
/*天气影响覆盖*/
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
/*最终结算点数*/
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
			isEnemyGiveUp=TRUE;//没牌就弃牌
		}else if(gameStage==3&&enemyHandcards>0){
			isEnemyGiveUp=FALSE;
		}else if((gameStage==1||gameStage==2&&enemyWin==1)&&fabs(yourAttacks-enemyAttacks)>=25){
			isEnemyGiveUp=TRUE;//非赛点，attack差距超过25则放弃跟牌
		
		}else if(isYouGiveUp==TRUE&&(enemyAttacks>yourAttacks&&(enemySide!=2||enemySide==2&&yourSide==2)||enemyAttacks>=yourAttacks&&enemySide==2&&yourSide!=2)){
			isEnemyGiveUp=TRUE;//你放弃了，对手点数高于你则放弃跟牌 
		}else if(gameStage==1&&enemyHandcards<=6){
			isEnemyGiveUp=TRUE;
		}else{
			isEnemyGiveUp=FALSE;
		}
	}
	if(isEnemyGiveUp==FALSE){
		int hero1=0,hero2=0,hero3=0;//用于统计玩家每一行的英雄牌张数
		int pureattack1=yourAttack[0],pureattack2=yourAttack[1],pureattack3=yourAttack[2];//用于统计玩家三行不含英雄的总点数 
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
		//不同出牌风格
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
			case NORTHERN_REALMS://北方领域有大量同袍之情，以及点数低的间谍牌
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
			case NILFGAARD://尼弗迦德帝国有强大的单张牌，且分布在多排，有较多医生牌，但间谍牌点数普遍过高
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
			case SCOIA://松鼠党有大量集合牌和医生牌，但缺少攻城单位，集合牌点数较低
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
			case MONSTERS://拥有大量集合牌，且点数很高，但集中在近战单位行，且缺乏间谍和医生 
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
				DrawTextString("对手跳过回合");
			}
		}
}
