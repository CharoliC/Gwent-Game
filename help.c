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
		MovePen(gameWidth/2-TextStringWidth("�淨˵��")/2,6.2);
		DrawTextString("�淨˵��");
	}
	
				
	SetPenColor("White");
	SetPointSize(60); 
	MovePen(0.6,0.6);
	DrawTextString("��");
	MovePen(gameWidth-0.6-TextStringWidth("��"),0.6);
	DrawTextString("��");
	
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
	if(lan==0){//Ӣ��help 
		switch(page){
			case 1:
				SetPenColor("Light_Brown");//��ס���ͷ 
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
				SetPenColor("Light_Brown");//��ס�Ҽ�ͷ 
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
		
	}else{//����help 
		switch(page){
			case 1:
				SetPenColor("Light_Brown");//��ס���ͷ 
				StartFilledRegion(1);
				DrawBox(0.5,0.5,1,0.4);
				EndFilledRegion();
				
				SetPenColor("White");
				SetPointSize(30);
				MovePen(gameWidth/2-TextStringWidth("���")/2,5.5);
				DrawTextString("���");
				
				SetPointSize(25);
				MovePen(0.7,5);
				DrawTextString("      ��������һ�ֿ����ļ���ʽ������Ϸ��������Ϸ����");
				MovePen(0.7,4.6);
				DrawTextString("ʦ3�����ԡ���");
				MovePen(0.7,4);
				DrawTextString("      ��������Ϸ��һ��΢����ս�ۣ��������ĶԿ��У����");
				MovePen(0.7,3.6);
				DrawTextString("������ָ�ӹٵĽ�ɫ�������ƾ������µľ��ӡ��ĸ���ͬ��");
				MovePen(0.7,3.2);
				DrawTextString("Ӫ�������ֲ�ͬ��ս�����Ժ��������飬ͨ��ʤ����·ԶԶ");
				MovePen(0.7,2.8);
				DrawTextString("��ֹһ������ÿһ����Ҫ��������Ϸ������һ��һ��������");
				MovePen(0.7,2.4);
				DrawTextString("����˵�������ƶ�������ӹ���ɵ�����ѡ��");
			break;
			case 2:
				SetPenColor("White");
				SetPointSize(30);
				MovePen(gameWidth/2-TextStringWidth("���鹹��")/2,5.5);
				DrawTextString("���鹹��");
				
				SetPointSize(25);
				MovePen(0.7,5);
				DrawTextString("      ���ȣ��ӱ��������ḥ�ȵµ۹������󵳺͹�����ѡ��");
				MovePen(0.7,4.6);
				DrawTextString("֮һ��Ϊ�Լ�����Ӫ����ͬ����Ӫ�в�ͬ�����Ժ����ƣ���");
				MovePen(0.7,4.2);
				DrawTextString("�����鲿�֣���������Ϸ��ʼǰ�����Լ������顣");
			break;
			case 3:
				SetPenColor("White");
				SetPointSize(30);
				MovePen(gameWidth/2-TextStringWidth("ʤ������")/2,5.5);
				DrawTextString("ʤ������");
				
				SetPointSize(25);
				MovePen(0.7,5);
				DrawTextString("      ������ʤ������Ӯ�����ֵ����ȡ��ʤ����");
			break;
			case 4:
				SetPenColor("White");
				SetPointSize(30);
				MovePen(gameWidth/2-TextStringWidth("���־���")/2,5.5);
				DrawTextString("���־���");
				
				SetPointSize(25);
				MovePen(0.7,5);
				DrawTextString("      ��Ϸ��ʽ��ʼ֮ǰ�����Ӧ����һ�ֹ�ƽ�ķ�ʽ������һ");
				MovePen(0.7,4.6);
				DrawTextString("�����ֳ��ƣ�������Ӳ�ҡ�������������Ӫ���Ծ������֡�");
				MovePen(0.7,4);
				DrawTextString("      �ӵڶ��ֿ�ʼ����һ�ֵĻ�ʤ��Ϊ���֡� ");
			break;
			case 5:
				SetPenColor("White");
				SetPointSize(30);
				MovePen(gameWidth/2-TextStringWidth("�������")/2,5.5);
				DrawTextString("�������");
				
				SetPointSize(25);
				MovePen(0.7,5);
				DrawTextString("      һ����Ϸ�У�˫���������ƻ�ʹ�����似�ܣ�һ�غ�ֻ��");
				MovePen(0.7,4.6);
				DrawTextString("��ȡһ���ж���ֱ��һ���޿��ɳ���������ȨΪֹ����ʱ��");
				MovePen(0.7,4.2);
				DrawTextString("�н��㡣��ƽ�֣����ḥ�ȵµ۹���Ӫ�����ʤ����˫����");
				MovePen(0.7,3.8);
				DrawTextString("�ǻ����������˫����ʤ��");
			break;
			case 6:
				SetPenColor("White");
				SetPointSize(30);
				MovePen(gameWidth/2-TextStringWidth("��Ϸ����")/2,5.5);
				DrawTextString("��Ϸ����");
				
				SetPointSize(25);
				MovePen(1.2,5);
				DrawTextString("* ���ơ�");
				MovePen(1.2,4.5);
				DrawTextString("* �������֡�");
				MovePen(1.2,4);
				DrawTextString("* �������ƻ�ʹ�����似�ܡ�");
				MovePen(1.2,3.5);
				DrawTextString("* ˫����Ȩ��");
				SetPenColor("Yellow");
				MovePen(0.7,3);
				DrawTextString("ע�⣺������Ȩ�Ժ�ֱ��������Ϸ�����㶼���ܲ�ȡ�κ�");
				MovePen(1.6,2.65);
				DrawTextString("�ж���");
				SetPenColor("White");
				MovePen(1.2,2.15);
				DrawTextString("* �ظ����Ϲ��̣�ֱ��һ����ʤ���֡�");
			break;
			case 7:
				SetPenColor("White");
				SetPointSize(30);
				MovePen(gameWidth/2-TextStringWidth("��������")/2,5.5);
				DrawTextString("��������");
				
				SetPointSize(25);
				MovePen(0.7,5);
				DrawTextString("      ���ƴ��¿��Է�Ϊ���ࣺ��λ�ƣ������ƺ������ơ�");
			break;
			case 8:
				SetPenColor("White");
				SetPointSize(30);
				MovePen(gameWidth/2-TextStringWidth("��λ��")/2,5.5);
				DrawTextString("��λ��");
				
				SetPointSize(25);
				MovePen(0.7,5);
				DrawTextString("      ��������λ�ò�ͬ����λ�ƿɷ�Ϊ��ս��λ�ơ�Զ�̵�λ");
				MovePen(0.7,4.6);
				DrawTextString("�ƺ͹��ǵ�λ�ơ�ͬһ���͵ĵ�λ�Ʊ��뱻����ͬһ�š���");
				MovePen(0.7,4.2);
				DrawTextString("Ϸ˫����ֻ��3�š�");
				MovePen(0.7,3.6);
				DrawTextString("      ���ݿ���Ч������λ�ƿɷ�Ϊ��ͨ��λ��Ч����λ��Ч");
				MovePen(0.7,3.2);
				DrawTextString("����λ�������⣬��ӵ������Ч���������������ơ�ͬ��");
				MovePen(0.7,2.8);
				DrawTextString("֮�顢���ں�ʿ�����ǡ�");
				MovePen(0.7,2.2);
				DrawTextString("      ���ݿ��Ƽ��𣬵�λ�ƿɷ�Ϊʿ����λ��Ӣ�۵�λ��Ӣ");
				MovePen(0.7,1.8);
				DrawTextString(" Ӣ�۵�λ�����κ����桢����Ч��Ӱ�졣");
			break;
			case 9:
				SetPenColor("White");
				SetPointSize(30);
				MovePen(gameWidth/2-TextStringWidth("������")/2,5.5);
				DrawTextString("������");
				
				SetPointSize(25);
				MovePen(0.7,5);
				DrawTextString("      �����ƿ��Դ��·�Ϊ���ࣺ�����ƺͷ����ơ�");
				MovePen(0.7,4.5);
				DrawTextString("      �����������֣��̹Ǳ�˪������Ũ�������������졣");
				MovePen(0.7,4.1);
				DrawTextString("ǰ���������ֱ����ʹһ���ŵĵ�λ�Ƶ�������1���Ե��Ҿ�");
				MovePen(0.7,3.7);
				DrawTextString("��Ӱ�졣");
				MovePen(0.7,3.1);
				DrawTextString("      �����������֣��ŽǺ����ա��Žǿ���ʹһ���ŵĵ�λ��");
				MovePen(0.7,2.7);
				DrawTextString("���������������տ���ʹ��������һ���Ƶ�������8��");
			break;
			/*case 10:
				SetPenColor("White");
				SetPointSize(30);
				MovePen(gameWidth/2-TextStringWidth("������")/2,5.5);
				DrawTextString("������");
				
				SetPointSize(25);
				MovePen(0.7,5);
				DrawTextString("      ÿ�����䶼��һ�����������һ������Ϸֻ�ɷ���һ�Ρ�");
			break;*/
			case 10:
				SetPenColor("Light_Brown");//��ס�Ҽ�ͷ 
				StartFilledRegion(1);
				DrawBox(gameWidth-1.5,0.5,1,0.4);
				EndFilledRegion();
				
				SetPenColor("White");
				SetPointSize(30);
				MovePen(gameWidth/2-TextStringWidth("��Ӫ")/2,5.5);
				DrawTextString("��Ӫ");
				
				SetPointSize(25);
				MovePen(0.7,5);
				DrawTextString("      ��ͬ��Ӫ�в�ͬЧ����");
				MovePen(1.2,4.5);
				DrawTextString("* ��������");
				MovePen(1.2,4);
				DrawTextString("* �ḥ�ȵµ۹�");
				MovePen(1.2,3.5);
				DrawTextString("* ����");
				MovePen(1.2,3);
				DrawTextString("* ����");
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
