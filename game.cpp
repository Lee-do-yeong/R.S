#include "poker_header.h"

int survivor = 5;
card Deck[52];
int top = 51;

void endGame(player member[],int &gambler)
{
	checkCard(); //임시 족보 비교 함수
	checkDie(member,gambler);
	suppleDeck(); // top = 51;
}

int checkCard()//임시
{
	return 0;
}

void suppleDeck()// 임시
{

}

void checkDie(player member[], int& gambler)
{
	int nowCheck = 0;
	for (int i = 0; i < survivor; i++)
	{
		while (member[nowCheck].checkSurvivor() == false)
		{
			nowCheck=(nowCheck+1)%survivor;
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

void resetGame(player member)
{
	member.returnPlay();
	member.resetUsed();
}


void choiceBet(player member[], int& gambler, int leader, int& totalBet)
{
	int nowBet = leader - 1, betMoney = 0,first=0;		
		
	for (int i = 0; i < gambler; i++) 
	{
		nowBet = (nowBet + 1)%survivor;
		
		while (member[nowBet].nowPlay() == false) //다음 플레이어가 이번판 다이를 쳤을 경우.
		{
			nowBet = (nowBet + 1)%survivor;
		}
		cout << "현재 차례 : " << member[nowBet].getName() << endl;
		if (first == 0) //첫 턴 leader만 배팅 다름.
		{
			betMoney = member[nowBet].leaderBet(totalBet, gambler);
			while (betMoney == 0) //만약 리더가 다이한 경우
			{
				if (gambler == 1) // 한 명빼고 gambler가 없을 경우
					break;
				nowBet = (nowBet + 1)%survivor;
				while (member[nowBet].nowPlay() == false) //다음 플레이어가 이번판 다이를 쳤을 경우.
				{
					nowBet = (nowBet + 1) % survivor;
				}
				cout << "현재 차례 : " << member[nowBet].getName() << endl;
				betMoney = member[nowBet].leaderBet(totalBet, gambler);
			}
			first = 999;
		}
		else
		{
			if (member[nowBet].canBet(betMoney) == true) // 돈 낼 능력이 있는가 판단
				choiceFollower(member, betMoney, totalBet, gambler, i, nowBet);

			else
				cant_Bet(member[nowBet], betMoney, gambler, totalBet);
		}
		cout << "전체 배팅 금액: " << totalBet << endl << "현재 배팅 : " << betMoney << endl;
	}
	cout << "BetMoney : " << betMoney << endl;
	nowBet = 0;
	for (int j = 0; j < gambler; j++)
	{
		do {
			nowBet = (nowBet + 1) % survivor;
		} while (member[nowBet].nowPlay() == false);
		member[nowBet].payBet(betMoney);
	}

	betMoney = 0;
}

void choiceFollower(player  member[], int& betMoney, int& totalBet, int& gambler, int& bet, int& nowBet)
{
	cout << "팔로우 배팅 : (1: 콜, 2: 다이, 3: 더블, 4: 하프, 5: 올인) \n";
	int choice;
	cin >> choice; // 인터페이스에서는 선택

	switch (choice)
	{
	case 1: //콜
		if (betMoney > member[nowBet].getMoney())
		{
			cout << "금액이 충분하지 않습니다.\n";
			choiceFollower(member, betMoney, totalBet, gambler, bet,nowBet);
		}
		else
			cout << "---------------------콜---------------------\n";
		member[nowBet].call(betMoney, totalBet);
		break;
	case 2: //다이
		member[nowBet].playerDie(gambler);
		cout << "---------------------다 이---------------------\n";
		if (bet++ < gambler)
		{
			while (member[nowBet].nowPlay() == false) //다음 플레이어가 이번판 다이를 쳤을 경우.
			{
				nowBet = (nowBet + 1) % survivor;
			}
			cout << "현재 차례 : " << member[nowBet].getName() << endl
				<< "전체 배팅 금액: " << totalBet << endl
				<< "현재 배팅 : " << betMoney << endl;
			if (gambler == 1)
				cout << "플레이어 없음\n";
			else
				choiceFollower(member, betMoney, totalBet, gambler, bet, nowBet);
		}
		bet--;
		break;
	case 3: // 더블, 배팅 금액 없는 경우 생각
		
		if (betMoney * 2 <= member[nowBet].getMoney())
		{
			bet = 0; // 더블 다음 사람부터 다시 팔로워처럼 배팅 선택
			cout << "---------------------더블---------------------\n";
			member[nowBet].doubleBet(betMoney, totalBet);
		}
		else
		{
			cout << "금액이 충분하지 않습니다.\n";
			choiceFollower(member, betMoney, totalBet, gambler, bet,betMoney);
		}
		break;
	case 4: // 하프
		if (betMoney > totalBet / 2)
		{
			cout << "하프가 배팅 금액보다 적습니다.\n";
			choiceFollower(member, betMoney, totalBet, gambler, bet,nowBet);
		}
		else if (member[nowBet].getMoney() < totalBet / 2)
		{
			cout << "현재 가진 돈이 판돈의 절반이 되지 않습니다.\n";
			choiceFollower(member, betMoney, totalBet, gambler, bet,nowBet);
		}
		else
		{
			cout << "---------------------하프---------------------\n";
			member[nowBet].halfBet(betMoney, totalBet);
			bet = 0;
		}
		break;
	case 5: //All in
		bet = 0; // 올인 다음 사람부터 다시 팔로워처럼 배팅 선택
		cout << "---------------------올 인---------------------\n";
		member[nowBet].allMoney(betMoney, totalBet);
	}
	
}

void cant_Bet(player & follwer, int& betMoney, int& gambler, int& totalBet)
{
	cout << "배팅 불가능 배팅 : (1. 올인, 2. 다이)\n";
	int choice;
	cin >> choice;

	switch (choice)
	{
	case 1: // 올인 
		cout << "---------------------올 인---------------------\n";
		follwer.dieAllMoney(totalBet);
		break;
	case 2: // 다이
		cout << "---------------------다이---------------------\n";
		follwer.playerDie(gambler);
	}
}


card drawCard()
{
	 // 임시 변수. 전역으로 할 지, 주소를 넘길지 고민.
	return Deck[top--];
}

void obliBet(player member[], int& totalBet) // 의무 배팅
{
	int obli = 3;

	for (int i = 0; i < survivor; i++)
	{
		member[i].payMoney(obli, totalBet);
		member[i].showMoney();

	}
	cout << "전체 배팅 금액 : " << totalBet << endl;
}



int choiceLeader(player member[], const int gambler) // 손봐야함
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

void reGame(player member[],player& dealer)
{
	char check;
	cout << "게임을 그만하시려면 N을 입력하시오 : ";
	cin >> check;

	if (check != 'n' && check != 'N')
		playGame(member, dealer);

}


void testPlayer(player member[])
{
	for (int i = 0; i < 5; i++) 
	{
		cout << "---------------" << member[i].getName() << "---------------\n"
			 << "Gaem Money : " << member[i].getMoney()<<endl
			 << "Play check : " << member[i].checkPlayer()<<endl
			 << "Survivor check : " << member[i].checkSurvivor()<<endl
			 << "Used : " << member[i].returnUsed() << endl;
	}
}

void resultantPlate(player member[])
{
	cout << "Game Set\n";
	cout << "Game Money : " << member[0].getMoney();
}

void playGame(player member[], player & dealer) // 게임 진행
{
	int totalBet = 0, leader;
	int gambler = survivor;
	obliBet(member, totalBet);

	for (int i = 0; i < gambler; i++) // 2장씩 배팅
	{
		cout << member[i].getName() << "의 플레이어 카드 분배\n";
		member[i].takeCard();
		member[i].takeCard();
	}

	cout << "딜러 카드 분배\n";

	for (int i = 0; i < 3; i++)
		dealer.takeCard();


	leader = choiceLeader(member, gambler); // 리더는 한 번만 정하면 다음부터는 오른쪽 사람이 리더

	for (int i = 0; i < 3; i++)
	{
		cout << member[i].getName() << "의 배팅\n";
		choiceBet(member, gambler, leader, totalBet);
		if (gambler == 1)
			break;
		if (i != 2) {
			dealer.takeCard();
			do
			{
				leader = (leader + 1)%survivor;
				
			} while (member[leader].checkPlayer() == false);
		}
		for (int j = 0; j < 5; j++)
			cout << member[j].getName() << "의 게임머니 : " << member[j].getMoney()<<endl;
	}

	//endGame(member, gambler);

	testPlayer(member);

	if (member[0].checkSurvivor() == false)
	{
		if(survivor != 1)
			reGame(member, dealer);
		else
			resultantPlate(member);
	}
	else
		resultantPlate(member);
}


//진행 상황 - 의무 배팅 구현, 카드 2장 주기 구현, 딜러 카드 3장 구현, 리더 선택 구현, 리더 배팅 구현, 팔로워 배팅 구현(예외사항 적용중)
