#include "Gwent.h"

bool newplay=FALSE;
bool newenter=TRUE;
void InitializeMenu()//��ʼ������
{
	PlaySound("background.wav",NULL,SND_FILENAME | SND_ASYNC | SND_LOOP);
    ColorDefine();//��ɫ��չ
    gameWidth = GetWindowWidth();
    gameHeight = GetWindowHeight();
    DrawBackground();

    DrawGwent();

/*С����*/
    SetPenColor("Gold_2");
    SetPointSize(30);
    MovePen(gameWidth/2-TextStringWidth("T H E   W I T H E R   C A R D   G A M E")/2,2.2);
    DrawTextString("T H E   W I T H E R   C A R D   G A M E");
    SetPenColor("Gold_1");
    SetPenSize(6);
    MovePen(2.8,2.1);
    DrawLine(4.1,0);

/*�ʹ�*/
    DrawLogo();

/*����*/
    SetPointSize(30);
    SetPenColor("White");
    MovePen(gameWidth/2-TextStringWidth("Press  ENTER  to  Continue")/2,1.7);
    DrawTextString("Press  ENTER  to  Continue");

    registerKeyboardEvent(KeyboardMenuProcess);//ע�������Ϣ�ص�����
}

void InitializeOption()//��ʼ��ѡ�����
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
/*ѡ���*/
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
        DrawTextString("��ʼ��Ϸ");
        MovePen(4.37,4.7);
        DrawTextString("��������");
        MovePen(4.37,3.9);
        DrawTextString("�˻��л�");
        MovePen(4.37,3.1);
        DrawTextString("�淨˵��");
        MovePen(4.37,2.3);
        DrawTextString("��������");
        MovePen(4.37,1.5);
        DrawTextString("�˳���Ϸ");
    }
    if(lan==0){
    	SetPointSize(20);
        SetPenColor("White");
        MovePen(gameWidth/2-TextStringWidth("Press UP and DOWN to switch��RETURN to choose, BACKSPACE to go back")/2,0.5);
        DrawTextString("Press UP and DOWN to switch��RETURN to choose, BACKSPACE to go back");
	}else{
		SetPointSize(20);
    SetPenColor("White");
    MovePen(gameWidth/2-TextStringWidth("���������ѡ�񣬻س�ѡ�У��˸���ص��˵�")/2,0.5);
    DrawTextString("���������ѡ�񣬻س�ѡ�У��˸���ص��˵�");
	}
/*Ĭ�Ϲ��*/
	if(state<1)
    {
		state=1;
	} 
    SetPenColor("White");
    DrawCursor(6.4-0.8*state,1.2);
    
    registerKeyboardEvent(KeyboardOptionProcess);//ע�������Ϣ�ص����� 
}


void KeyboardMenuProcess(int key, int event)//������Ϣ�ص����������棩
{
    switch(event)
    {
        case KEY_DOWN:
            switch(key)
            {
                case VK_RETURN:
                    InitializeOption();//���س�������ѡ�����
                    break;
            }
            break;
    }
}

void KeyboardOptionProcess(int key, int event)//������Ϣ�ص�������ѡ����棩
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
                    
                case VK_RETURN://���س���������Ӧѡ����� 
           			switch(state)
           			{
           				case 1: //��ʼ��Ϸ 
           					newplay=TRUE;
						   InitializeSideSelect();
						   break;
           				case 2:	//�������� 
           					InitializeView();
							break; 
           				case 3: //��ʷ��¼ 
                            InitializeAccounts();
           					break;
           				case 4: //�淨˵�� 
           					InitializeHelp();
           					break;
           				case 5: //�������� 
           					InitializeLan();
							break;
           				case 6: //�˳���Ϸ
						    exit(0); 
           					break;	
					}	
        }
    }    
}

