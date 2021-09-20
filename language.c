#include"Gwent.h"

int lan=0; 
void InitializeLan(){
	PlaySound(NULL,NULL,SND_FILENAME | SND_ASYNC | SND_LOOP);
	PlaySound("language.wav",NULL,SND_FILENAME | SND_ASYNC | SND_LOOP);
	DrawBackground();
	StartFilledRegion(1);
	SetPenColor("White");
	DrawBox(gameWidth/2-1.1,gameHeight/2-0.55,2.2,1.1);
	EndFilledRegion();
	StartFilledRegion(1);
	SetPenColor("Dark_Brown");
	DrawBox(gameWidth/2-1.075,gameHeight/2-0.525,2.15,1.05);
	EndFilledRegion();
	SetPenColor("White");
	SetPointSize(30);
	MovePen(gameWidth/2-2.5,gameHeight/2);
	DrawTextString("English");
	MovePen(gameWidth/2+1.6,gameHeight/2);
	DrawTextString("ÖÐÎÄ"); 
	if(lan==0){
		StartFilledRegion(1);
		SetPenColor("Dark_Golden");
		DrawBox(gameWidth/2-1.05,gameHeight/2-0.5,1,1);
		EndFilledRegion();
		StartFilledRegion(1);
		SetPenColor("Light_Brown");
		DrawBox(gameWidth/2-1.02,gameHeight/2-0.47,0.94,0.94);
		EndFilledRegion();
		SetPenColor("Dark_Golden");
		SetPenSize(3);
		MovePen(gameWidth/2-0.8, gameHeight/2-0.25);
		DrawLine(0, 0.5);
		DrawLine(0.5, 0);
		DrawLine(0, -0.5);
		DrawLine(-0.5, 0);
	}else{
		StartFilledRegion(1);
		SetPenColor("Dark_Golden");
		DrawBox(gameWidth/2+0.05,gameHeight/2-0.5,1,1);
		EndFilledRegion();
		StartFilledRegion(1);
		SetPenColor("Light_Brown");
		DrawBox(gameWidth/2+0.08,gameHeight/2-0.47,0.94,0.94);
		EndFilledRegion();
		SetPenColor("Dark_Golden");
		SetPenSize(3);
		MovePen(gameWidth/2+0.3, gameHeight/2-0.25);
		DrawLine(0, 0.5);
		DrawLine(0.5, 0);
		DrawLine(0, -0.5);
		DrawLine(-0.5, 0);
	}
	
	registerKeyboardEvent(KeyboardLanProcess);
}

void KeyboardLanProcess(int key,int event){
	extern int lan;
	switch(event){
		case KEY_DOWN:
			switch(key){
				case VK_BACK:
				    InitializeOption();
				break;
				case VK_RETURN:
					if(lan==0){
						lan=1;
					}else{
						lan=0;
					}
					InitializeLan();
				break;
				}break; 
			}
	}

