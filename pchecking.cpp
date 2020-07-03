#include "poker_header.h"

//두명의 패 족보 서로 비교하는 함수
Player* pchecking(Player& one,Player &two,Player &dealer)
{
	Player* winner=&one;  
	int pedigree1 = Cpedigree_check(one, dealer.getCard(), one.getCard());
	int pedigree2 = Cpedigree_check(two, dealer.getCard(), two.getCard());


	// 두 사람의 패 족보 등급이 다를 때
	if (pedigree1 > pedigree2)
		return &one;
	else if (pedigree1 < pedigree2)
		return &two;

	// 두 사람의 패 족보 등급이 같을 때
	else if (pedigree1 == pedigree2)
	{
		// highcard로 같을 때
		if (pedigree1 == High_card)
		{
			// maxnumber가 큰 사람이 winner
			if (one.getNMax() > two.getNMax())
				winner = &one;
			else if (one.getNMax() >= two.getNMax())
				winner = &two;
			// maxnumber가 같으면 문양으로 승자 결정
			else if (one.getNMax() == two.getNMax())
			{
				if (one.getPMax() > two.getPMax())
					winner = &one;
				if (one.getPMax() <= two.getPMax())
					winner = &two;
			}
		}

		// one pair 로 같을 때
		else if (pedigree1 == One_pair)
		{
			if (one.getNMax() > two.getNMax())
				winner = &one;
			else if (one.getNMax() < two.getNMax())
				winner = &two;
			else if (one.getNMax() == two.getNMax())
			{
				if (one.getPMax() > two.getPMax())
					winner = &one;
				else if (one.getPMax() <= two.getPMax())
					winner = &two;
				else if (one.getPMax() == two.getPMax())
				{
					if (one.getNMax2() > two.getNMax2())
						winner = &one;
					else if (one.getNMax2() < two.getNMax2())
						winner = &two;
					else if (one.getNMax2() == two.getNMax2())
					{
						if (one.getPMax2() > two.getPMax2())
							winner = &one;
						else if (one.getPMax2() <= two.getPMax2())
							winner = &two;
					}
				}
			}
		}

		// two pair 로 같을 때
		else if (pedigree1 == Two_pair)
		{
			if (one.getNMax() > two.getNMax())
				winner = &one;
			else if (one.getNMax() < two.getNMax())
				winner = &two;
			else if (one.getNMax() == two.getNMax())
			{
				if (one.getPMax() > two.getPMax())
					winner = &one;
				if (one.getPMax() < two.getPMax())
					winner = &two;
				if (one.getPMax() == two.getPMax())
				{
					if (one.getNMax2() > two.getNMax2())
						winner = &one;
					if (one.getNMax2() < two.getNMax2())
						winner = &two;
					if (one.getNMax2() == two.getNMax2())
					{
						if (one.getPMax2() > two.getPMax2())
							winner = &one;
						if (one.getPMax2() <= two.getPMax2())
							winner = &two;
					}
				}
			}
		}

		//두 패 모두 트리플 인 경우
		else if (pedigree1 == Triple)
		{
			if (one.getNMax() > two.getNMax())
				winner = &one;
			else if (one.getNMax() <= two.getNMax())
				winner = &two;
		}

		//두 패 모두 스트레이트 인 경우
		else if (pedigree1 == Straight)
		{
			if (one.getNMax() > two.getNMax())
				winner = &one;
			else if (one.getNMax() < two.getNMax())
				winner = &two;
			else if (one.getNMax() == two.getNMax())
			{
				if (one.getPMax() > two.getPMax())
					winner = &one;
				else if (one.getPMax() <= two.getPMax())
					winner = &two;
			}
		}

		// 두 패 모두 flush 인 경우
		else if (pedigree1 == Flush)
		{
			if (one.getPMax() > two.getPMax())
				winner = &one;
			else if (one.getPMax() < two.getPMax())
				winner = &two;
			else if (one.getPMax() == two.getPMax())
			{
				if (one.getNMax() > two.getNMax())
					winner = &one;
				else if (one.getNMax() <= two.getNMax())
					winner = &two;
			}
		}

		// 두 패 모두 full house 인 경우
		else if (pedigree1 == Full_house)
		{
			if (one.getNMax() > two.getNMax())
				winner = &one;
			if (one.getNMax() <= two.getNMax())
				winner = &two;
		}

		//두 패 모두 four card 인 경우
		else if (pedigree1 == Four_card)
		{
			if (one.getNMax() > two.getNMax())
				winner = &one;
			else if (one.getNMax() <= two.getNMax())
				winner = &two;
		}

		//두 패 모두 straight flush 인 경우
		else if (pedigree1 == Straight_flush)
		{
			if (one.getNMax() > two.getNMax())
				winner = &one;
			else if (one.getNMax() < two.getNMax())
				winner = &two;
			else if (one.getNMax() == two.getNMax())
			{
				if (one.getPMax() > two.getPMax())
					winner = &one;
				else if (one.getPMax() <= two.getPMax())
					winner = &two;
			}
		}
	}
	return winner;
}

Player* checkWinner(Player member[],Player &dealer,int gambler)
{
	Player* temp=&member[0];
	int i;

	for (i = 0; member[i].checkSurvivor() == true; i++);
	
	temp = &member[i];

	


	for (int k=0; k < 5; k++)
	{
		if (member[k].checkSurvivor() == false)
		{	
			temp = pchecking((*temp), member[k], dealer);
			//cout << endl;
			//cout << k<<" "<< member[k].getNMax() << " " << member[k].getPMax() << " " << member[k].getNMax2() << " " << member[k].getPMax2() << endl;
		}
	}
	return temp;
}