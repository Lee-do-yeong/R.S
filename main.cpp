#pragma once
#include "poker_header.h"

int Play_number[6] = { 0 }, Computer_number[6] = { 0 }, Play_pattern[6] = { 0 }, Computer_pattern[6] = { 0 };

int main()
{
	init(); //â ũ��� ���� ���� �Լ�

	Player member[5] = { {"�÷��̾�"}, {"����"},{"����"},{"����"},{"����"} }, dealer; // member[0]�� �÷��̾�
	string Pattern[4] = { "Clover", "Heart", "Diamond", "Spade" };
	string Number[13] = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King","Ace"};

	while (1) {
		introGame(); // ����ȭ���� ǥ�úκ� �Լ�
		int menuNumber = menuChoice(); // �޴� ���� �Լ�
		if (menuNumber == 0) //���� ���� ��ư
		{
			gameImage(member);
			playGame(member, dealer);			
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







