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
				if (one.getPMax() <= two.getPMax())
					winner = &two;
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
				if (one.getPMax() <= two.getPMax())
					winner = &two;
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

Player* checkWinner(Player member[],Player &dealer)
{
	Player* temp=&member[0];
	int i;

	for(i=0;member[i].checkSurvivor()==true;i++)
		temp = &member[i];

	i--;

	for (; i < 5; i++)
	{	if(member[i].checkPlayer()==true)
			temp = pchecking((*temp), member[i], dealer);
	}
	return temp;
}