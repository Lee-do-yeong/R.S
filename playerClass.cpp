#include "poker_header.h"

extern int survivor;
extern int top;

player::player() : used(0), gameMoney(50), play(true), die(false)
{
	char* temp;
	temp = new char[20];
	name = temp;
}

ostream& operator<< (ostream& a, const card& thiscard) // 삭제 고려
{
	a << thiscard.pat << thiscard.cardNumber;

	return a;
}

void player::showMoney() // 남은 플레이어 돈 확인
{
	cout << gameMoney << endl;
}

void player::payMoney(int pay, int& totalBet) //첫 의무돈 지불, 콜
{
	if (pay >= gameMoney)
	{
		gameMoney = 0;
		totalBet = totalBet + gameMoney;
		play = false;
	}

	else
	{
		gameMoney = gameMoney - pay;
		totalBet = totalBet + pay;
	}
}

void player::playerDie(int& gambler) 
{
	play = false;
	die = false;
	gambler--;
}

void player::getCard(card newCard1, card newCard2)
{
	cout << "카드 2장 드로우\n"; // 임시
	myCard[0] = newCard1;
	myCard[1] = newCard2;
}

void player::payBet(int betMoney)
{
	gameMoney = gameMoney - betMoney;
}

bool player::checkPlayer()
{
	if (play == true)
		return true;
	else
		return false;
}

void player::takeCard()
{
	cout << "카드 받음\n"; //임시
	myCard[used++] = drawCard();
}

int player::getMoney()
{
	return gameMoney;
}

int player::inputBet(int &totalBet) // 베팅 범위 정해야 함.
{
	int betMoney;
	cin >> betMoney;
	while (betMoney > gameMoney || betMoney < 0)
	{
		cout << "배팅 금액 범위 초과, 다시 입력\n배팅 금액 : ";
		cin >> betMoney;
	}

	totalBet = totalBet + betMoney;
	//gameMoney = gameMoney - betMoney; // 고려

	return betMoney;
}

int player::leaderBet(int &totalMoney,int& gambler)
{
	cout << "리더 배팅 (1: 배팅, 2: 다이)\n";//임시
	int choice, betMoney;
	cin >> choice;

	switch (choice)
	{
	case 1:
		cout << "---------------------배팅---------------------\n";
		cout << "배팅 금액 : "; //임시
		betMoney = inputBet(totalMoney);
		return betMoney;
	case 2:
		cout << "---------------------다 이---------------------\n";
		playerDie(gambler);
		return 0;
	}
}

void player::doubleBet(int& betMoney,int& totalBet)
{
	betMoney = betMoney * 2;
	//gameMoney = gameMoney - betMoney; //고려
	totalBet = totalBet + betMoney;
}

void player::allMoney(int& betMoney, int& totalBet)
{
	totalBet = totalBet - betMoney;
	betMoney = gameMoney;
	gameMoney = 0; //고려
	totalBet = totalBet + betMoney;
	play = false;
}

bool player::canBet(int betMoney) //배팅할 능력이 있는지 판단
{
	if (betMoney > gameMoney)
		return false;
	else
		return true;
}

void player::halfBet(int& betMoney, int& totalBet)
{
	totalBet = totalBet - betMoney;
	betMoney = totalBet / 2;
	//gameMoney = gameMoney - betMoney; //고려
	totalBet = betMoney;
}

void player::dieAllMoney(int& totalBet)
{
	totalBet = totalBet + gameMoney;
	gameMoney = 0; //고려
	play = false;
}

bool player::nowPlay()
{
	return play;
}

bool player::checkSurvivor()
{
	if (die == true)
		return true;
	else
		return false;
}

void player::setName(string setN)
{
	name = setN;
}


string player::getName()
{
	return name;
}

void player::retireGame()
{
	die = true;
	play = false;
	survivor--;
}

void player::returnPlay()
{
	play = true;
}

void player::resetUsed()
{
	used = 0;
}

int player::returnUsed()
{
	return used;
}

void player::call(int& betMoney,int &totalMoney)
{
	totalMoney = totalMoney + betMoney;
}

player::player(string setN) : used(0), gameMoney(50), play(true), die(false)
{
	name = setN;
}