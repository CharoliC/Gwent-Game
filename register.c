#include "Gwent.h"

extern char username[3][40];

void InitializeRegister()
{
	DrawBackground();
	SetPointSize(15);
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
	
	//画提示界面 
	MovePen(3.1, 5.7);
	SetPenColor("Gold_2");
	SetPointSize(40);
	DrawTextString("Choose the Account");
	MovePen(3.3, 1);
	SetPointSize(30);
	DrawTextString("Press Enter to Determine");
	
	registerKeyboardEvent(KeyboardRegisterProcess);
}


void KeyboardRegisterProcess(int key, int event)
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
					if(state < 3)
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
					InitializeEvent(state);
					break;
				case VK_BACK:
					InitializeAccounts();
					break;
			}
	}
}


