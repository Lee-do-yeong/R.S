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
		
		while (member[nowBet].nowPlay() == false) //���� �÷��̾ �̹��� ���̸� ���� ���.
		{
			nowBet = (nowBet + 1) % 5;
		}

		nowPlayName(member[nowBet].getName());
		if (first == 0) //ù �� leader�� ���� �ٸ�.
		{
			member[nowBet].leaderBet(totalBet, gambler,betMoney,nowBet,turn,member,dealer,i);
			member[nowBet].setDieMoney(betMoney);
			while (betMoney == 0) //���� ������ ������ ���
			{
				for (int k = 0; k < 5; k++)
					if (member[k].checkSurvivor() == false)
						j++;
				if (j <= 1) // �� ���� gambler�� ���� ���
					break;
				nowBet = (nowBet + 1) % 5;
				for (int k = 0; k < 5 && member[nowBet].nowPlay() == false;k++) //���� �÷��̾ �̹��� ���̸� ���� ���.				
					nowBet = (nowBet + 1) % 5;
				
				nowPlayName(member[nowBet].getName());
				member[nowBet].leaderBet(totalBet, gambler,betMoney, nowBet, turn, member, dealer,i);
				member[nowBet].setDieMoney(betMoney);
			}
			first = 999;
		}
		else
		{
			if (member[nowBet].canBet(betMoney) == true) // �� �� �ɷ��� �ִ°� �Ǵ�
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
	cout << "�ȷο� ����";

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
	case 1: //��
		if (betMoney > member[nowBet].getMoney())
			cant_Bet(member[nowBet], betMoney, gambler, totalBet, member, nowBet,bet,dealer,turn);
	
		else
		{
			interCall();
			member[nowBet].call(betMoney, totalBet);//,pastChoice);
			member[nowBet].setDieMoney(betMoney);
		}
		break;
	case 2: //����
		interDie();
		member[nowBet].playerDie(gambler);
		checkStatus(member, gambler);
		if(gambler != bet)
			bet--;
		if (bet++ < gambler)
		{
			while (member[nowBet].nowPlay() == false) //���� �÷��̾ �̹��� ���̸� ���� ���.
			{
				nowBet = (nowBet + 1) % 5;
			}
			nowPlayName(member[nowBet].getName());
			betting_all(betMoney,totalBet);
			for (int i = 0; i < 5; i++) 
				if (member[i].checkSurvivor() == false)
					j++;
			
			if (j <= 1)
				showSentence("�÷��̾� ����", 81, 12);
			else
				choiceFollower(member, betMoney, totalBet, gambler, bet, nowBet, dealer, turn);
		}
		break;
	case 3: // ����, ���� �ݾ� ���� ��� ����

		if (betMoney * 2 > member[nowBet].getMoney())
		{
			showSentence("�ݾ��� ������� �ʽ��ϴ�.", 78, 12);
			choiceFollower(member, betMoney, totalBet, gambler, bet, betMoney, dealer, turn);
		}
		else
		{
			bet = 0; // ���� ���� ������� �ٽ� �ȷο�ó�� ���� ����
			interDouble();
			member[nowBet].doubleBet(betMoney, totalBet);
			member[nowBet].setDieMoney(betMoney);
		}

		break;
	case 4: // ����
		if (betMoney > totalBet / 2)
		{
			showSentence("������ ���� �ݾ׺��� �����ϴ�.",73,12);
			choiceFollower(member, betMoney, totalBet, gambler, bet, nowBet,dealer,turn);
		}
		else if (member[nowBet].getMoney() < totalBet / 2)
		{
			showSentence("���� ���� ���� �ǵ��� ������ ���� �ʽ��ϴ�.",70,12);
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
		bet = -1; // ���� ���� ������� �ٽ� �ȷο�ó�� ���� ����
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
	gotoxy(84, 12);  cout << "ĵƮ ����";
	if(nowBet==0)
		choice = choice_betting2(betMoney);
	else 
	{
		choice = probabli_Cant();
		computaTurn(member, nowBet);
	}
	switch (choice)
	{
	case 1: // ���� 
		interAllin();
		follwer.dieAllMoney(totalBet, gambler);
		checkStatus(member, gambler);
		bet = -1;
		break;
	case 2: // ����
		interDie();
		follwer.playerDie(gambler);
		checkStatus(member, gambler);
		if (gambler != bet)
			bet--;
		if (bet++ < gambler)
		{
			while (member[nowBet].nowPlay() == false) //���� �÷��̾ �̹��� ���̸� ���� ���.
			{
				nowBet = (nowBet + 1) % survivor;
			}
			nowPlayName(member[nowBet].getName());
			betting_all(betMoney, totalBet);
			for (int i = 0; i < 5; i++)
				if (member[i].checkSurvivor() == false)
					j++;

			if (j <= 1)
				showSentence("�÷��̾� ����", 81, 12);
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


void obliBet(Player member[], int& totalBet,int &gambler) // �ǹ� ���� //10 3 ��, 10 18 ��, 150 3 ��, 150 18 ��, 85 36 ��
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

int choiceLeader(Player member[], const int gambler) // �պ�����
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
	cout << "������ �׸��Ͻ÷��� N�� �Է��Ͻÿ� : ";
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

void playGame(Player member[], Player& dealer) // ���� ����
{

	int totalBet = 0, leader;
	int gambler = survivor;
	int num1 = 0, j = 0,turn=1;
	Player* temp;
	temp = new Player;

	shuffle(member, dealer);
	picture(dealer.getCard(),member);
	checkStatus(member, gambler);
	
	
	for(int i=0; i<3; i++) // ���� ī�� �й�
		showDealerCard(dealer.getCard(), num1, j,member);
	obliBet(member, totalBet,gambler);
	leader = choiceLeader(member, gambler); // ������ �� ���� ���ϸ� �������ʹ� ������ ����� ����

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


//���� ��Ȳ - �ǹ� ���� ����, ī�� 2�� �ֱ� ����, ���� ī�� 3�� ����, ���� ���� ����, ���� ���� ����, �ȷο� ���� ����(���ܻ��� ������)
