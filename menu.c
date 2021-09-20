#include "Gwent.h"

bool newplay=FALSE;
bool newenter=TRUE;
void InitializeMenu()//初始化封面
{
	PlaySound("background.wav",NULL,SND_FILENAME | SND_ASYNC | SND_LOOP);
    ColorDefine();//颜色拓展
    gameWidth = GetWindowWidth();
    gameHeight = GetWindowHeight();
    DrawBackground();

    DrawGwent();

/*小标题*/
    SetPenColor("Gold_2");
    SetPointSize(30);
    MovePen(gameWidth/2-TextStringWidth("T H E   W I T H E R   C A R D   G A M E")/2,2.2);
    DrawTextString("T H E   W I T H E R   C A R D   G A M E");
    SetPenColor("Gold_1");
    SetPenSize(6);
    MovePen(2.8,2.1);
    DrawLine(4.1,0);

/*皇冠*/
    DrawLogo();

/*其它*/
    SetPointSize(30);
    SetPenColor("White");
    MovePen(gameWidth/2-TextStringWidth("Press  ENTER  to  Continue")/2,1.7);
    DrawTextString("Press  ENTER  to  Continue");

    registerKeyboardEvent(KeyboardMenuProcess);//注册键盘消息回调函数
}

void InitializeOption()//初始化选择界面
{
	if(newenter==TRUE){
		newenter=FALSE;
	}else{
		PlaySound(NULL,NULL,SND_FILENAME | SND_ASYNC | SND_LOOP);
		PlaySound("background.wav",NULL,SND_FILENAME | SND_ASYNC | SND_LOOP);
	}
    DrawBackground();
    extern int lan;
    InitializeCards();
/*选项框*/
    if(lan==0)
    {
        SetPointSize(35);
        SetPenColor("Gold_2");
        MovePen(gameWidth/2-TextStringWidth("Play")/2,5.5);
        DrawTextString("Play");
        MovePen(gameWidth/2-TextStringWidth("View Cards")/2,4.7);
        DrawTextString("View Cards");
        MovePen(gameWidth/2-TextStringWidth("Accounts")/2,3.9);
        DrawTextString("Accounts");
        MovePen(gameWidth/2-TextStringWidth("Help")/2,3.1);
        DrawTextString("Help");
        MovePen(gameWidth/2-TextStringWidth("Language")/2,2.3);
        DrawTextString("Language");
        MovePen(gameWidth/2-TextStringWidth("Exit")/2,1.5);
        DrawTextString("Exit");
    }
    else
    {
        SetPointSize(30);
        SetPenColor("Gold_2");
        MovePen(4.37,5.5);
        DrawTextString("开始游戏");
        MovePen(4.37,4.7);
        DrawTextString("牌组配置");
        MovePen(4.37,3.9);
        DrawTextString("账户切换");
        MovePen(4.37,3.1);
        DrawTextString("玩法说明");
        MovePen(4.37,2.3);
        DrawTextString("语言设置");
        MovePen(4.37,1.5);
        DrawTextString("退出游戏");
    }
    if(lan==0){
    	SetPointSize(20);
        SetPenColor("White");
        MovePen(gameWidth/2-TextStringWidth("Press UP and DOWN to switch，RETURN to choose, BACKSPACE to go back")/2,0.5);
        DrawTextString("Press UP and DOWN to switch，RETURN to choose, BACKSPACE to go back");
	}else{
		SetPointSize(20);
    SetPenColor("White");
    MovePen(gameWidth/2-TextStringWidth("方向键上下选择，回车选中，退格键回到菜单")/2,0.5);
    DrawTextString("方向键上下选择，回车选中，退格键回到菜单");
	}
/*默认光标*/
	if(state<1)
    {
		state=1;
	} 
    SetPenColor("White");
    DrawCursor(6.4-0.8*state,1.2);
    
    registerKeyboardEvent(KeyboardOptionProcess);//注册键盘消息回调函数 
}


void KeyboardMenuProcess(int key, int event)//键盘消息回调函数（封面）
{
    switch(event)
    {
        case KEY_DOWN:
            switch(key)
            {
                case VK_RETURN:
                    InitializeOption();//按回车键进入选择界面
                    break;
            }
            break;
    }
}

void KeyboardOptionProcess(int key, int event)//键盘消息回调函数（选择界面）
{
    switch(event)
    {
        case KEY_DOWN:
            switch(key)
            {
                case VK_DOWN:
                    if(state<6)
                    {
                        ClearCursor(state);
                        SetPenColor("White");
                        DrawCursor(5.6-0.8*state,1.2);
                        state++;
                    } break;
                    
                case VK_UP:
                    if(state>1)
                    { 
						ClearCursor(state);
                        SetPenColor("White");
                        DrawCursor(7.2-0.8*state,1.2);
                        state--;
                        break;
					}break;
                    
                case VK_RETURN://按回车键进入相应选项界面 
           			switch(state)
           			{
           				case 1: //开始游戏 
           					newplay=TRUE;
						   InitializeSideSelect();
						   break;
           				case 2:	//牌组配置 
           					InitializeView();
							break; 
           				case 3: //历史记录 
                            InitializeAccounts();
           					break;
           				case 4: //玩法说明 
           					InitializeHelp();
           					break;
           				case 5: //语言设置 
           					InitializeLan();
							break;
           				case 6: //退出游戏
						    exit(0); 
           					break;	
					}	
        }
    }    
}

