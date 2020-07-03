#include "poker_header.h"

extern int survivor;
extern int top;

Player::Player() :  gameMoney(50), play(true), die(false)
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

void Player::playerDie(int& gambler) 
{
	gameMoney = gameMoney - dieMoney;
	play = false;
	die = true;
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

void Player::leaderBet(int &totalMoney,int& gambler, int &betMoney,int nowBet,int turn,Player member[],Player &dealer,int &bet) //85 36
{
	int choice = 0,temp;
	gotoxy(84, 12);
	cout << "리더 베팅";
	if (nowBet==0)
		choice = choice_betting(betMoney);
	else
	{

		switch (turn)
		{
		case 1:
			temp = aPedigree_check(member[nowBet], dealer.getCard(), member[nowBet].getCard());
			choice = probabli_Leader(temp,betMoney,member[nowBet]);
			computaTurn(member, nowBet);
			break;
		case 2:
			temp = Bpedigree_check(member[nowBet], dealer.getCard(), member[nowBet].getCard());
			choice = probabli_Leader(temp, betMoney, member[nowBet]);
			computaTurn(member, nowBet);
			break;
		case 3:
			temp = Cpedigree_check(member[nowBet], dealer.getCard(), member[nowBet].getCard());
			choice = probabli_Leader(temp, betMoney, member[nowBet]);
			computaTurn(member, nowBet);
		}

	}
	switch (choice)
	{
	case 1:
		interBetting();
		inputBet(totalMoney,betMoney);
		break;
	case 2:
		interAllin();
		allMoney(betMoney, totalMoney, gambler);
		bet = -1;
		break;
	case 3:
		interDie();
		playerDie(gambler);
		betMoney = 0;

	}
	setColor(GREEN, WHITE);
	gotoxy(79, 12);
	cout << "                      ";
}

void Player::doubleBet(int& betMoney,int& totalBet)
{
	betMoney = betMoney * 2;
	totalBet = totalBet + betMoney;
}

void Player::allMoney(int& betMoney, int& totalBet, int& gambler)
{
	betMoney = gameMoney;
	gameMoney = 0;
	totalBet = totalBet + betMoney;
	play = false;
	gambler--;
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
	betMoney = totalBet / 2;
	totalBet = totalBet + betMoney;
}

void Player::dieAllMoney(int& totalBet,int& gambler)
{
	totalBet = totalBet + gameMoney;
	gameMoney = 0; //고려
	play = false;
	gambler--;
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
	retire = true;
	die = true;
	play = false;
	survivor--;
}

void Player::returnPlay()
{
	die = false;
	play = true;
}

void Player::call(int& betMoney,int &totalMoney)//,int& pastChoice)
{
	if(dieMoney ==0)
		totalMoney = totalMoney + betMoney;
	else
		totalMoney = (betMoney - dieMoney) + totalMoney;

}

Player::Player(string setN) : gameMoney(50), play(true), die(false), dieMoney(0), retire(false)
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
	maxPattern = maxN;
	maxNumber = maxP;
}

void Player::setMax(int maxP, int maxN,int maxP2, int maxN2)
{
	maxPattern = maxN;
	maxNumber = maxP;
	maxPattern2 = maxN2;
	maxNumber2 = maxP2;
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

int Player::getNMax()
{
	return maxNumber;
}
int Player::getNMax2()
{
	return maxNumber2;
}

int Player::getPMax()
{
	return maxPattern;
}
int Player::getPMax2()
{
	return maxPattern2;
}

void Player::winnerMoney(int& totalBet)
{
	gameMoney = gameMoney + totalBet;
	totalBet = 0;
}

void Player::setDieMoney(int die)
{
	dieMoney = die;
}

int Player::getDieMoney()
{
	return dieMoney;
}

void Player::zeroMoney()
{
	play = false;
}

bool Player::getRetire()
{
	return retire;
}