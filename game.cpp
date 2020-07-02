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
		while (member[nowCheck].getRetire() == false)
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
	int nowBet = leader - 1, betMoney = 0, first = 0, dieBet = -1,payBet;//,pastChoice;

	betting_all(0, totalBet);
	for (int i = 0; i < gambler; i++)
	{
		nowBet = (nowBet + 1) % survivor;
		
		while (member[nowBet].nowPlay() == false) //���� �÷��̾ �̹��� ���̸� ���� ���.
		{
			checkStatus(member);
			nowBet = (nowBet + 1) % survivor;
		}
		nowPlayName(member[nowBet].getName());
		if (first == 0) //ù �� leader�� ���� �ٸ�.
		{
			member[nowBet].leaderBet(totalBet, gambler,betMoney,nowBet,turn,member,dealer);
			member[nowBet].setDieMoney(betMoney);
			while (betMoney == 0) //���� ������ ������ ���
			{
				if (gambler == 1) // �� ���� gambler�� ���� ���
					break;
				nowBet = (nowBet + 1) % survivor;
				while (member[nowBet].nowPlay() == false) //���� �÷��̾ �̹��� ���̸� ���� ���.				
					nowBet = (nowBet + 1) % survivor;
				
				nowPlayName(member[nowBet].getName());
				member[nowBet].leaderBet(totalBet, gambler,betMoney, nowBet, turn, member, dealer);
				member[nowBet].setDieMoney(betMoney);
			}
			first = 999;
		}
		else
		{
			if (member[nowBet].canBet(betMoney) == true) // �� �� �ɷ��� �ִ°� �Ǵ�
				choiceFollower(member, betMoney, totalBet, gambler, i, nowBet, dieBet, dealer, turn);// , pastChoice);

			else
				cant_Bet(member[nowBet], betMoney, gambler, totalBet, member,nowBet);
		}
		
		betting_all(betMoney, totalBet);
	}
	for (int i = 0; i < 5; i++)
		member[i].setDieMoney(0);
	payBet = 0;
	for (int j = 0; j < gambler; j++)
	{
		do {
			payBet = (payBet + 1) % survivor;
		} while (member[payBet].nowPlay() == false);
		member[payBet].payBet(betMoney);
	}
	checkStatus(member);
	showCoinAll(member);

}

void choiceFollower(Player  member[], int& betMoney, int& totalBet, int& gambler, int& bet, int& nowBet,int &dieBet,Player &dealer, int turn)//,int &pastChoice)
{
	int choice,temp;

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
			cant_Bet(member[nowBet], betMoney, gambler, totalBet, member, nowBet);
	
		else
		{
			interCall();
			member[nowBet].call(betMoney, totalBet);//,pastChoice);
			member[nowBet].setDieMoney(betMoney);
		}
		dieBet = -1;
		break;
	case 2: //����
		interDie();
		member[nowBet].playerDie(gambler);
		dieBet = nowBet;
		checkStatus(member);
		if (bet++ < gambler)
		{
			while (member[nowBet].nowPlay() == false) //���� �÷��̾ �̹��� ���̸� ���� ���.
			{
				nowBet = (nowBet + 1) % survivor;
			}
			nowPlayName(member[nowBet].getName());
			betting_all(betMoney,totalBet);
			if (gambler == 1)
				showSentence("�÷��̾� ����",81,12);
			else
				choiceFollower(member, betMoney, totalBet, gambler, bet, nowBet, dieBet,dealer,turn);
		}
		bet--;
		break;
	case 3: // ����, ���� �ݾ� ���� ��� ����

		if (betMoney * 2 <= member[nowBet].getMoney())
		{
			bet = 0; // ���� ���� ������� �ٽ� �ȷο�ó�� ���� ����
			interDouble();
			member[nowBet].doubleBet(betMoney, totalBet);
			member[nowBet].setDieMoney(betMoney);
		}
		else
		{
			showSentence("�ݾ��� ������� �ʽ��ϴ�.",78,12);
			choiceFollower(member, betMoney, totalBet, gambler, bet, betMoney, dieBet,dealer,turn);
		}
		if (dieBet != -1)
			bet = 1;
		dieBet = -1;
		break;
	case 4: // ����
		if (betMoney > totalBet / 2)
		{
			showSentence("������ ���� �ݾ׺��� �����ϴ�.",73,12);
			choiceFollower(member, betMoney, totalBet, gambler, bet, nowBet,dieBet,dealer,turn);
		}
		else if (member[nowBet].getMoney() < totalBet / 2)
		{
			showSentence("���� ���� ���� �ǵ��� ������ ���� �ʽ��ϴ�.",70,12);
			choiceFollower(member, betMoney, totalBet, gambler, bet, nowBet,dieBet, dealer, turn);
		}
		else
		{
			interHalf();
			member[nowBet].halfBet(betMoney, totalBet);
			member[nowBet].setDieMoney(betMoney);
			bet = 0;
		}
		if (dieBet != -1)
			bet = 1;
		dieBet = -1;
		break;
	case 5: //All in
		interAllin();
		bet = 0; // ���� ���� ������� �ٽ� �ȷο�ó�� ���� ����
		member[nowBet].allMoney(betMoney, totalBet, gambler);
		member[nowBet].setDieMoney(betMoney);
		checkStatus(member);
		if (dieBet != -1)
			bet = 1;
		dieBet = -1;
	}
	//pastChoice = choice;
	setColor(GREEN, WHITE);
	gotoxy(81, 12);
	cout << "                       ";
}

void cant_Bet(Player& follwer, int& betMoney, int& gambler, int& totalBet, Player member[],int &nowBet)
{
	int choice;

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
		follwer.dieAllMoney(totalBet, gambler);
		checkStatus(member);
		break;
	case 2: // ����
		follwer.playerDie(gambler);
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

	shuffle(member, dealer);
	picture(dealer.getCard(),member);
	
	
	
	for(int i=0; i<3; i++) // ���� ī�� �й�
		showDealerCard(dealer.getCard(), num1, j,member[0]);
	obliBet(member, totalBet);
	leader = choiceLeader(member, gambler); // ������ �� ���� ���ϸ� �������ʹ� ������ ����� ����

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
	
	if (member[0].getRetire() == false)
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
