#include"Gwent.h"

void DrawIntroduction(int i,int j){
	extern int lan;
	if (lan == 0) {
		StartFilledRegion(1);
		SetPenColor("Light_Brown");
		DrawBox(0.5, 0.5, gameWidth - 4.1, gameHeight - 5);
		EndFilledRegion();
		SetPenColor("White");
		DrawBox(0.5, 0.5, gameWidth - 4.1, gameHeight - 5);
		MovePen(0.5, gameHeight - 4.8);
		DrawLine(gameWidth - 4.1, 0);
		MovePen(0.5, gameHeight - 4.7);
		SetPointSize(10);
		DrawTextString("  The Introduction of Selected Card");

		if (cards[10 * j + i - 11].isHero) { //区分卡牌颜色 
			SetPenColor("Yellow"); //英雄为金色 
		}
		else if (cards[10 * j + i - 11].type != 4 && cards[10 * j + i - 11].type != 5) {//非天气、法术牌 
			switch (cards[10 * j + i - 11].isSpecial) {
			case 1:SetPenColor("Violet");
				break;
			case 2:SetPenColor("Green");
				break;
			default:SetPenColor("White");
				break;
			}
		}
		else {
			SetPenColor("Light_Blue");
		}
		SetPointSize(18);
		MovePen(0.6, gameHeight - 5);
		DrawTextString(cards[10 * j + i - 11].ename);
		SetPenColor("White");
		SetPointSize(15);
		MovePen(0.6, gameHeight - 5.2);
		DrawTextString("Attack:");
		MovePen(1.1, gameHeight - 5.2);
		char attack[10];
		sprintf(attack, "%d", cards[10 * j + i - 11].attack);//将attack转移入字符串 
		DrawTextString(attack);
		MovePen(0.6, gameHeight - 5.4);
		DrawTextString("Type:");
		MovePen(1.1, gameHeight - 5.4);
		switch (cards[10 * j + i - 11].type) {
		case 1:DrawTextString("Close Combat");
			break;
		case 2:DrawTextString("Ranged");
			break;
		case 3:DrawTextString("Siege");
			break;
		case 4:DrawTextString("Weather");
			break;
		case 5:DrawTextString("Spell");
			break;
		}
		MovePen(0.6, gameHeight - 5.6);
		DrawTextString("Effect:");
		MovePen(1.15, gameHeight - 5.6);
		if (cards[10 * j + i - 11].type <= 3) {
			switch (cards[10 * j + i - 11].isSpecial) {
			case 0:DrawTextString("None");
				break;
			case 1:DrawTextString("Spy. Place on your opponent's field and play 1 cards from your deck instantly.");
				break;
			case 2:DrawTextString("Medic. Find one card from your discard pile and play it instantly.");
				break;
			case 3:DrawTextString("Tight Bond. Strength double when placed beside a same-named card.");
				break;
			case 4:DrawTextString("Muster. Find all the same-named cards in your deck and play them.");
				break;
			case 5:DrawTextString("Morale Boost. Adds+1 to all units in the row ( excluding itself ) .");
				break;
			}
		}
		else {
			switch (cards[10 * j + i - 11].ID) {
			case 28:case 29:DrawTextString("Weather. Sets the strength of all close combat cards to 1 for both players.");
				break;
			case 30:case 31:DrawTextString("Weather. Sets the strength of all ranged combat cards to 1 for both players.");
				break;
			case 32:case 33:DrawTextString("Weather. Sets the strength of all siege combat cards to 1 for both players.");
				break;
			case 34:case 35:DrawTextString("Weather. Removes all weather cards. ");
				break;
			case 36:case 37:DrawTextString("Spell. Doubles the strength of all unit cards in that row.Limited to 1 per row.");
				break;
			case 38:case 39:case 40:DrawTextString("Spell. Make an arbitrary unit's attack reduce by 8.");
				break;
			}
		}
		SetPointSize(12);
		SetPenColor("White");
		MovePen(0.6, gameHeight - 6.2);
		DrawTextString(intro[20 * j + 2 * i - 22].x);
		MovePen(0.6, gameHeight - 6.4);
		DrawTextString(intro[20 * j + 2 * i - 21].x);
	}
	else {
		StartFilledRegion(1);
		SetPenColor("Light_Brown");
		DrawBox(0.5, 0.5, gameWidth - 4.1, gameHeight - 5);
		EndFilledRegion();
		SetPenColor("White");
		DrawBox(0.5, 0.5, gameWidth - 4.1, gameHeight - 5);
		MovePen(0.5, gameHeight - 4.8);
		DrawLine(gameWidth - 4.1, 0);
		MovePen(0.5, gameHeight - 4.7);
		SetPointSize(10);
		DrawTextString("  卡牌信息");

		if (cards[10 * j + i - 11].isHero) { //区分卡牌颜色 
			SetPenColor("Yellow"); //英雄为金色 
		}
		else if (cards[10 * j + i - 11].type != 4 && cards[10 * j + i - 11].type != 5) {//非天气、法术牌 
			switch (cards[10 * j + i - 11].isSpecial) {
			case 1:SetPenColor("Violet");
				break;
			case 2:SetPenColor("Green");
				break;
			default:SetPenColor("White");
				break;
			}
		}
		else {
			SetPenColor("Light_Blue");
		}
		SetPointSize(18);
		MovePen(0.6, gameHeight - 5);
		DrawTextString(cards[10 * j + i - 11].cname);
		SetPenColor("White");
		SetPointSize(15);
		MovePen(0.6, gameHeight - 5.2);
		DrawTextString("点数:");
		MovePen(1.1, gameHeight - 5.2);
		char attack[10];
		sprintf(attack, "%d", cards[10 * j + i - 11].attack);//将attack转移入字符串 
		DrawTextString(attack);
		MovePen(0.6, gameHeight - 5.4);
		DrawTextString("类型:");
		MovePen(1.1, gameHeight - 5.4);
		switch (cards[10 * j + i - 11].type) {
		case 1:DrawTextString("近战单位");
			break;
		case 2:DrawTextString("远程单位");
			break;
		case 3:DrawTextString("攻城单位");
			break;
		case 4:DrawTextString("天气");
			break;
		case 5:DrawTextString("法术");
			break;
		}
		MovePen(0.6, gameHeight - 5.6);
		DrawTextString("效果:");
		MovePen(1.15, gameHeight - 5.6);
		if (cards[10 * j + i - 11].type <= 3) {
			switch (cards[10 * j + i - 11].isSpecial) {
			case 0:DrawTextString("无");
				break;
			case 1:DrawTextString("间谍。置于对手战场并且从自己的牌组中立即打出一张牌。");
				break;
			case 2:DrawTextString("治疗。从墓地中找到一张非英雄牌并立即打出。");
				break;
			case 3:DrawTextString("同袍之谊。旁边每有一张同名牌便获得一倍增益。");
				break;
			case 4:DrawTextString("聚众。打出此卡时，立即从牌组中打出所有的同名牌。");
				break;
			case 5:DrawTextString("士气高涨。令此行的所有非英雄牌点数加一。");
				break;
			}
		}
		else {
			switch (cards[10 * j + i - 11].ID) {
			case 28:case 29:DrawTextString("天气。将双方的非英雄近战单位牌点数均降至1。");
				break;
			case 30:case 31:DrawTextString("天气。将双方的非英雄远程单位牌点数均降至1。");
				break;
			case 32:case 33:DrawTextString("天气。将双方的非英雄攻城单位牌点数均降至1。");
				break;
			case 34:case 35:DrawTextString("天气。清除场上所有天气效果。");
				break;
			case 36:case 37:DrawTextString("法术。让一行的所有单位牌点数翻倍（每行至多一张号角）。");
				break;
			case 38:case 39:case 40:DrawTextString("法术。将场上任意一张卡牌点数减少8。");
				break;
			}
		}
		SetPointSize(12);
		SetPenColor("White");
		MovePen(0.6, gameHeight - 6.2);
		DrawTextString(intro[20 * j + 2 * i - 22].x);
		MovePen(0.6, gameHeight - 6.4);
		DrawTextString(intro[20 * j + 2 * i - 21].x);
	}
	
}


