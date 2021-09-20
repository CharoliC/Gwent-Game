#include "Gwent.h"

char username[3][40];//用户名 

int usernow = 0;//当前用户 


void InitializeAccounts()
{
	PlaySound(NULL,NULL,SND_FILENAME | SND_ASYNC | SND_LOOP);
	DrawBackground();
	char name[40];
	FILE *fp_act;
	fp_act = fopen("accounts.txt", "r");
	int i;
	for(i = 0; i < 3; i++)
	{
		fscanf(fp_act, "%s", name);
		strcpy(username[i], name);
	}
	fclose(fp_act);
	SetPenColor("Gold_2");
	extern int lan;
	if(lan==0){
		SetPointSize(50);
		MovePen(gameWidth/2-TextStringWidth("Accounts")/2, 5.5);
		DrawTextString("Accounts");
		SetPenColor("White");
		SetPointSize(15);
		MovePen(4.0, 5.2);
		DrawTextString("Your Account Now:");
		SetPenColor("Red");
		MovePen(5.48,5.2);
		DrawTextString(username[usernow]);//画用户名 
		SetPenColor("White");
		MovePen(gameWidth/2-TextStringWidth("You can save and load your schemes here")/2, gameHeight-0.6);
		DrawTextString("You can save and load your schemes here");
	}else{
		SetPointSize(40);
		MovePen(gameWidth/2-TextStringWidth("账 户")/2, 5.5);
		DrawTextString("账 户");
		SetPenColor("White");
		SetPointSize(15);
		MovePen(4.0, 5.2);
		DrawTextString("当前账户:");
		SetPenColor("Red");
		DrawTextString(username[usernow]);//画用户名 
		SetPenColor("White");
		MovePen(gameWidth/2-TextStringWidth("您可以在这里保存并切换牌组方案")/2, gameHeight-0.6);
		DrawTextString("您可以在这里保存并切换牌组方案");
	}
	
	StartFilledRegion(1);
	SetPenColor("Gray");
	DrawBox(3.66, 4.1, 3, 0.9);
	EndFilledRegion();
	MovePen(4.78, 4.50); 
	SetPenColor("Red");
	DrawTextString(username[0]);//画用户名 1
	
	StartFilledRegion(1);
	SetPenColor("Gray");
	DrawBox(3.66, 2.9, 3, 0.9);
	EndFilledRegion();
	MovePen(4.78, 3.30);
	SetPenColor("Red");
	DrawTextString(username[1]);//画用户名 2
	
	StartFilledRegion(1);
	SetPenColor("Gray");
	DrawBox(3.66, 1.7, 3, 0.9);
	EndFilledRegion();
	MovePen(4.78, 2.1);
	SetPenColor("Red");
	DrawTextString(username[2]);//画用户名 3
	
	StartFilledRegion(1);
	SetPenColor("Gray"); 
	DrawBox(3.66, 0.5, 3, 0.9);
	EndFilledRegion();
	MovePen(4.78, 0.9);
	SetPenColor("Red");
	DrawTextString("Register");//更改用户名 
	
	registerKeyboardEvent(KeyboardAccountProcess);
}

void KeyboardAccountProcess(int key, int event)
{
	static int state = 1;//选框移动 
	SetPenColor("Red");
	DrawBox(3.68, 5.32-1.2*state, 2.96, 0.86);
	switch(event)
	{
		case KEY_DOWN:
			switch(key)
			{
				case VK_DOWN:
					if(state < 4)
					{
						SetPenColor("Gray");
						DrawBox(3.68, 5.32-1.2*state, 2.96, 0.86);
						state++;
						SetPenColor("Red");
						DrawBox(3.68, 5.32-1.2*state, 2.96, 0.86);
					}
					break;
				case VK_UP:
					if(state > 1)
					{
						SetPenColor("Gray");
						DrawBox(3.68, 5.32-1.2*state, 2.96, 0.86);
						state--;
						SetPenColor("Red");
						DrawBox(3.68, 5.32-1.2*state, 2.96, 0.86);
					}
					break;
				case VK_RETURN:
					if(state < 4)
					{
						usernow = state - 1;
						SetPointSize(15);
						SetPenColor("Light_Brown");
						StartFilledRegion(1);
						DrawBox(5.48, 5.1, 3, 0.3);
						EndFilledRegion();
						SetPenColor("Red");
						MovePen(5.5, 5.2);
						DrawTextString(username[usernow]);
					}
					else if(state == 4)
					{
						InitializeRegister();
					}
					break;
				case VK_BACK:
					InitializeOption();
					break;
			}
	}
}

