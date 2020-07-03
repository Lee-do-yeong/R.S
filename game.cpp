#include "poker_header.h"

int survivor = 5;


void endGame(Player member[], int& gambler)
{
	checkDie(member, gambler);
}




void checkDie(Player member[], int& gambler)
{
	for (int i = 0; i < 5; i++)
	{
		
		if (member[i].getRetire() == false)
		{
			if (member[i].getMoney() == 0)
			{
				member[i].retireGame();
			}
			else
			{
				resetGame(member[i]);
			}
		}
	}
}

void resetGame(Player& member)
{
	member.returnPlay();
}


void choiceBet(Player member[], int& gambler, int leader, int& totalBet,Player &dealer,const int turn)
{
	int nowBet = leader - 1, betMoney = 0, first = 0,  payBet,j=0,alone=0;//,pastChoice;

	betting_all(0, totalBet);

	for (int i = 0; i < gambler; i++)
	{
		for (int t = 0; t < 5; t++)
			if (member[t].nowPlay() == true)
				alone++;
		if (alone == 1)
			break;
		nowBet = (nowBet + 1) % 5;
		
		while (member[nowBet].nowPlay() == false) //다음 플레이어가 이번판 다이를 쳤을 경우.
		{
			nowBet = (nowBet + 1) % 5;
		}

		nowPlayName(member[nowBet].getName());
		if (first == 0) //첫 턴 leader만 배팅 다름.
		{
			member[nowBet].leaderBet(totalBet, gambler,betMoney,nowBet,turn,member,dealer,i);
			member[nowBet].setDieMoney(betMoney);
			while (betMoney == 0) //만약 리더가 다이한 경우
			{
				for (int k = 0; k < 5; k++)
					if (member[k].checkSurvivor() == false)
						j++;
				if (j <= 1) // 한 명빼고 gambler가 없을 경우
					break;
				nowBet = (nowBet + 1) % 5;
				for (int k = 0; k < 5 && member[nowBet].nowPlay() == false;k++) //다음 플레이어가 이번판 다이를 쳤을 경우.				
					nowBet = (nowBet + 1) % 5;
				
				nowPlayName(member[nowBet].getName());
				member[nowBet].leaderBet(totalBet, gambler,betMoney, nowBet, turn, member, dealer,i);
				member[nowBet].setDieMoney(betMoney);
			}
			first = 999;
		}
		else
		{
			if (member[nowBet].canBet(betMoney) == true) // 돈 낼 능력이 있는가 판단
				choiceFollower(member, betMoney, totalBet, gambler, i, nowBet,  dealer, turn);// , pastChoice);

			else
				cant_Bet(member[nowBet], betMoney, gambler, totalBet, member,nowBet,i,dealer,turn);
		}
		
		betting_all(betMoney, totalBet);
	}

	for (int i = 0; i < 5; i++)
		member[i].setDieMoney(0);
	payBet = 0;
	if (gambler>1) {
		for (int j = 0; j < gambler; j++)
		{
			do {
				payBet = (payBet + 1) % 5;
			} while (member[payBet].nowPlay() == false);
			member[payBet].payBet(betMoney);
		}
	}
	checkStatus(member, gambler);
	showCoinAll(member);

}

void choiceFollower(Player  member[], int& betMoney, int& totalBet, int& gambler, int& bet, int& nowBet,Player &dealer, int turn)//,int &pastChoice)
{
	int choice,temp,j=0;

	setColor(GREEN, WHITE);
	gotoxy(82, 12);
	cout << "                       ";
	gotoxy(82, 12);
	cout << "팔로우 배팅";

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
			cant_Bet(member[nowBet], betMoney, gambler, totalBet, member, nowBet,bet,dealer,turn);
	
		else
		{
			interCall();
			member[nowBet].call(betMoney, totalBet);//,pastChoice);
			member[nowBet].setDieMoney(betMoney);
		}
		break;
	case 2: //다이
		interDie();
		member[nowBet].playerDie(gambler);
		checkStatus(member, gambler);
		if(gambler != bet)
			bet--;
		if (bet++ < gambler)
		{
			while (member[nowBet].nowPlay() == false) //다음 플레이어가 이번판 다이를 쳤을 경우.
			{
				nowBet = (nowBet + 1) % 5;
			}
			nowPlayName(member[nowBet].getName());
			betting_all(betMoney,totalBet);
			for (int i = 0; i < 5; i++) 
				if (member[i].checkSurvivor() == false)
					j++;
			
			if (j <= 1)
				showSentence("플레이어 없음", 81, 12);
			else
				choiceFollower(member, betMoney, totalBet, gambler, bet, nowBet, dealer, turn);
		}
		break;
	case 3: // 더블, 배팅 금액 없는 경우 생각

		if (betMoney * 2 > member[nowBet].getMoney())
		{
			showSentence("금액이 충분하지 않습니다.", 78, 12);
			choiceFollower(member, betMoney, totalBet, gambler, bet, betMoney, dealer, turn);
		}
		else
		{
			bet = 0; // 더블 다음 사람부터 다시 팔로워처럼 배팅 선택
			interDouble();
			member[nowBet].doubleBet(betMoney, totalBet);
			member[nowBet].setDieMoney(betMoney);
		}

		break;
	case 4: // 하프
		if (betMoney > totalBet / 2)
		{
			showSentence("하프가 배팅 금액보다 적습니다.",73,12);
			choiceFollower(member, betMoney, totalBet, gambler, bet, nowBet,dealer,turn);
		}
		else if (member[nowBet].getMoney() < totalBet / 2)
		{
			showSentence("현재 가진 돈이 판돈의 절반이 되지 않습니다.",70,12);
			choiceFollower(member, betMoney, totalBet, gambler, bet, nowBet, dealer, turn);
		}
		else
		{
			interHalf();
			member[nowBet].halfBet(betMoney, totalBet);
			member[nowBet].setDieMoney(betMoney);
			bet = 0;

		}

		break;
	case 5: //All in
		interAllin();
		bet = -1; // 올인 다음 사람부터 다시 팔로워처럼 배팅 선택
		member[nowBet].allMoney(betMoney, totalBet, gambler);
		member[nowBet].setDieMoney(betMoney);
		checkStatus(member, gambler);

	}

	//pastChoice = choice;
	setColor(GREEN, WHITE);
	gotoxy(81, 12);
	cout << "                       ";
}

void cant_Bet(Player& follwer, int& betMoney, int& gambler, int& totalBet, Player member[],int &nowBet,int &bet,Player &dealer, int turn)
{
	int choice,j=0;
	setColor(GREEN, WHITE);
	gotoxy(80, 12);
	cout << "                     ";
	gotoxy(84, 12);  cout << "캔트 베팅";
	if(nowBet==0)
		choice = choice_betting2(betMoney);
	else 
	{
		choice = probabli_Cant();
		computaTurn(member, nowBet);
	}
	switch (choice)
	{
	case 1: // 올인 
		interAllin();
		follwer.dieAllMoney(totalBet, gambler);
		checkStatus(member, gambler);
		bet = -1;
		break;
	case 2: // 다이
		interDie();
		follwer.playerDie(gambler);
		checkStatus(member, gambler);
		if (gambler != bet)
			bet--;
		if (bet++ < gambler)
		{
			while (member[nowBet].nowPlay() == false) //다음 플레이어가 이번판 다이를 쳤을 경우.
			{
				nowBet = (nowBet + 1) % survivor;
			}
			nowPlayName(member[nowBet].getName());
			betting_all(betMoney, totalBet);
			for (int i = 0; i < 5; i++)
				if (member[i].checkSurvivor() == false)
					j++;

			if (j <= 1)
				showSentence("플레이어 없음", 81, 12);
			else
			{
				setColor(GREEN, WHITE);
				gotoxy(84, 12);
				cout << "                     ";
				choiceFollower(member, betMoney, totalBet, gambler, bet, nowBet, dealer, turn);
			}
		}
	}
	setColor(GREEN, WHITE);
	gotoxy(84, 12);
	cout << "                     ";
	gotoxy(70, 13);
	cout << "                                               ";
}


void obliBet(Player member[], int& totalBet,int &gambler) // 의무 배팅 //10 3 이, 10 18 범, 150 3 임, 150 18 김, 85 36 플
{
	int obli = 3;
	for (int i = 0; i < 5 && member[i].getRetire() == false; i++)
	{
		if (member[i].getMoney() < 3)
			member[i].dieAllMoney(totalBet,gambler);
		else
			member[i].payMoney(obli, totalBet);
	}
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

int reGame(Player member[], Player& dealer)
{
	char check;
	setColor(GREEN, WHITE);
	gotoxy(72, 12);
	cout << "                                            ";
	gotoxy(72, 12);
	cout << "게임을 그만하시려면 N을 입력하시오 : ";
	cin >> check;

	if (check == 'f' || check == 'F')
	{
		return 3;
	}
	else if (check != 'n' && check != 'N')
	{
		return 1;
	}
	
	return -1;
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
	temp = new Player;

	shuffle(member, dealer);
	picture(dealer.getCard(),member);
	checkStatus(member, gambler);
	
	
	for(int i=0; i<3; i++) // 딜러 카드 분배
		showDealerCard(dealer.getCard(), num1, j,member);
	obliBet(member, totalBet,gambler);
	leader = choiceLeader(member, gambler); // 리더는 한 번만 정하면 다음부터는 오른쪽 사람이 리더

	for (int i = 0; i < 2; i++)
	{
		choiceBet(member, gambler, leader, totalBet,dealer,turn);
		turn++;
		for (int k = 0; k < 5 && member[++leader].checkPlayer() == false;k++);
		showDealerCard(dealer.getCard(), num1, j,member);
	}
	choiceBet(member, gambler, leader, totalBet,dealer,turn);
	checkStatus(member, gambler);
	printAll(member);

	temp=checkWinner(member, dealer, gambler);

	temp->winnerMoney(totalBet);

	showCoinAll(member);
	Print_result((*temp),dealer);
	checkDie(member, gambler);

}


//진행 상황 - 의무 배팅 구현, 카드 2장 주기 구현, 딜러 카드 3장 구현, 리더 선택 구현, 리더 배팅 구현, 팔로워 배팅 구현(예외사항 적용중)
