#include "poker_header.h"

int survivor = 5;


void endGame(Player member[], int& gambler)
{
	checkCard(); //임시 족보 비교 함수
	checkDie(member, gambler);
}

int checkCard()//임시
{
	return 0;
}


void checkDie(Player member[], int& gambler)
{
	int nowCheck = 0;
	for (int i = 0; i < survivor; i++)
	{
		while (member[nowCheck].checkSurvivor() == false)
		{
			nowCheck = (nowCheck + 1) % survivor;
		}

		if (member[nowCheck].getMoney() == 0)
		{
			member[nowCheck].retireGame();
		}
		else
		{
			resetGame(member[nowCheck]);
		}
	}
	gambler = survivor;
}

void resetGame(Player member)
{
	member.returnPlay();
	member.resetUsed();
}


void choiceBet(Player member[], int& gambler, int leader, int& totalBet,Player &dealer,const int turn)
{
	int nowBet = leader - 1, betMoney = 0, first = 0, dieMoney = 0,dieBet=-1;

	betting_all(0, totalBet);
	for (int i = 0; i < gambler; i++)
	{
		nowBet = (nowBet + 1) % survivor;
		dieMoney = 0;
		
		while (member[nowBet].nowPlay() == false) //다음 플레이어가 이번판 다이를 쳤을 경우.
		{
			nowBet = (nowBet + 1) % survivor;
		}
		nowPlayName(member[nowBet].getName());
		if (first == 0) //첫 턴 leader만 배팅 다름.
		{
			dieMoney = betMoney;
			member[nowBet].leaderBet(totalBet, gambler, dieMoney,betMoney,nowBet,turn,member,dealer);
			while (betMoney == 0) //만약 리더가 다이한 경우
			{
				if (gambler == 1) // 한 명빼고 gambler가 없을 경우
					break;
				nowBet = (nowBet + 1) % survivor;
				while (member[nowBet].nowPlay() == false) //다음 플레이어가 이번판 다이를 쳤을 경우.				
					nowBet = (nowBet + 1) % survivor;
				
				nowPlayName(member[nowBet].getName());
				member[nowBet].leaderBet(totalBet, gambler, dieMoney,betMoney, nowBet, turn, member, dealer);
				dieMoney = betMoney;
			}
			first = 999;
		}
		else
		{
			if (member[nowBet].canBet(betMoney) == true) // 돈 낼 능력이 있는가 판단
				choiceFollower(member, betMoney, totalBet, gambler, i, nowBet, dieMoney, dieBet,dealer,turn);

			else
				cant_Bet(member[nowBet], betMoney, gambler, totalBet, dieMoney,member);
		}
		
		betting_all(betMoney, totalBet);
	}
	nowBet = 0;
	for (int j = 0; j < gambler; j++)
	{
		do {
			nowBet = (nowBet + 1) % survivor;
		} while (member[nowBet].nowPlay() == false);
		member[nowBet].payBet(betMoney);
	}
	showCoinAll(member);

}

void choiceFollower(Player  member[], int& betMoney, int& totalBet, int& gambler, int& bet, int& nowBet, int& dieMoney,int &dieBet,Player &dealer, int turn)
{
	int choice,temp;
	
	if (nowBet == 0)
		choice = bettingNumber();
	else
	{
		switch (turn)
		{
		case 1:
			temp = aPedigree_check(member[nowBet],dealer.getCard(),member[nowBet].getCard());
			choice=probabli(temp);
			computaTurn(member, nowBet);
			break;
		case 2:
			temp = Bpedigree_check(member[nowBet], dealer.getCard(), member[nowBet].getCard());
			choice=probabli(temp);
			computaTurn(member, nowBet);
			break;
		case 3:
			temp = Cpedigree_check(member[nowBet], dealer.getCard(), member[nowBet].getCard());
			choice=probabli(temp);
			computaTurn(member, nowBet);
		}
	}
	switch (choice)
	{
	case 1: //콜
		if (betMoney > member[nowBet].getMoney())
		{
			showSentence("금액이 충분하지 않습니다.",78,12);
			choiceFollower(member, betMoney, totalBet, gambler, bet, nowBet, dieMoney, dieBet,dealer,turn);
		}
		else
		{
			interCall();
			member[nowBet].call(betMoney, totalBet);
		}
		dieBet = -1;
		break;
	case 2: //다이
		interDie();
		member[nowBet].playerDie(gambler, dieMoney);
		dieBet = nowBet;
		checkStatus(member);
		if (bet++ < gambler)
		{
			while (member[nowBet].nowPlay() == false) //다음 플레이어가 이번판 다이를 쳤을 경우.
			{
				nowBet = (nowBet + 1) % survivor;
			}
			nowPlayName(member[nowBet].getName());
			betting_all(betMoney,totalBet);
			if (gambler == 1)
				showSentence("플레이어 없음",81,12);
			else
				choiceFollower(member, betMoney, totalBet, gambler, bet, nowBet, dieMoney, dieBet,dealer,turn);
		}
		bet--;
		break;
	case 3: // 더블, 배팅 금액 없는 경우 생각

		if (betMoney * 2 <= member[nowBet].getMoney())
		{
			dieMoney = betMoney;
			bet = 0; // 더블 다음 사람부터 다시 팔로워처럼 배팅 선택
			interDouble();
			member[nowBet].doubleBet(betMoney, totalBet);
		}
		else
		{
			showSentence("금액이 충분하지 않습니다.",78,12);
			choiceFollower(member, betMoney, totalBet, gambler, bet, betMoney, dieMoney, dieBet,dealer,turn);
		}
		if (dieBet != -1)
			bet = 1;
		dieBet = -1;
		break;
	case 4: // 하프
		if (betMoney > totalBet / 2)
		{
			showSentence("하프가 배팅 금액보다 적습니다.",73,12);
			choiceFollower(member, betMoney, totalBet, gambler, bet, nowBet, dieMoney,dieBet,dealer,turn);
		}
		else if (member[nowBet].getMoney() < totalBet / 2)
		{
			showSentence("현재 가진 돈이 판돈의 절반이 되지 않습니다.",70,12);
			choiceFollower(member, betMoney, totalBet, gambler, bet, nowBet, dieMoney,dieBet, dealer, turn);
		}
		else
		{
			interHalf();
			dieMoney = betMoney;
			member[nowBet].halfBet(betMoney, totalBet);
			bet = 0;
		}
		if (dieBet != -1)
			bet = 1;
		dieBet = -1;
		break;
	case 5: //All in
		interAllin();
		bet = 0; // 올인 다음 사람부터 다시 팔로워처럼 배팅 선택
		dieMoney = betMoney;
		member[nowBet].allMoney(betMoney, totalBet);
		checkStatus(member);
		if (dieBet != -1)
			bet = 1;
		dieBet = -1;
	}

}

void cant_Bet(Player& follwer, int& betMoney, int& gambler, int& totalBet, int dieMoney,Player member[])
{
	int choice;
	choice = choice_betting2(betMoney);

	switch (choice)
	{
	case 1: // 올인 
		follwer.dieAllMoney(totalBet);
		checkStatus(member);
		break;
	case 2: // 다이
		follwer.playerDie(gambler, dieMoney);
		checkStatus(member);
	}
}


void obliBet(Player member[], int& totalBet) // 의무 배팅 //10 3 이, 10 18 범, 150 3 임, 150 18 김, 85 36 플
{
	int obli = 3;
	for (int i = 0; i < survivor; i++)
		member[i].payMoney(obli, totalBet);
	showObli();
	showCoinAll(member);
	
}

void showCoinAll(Player member[])
{
	setColor(BLACK, WHITE);
	showCoin(10, 3, member[2].getMoney());
	showCoin(10, 18, member[1].getMoney());
	showCoin(150, 3, member[3].getMoney());
	showCoin(150, 18, member[4].getMoney());
	showCoin(82, 40, member[0].getMoney());
}

int choiceLeader(Player member[], const int gambler) // 손봐야함
{
	int temp = member[0].getMoney(), leader = 0;

	for (int i = 1; i < gambler; i++)
	{
		if (member[i].getMoney() > temp)
		{
			temp = member[i].getMoney();
			leader = i;
		}
	}
	if (leader == survivor)
		leader = 0;

	return leader;
}

void reGame(Player member[], Player& dealer)
{
	char check;
	gotoxy(72, 12);
	setColor(GREEN, WHITE);
	cout << "게임을 그만하시려면 N을 입력하시오 : ";
	cin >> check;

	if (check != 'n' && check != 'N')
	{
		setColor(BLACK, WHITE);
		picture(dealer.getCard(), member);
		playGame(member, dealer);
	}
}


void resultantPlate(Player member[])
{
	cout << "Game Set\n";
	cout << "Game Money : " << member[0].getMoney();
}

void playGame(Player member[], Player& dealer) // 게임 진행
{

	int totalBet = 0, leader;
	int gambler = survivor;
	int num1 = 0, j = 0,turn=1;
	Player* temp;

	shuffle(member, dealer);
	picture(dealer.getCard(),member);
	
	
	
	for(int i=0; i<3; i++) // 딜러 카드 분배
		showDealerCard(dealer.getCard(), num1, j,member[0]);
	obliBet(member, totalBet);
	leader = choiceLeader(member, gambler); // 리더는 한 번만 정하면 다음부터는 오른쪽 사람이 리더

	for (int i = 0; i < 2; i++)
	{
		choiceBet(member, gambler, leader, totalBet,dealer,turn);
		turn++;
		if (gambler == 1)
			break;
		while (member[++leader].checkPlayer() == false);
		showDealerCard(dealer.getCard(), num1, j,member[0]);
	}
	choiceBet(member, gambler, leader, totalBet,dealer,turn);
	checkStatus(member);
	printAll(member);
	temp=checkWinner(member, dealer);
	temp->winnerMoney(totalBet);
	Print_result((*temp),dealer);
	checkDie(member, gambler);
	
	if (member[0].checkSurvivor() == false)
	{
		if (survivor != 1)
			reGame(member, dealer);
		else
			resultantPlate(member);
	}
	else
		resultantPlate(member);
}


//진행 상황 - 의무 배팅 구현, 카드 2장 주기 구현, 딜러 카드 3장 구현, 리더 선택 구현, 리더 배팅 구현, 팔로워 배팅 구현(예외사항 적용중)
