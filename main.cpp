#pragma once
#include "poker_header.h"

int Play_number[6] = { 0 }, Computer_number[6] = { 0 }, Play_pattern[6] = { 0 }, Computer_pattern[6] = { 0 };

int main()
{
	init(); //창 크기와 제목 설정 함수

	Player member[5] = { {"플레이어"}, {"진혁"},{"도영"},{"정훈"},{"강민"} }, dealer; // member[0]가 플레이어
	string Pattern[4] = { "Clover", "Heart", "Diamond", "Spade" };
	string Number[13] = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King","Ace"};

	while (1) {
		introGame(); // 시작화면의 표시부분 함수
		int menuNumber = menuChoice(); // 메뉴 선택 함수
		if (menuNumber == 0) //게임 시작 버튼
		{
			gameImage(member);
			playGame(member, dealer);			
		}
		else if (menuNumber == 1) // 게임 규칙 설명
		{
			gameRule();
		}
		else if (menuNumber == 2) // 게임 종료 버튼
		{
			return 0;
		}
		setColor(WHITE, BLACK);
		system("cls");
	}
	
	return 0;
}







