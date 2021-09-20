#include "Gwent.h"

#define TIMER_BLINK500  1

static int textlen = 0;
static int location = -1;
static char text[40];
extern char username[3][40];
const int mseconds500 = 500;  
static bool isBlink = FALSE;   /*�Ƿ���˸��־*/
static bool isDisplayText = FALSE; /*�ַ�����ʾ��־*/ 
static int state1 = 0;//�ı���˻�state��Ӧ 

void InitializeEvent(int state)
{
	textlen = 0;
	location = -1;
	text[0] = '\0';
	state1 = state; 
	//����ʾ���� 
	DrawBackground();
	SetPenColor("White");
	StartFilledRegion(1);
	DrawBox(2, 3.9, 6, 0.4);
	EndFilledRegion();
	MovePen(3.8, 5);
	SetPenColor("Gold_2");
	SetPointSize(50);
	DrawTextString("Register");
	MovePen(3.2, 3);
	SetPointSize(30);
	DrawTextString("Press Enter to Determine");
	SetPenColor("Red");
	MovePen(2, 4);
	DrawTextString("Your Name: ");
	
	registerKeyboardEvent(KeyboardEventProcess);/*ע�������Ϣ�ص�����*/
	registerCharEvent(CharEventProcess);/*ע���ַ���Ϣ�ص�����*/
	registerTimerEvent(TimerEventProcess);/*ע�ᶨʱ����Ϣ�ص�����*/
	
	if(isBlink) startTimer(TIMER_BLINK500, mseconds500);
    isBlink = !isBlink;
    if(isBlink) startTimer(TIMER_BLINK500, mseconds500);
    else cancelTimer(TIMER_BLINK500);
}

void KeyboardEventProcess(int key, int event)/*ÿ������������Ϣ����Ҫִ��*/
{
	FILE *fp;
	SetPointSize(30);
	static char str[2] = {0, 0};
    switch (event) 
	{
	 	case KEY_DOWN:
			switch(key)
			{
				case VK_DELETE: case VK_BACK:/* ɾ�����ǰһλ���ַ� */
				{
					if(location < 0) break;
					SetEraseMode(TRUE);
					str[0] = text[location];
					if(isBlink && isDisplayText)
					{
						MovePen(GetCurrentX(), GetCurrentY());
						DrawTextString("_");
						MovePen(GetCurrentX() - TextStringWidth("_"), GetCurrentY());
					}
					MovePen(GetCurrentX() - TextStringWidth(str), GetCurrentY());
					DrawTextString(str);
					string s1, s2;
					s1 = SubString(text, location + 1, textlen);
					s2 = SubString(text, location, textlen); 
					SetEraseMode(TRUE);
					DrawTextString(s1);
					SetEraseMode(FALSE);
					MovePen(GetCurrentX() - TextStringWidth(s2), GetCurrentY());
					DrawTextString(s1);
					MovePen(GetCurrentX() - TextStringWidth(s1), GetCurrentY());
					int i;
					for(i = location; i < textlen; i++)
		        		text[i] = text[i + 1];
		        	text[--textlen] = '\0';
					location--;
 					SetEraseMode(FALSE);
 					break;
				}
				case VK_LEFT:
				{
					if(location < 0) break;
					str[0] = text[location];
					if(isBlink && isDisplayText)
					{
		 	     	   	SetEraseMode(TRUE);
	 	              	DrawTextString("_");
	 	         	   	SetEraseMode(FALSE);
			           	MovePen(GetCurrentX() - TextStringWidth("_"), GetCurrentY());
			    	}
			       	MovePen(GetCurrentX() - TextStringWidth(str), GetCurrentY());
			       	location--;
			       	break;
				}
				case VK_RIGHT:	
				{
					if(location >= textlen) break; 
					str[0] = text[location + 1];
					if(isBlink && isDisplayText)
					{
		 	     	   	SetEraseMode(TRUE);
	 	              	DrawTextString("_");
	 	         	   	SetEraseMode(FALSE);
			           	MovePen(GetCurrentX() - TextStringWidth("_"), GetCurrentY());
			       	}
			       	MovePen(GetCurrentX() + TextStringWidth(str), GetCurrentY());
			       	location++;
			       	break;
				}
				case VK_RETURN:
					strcpy(username[state1-1], text);
			   		fp = fopen("accounts.txt", "w+");
					fprintf(fp, "%s\n", username[0]);
					fprintf(fp, "%s\n", username[1]);
					fprintf(fp, "%s\n", username[2]);
					fclose(fp);
					cancelTimer(TIMER_BLINK500);
					cancelCharEvent();
					InitializeAccounts();
					default:
						break;
			}
		case KEY_UP:
			break;
	}	 
}

void CharEventProcess(char c)
{	
	SetPointSize(30);
	static char str[2] = {0, 0};
	switch (c) 
	{
		case VK_BACK: case VK_DELETE: case 27:
			break;
		default:
		{
			str[0] = c;/*�γɵ�ǰ�ַ����ַ���*/
			if(location == textlen - 1)
			{
				text[textlen++] = c;/*����ǰ�ַ����뵽�����ַ���������*/
				text[textlen] = '\0';
				DrawTextString(str);/*�����ǰ�ַ��������λ����Ӧ����*/
				location++;
			}
			else//���������ĸ��������ĸ�滻 
			{
				string s1, s2;
				s1 = SubString(text, location + 1, textlen);
				s2 = SubString(text, location + 2, textlen);
				SetEraseMode(TRUE);
				DrawTextString(s1);
				MovePen(GetCurrentX() - TextStringWidth(s1), GetCurrentY());
				SetEraseMode(FALSE);
				DrawTextString(str);
				DrawTextString(s2);
				MovePen(GetCurrentX() - TextStringWidth(s2) - TextStringWidth(str), GetCurrentY());
				text[location + 1] = c;
			}
			if(isBlink && isDisplayText)
			{
				SetEraseMode(TRUE);
				MovePen(GetCurrentX() - TextStringWidth(str), GetCurrentY());
	 			DrawTextString("_");
	 			MovePen(GetCurrentX() - TextStringWidth("_"), GetCurrentY());
	 			SetEraseMode(FALSE);
	 			MovePen(GetCurrentX() + TextStringWidth(str), GetCurrentY()); 
			}
		}
	}
}


void TimerEventProcess(int timerID)
{
	double textx, texty;
	bool erasemode;
	switch (timerID)
	{
		case TIMER_BLINK500: /*500ms�ı���˸��ʱ��*/
			if (!isBlink) break;
			erasemode = GetEraseMode();
			textx = GetCurrentX();
			texty = GetCurrentY();
			SetEraseMode(isDisplayText);/*���ݵ�ǰ��ʾ��־����������ʾ���������ַ���*/
			DrawTextString("_");/*��ǰλ�û����ַ�������*/
			MovePen(textx, texty);/*��ʼλ��*/
			if(textlen - 1 != location)//�ָ��������ȥ�ĵ��� 
			{
				char str[2] = {0, 0};
				str[0] = text[location + 1];
				SetEraseMode(FALSE);
				DrawTextString(str);
				MovePen(textx, texty);
			}
			SetEraseMode(erasemode);
			isDisplayText = !isDisplayText;/*������ʾ/�����ַ�������*/
			break;
	}
}
