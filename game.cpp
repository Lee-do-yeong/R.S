#include "poker_header.h"

int survivor = 5;


void endGame(Player member[], int& gambler)
{
	checkCard(); //�ӽ� ���� �� �Լ�
	checkDie(member, gambler);
}

int checkCard()//�ӽ�
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


void choiceBet(Player member[], int& gambler, int leader, int& totalBet)
{
	int nowBet = leader - 1, betMoney = 0, first = 0, dieMoney = 0;

	for (int i = 0; i < gambler; i++)
	{
		nowBet = (nowBet + 1) % survivor;

		while (member[nowBet].nowPlay() == false) //���� �÷��̾ �̹��� ���̸� ���� ���.
		{
			nowBet = (nowBet + 1) % survivor;
		}
		nowPlay(member[nowBet].getName());
		if (first == 0) //ù �� leader�� ���� �ٸ�.
		{
			dieMoney = betMoney;
			member[nowBet].leaderBet(totalBet, gambler, dieMoney,betMoney);
			while (betMoney == 0) //���� ������ ������ ���
			{
				if (gambler == 1) // �� ���� gambler�� ���� ���
					break;
				nowBet = (nowBet + 1) % survivor;
				while (member[nowBet].nowPlay() == false) //���� �÷��̾ �̹��� ���̸� ���� ���.				
					nowBet = (nowBet + 1) % survivor;
				
				nowPlay(member[nowBet].getName());
				member[nowBet].leaderBet(totalBet, gambler, dieMoney,betMoney);
				dieMoney = betMoney;
			}
			first = 999;
		}
		else
		{
			if (member[nowBet].canBet(betMoney) == true) // �� �� �ɷ��� �ִ°� �Ǵ�
				choiceFollower(member, betMoney, totalBet, gambler, i, nowBet, dieMoney);

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

void choiceFollower(Player  member[], int& betMoney, int& totalBet, int& gambler, int& bet, int& nowBet, int& dieMoney)
{
	int choice;
	
//	if (nowBet == 0)
		choice = bettingNumber();
	//else
	//	choice = 1; //��ǻ�� Ȯ���Լ� �߰�


	switch (choice)
	{
	case 1: //��
		if (betMoney > member[nowBet].getMoney())
		{
			showSentence("�ݾ��� ������� �ʽ��ϴ�.",78,12);
			choiceFollower(member, betMoney, totalBet, gambler, bet, nowBet, dieMoney);
		}
		else
		member[nowBet].call(betMoney, totalBet);
		break;
	case 2: //����
		member[nowBet].playerDie(gambler, dieMoney);
		checkStatus(member);
		if (bet++ < gambler)
		{
			while (member[nowBet].nowPlay() == false) //���� �÷��̾ �̹��� ���̸� ���� ���.
			{
				nowBet = (nowBet + 1) % survivor;
			}
			nowPlay(member[nowBet].getName());
			betting_all(betMoney,totalBet);
			if (gambler == 1)
				showSentence("�÷��̾� ����",81,12);
			else
				choiceFollower(member, betMoney, totalBet, gambler, bet, nowBet, dieMoney);
		}
		bet--;
		break;
	case 3: // ����, ���� �ݾ� ���� ��� ����

		if (betMoney * 2 <= member[nowBet].getMoney())
		{
			dieMoney = betMoney;
			bet = 0; // ���� ���� ������� �ٽ� �ȷο�ó�� ���� ����
			member[nowBet].doubleBet(betMoney, totalBet);
		}
		else
		{
			showSentence("�ݾ��� ������� �ʽ��ϴ�.",78,12);
			choiceFollower(member, betMoney, totalBet, gambler, bet, betMoney, dieMoney);
		}
		break;
	case 4: // ����
		if (betMoney > totalBet / 2)
		{
			showSentence("������ ���� �ݾ׺��� �����ϴ�.",73,12);
			choiceFollower(member, betMoney, totalBet, gambler, bet, nowBet, dieMoney);
		}
		else if (member[nowBet].getMoney() < totalBet / 2)
		{
			showSentence("���� ���� ���� �ǵ��� ������ ���� �ʽ��ϴ�.",70,12);
			choiceFollower(member, betMoney, totalBet, gambler, bet, nowBet, dieMoney);
		}
		else
		{
			dieMoney = betMoney;
			member[nowBet].halfBet(betMoney, totalBet);
			bet = 0;
		}
		break;
	case 5: //All in
		bet = 0; // ���� ���� ������� �ٽ� �ȷο�ó�� ���� ����
		dieMoney = betMoney;
		member[nowBet].allMoney(betMoney, totalBet);
		checkStatus(member);
	}

}

void cant_Bet(Player& follwer, int& betMoney, int& gambler, int& totalBet, int dieMoney,Player member[])
{
	showSentence("���� �Ұ��� ����",81,12);
	showSentence("1: ����,  2: ����",80,13);
	int choice;
	cin >> choice;

	switch (choice)
	{
	case 1: // ���� 
		cout << "---------------------�� ��---------------------\n";
		follwer.dieAllMoney(totalBet);
		checkStatus(member);
		break;
	case 2: // ����
		cout << "---------------------����---------------------\n";
		follwer.playerDie(gambler, dieMoney);
		checkStatus(member);
	}
}


void obliBet(Player member[], int& totalBet) // �ǹ� ���� //10 3 ��, 10 18 ��, 150 3 ��, 150 18 ��, 85 36 ��
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

void reGame(Player member[], Player& dealer)
{
	char check;
	gotoxy(72, 12);
	setColor(GREEN, WHITE);
	cout << "������ �׸��Ͻ÷��� N�� �Է��Ͻÿ� : ";
	cin >> check;

	if (check != 'n' && check != 'N')
	{
		setColor(BLACK, WHITE);
		picture(dealer.getCard(), member);
		playGame(member, dealer);
	}
}


void testPlayer(Player member[])
{
	for (int i = 0; i < 5; i++)
	{
		cout << "---------------" << member[i].getName() << "---------------\n"
			<< "Gaem Money : " << member[i].getMoney() << endl
			<< "Play check : " << member[i].checkPlayer() << endl
			<< "Survivor check : " << member[i].checkSurvivor() << endl
			<< "Used : " << member[i].returnUsed() << endl;
	}
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
	int num1 = 0, j = 0;
	

	shuffle(member, dealer);
	picture(dealer.getCard(),member);
	
	
	
	for(int i=0; i<3; i++) // ���� ī�� �й�
		showDealerCard(dealer.getCard(), num1, j,member[0]);
	obliBet(member, totalBet);
	leader = choiceLeader(member, gambler); // ������ �� ���� ���ϸ� �������ʹ� ������ ����� ����

	for (int i = 0; i < 2; i++)
	{
		choiceBet(member, gambler, leader, totalBet);
		if (gambler == 1)
			break;
		while (member[++leader].checkPlayer() == false);
		showDealerCard(dealer.getCard(), num1, j,member[0]);
	}
	choiceBet(member, gambler, leader, totalBet);
	checkStatus(member);
	printAll(member);
	//main����
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


//���� ��Ȳ - �ǹ� ���� ����, ī�� 2�� �ֱ� ����, ���� ī�� 3�� ����, ���� ���� ����, ���� ���� ����, �ȷο� ���� ����(���ܻ��� ������)
