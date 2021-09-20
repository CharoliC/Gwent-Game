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

		if (cards[10 * j + i - 11].isHero) { //���ֿ�����ɫ 
			SetPenColor("Yellow"); //Ӣ��Ϊ��ɫ 
		}
		else if (cards[10 * j + i - 11].type != 4 && cards[10 * j + i - 11].type != 5) {//�������������� 
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
		sprintf(attack, "%d", cards[10 * j + i - 11].attack);//��attackת�����ַ��� 
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
		DrawTextString("  ������Ϣ");

		if (cards[10 * j + i - 11].isHero) { //���ֿ�����ɫ 
			SetPenColor("Yellow"); //Ӣ��Ϊ��ɫ 
		}
		else if (cards[10 * j + i - 11].type != 4 && cards[10 * j + i - 11].type != 5) {//�������������� 
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
		DrawTextString("����:");
		MovePen(1.1, gameHeight - 5.2);
		char attack[10];
		sprintf(attack, "%d", cards[10 * j + i - 11].attack);//��attackת�����ַ��� 
		DrawTextString(attack);
		MovePen(0.6, gameHeight - 5.4);
		DrawTextString("����:");
		MovePen(1.1, gameHeight - 5.4);
		switch (cards[10 * j + i - 11].type) {
		case 1:DrawTextString("��ս��λ");
			break;
		case 2:DrawTextString("Զ�̵�λ");
			break;
		case 3:DrawTextString("���ǵ�λ");
			break;
		case 4:DrawTextString("����");
			break;
		case 5:DrawTextString("����");
			break;
		}
		MovePen(0.6, gameHeight - 5.6);
		DrawTextString("Ч��:");
		MovePen(1.15, gameHeight - 5.6);
		if (cards[10 * j + i - 11].type <= 3) {
			switch (cards[10 * j + i - 11].isSpecial) {
			case 0:DrawTextString("��");
				break;
			case 1:DrawTextString("��������ڶ���ս�����Ҵ��Լ����������������һ���ơ�");
				break;
			case 2:DrawTextString("���ơ���Ĺ�����ҵ�һ�ŷ�Ӣ���Ʋ����������");
				break;
			case 3:DrawTextString("ͬ��֮�ꡣ�Ա�ÿ��һ��ͬ���Ʊ���һ�����档");
				break;
			case 4:DrawTextString("���ڡ�����˿�ʱ�������������д�����е�ͬ���ơ�");
				break;
			case 5:DrawTextString("ʿ�����ǡ�����е����з�Ӣ���Ƶ�����һ��");
				break;
			}
		}
		else {
			switch (cards[10 * j + i - 11].ID) {
			case 28:case 29:DrawTextString("��������˫���ķ�Ӣ�۽�ս��λ�Ƶ���������1��");
				break;
			case 30:case 31:DrawTextString("��������˫���ķ�Ӣ��Զ�̵�λ�Ƶ���������1��");
				break;
			case 32:case 33:DrawTextString("��������˫���ķ�Ӣ�۹��ǵ�λ�Ƶ���������1��");
				break;
			case 34:case 35:DrawTextString("���������������������Ч����");
				break;
			case 36:case 37:DrawTextString("��������һ�е����е�λ�Ƶ���������ÿ������һ�źŽǣ���");
				break;
			case 38:case 39:case 40:DrawTextString("����������������һ�ſ��Ƶ�������8��");
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


