#include"Gwent.h"

int page=1; 
bool newhelp=TRUE;
void InitializeHelp()
{
	if(newhelp==TRUE){
		PlaySound(NULL,NULL,SND_FILENAME | SND_ASYNC | SND_LOOP);
		PlaySound("help.wav",NULL,SND_FILENAME | SND_ASYNC | SND_LOOP);
		newhelp=FALSE;
	}
	DrawBackground();
	
	extern int lan;
	
	SetPenColor("White");
	if(lan==0){
		SetPointSize(40);
		MovePen(gameWidth/2-TextStringWidth("HELP")/2,6.2);
		DrawTextString("HELP");
	}else{
		SetPointSize(35);
		MovePen(gameWidth/2-TextStringWidth("玩法说明")/2,6.2);
		DrawTextString("玩法说明");
	}
	
				
	SetPenColor("White");
	SetPointSize(60); 
	MovePen(0.6,0.6);
	DrawTextString("←");
	MovePen(gameWidth-0.6-TextStringWidth("→"),0.6);
	DrawTextString("→");
	
	char x[10];
	sprintf(x,"%d",page);
	SetPointSize(25);
	MovePen(gameWidth/2-TextStringWidth("00 / 00")/2,0.5);
	DrawTextString(x);
	MovePen(gameWidth/2-TextStringWidth("00 / 00")/2+TextStringWidth(x),0.5);
	DrawTextString(" / 10");
	
	if(page<1){
		page=1;
	}
	if(lan==0){//英文help 
		switch(page){
			case 1:
				SetPenColor("Light_Brown");//盖住左箭头 
				StartFilledRegion(1);
				DrawBox(0.5,0.5,1,0.4);
				EndFilledRegion();
				
				SetPenColor("White");
				SetPointSize(35);
				MovePen(gameWidth/2-TextStringWidth("Profile")/2,5.5);
				DrawTextString("Profile");
				
				SetPointSize(25);
				MovePen(0.7,5);
				DrawTextString("      Gwent is a fast-paced trading card game which first showed");
				MovePen(0.7,4.6);
				DrawTextString("in the video game The Witcher 3: Wild Hunt.");
				MovePen(0.7,4);
				DrawTextString("      The game is about the clash of two armies locked in mortal");
				MovePen(0.7,3.6);
				DrawTextString("struggle on a battlefield where the players are the leaders and");
				MovePen(0.7,3.2);
				DrawTextString("the cards their forces. With four different factions offering unique");
				MovePen(0.7,2.8);
				DrawTextString("combat styles and endless paths to victory, Gwent is every adv-");
				MovePen(0.7,2.4);
				DrawTextString("enturer's first choice when it comes to one-on-one card-based");
				MovePen(0.7,2);
				DrawTextString("dueling.");
			break;
			case 2:
				SetPenColor("White");
				SetPointSize(35);
				MovePen(gameWidth/2-TextStringWidth("Building of Deck")/2,5.5);
				DrawTextString("Building of Deck");
				
				SetPointSize(25);
				MovePen(0.7,5);
				DrawTextString("      First, Choose a faction from Northern Realms, Empire of Nil-");
				MovePen(0.7,4.6);
				DrawTextString("fgaard, Scoia' Tael, and Monsters. Different factions have differ-");
				MovePen(0.7,4.2);
				DrawTextString("ent special abilities ( see part \"Uniqueness of the Factions\" ). ");
				MovePen(0.7,3.8);
				DrawTextString("Then build your own deck in \" View Cards \" in advance of starting");
				MovePen(0.7,3.4);
				DrawTextString("a new game.");
			break;
			case 3:
				SetPenColor("White");
				SetPointSize(35);
				MovePen(gameWidth/2-TextStringWidth("Conditions Determining the Outcome")/2,5.5);
				DrawTextString("Conditions Determining the Outcome");
				
				SetPointSize(25);
				MovePen(0.7,5);
				DrawTextString("      Do two out of three. The player winning two rounds first is vi-");
				MovePen(0.7,4.6);
				DrawTextString("ctorious.");
			break;
			case 4:
				SetPenColor("White");
				SetPointSize(35);
				MovePen(gameWidth/2-TextStringWidth("Upper Hand")/2,5.5);
				DrawTextString("Upper Hand");
				
				SetPointSize(25);
				MovePen(0.7,5);
				DrawTextString("      Before a game starts in earnest. Players should decide with");
				MovePen(0.7,4.6);
				DrawTextString("a fair way which one to hold the upper hand, like coin tossing.");
				MovePen(0.7,4.2);
				DrawTextString("Unless one and only one player is in Scoia'Tael. ");
				MovePen(0.7,3.6);
				DrawTextString("      From the second round on, the winner of the previous round");
				MovePen(0.7,3.2);
				DrawTextString("holds the upper hand.");
			break;
			case 5:
				SetPenColor("White");
				SetPointSize(35);
				MovePen(gameWidth/2-TextStringWidth("Clearing Form")/2,5.5);
				DrawTextString("Clearing Form");
				
				SetPointSize(25);
				MovePen(0.7,5);
				DrawTextString("      In a single round, two players take turns to play cards or use");
				MovePen(0.7,4.6);
				DrawTextString("leader's skill. Only one action at every turn. This continues until");
				MovePen(0.7,4.2);
				DrawTextString("one player has no hand or takes the initiative to give up playing");
				MovePen(0.7,3.8);
				DrawTextString("a card, after which player having higher total amount of attacks");
				MovePen(0.7,3.4);
				DrawTextString("will win the single round. If they have the same total amount of");
				MovePen(0.7,3);
				DrawTextString("attacks, the player in the Nilfgaardian Empire will win. If there's");
				MovePen(0.7,2.6);
				DrawTextString("no player in the Nilfgaardian Empire, both sides win the round. ");
			break;
			case 6:
				SetPenColor("White");
				SetPointSize(35);
				MovePen(gameWidth/2-TextStringWidth("Game Process")/2,5.5);
				DrawTextString("Game Process");
				
				SetPointSize(25);
				MovePen(1.2,5);
				DrawTextString("* Draw cards.");
				MovePen(1.2,4.5);
				DrawTextString("* Deciding the upper hand.");
				MovePen(1.2,4);
				DrawTextString("* Play a card or use leader's skill in turns.");
				MovePen(1.2,3.5);
				DrawTextString("* Both sides abstain.");
				SetPenColor("Yellow");
				MovePen(0.7,3);
				DrawTextString("Attention: after you abstain,");
				MovePen(2,2.65);
				DrawTextString("you can't take any action until the round ends.");
				SetPenColor("White");
				MovePen(1.2,2.15);
				DrawTextString("* Repeat, until one player wins two rounds first");
			break;
			case 7:
				SetPenColor("White");
				SetPointSize(35);
				MovePen(gameWidth/2-TextStringWidth("Cards Classification")/2,5.5);
				DrawTextString("Cards Classification");
				
				SetPointSize(25);
				MovePen(0.7,5);
				DrawTextString("      The cards can be roughly divided into three categories: unit");
				MovePen(0.7,4.6);
				DrawTextString("cards, special cards and leaders.");
			break;
			case 8:
				SetPenColor("White");
				SetPointSize(35);
				MovePen(gameWidth/2-TextStringWidth("Unit Cards")/2,5.5);
				DrawTextString("Unit Cards");
				
				SetPointSize(25);
				MovePen(0.7,5);
				DrawTextString("      By different positions, unit cards can be divided into three ca-");
				MovePen(0.7,4.6);
				DrawTextString("tegories: close combat units, ranged units and siege units. The");
				MovePen(0.7,4.2);
				DrawTextString("same-typed units need to be posted in the same row.");
				MovePen(0.7,3.6);
				DrawTextString("      By special effects, unit cards can be divided into two kinds:");
				MovePen(0.7,3.2);
				DrawTextString("normal units and effective units. The effective units have some");
				MovePen(0.7,2.8);
				DrawTextString("differnt effects like Spy, Medic, Tight Bond, Muster and Morale B-");
				MovePen(0.7,2.4);
				DrawTextString("oost.");
				MovePen(0.7,1.8);
				DrawTextString("      By ranks, unit cards can be divided into two kinds: soldiers");
				MovePen(0.7,1.4);
				DrawTextString("and heroes. Heroes can't be influenced by any effect.");
			break;
			case 9:
				SetPenColor("White");
				SetPointSize(35);
				MovePen(gameWidth/2-TextStringWidth("Special Cards")/2,5.5);
				DrawTextString("Special Cards");
				
				SetPointSize(25);
				MovePen(0.7,5);
				DrawTextString("      Special cards can be roughly divided into two kinds: weather");
				MovePen(0.7,4.6);
				DrawTextString("cards and spell cards.");
				MovePen(0.7,4);
				DrawTextString("      There are four kinds of weather cards: Biting Frost, Impenetr-");
				MovePen(0.7,3.6);
				DrawTextString("able Fog, Torrential Rain and Clear Weather. Except Clear Weat-");
				MovePen(0.7,3.2);
				DrawTextString("her, weather cards can lower a row of non-hero units' attacks to 1.");
				MovePen(0.7,2.6);
				DrawTextString("      There are two kinds of spell cards: Horn and Burn. Horn can");
				MovePen(0.7,2.2);
				DrawTextString("double a row of units' attacks, while Burn can destroy all of the");
				MovePen(0.7,1.8);
				DrawTextString("unit cards with the highest attack.");
			break;
			/*case 10:
				SetPenColor("White");
				SetPointSize(35);
				MovePen(gameWidth/2-TextStringWidth("Leaders")/2,5.5);
				DrawTextString("Leaders");
				
				SetPointSize(25);
				MovePen(0.7,5);
				DrawTextString("      Every Leader have a characteristic skill, which can be used");
				MovePen(0.7,4.6);
				DrawTextString("only once a whole game.");
			break;*/
			case 10:
				SetPenColor("Light_Brown");//盖住右箭头 
				StartFilledRegion(1);
				DrawBox(gameWidth-1.5,0.5,1,0.4);
				EndFilledRegion();
				
				SetPenColor("White");
				SetPointSize(35);
				MovePen(gameWidth/2-TextStringWidth("Factions")/2,5.5);
				DrawTextString("Factions");
				
				SetPointSize(25);
				MovePen(0.7,5);
				DrawTextString("      Differnt factions have different speciality.");
				MovePen(1.2,4.5);
				DrawTextString("* Northern Realms");
				MovePen(1.2,4);
				DrawTextString("* The Nilfgaardian Empire");
				MovePen(1.2,3.5);
				DrawTextString("* Scoia' Tael");
				MovePen(1.2,3);
				DrawTextString("* Monsters");
			break;
		}
		
	}else{//中文help 
		switch(page){
			case 1:
				SetPenColor("Light_Brown");//盖住左箭头 
				StartFilledRegion(1);
				DrawBox(0.5,0.5,1,0.4);
				EndFilledRegion();
				
				SetPenColor("White");
				SetPointSize(30);
				MovePen(gameWidth/2-TextStringWidth("简介")/2,5.5);
				DrawTextString("简介");
				
				SetPointSize(25);
				MovePen(0.7,5);
				DrawTextString("      昆特牌是一种快节奏的集换式卡牌游戏，出自游戏《巫");
				MovePen(0.7,4.6);
				DrawTextString("师3：狂猎》。");
				MovePen(0.7,4);
				DrawTextString("      昆特牌游戏是一场微缩的战役，在两军的对抗中，玩家");
				MovePen(0.7,3.6);
				DrawTextString("扮演着指挥官的角色，而卡牌就是麾下的军队。四个不同阵");
				MovePen(0.7,3.2);
				DrawTextString("营带来四种不同的战斗策略和游玩体验，通往胜利的路远远");
				MovePen(0.7,2.8);
				DrawTextString("不止一条，对每一个想要在棋牌游戏中体验一对一决斗的玩");
				MovePen(0.7,2.4);
				DrawTextString("家来说，昆特牌都是其毋庸置疑的最优选择。");
			break;
			case 2:
				SetPenColor("White");
				SetPointSize(30);
				MovePen(gameWidth/2-TextStringWidth("牌组构成")/2,5.5);
				DrawTextString("牌组构成");
				
				SetPointSize(25);
				MovePen(0.7,5);
				DrawTextString("      首先，从北方领域、尼弗迦德帝国、松鼠党和怪物中选择");
				MovePen(0.7,4.6);
				DrawTextString("之一作为自己的阵营，不同的阵营有不同的特性和优势（详");
				MovePen(0.7,4.2);
				DrawTextString("见牌组部分），并在游戏开始前构建自己的牌组。");
			break;
			case 3:
				SetPenColor("White");
				SetPointSize(30);
				MovePen(gameWidth/2-TextStringWidth("胜负条件")/2,5.5);
				DrawTextString("胜负条件");
				
				SetPointSize(25);
				MovePen(0.7,5);
				DrawTextString("      三局两胜。率先赢得两局的玩家取得胜利。");
			break;
			case 4:
				SetPenColor("White");
				SetPointSize(30);
				MovePen(gameWidth/2-TextStringWidth("先手决定")/2,5.5);
				DrawTextString("先手决定");
				
				SetPointSize(25);
				MovePen(0.7,5);
				DrawTextString("      游戏正式开始之前，玩家应该用一种公平的方式决定哪一");
				MovePen(0.7,4.6);
				DrawTextString("方先手出牌，例如抛硬币。或者由松鼠党阵营特性决定先手。");
				MovePen(0.7,4);
				DrawTextString("      从第二轮开始，上一轮的获胜者为先手。 ");
			break;
			case 5:
				SetPenColor("White");
				SetPointSize(30);
				MovePen(gameWidth/2-TextStringWidth("结算规则")/2,5.5);
				DrawTextString("结算规则");
				
				SetPointSize(25);
				MovePen(0.7,5);
				DrawTextString("      一轮游戏中，双方轮流出牌或使用领袖技能，一回合只可");
				MovePen(0.7,4.6);
				DrawTextString("采取一项行动，直到一方无卡可出或主动弃权为止，此时进");
				MovePen(0.7,4.2);
				DrawTextString("行结算。若平局，则尼弗迦德帝国阵营的玩家胜利，双方均");
				MovePen(0.7,3.8);
				DrawTextString("是或均不是则算双方获胜。");
			break;
			case 6:
				SetPenColor("White");
				SetPointSize(30);
				MovePen(gameWidth/2-TextStringWidth("游戏流程")/2,5.5);
				DrawTextString("游戏流程");
				
				SetPointSize(25);
				MovePen(1.2,5);
				DrawTextString("* 抽牌。");
				MovePen(1.2,4.5);
				DrawTextString("* 决定先手。");
				MovePen(1.2,4);
				DrawTextString("* 轮流出牌或使用领袖技能。");
				MovePen(1.2,3.5);
				DrawTextString("* 双方弃权。");
				SetPenColor("Yellow");
				MovePen(0.7,3);
				DrawTextString("注意：在你弃权以后，直到本轮游戏结束你都不能采取任何");
				MovePen(1.6,2.65);
				DrawTextString("行动。");
				SetPenColor("White");
				MovePen(1.2,2.15);
				DrawTextString("* 重复以上过程，直至一方获胜两轮。");
			break;
			case 7:
				SetPenColor("White");
				SetPointSize(30);
				MovePen(gameWidth/2-TextStringWidth("卡牌类型")/2,5.5);
				DrawTextString("卡牌类型");
				
				SetPointSize(25);
				MovePen(0.7,5);
				DrawTextString("      卡牌大致可以分为三类：单位牌，特殊牌和领袖牌。");
			break;
			case 8:
				SetPenColor("White");
				SetPointSize(30);
				MovePen(gameWidth/2-TextStringWidth("单位牌")/2,5.5);
				DrawTextString("单位牌");
				
				SetPointSize(25);
				MovePen(0.7,5);
				DrawTextString("      根据所处位置不同，单位牌可分为近战单位牌、远程单位");
				MovePen(0.7,4.6);
				DrawTextString("牌和攻城单位牌。同一类型的单位牌必须被放在同一排。游");
				MovePen(0.7,4.2);
				DrawTextString("戏双方均只有3排。");
				MovePen(0.7,3.6);
				DrawTextString("      根据卡牌效果，单位牌可分为普通单位和效果单位。效");
				MovePen(0.7,3.2);
				DrawTextString("果单位除点数外，还拥有特殊效果，例如间谍、治疗、同袍");
				MovePen(0.7,2.8);
				DrawTextString("之情、聚众和士气高涨。");
				MovePen(0.7,2.2);
				DrawTextString("      根据卡牌级别，单位牌可分为士兵单位和英雄单位，英");
				MovePen(0.7,1.8);
				DrawTextString(" 英雄单位不受任何增益、减益效果影响。");
			break;
			case 9:
				SetPenColor("White");
				SetPointSize(30);
				MovePen(gameWidth/2-TextStringWidth("特殊牌")/2,5.5);
				DrawTextString("特殊牌");
				
				SetPointSize(25);
				MovePen(0.7,5);
				DrawTextString("      特殊牌可以大致分为两类：天气牌和法术牌。");
				MovePen(0.7,4.5);
				DrawTextString("      天气牌有四种：刺骨冰霜、蔽日浓雾、倾盆大雨和晴天。");
				MovePen(0.7,4.1);
				DrawTextString("前三种天气分别可以使一整排的单位牌点数降至1。对敌我均");
				MovePen(0.7,3.7);
				DrawTextString("有影响。");
				MovePen(0.7,3.1);
				DrawTextString("      法术牌有两种：号角和灼烧。号角可以使一整排的单位牌");
				MovePen(0.7,2.7);
				DrawTextString("点数翻倍，而灼烧可以使场上任意一张牌点数降低8。");
			break;
			/*case 10:
				SetPenColor("White");
				SetPointSize(30);
				MovePen(gameWidth/2-TextStringWidth("领袖牌")/2,5.5);
				DrawTextString("领袖牌");
				
				SetPointSize(25);
				MovePen(0.7,5);
				DrawTextString("      每个领袖都有一项独特能力，一整局游戏只可发动一次。");
			break;*/
			case 10:
				SetPenColor("Light_Brown");//盖住右箭头 
				StartFilledRegion(1);
				DrawBox(gameWidth-1.5,0.5,1,0.4);
				EndFilledRegion();
				
				SetPenColor("White");
				SetPointSize(30);
				MovePen(gameWidth/2-TextStringWidth("阵营")/2,5.5);
				DrawTextString("阵营");
				
				SetPointSize(25);
				MovePen(0.7,5);
				DrawTextString("      不同阵营有不同效果。");
				MovePen(1.2,4.5);
				DrawTextString("* 北方领域");
				MovePen(1.2,4);
				DrawTextString("* 尼弗迦德帝国");
				MovePen(1.2,3.5);
				DrawTextString("* 松鼠党");
				MovePen(1.2,3);
				DrawTextString("* 怪物");
			break;
		}
	}
	
	registerKeyboardEvent(KeyboardHelpProcess); 
}

void KeyboardHelpProcess(int key,int event)
{
	switch(event)
	{ 
		case KEY_DOWN:
			switch(key)
			{
				case VK_RIGHT:
					if(page<10){
						page++;
						InitializeHelp(); 
					}	
				break; 
				
				case VK_LEFT:
					if(page>1){
						page--;
						InitializeHelp(); 
					}	
				break; 
				
				case VK_BACK:case VK_ESCAPE:
					page=1;
					newhelp=TRUE;
					InitializeOption();
				break;
			}
	}
}
