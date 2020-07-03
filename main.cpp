#pragma once
#include "poker_header.h"
extern int survivor;
int Play_number[6] = { 0 }, Computer_number[6] = { 0 }, Play_pattern[6] = { 0 }, Computer_pattern[6] = { 0 };

int main()
{
	int re=1;
	init(); //â ũ��� ���� ���� �Լ�

	Player member[5] = { {"�÷��̾�"}, {"����"},{"����"},{"����"},{"����"} }, dealer; // member[0]�� �÷��̾�
	string Pattern[4] = { "Clover", "Heart", "Diamond", "Spade" };
	string Number[13] = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King","Ace"};

	while (1) {
		introGame(); // ����ȭ���� ǥ�úκ� �Լ�
		int menuNumber = menuChoice(); // �޴� ���� �Լ�
		if (menuNumber == 0) //���� ���� ��ư
		{
			while (1)
			{
				gameImage(member);
				playGame(member, dealer);
				if (member[0].getRetire() == true)
					defeatPrint();
				else 
					re = reGame(member, dealer);
				if (re==3 || (member[1].getRetire() == true && member[2].getRetire() == true && member[3].getRetire() == true && member[4].getRetire() == true))
					victoryPrint();
		
					re = reGame(member, dealer);

				if (re == -1)
					break;
			}
		}
		else if (menuNumber == 1) // ���� ��Ģ ����
		{
			gameRule();
		}
		else if (menuNumber == 2) // ���� ���� ��ư
		{
			return 0;
		}
		setColor(WHITE, BLACK);
		system("cls");
	}
	
	return 0;
}







