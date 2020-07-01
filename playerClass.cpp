#include "poker_header.h"

extern int survivor;
extern int top;

Player::Player() : used(0), gameMoney(50), play(true), die(false)
{
	char* temp;
	temp = new char[20];
	name = temp;
}



void Player::showMoney() // 남은 플레이어 돈 확인
{
	cout << gameMoney << endl;
}

void Player::payMoney(int pay, int& totalBet) //첫 의무돈 지불, 콜
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

void Player::playerDie(int& gambler,int dieMoney) 
{
	gameMoney = gameMoney - dieMoney;
	play = false;
	die = false;
	gambler--;
}

void Player::payBet(int betMoney)
{
	gameMoney = gameMoney - betMoney;
}

bool Player::checkPlayer()
{
	if (play == true)
		return true;
	else
		return false;
}

int Player::getMoney()
{
	return gameMoney;
}

void Player::inputBet(int &totalBet,int& betMoney) // 베팅 범위 정해야 함.
{
	totalBet = totalBet + betMoney;
	//gameMoney = gameMoney - betMoney; // 고려
}

void Player::leaderBet(int &totalMoney,int& gambler,int dieMoney,int &betMoney) //85 36
{
	int choice = 0;

	choice = choice_betting(betMoney);
	switch (choice)
	{
	case 1:
		inputBet(totalMoney,betMoney);
		break;
	case 2:
		interDie();
		playerDie(gambler,dieMoney);
		betMoney = 0;
	}
	gotoxy(83, 12);
}

void Player::doubleBet(int& betMoney,int& totalBet)
{
	betMoney = betMoney * 2;
	//gameMoney = gameMoney - betMoney; //고려
	totalBet = totalBet + betMoney;
}

void Player::allMoney(int& betMoney, int& totalBet)
{
	totalBet = totalBet - betMoney;
	betMoney = gameMoney;
	gameMoney = 0; //고려
	totalBet = totalBet + betMoney;
	play = false;
}

bool Player::canBet(int betMoney) //배팅할 능력이 있는지 판단
{
	if (betMoney > gameMoney)
		return false;
	else
		return true;
}

void Player::halfBet(int& betMoney, int& totalBet)
{
	totalBet = totalBet - betMoney;
	betMoney = totalBet / 2;
	//gameMoney = gameMoney - betMoney; //고려
	totalBet = betMoney;
}

void Player::dieAllMoney(int& totalBet)
{
	totalBet = totalBet + gameMoney;
	gameMoney = 0; //고려
	play = false;
}

bool Player::nowPlay()
{
	return play;
}

bool Player::checkSurvivor()
{
	if (die == true)
		return true;
	else
		return false;
}


string Player::getName()
{
	return name;
}

void Player::retireGame()
{
	die = true;
	play = false;
	survivor--;
}

void Player::returnPlay()
{
	play = true;
}

void Player::resetUsed()
{
	used = 0;
}

int Player::returnUsed()
{
	return used;
}

void Player::call(int& betMoney,int &totalMoney)
{
	totalMoney = totalMoney + betMoney;
}

Player::Player(string setN) : used(0), gameMoney(50), play(true), die(false)
{
	name = setN;
}

void Player::setCardSR(int R, int S, int now)
{
		myCard[now].setSR(S, R);
	//	cout << myCard[0].getR() << " " << myCard[0].getS() << " " << myCard[1].getR() << " " << myCard[1].getS() << " \n";
}
void Player::setMax(int maxP, int maxN)
{
	maxPattern = maxP;
	maxNumber = maxN;
}

card* Player::getCard()
{
	return myCard;
}

int Player::numGetCard(int num)
{
	return myCard[num].getR();
}

int Player::patGetCard(int num)
{
	return myCard[num].getS();
}
