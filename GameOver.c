#include"Gwent.h"

void GameOver(){
	extern int lan; 
	extern int gameStage,yourWin,enemyWin;
	DrawBackground();
	SetPenColor("White");
	
	if(yourWin>enemyWin){
		PlaySound(NULL,NULL,SND_FILENAME | SND_ASYNC | SND_LOOP);
		PlaySound("victory.wav",NULL,SND_FILENAME | SND_ASYNC);
	}else if(yourWin<enemyWin){
		PlaySound(NULL,NULL,SND_FILENAME | SND_ASYNC | SND_LOOP);
		PlaySound("defeat.wav",NULL,SND_FILENAME | SND_ASYNC);
	}else{
		PlaySound(NULL,NULL,SND_FILENAME | SND_ASYNC | SND_LOOP);
	}
	if(lan==0){
		SetPointSize(35);
		MovePen(gameWidth/2-TextStringWidth("Game Over")/2,gameHeight/2+1);
		DrawTextString("Game Over");
		if(yourWin>enemyWin){
			SetPenColor("Yellow");
			MovePen(gameWidth/2-TextStringWidth("Victory")/2,gameHeight/2);
			DrawTextString("Victory");
		}else if(yourWin<enemyWin){
			SetPenColor("Red");
			MovePen(gameWidth/2-TextStringWidth("Defeat")/2,gameHeight/2);
			DrawTextString("Defeat");
		}else{
			SetPenColor("White");
			MovePen(gameWidth/2-TextStringWidth("Draw")/2,gameHeight/2);
			DrawTextString("Draw");
		}
	}else{
		SetPointSize(30);
		MovePen(gameWidth/2-TextStringWidth("��Ϸ����")/2,gameHeight/2+1);
		DrawTextString("��Ϸ����");
		if(yourWin>enemyWin){
			SetPenColor("Yellow");
			MovePen(gameWidth/2-TextStringWidth("ʤ��")/2,gameHeight/2);
			DrawTextString("ʤ��");
		}else if(yourWin<enemyWin){
			SetPenColor("Red");
			MovePen(gameWidth/2-TextStringWidth("ʧ��")/2,gameHeight/2);
			DrawTextString("ʧ��");
		}else{
			SetPenColor("White");
			MovePen(gameWidth/2-TextStringWidth("ƽ��")/2,gameHeight/2);
			DrawTextString("ƽ��");
		}
	}
	gameStage=1;
	yourWin=0;
	enemyWin=0;

	registerKeyboardEvent(KeyboardoverProcess);
}

void KeyboardoverProcess(int key, int event){
	switch(event){
		case KEY_DOWN:
			switch(key){
			case VK_RETURN:
				InitializeOption();
					break;
			}
			break;
	}
}
