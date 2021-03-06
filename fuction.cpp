﻿#include "poker_header.h"

void setColor(int back, int text)
{
	HANDLE hcon;

	hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hcon, (back << 4) | text);
}

void init()
{
	system("mode con cols=176 lines=45 | title 텍사스 홀덤 ");
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO ConsoleCursor;
	ConsoleCursor.bVisible = 0;
	ConsoleCursor.dwSize = 1;
	SetConsoleCursorInfo(consoleHandle, &ConsoleCursor);
	system("color F5");
	//setColor(WHITE, GREEN); // 게임화면 만들때 사용..
}

void gotoxy(int x, int y)
{
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void introGame()
{
	setColor(WHITE, BLACK);
	gotoxy(45, 5); cout << "       □□□□□     □□□□□     □      □         □         □□□□□";
	gotoxy(45, 6); cout << "           □         □               □  □         □  □       □        ";
	gotoxy(45, 7); cout << "           □         □□□□□         □         □□□□□       □□□  ";
	gotoxy(45, 8); cout << "           □         □               □  □       □      □             □";
	gotoxy(45, 9); cout << "           □         □□□□□     □      □     □      □     □□□□□";
	gotoxy(45, 10); cout << "																			 ";
	gotoxy(45, 12); cout << " □      □     □□□□□     □             □□□□       □□□□□     □      □";
	gotoxy(45, 13); cout << " □      □     □      □     □             □     □      □             □□  □□";
	gotoxy(45, 14); cout << " □□□□□     □      □     □             □      □     □□□□□     □  □  □";
	gotoxy(45, 15); cout << " □      □     □      □     □             □     □      □             □      □";
	gotoxy(45, 16); cout << " □      □     □□□□□     □□□□□     □□□□       □□□□□     □      □";
	gotoxy(82, 25); cout << "[게임시작]";
	gotoxy(82, 26); cout << "[게임규칙]";
	gotoxy(82, 27); cout << "[게임종료]";
}

int keyControl()
{
	char c;
	while (1) {
		if (_kbhit())
		{
			c = _getch();
			if (c == -32)
			{
				c = _getch();

				if (c == UP)
					return UP;
				else if (c == DOWN)
					return DOWN;
				else if (c == RIGHT)
					return RIGHT;
				else if (c == LEFT)
					return LEFT;
			}
			else if (c == CHOICE)
				return CHOICE;
		}
	}
}

int menuChoice()
{
	int x = 82;
	int y = 25;
	setColor(WHITE, BLACK);
	gotoxy(x - 2, y); cout << "> [게임시작]";
	gotoxy(x, y + 1); cout << "[게임규칙]";
	gotoxy(x, y + 2); cout << "[게임종료]";
	while (1) {
		int n = keyControl();
		switch (n) {
		case UP: {
			if (y > 25) {
				gotoxy(x - 2, y); cout << " ";
				gotoxy(x - 2, --y); cout << ">";
			}
			break;
		}

		case DOWN:
		{
			if (y < 27)
			{
				gotoxy(x - 2, y); cout << " ";
				gotoxy(x - 2, ++y); cout << ">";
			}
			break;
		}

		case CHOICE:
		{
			return y - 25;
		}

		}
	}

}

void gameImage(Player member[])
{
	int x = 67;
	int y = 40;
	system("color 02");
	system("cls");
	setColor(GREEN, GREEN);
	for (int i = 1; i < 35; i++)
	{
		gotoxy(30, i);
		cout << "▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒";
	}
	setColor(WHITE, WHITE);
	for (int i = 0; i < 35; i++)
	{
		gotoxy(29, i); cout << "▒";
		gotoxy(145, i); cout << "▒";
	}
	gotoxy(29, 0);	cout << "▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒";
	gotoxy(29, 35); cout << "▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒";

	player(10, 3,member[2].getMoney());  cout << "도영";
	player(10, 18, member[1].getMoney()); cout << "진혁";
	player(150, 3, member[3].getMoney()); cout << "정훈";
	player(150, 18, member[4].getMoney()); cout << "강민";
	gotoxy(85, 36); cout << "플레이어";
	gotoxy(82, 38); cout << "남은 칩 : " << member[0].getMoney() << endl;

	gotoxy(x, y);  cout << "콜";
	gotoxy(x + 10, y); cout << "다이";
	gotoxy(x + 20, y); cout << "더블";
	gotoxy(x + 30, y); cout << "하프";
	gotoxy(x + 40, y); cout << "올인";

}

void gameRule()
{
	system("cls");
	gotoxy(15, 10); cout << "텍사스 홀덤 간단 요약" << endl;
	gotoxy(15, 10); cout << "1. 플레이어들은 개인별 손패 2장의 카드를 받습니다." << endl;
	gotoxy(15, 11); cout << "2. 모든 플레이어들이 공유하는 커뮤니티 카드 5장이 주어집니다." << endl;
	gotoxy(15, 12); cout << "3. 커뮤니티 카드 5장과 개인별 손패 2장의 카드의 조합이 가장 높은 플레이어가 승리합니다." << endl;
	gotoxy(15, 13); cout << "카드 조합에 대한 자세한 설명은 아래 홈페이지를 참고하시기 바랍니다." << endl;
	gotoxy(15, 14); cout << "https://crash-landing.github.io" << endl;
	while (1)
	{
		if (keyControl() == CHOICE)
		{
			break;
		}
	}
}

void player(int x, int y, int coin) //10 3 이, 10 18 범, 150 3 임, 150 18 김
{
	setColor(BLACK, WHITE);
	gotoxy(x, y - 2); cout << "  남은 칩: " << coin << endl;
	gotoxy(x, y);     cout << "■■■■■■■■\n";
	gotoxy(x, y + 1); cout << "■□□■■□□■\n";
	gotoxy(x, y + 2); cout << "■□□■■□□■\n";
	gotoxy(x, y + 3); cout << "■■■□□■■■\n";
	gotoxy(x, y + 4); cout << "■□■■■■□■\n";
	gotoxy(x, y + 5); cout << "■□□□□□□■\n\n";
	gotoxy(x, y + 6); cout << "■■■■■■■■\n\n";
	gotoxy(x, y + 8); cout << "  참가자: ";
}

void showCoin(int x, int y,int coin)
{
	gotoxy(x, y - 2); cout << "               "<< endl;
	gotoxy(x, y - 2); cout << "  남은 칩: " << coin << endl;
}

int bettingMenuChoice()
{
	
	int x = 67;
	int y = 40;
	setColor(GREEN, WHITE);
	

	setColor(BLACK, WHITE);
	gotoxy(x - 10, y);  cout << "                                                            ";
	gotoxy(x - 2, y);  cout << "> 콜";
	gotoxy(x + 10, y); cout << "다이";
	gotoxy(x + 20, y); cout << "더블";
	gotoxy(x + 30, y); cout << "하프";
	gotoxy(x + 40, y); cout << "올인";
	while (1) {
		int n = keyControl();
		switch (n) {
		case RIGHT:
		{
			if (x < 107)
			{
				gotoxy(x - 2, y); cout << " ";
				x = x + 10;
				gotoxy(x - 2, y); cout << ">";
			}
			break;
		}

		case LEFT:
		{
			if (x > 67)
			{
				gotoxy(x - 2, y); cout << " ";
				x = x - 10;
				gotoxy(x - 2, y); cout << ">";
			}
			break;
		}

		case CHOICE:
		{
			gotoxy(x - 2, y); cout << " ";
			setColor(GREEN, GREEN);

			return x - 50;
		}
		}
	}

}
void bettingPrint(int x) //베팅 문자 출력 
{

	switch (x / 10) {
	case 0:  // 빈 화면
		interInit();
		break;
	case 1: // 콜
		interCall();
		break;

	case 2: // 다이
		interDie();
		break;

	case 3: // 더블
		interDouble();
		break;

	case 4: // 하프
		interHalf();
		break;

	case 5:  // 올인
		interAllin();
	}
	
}

void interInit()
{
	int y = 12;
	setColor(GREEN, GREEN);
	for (int i = y; i < y + 5; i++)
	{
		gotoxy(40, i);
		cout << "▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒";
	}
}

void interCall()
{
	int y = 12;
	setColor(GREEN, WHITE);
	gotoxy(45, y);     cout << "                ■■■■■         ■         ■           ■           ■           ";
	gotoxy(45, y + 1); cout << "                ■               ■  ■       ■           ■           ■           ";
	gotoxy(45, y + 2); cout << "                ■             ■■■■■     ■           ■           ■           ";
	gotoxy(45, y + 3); cout << "                ■             ■      ■     ■           ■                        ";
	gotoxy(45, y + 4); cout << "                ■■■■■     ■      ■     ■■■■     ■■■■     ■           ";
	Sleep(1500);
	interInit();
	setColor(BLACK, WHITE);

}

void interDie()
{
	int y = 12;
	setColor(GREEN, WHITE);
	gotoxy(45, y);     cout << "                       ■■■■         ■■■       ■■■■     ■                   ";
	gotoxy(45, y + 1); cout << "                       ■     ■          ■         ■           ■                   ";
	gotoxy(45, y + 2); cout << "                       ■      ■         ■         ■■■■     ■                   ";
	gotoxy(45, y + 3); cout << "                       ■     ■          ■         ■                                ";
	gotoxy(45, y + 4); cout << "                       ■■■■         ■■■       ■■■■     ■                   ";
	Sleep(1500);
	interInit();
	setColor(BLACK, WHITE);
}

void interDouble()
{
	int y = 12;
	setColor(GREEN, WHITE);
	gotoxy(45, y);     cout << " ■■■■        ■■■■      ■      ■     ■■■■       ■           ■■■■     ■   ";
	gotoxy(45, y + 1); cout << " ■     ■      ■      ■     ■      ■     ■     ■      ■           ■           ■   ";
	gotoxy(45, y + 2); cout << " ■      ■     ■      ■     ■      ■     ■■■■       ■           ■■■■     ■   ";
	gotoxy(45, y + 3); cout << " ■     ■      ■      ■     ■      ■     ■     ■      ■           ■                ";
	gotoxy(45, y + 4); cout << " ■■■■        ■■■■       ■■■■      ■■■■       ■■■■     ■■■■     ■   ";
	Sleep(1500);
	interInit();
	setColor(BLACK, WHITE);
}

void interHalf()
{
	int y = 12;
	setColor(GREEN, WHITE);
	gotoxy(45, y);     cout << "                ■      ■         ■         ■           ■■■■     ■             ";
	gotoxy(45, y + 1); cout << "                ■      ■       ■  ■       ■           ■           ■             ";
	gotoxy(45, y + 2); cout << "                ■■■■■     ■■■■■     ■           ■■■■     ■             ";
	gotoxy(45, y + 3); cout << "                ■      ■     ■      ■     ■           ■                          ";
	gotoxy(45, y + 4); cout << "                ■      ■     ■      ■     ■■■■     ■           ■             ";
	Sleep(1500);
	interInit();
	setColor(BLACK, WHITE);
}

void interAllin()
{
	int y = 12;
	setColor(GREEN, WHITE);
	gotoxy(45, y);     cout << "         ■         ■           ■                ■■■       ■      ■     ■      ";
	gotoxy(45, y + 1); cout << "       ■  ■       ■           ■                  ■         ■■    ■     ■      ";
	gotoxy(45, y + 2); cout << "     ■■■■■     ■           ■                  ■         ■  ■  ■     ■      ";
	gotoxy(45, y + 3); cout << "     ■      ■     ■           ■                  ■         ■    ■■             ";
	gotoxy(45, y + 4); cout << "     ■      ■     ■■■■     ■■■■          ■■■       ■      ■     ■      ";
	Sleep(1500);
	interInit();
	setColor(BLACK, WHITE);
}

void interBetting()
{
	int y = 12;
	setColor(GREEN, WHITE);
	gotoxy(40, y);     cout << " ■■■■       ■■■■     ■■■■■     ■■■■■     ■■■       ■      ■       ■■■       ";
	gotoxy(40, y + 1); cout << " ■     ■      ■               ■             ■           ■         ■■    ■     ■             ";
	gotoxy(40, y + 2); cout << " ■■■■       ■■■■         ■             ■           ■         ■  ■  ■     ■    ■■     ";
	gotoxy(40, y + 3); cout << " ■     ■      ■               ■             ■           ■         ■    ■■     ■      ■     ";
	gotoxy(40, y + 4); cout << " ■■■■       ■■■■         ■             ■         ■■■       ■      ■       ■■■■     ";
	Sleep(1500);
	interInit();
	setColor(BLACK, WHITE);
}

int bettingNumber()
{
	int x = bettingMenuChoice(); // 베팅메뉴 선택 함수

	return x / 10;
}

void victoryPrint()
{
	Sleep(14000);
	setColor(WHITE, BLACK);
	system("cls");
	gotoxy(40, 17); cout << " ■        ■     ■■■     ■■■■■     ■■■■■      ■■■■      ■■■■      ■    ■     ";
	gotoxy(40, 18); cout << "  ■      ■        ■       ■                 ■         ■      ■     ■     ■      ■  ■      ";
	gotoxy(40, 19); cout << "   ■    ■         ■       ■                 ■         ■      ■     ■■■■         ■        ";
	gotoxy(40, 20); cout << "    ■  ■          ■       ■                 ■         ■      ■     ■   ■          ■        ";
	gotoxy(40, 21); cout << "      ■          ■■■     ■■■■■         ■          ■■■■      ■     ■        ■        ";
	gotoxy(0, 40);
	exit(1);
}

void defeatPrint()
{
	Sleep(14000);
	setColor(WHITE, BLACK);
	system("cls");
	gotoxy(40, 17); cout << "      ■■■■       ■■■■     ■■■■     ■■■■         ■         ■■■■■     ";
	gotoxy(40, 18); cout << "      ■     ■      ■           ■           ■             ■  ■           ■         ";
	gotoxy(40, 19); cout << "      ■      ■     ■■■■     ■■■■     ■■■■     ■■■■■         ■         ";
	gotoxy(40, 20); cout << "      ■     ■      ■           ■           ■           ■      ■         ■         ";
	gotoxy(40, 21); cout << "      ■■■■       ■■■■     ■           ■■■■     ■      ■         ■         ";
	gotoxy(0, 40);
	exit(1);
}

void picture(card dealerCard[],Player member[])
{
	setColor(GREEN, WHITE);
	int shape[5] = { 0,1,2,3,4 }; //null, spade, diamond, heart, cluber
	int number[14] = { 0,2,3,4,5,6,7,8,9,10,11,12,13,1 }; //null, 2~10, jack, queen, king, ace
	int x = 100, y = 14;
	int i, j, v = 1, hide = 0;		//hide 0 숨김, 1 표시
	int get = 4;
	int num1 = 0, num2 = 0;



	for (i = 0; i < 4; i++) // 카드가 나열되는 그래픽
	{
		num1 = 0;
		for (j = 0; j < 15; j++)
		{
			Sleep(10);
			gotoxy(x - num1, 14); cout << "┏━━━━━━┓";
			gotoxy(x - num1, 15); cout << "┃?     ┃";
			gotoxy(x - num1, 16); cout << "┃      ┃";
			gotoxy(x - num1, 17); cout << "┃   ?  ┃";
			gotoxy(x - num1, 18); cout << "┃      ┃";
			gotoxy(x - num1, 19); cout << "┃     ?┃";
			gotoxy(x - num1, 20); cout << "┗━━━━━━┛";
			num1 += 1;
		}
		x += 2;
	}
	num1 = 0;
	for (i = 0; i < 15; i++) // 카드가 배분되는 그래픽
	{
		num1 = 1;
		if (i % 2 == 1)
		{
			num1 *= -1;
		}
		for (j = 0; j < 7; j++)
		{
			Sleep(20);
			if (i % 2 == 0)
			{
				gotoxy(80 - num2, 21 - num1); cout << "          ";
			}
			gotoxy(80 - num2, 14 - num1); cout << "┏━━━━━━┓";
			gotoxy(80 - num2, 15 - num1); cout << "┃?     ┃";
			gotoxy(80 - num2, 16 - num1); cout << "┃      ┃";
			gotoxy(80 - num2, 17 - num1); cout << "┃   ?  ┃";
			gotoxy(80 - num2, 18 - num1); cout << "┃      ┃";
			gotoxy(80 - num2, 19 - num1); cout << "┃     ?┃";
			gotoxy(80 - num2, 20 - num1); cout << "┗━━━━━━┛";
			if (i % 2 == 1)
			{
				gotoxy(80 - num2, 13 - num1); cout << "          ";
			}
			if (i % 2 == 0)
				num1 += 1;
			else
				num1 -= 1;
		}
		num2 += 2;
	}
	system("cls");
	gameImage(member);
}

void showDealerCard(card dealerCard[],int &num1,int &j,Player member[]) // int get =4, num1 =0, int j=0
{
		int shape[4] = { 0,1,2,3}; //null, spade, diamond, heart, cluber
		int number[13] = {2,3,4,5,6,7,8,9,10,11,12,13,1}; //null, 2~10, jack, queen, king, ace
		setColor(GREEN, WHITE);
		if(member[2].getRetire()==false)
			playerCard(35, 3);
		if (member[3].getRetire() == false)
			playerCard(125, 3);
		if (member[1].getRetire() == false)
			playerCard(35, 18);
		if (member[4].getRetire() == false)
			playerCard(125, 18);
		PrintMCard(80, 25, member[0].getCard());
		Sleep(1000);
		setColor(GREEN, WHITE);

		gotoxy(60 + num1, 3); cout << "┏━━━━━━┓";
		gotoxy(60 + num1, 4); cout << "┃      ┃";
		gotoxy(60 + num1, 5); cout << "┃      ┃";
		gotoxy(60 + num1, 6); cout << "┃      ┃";
		gotoxy(60 + num1, 7); cout << "┃      ┃";
		gotoxy(60 + num1, 8); cout << "┃      ┃";
		gotoxy(60 + num1, 9); cout << "┗━━━━━━┛";
		//					if(hide != 1){
		if (shape[dealerCard[j].getS()] == 3) {
				setColor(GREEN, BLACK);
				gotoxy(62 + num1, 4); cout << "♠";
				gotoxy(65 + num1, 8); cout << "♠";
		}
		else if (shape[dealerCard[j].getS()] == 2) {
			setColor(GREEN, RED);
			gotoxy(62 + num1, 4); cout << "◆";
			gotoxy(65 + num1, 8); cout << "◆";
		}
		else if (shape[dealerCard[j].getS()] == 1) {
			setColor(GREEN, RED);
			gotoxy(62 + num1, 4); cout << "♥";
			gotoxy(65 + num1, 8); cout << "♥";
		}
		else if (shape[dealerCard[j].getS()] == 0) {
			setColor(GREEN, BLACK);
			gotoxy(62 + num1, 4); cout << "♣";
			gotoxy(65 + num1, 8); cout << "♣";
		}
		if (number[dealerCard[j].getR()] == 1) {
			gotoxy(64 + num1, 6); cout << "A";
		}
		else if (number[dealerCard[j].getR()] == 11) {
			gotoxy(64 + num1, 6); cout << "J";
		}
		else if (number[dealerCard[j].getR()] == 12) {
			gotoxy(64 + num1, 6); cout << "Q";
		}
		else if (number[dealerCard[j].getR()] == 13) {
			gotoxy(64 + num1, 6); cout << "K";
		}
		else {
			gotoxy(64 + num1, 6); cout << number[dealerCard[j].getR()];
		}

		num1 += 12;
		j++;			//배열을 1칸씩 증가 시킨다.
}

void playerCard(int x, int y)
{
	gotoxy(x, y);     cout << "┏━━━━━━┓┏━━━━━━┓";
	gotoxy(x, y + 1); cout << "┃      ┃┃      ┃";
	gotoxy(x, y + 2); cout << "┃      ┃┃      ┃";
	gotoxy(x, y + 3); cout << "┃      ┃┃      ┃";
	gotoxy(x, y + 4); cout << "┃      ┃┃      ┃";
	gotoxy(x, y + 5); cout << "┃      ┃┃      ┃";
	gotoxy(x, y + 6); cout << "┗━━━━━━┛┗━━━━━━┛";
}

void printOrder(int result) //
{
	switch (result)
	{
	case 1:
		cout << "하이카드\n";
		break;
	case 2:
		cout << "원페어\n";
		break;
	case 3:
		cout << "투페어\n";
		break;
	case 4:
		cout << "트리플\n";
		break;
	case 5:
		cout << "스트레이트\n";
		break;
	case 6:
		cout << "플러쉬\n";
		break;
	case 7:
		cout << "풀하우스\n";
		break;
	case 8:
		cout << "포카드\n";
		break;
	case 9:
		cout << "스트레이트 플러시\n";
		break;
	}
}


int choice_betting(int &betMoney)
{
	int choice;
	setColor(GREEN, WHITE);

	choice = bettingLeaderChoice();
	betting_coin(choice,betMoney);
		gotoxy(79, 12);
		cout << "                      ";

	return choice;
}

int choice_betting2(int &betMoney)
{
	int choice;
	setColor(GREEN, WHITE);

	choice = bettingCantChoice();
	betting_coin2(choice,betMoney);


	return choice;
}

void betting_coin(int x,int &betMoney) //배팅 다이
{
	if (x == 1) {
		setColor(GREEN, GREEN);
		for (int i = 20; i < 24; i++)
		{
			
			gotoxy(60, i);
			cout << "▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒";
		}
		setColor(GREEN, WHITE);
		gotoxy(80, 12);
		cout << "금액 입력 : ";
		cin >> betMoney;
	}
	else if (x == 2) {
		setColor(GREEN, GREEN);
		for (int i = 20; i < 24; i++)
		{
			gotoxy(60, i);
			cout << "▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒";
		}
	}
	else
	{
	
		setColor(GREEN, GREEN);
		for (int i = 20; i < 24; i++)
		{
			gotoxy(60, i);
			cout << "▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒";
		}
	}
}

void betting_coin2(int x,int& betMoney) //올인 다이
{
	if (x == 1) {
		interAllin();
		setColor(GREEN, GREEN);
		for (int i = 20; i < 24; i++)
		{
			gotoxy(60, i);
			cout << "▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒";
		}
	}

	else
	{
		interDie();
		setColor(GREEN, GREEN);
		for (int i = 20; i < 24; i++)
		{
			gotoxy(60, i);
			cout << "▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒";
		}
	}
}

void betting_all(const int betMoney,const int totalBet) // 판돈 필드에 작성
{
	setColor(GREEN, WHITE);
	gotoxy(40, 29); cout << "                     " ;
	gotoxy(40, 30); cout << "                     " ;

	gotoxy(40, 29); cout << "총 베팅금액 :" << totalBet;
	gotoxy(40, 30); cout << "현재 베팅금액 :" << betMoney;
}

void nowPlayName(string name)
{
	gotoxy(120, 30);
	setColor(GREEN, WHITE);
	cout << "                         ";
	gotoxy(120, 30);
	cout << "<현재 차례 : " << name << ">";
}

void showObli()
{
	setColor(GREEN, WHITE);
	gotoxy(80, 12); cout << "의무 배팅 진행 중." ;
	gotoxy(80, 13); cout << " 의무 배팅 : 3 칩";
	Sleep(500);
	gotoxy(80, 12); cout << "                     ";
	gotoxy(80, 12); cout << "의무 배팅 진행 중..";
	Sleep(500);
	gotoxy(80, 12); cout << "                     ";
	gotoxy(80, 12); cout << "의무 배팅 진행 중...";
	Sleep(500);
	gotoxy(80, 12); cout << "                     ";
	gotoxy(80, 12); cout << "의무 배팅 진행 중.";
	Sleep(500);
	gotoxy(80, 12); cout << "                     ";
	gotoxy(80, 12); cout << "의무 배팅 진행 중..";
	Sleep(500);
	gotoxy(80, 12); cout << "                     ";
	gotoxy(80, 12); cout << "의무 배팅 진행 중...";
	Sleep(500);
	gotoxy(80, 12); cout << "                     ";
	gotoxy(80, 13); cout << "                     ";
}

void showSentence(string a,int x,int y)//80 12
{
	setColor(GREEN, WHITE);
	gotoxy(x, y); cout << "                                                              ";
	gotoxy(x, y); cout << a;
	Sleep(1700);
	gotoxy(x, y); cout << "                                                              ";
}

int bettingLeaderChoice()
{
	setColor(BLACK, WHITE);
	int x = 67;
	int y = 40; 
	int temp = 1;
	gotoxy(x - 2, y);  cout << "                                                         ";
	gotoxy(x + 8, y); cout << "> 배팅";
	gotoxy(x + 20, y); cout << "올인";
	gotoxy(x + 30, y); cout << "다이";
	x = 77;
	while (1) {
		int n = keyControl();
		switch (n) {
		case RIGHT:
		{
			if (x < 97)
			{
				gotoxy(x - 2, y); cout << " ";
				x = x + 10;
				gotoxy(x - 2, y); cout << ">";
			}
			break;
		}

		case LEFT:
		{
			if (x > 77)
			{
				gotoxy(x - 2, y); cout << " ";
				x = x - 10;
				gotoxy(x - 2, y); cout << ">";
			}
			break;
		}

		case CHOICE:
		{
			gotoxy(x - 2, y); cout << " ";
			if (x == 77)
				temp = 1;
			else if (x == 87)
				temp = 2;
			else
				temp = 3;
			return temp;
		}
		}
	}

}

void checkStatus(Player member[],int &gambler)
{
	setColor(BLACK, WHITE);
	for (int i = 0; i < 5; i++)
	{
		if (member[i].getMoney() == 0)
		{
			if (member[i].checkPlayer() == true)
			{
				member[i].zeroMoney();
				gambler--;
			}
		}
		if (member[i].getRetire() == true)
		{
			switch (i)
			{
			case 0:
				break;
			case 1: //진혁
				gotoxy(12, 27);
				cout << "            ";
				gotoxy(12, 27);
				cout << "[ 게임 오버 ]";
				break;
			case 2: //도영
				gotoxy(12, 12);
				cout << "            ";
				gotoxy(12, 12);
				cout << "[ 게임 오버 ]";
				break;
			case 3: // 정훈
				gotoxy(152, 12);
				cout << "            ";
				gotoxy(152, 12);
				cout << "[ 게임 오버 ]";
				break;
			case 4: // 강민
				gotoxy(152, 27);
				cout << "           ";
				gotoxy(152, 27);
				cout << "[ 게임 오버 ]";
			}
		}
		else if(member[i].checkSurvivor() == true)
		{
			switch (i)
			{
			case 0:
				gotoxy(85, 42);
				cout << "           ";
				gotoxy(85, 42);
				cout << "[ 다 이 ]";
				break;
			case 1: //진혁
				gotoxy(14, 27);
				cout << "           ";
				gotoxy(14, 27);
				cout << "[ 다 이 ]";
				break;
			case 2: //도영
				gotoxy(14, 12);
				cout << "            ";
				gotoxy(14, 12);
				cout << "[ 다 이 ]";
				break;
			case 3: // 정훈
				gotoxy(154, 12);
				cout << "            ";
				gotoxy(154, 12);
				cout << "[ 다 이 ]";
				break;
			case 4: // 강민
				gotoxy(154, 27);
				cout << "            ";
				gotoxy(154, 27);
				cout << "[ 다 이]";
			}
		}
		else if (member[i].checkPlayer() == false)
		{
			switch (i)
			{
			case 0:
				gotoxy(83, 42);
				cout << "           ";
				gotoxy(83, 42);
				cout << "[ 베팅 불가 ]";
				break;
			case 1: //진혁
				gotoxy(12, 27);
				cout << "           ";
				gotoxy(12, 27);
				cout << "[ 베팅 불가 ]";
				break;
			case 2: //도영
				gotoxy(12, 12);
				cout << "            ";
				gotoxy(12, 12);
				cout << "[ 베팅 불가 ]";
				break;
			case 3: // 정훈
				gotoxy(152, 12);
				cout << "            ";
				gotoxy(152, 12);
				cout << "[ 베팅 불가 ]";
				break;
			case 4: // 강민
				gotoxy(152, 27);
				cout << "            ";
				gotoxy(152, 27);
				cout << "[ 베팅 불가 ]";
			}
		}
		else
		{
			switch (i)
			{
			case 0:
				gotoxy(83, 42);
				cout << "            ";
				break;
			case 1: //진혁
				gotoxy(12, 27);
				cout << "            ";
				break;
			case 2: //도영
				gotoxy(12, 12);
				cout << "            ";
				break;
			case 3: // 정훈
				gotoxy(152, 12);
				cout << "            ";
				break;
			case 4: // 강민
				gotoxy(152, 27);
				cout << "            ";
			}
		}
	}
}

void printAll(Player member[])//80 25 플레이어
{
	
	for (int i = 0; i < 5 && member[i].getRetire()==false; i++) 
	{
		switch (i)
		{
		case 1:
			if(member[i].getRetire()==false)
				PrintMCard(35, 18, member[i].getCard());//진혁
			break;
		case 2:
			if (member[i].getRetire() == false)
				PrintMCard(35, 3, member[i].getCard()); //도영
			break;
		case 3:
			if (member[i].getRetire() == false)
				PrintMCard(125, 3, member[i].getCard());//정훈
			break;
		case 4:
			if (member[i].getRetire() == false)
				PrintMCard(125, 18, member[i].getCard());//강민
		}
	}
}


void PrintMCard(int x, int y, card playerCard[])
{
	setColor(GREEN, WHITE);
	int shape[4] = { 0,1,2,3}; //null, spade, diamond, heart, cluber
	int number[13] = {2,3,4,5,6,7,8,9,10,11,12,13,1 }; //null, 2~10, jack, queen, king, ace
	int num1 = 0;
	int j = 0;
	setColor(GREEN, WHITE);
	gotoxy(x, y);     cout << "┏━━━━━━┓┏━━━━━━┓";
	gotoxy(x, y + 1); cout << "┃      ┃┃      ┃";
	gotoxy(x, y + 2); cout << "┃      ┃┃      ┃";
	gotoxy(x, y + 3); cout << "┃      ┃┃      ┃";
	gotoxy(x, y + 4); cout << "┃      ┃┃      ┃";
	gotoxy(x, y + 5); cout << "┃      ┃┃      ┃";
	gotoxy(x, y + 6); cout << "┗━━━━━━┛┗━━━━━━┛";
	for (int i = 0; i < 2; i++)
	{
		//					if(hide != 1){
		if (shape[playerCard[j].getS()] == 3) {
			setColor(GREEN, BLACK);
			gotoxy(x + 2 + num1, y + 1); cout << "♠";
			gotoxy(x + 5 + num1, y + 5); cout << "♠";
		}
		else if (shape[playerCard[j].getS()] == 2) {
			setColor(GREEN, RED);
			gotoxy(x + 2 + num1, y + 1); cout << "◆";
			gotoxy(x + 5 + num1, y + 5); cout << "◆";
		}
		else if (shape[playerCard[j].getS()] == 1) {
			setColor(GREEN, RED);
			gotoxy(x + 2 + num1, y + 1); cout << "♥";
			gotoxy(x + 5 + num1, y + 5); cout << "♥";
		}
		else if (shape[playerCard[j].getS()] == 0) {
			setColor(GREEN, BLACK);
			gotoxy(x + 2 + num1, y + 1); cout << "♣";
			gotoxy(x + 5 + num1, y + 5); cout << "♣";
		}
		if (number[playerCard[j].getR()] == 1) {
			gotoxy(x + 4 + num1, y + 3); cout << "A";
		}
		else if (number[playerCard[j].getR()] == 11) {
			gotoxy(x + 4 + num1, y + 3); cout << "J";
		}
		else if (number[playerCard[j].getR()] == 12) {
			gotoxy(x + 4 + num1, y + 3); cout << "Q";
		}
		else if (number[playerCard[j].getR()] == 13) {
			gotoxy(x + 4 + num1, y + 3); cout << "K";
		}
		else {
			gotoxy(x + 4 + num1, y + 3); cout << number[playerCard[j].getR()];
		}
		//					}
		num1 += 8;
		j++;			//배열을 1칸씩 증가 시킨다.

	}
}

void Print_result(Player &winner,Player &dealer)
{
	string Play_name[5] = { "플레이어", "진혁", "도영", "정훈" , "강민" };
	setColor(GREEN, WHITE);
	int x = 80, y = 15;
	gotoxy(x, y );     cout << winner.getName()<< " : "; printOrder(Cpedigree_check(winner,dealer.getCard(),winner.getCard()));
	gotoxy(x, y + 2); cout << "승자는 " << winner.getName() << "입니다.";
}

int bettingCantChoice()
{
	setColor(BLACK, WHITE);
	int x = 65;
	int y = 40;
	int temp = 1;
	gotoxy(x - 2, y);  cout << "                                                         ";
	gotoxy(x + 8, y); cout << "> 올인";
	gotoxy(x + 35, y); cout << "다이";
	x = 75;
	while (1) {
		int n = keyControl();
		switch (n) {
		case RIGHT:
		{
			if (x < 95)
			{
				gotoxy(x - 2, y); cout << " ";
				x = x + 25;
				gotoxy(x - 2, y); cout << ">";
			}
			temp = 2;
			break;
		}

		case LEFT:
		{
			if (x > 75)
			{
				gotoxy(x - 2, y); cout << " ";
				x = x - 25;
				gotoxy(x - 2, y); cout << ">";
			}
			temp = 1;
			break;
		}

		case CHOICE:
		{
			gotoxy(x - 2, y); cout << " ";
			return temp;
		}
		}
	}

}

//84 12

void computaTurn(Player member[],int nowBet)
{
	setColor(GREEN, WHITE);
	gotoxy(79, 13);
	cout << "                       ";
	gotoxy(79, 13);
	cout << member[nowBet].getName()<<"의 턴 진행중.";
	Sleep(550);
	cout << "                       ";
	gotoxy(79, 13);
	cout << member[nowBet].getName() << "의 턴 진행중..";
	Sleep(550);
	cout << "                       ";
	gotoxy(79, 13);
	cout << member[nowBet].getName() << "의 턴 진행중...";
	Sleep(550);
	gotoxy(79, 13);
	cout << "                       ";
	gotoxy(79, 13);
	cout << member[nowBet].getName() << "의 턴 진행중.";
	Sleep(550);
	cout << "                       ";
	gotoxy(79, 13);
	cout << member[nowBet].getName() << "의 턴 진행중..";
	Sleep(550);
	cout << "                       ";
	gotoxy(79, 13);
	cout << member[nowBet].getName() << "의 턴 진행중...";
	Sleep(550);
	gotoxy(79, 13);
	cout << "                       ";
}