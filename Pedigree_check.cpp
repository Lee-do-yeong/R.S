#include "poker_header.h"

//족보 검사 함수 Pedigree_check
// 5장의 카드 족보 검사


int aPedigree_check(Player& nowPlay, card dealerCard[], card playerCard[]) // 덱의 숫자R[] , 문양S[], Player 매개변수로 전달
{
	
	int R[5] = { dealerCard[0].getR(),dealerCard[1].getR(),dealerCard[2].getR(),playerCard[0].getR(),playerCard[1].getR() };
	int S[5] = { dealerCard[0].getS(),dealerCard[1].getS(),dealerCard[2].getS(),playerCard[0].getS(),playerCard[1].getS() };
	//먼저 배열 정렬

	arrsort(R, S, 5);

	int ptr1, ptr2;
	// 처음에 Pedigree를  High_card로 초기화
	int Pedigree = High_card;
	// pair 체크
	if (R[0] == R[1] || R[1] == R[2] || R[2] == R[3] || R[3] == R[4])
	{
		//one pair 검사
		if ((R[0] == R[1]) && (R[1] != R[2]) && (R[2] != R[3]) && (R[3] != R[4]))
		{
			Pedigree = One_pair;
			ptr1 = R[1];
			if (S[1] > S[0])
				ptr2 = S[1];
			if (S[1] <= S[0])
				ptr2 = S[0];
			nowPlay.setMax(ptr1, ptr2);
		}
		else if ((R[1] == R[2]) && (R[0] != R[1]) && (R[2] != R[3]) && (R[3] != R[4]))
		{
			Pedigree = One_pair;
			ptr1 = R[2];
			if (S[2] > S[1])
				ptr2 = S[2];
			if (S[2] <= S[1])
				ptr2 = S[1];
			nowPlay.setMax(ptr1, ptr2);
		}
		else if (R[2] == R[3] && R[0] != R[1] && R[1] != R[2] && R[3] != R[4])
		{
			Pedigree = One_pair;
			ptr1 = R[3];
			if (S[2] > S[3])
				ptr2 = S[2];
			if (S[2] <= S[3])
				ptr2 = S[3];
			nowPlay.setMax(ptr1, ptr2);
		}
		else if (R[3] == R[4] && R[0] != R[1] && R[1] != R[2] && R[2] != R[3])
		{
			Pedigree = One_pair;
			ptr1 = R[4];
			ptr2 = 0;
			if (S[3] > S[4])
				ptr2 = S[3];
			if (S[3] <= S[4])
				ptr2 = S[4];
			nowPlay.setMax(ptr1, ptr2);
		}

		// two pair  검사
		else if ((R[0] == R[1]) && (R[2] == R[3]) && (R[1] != R[3] != R[4]))
		{
			Pedigree = Two_pair;
			ptr1 = R[3];
			ptr2 = 0;
			nowPlay.setMax(ptr1, ptr2);
		}
		else if ((R[0] == R[1]) && (R[3] == R[4]) && (R[1] != R[2] != R[4]))
		{
			Pedigree = Two_pair;
			ptr1 = R[4];
			ptr2 = 0;
			nowPlay.setMax(ptr1, ptr2);
		}
		else if ((R[1] == R[2]) && (R[3] == R[4]) && (R[0] != R[1] != R[3]))
		{
			Pedigree = Two_pair;
			ptr1 = R[4];
			ptr2 = 0;
			nowPlay.setMax(ptr1, ptr2);
		}

		//triple 체크
		else if ((R[0] == R[1] == R[2]) && (R[2] != R[3] != R[4]))
		{
			Pedigree = Triple;
			ptr1 = R[2];
			ptr2 = 0;
			nowPlay.setMax(ptr1, ptr2);
		}
		else if ((R[1] == R[2] == R[3]) && (R[0] != R[3] != R[4]))
		{
			Pedigree = Triple;
			ptr1 = R[3];
			ptr2 = 0;
			nowPlay.setMax(ptr1, ptr2);
		}
		else if ((R[2] == R[3] == R[4]) && (R[0] != R[1] != R[4]))
		{
			Pedigree = Triple;
			ptr1 = R[4];
			ptr2 = 0;
			nowPlay.setMax(ptr1, ptr2);
		}

		//full house 체크
		else if ((R[0] == R[1] == R[2]) && (R[3] == R[4]))
		{
			Pedigree = Full_house;
			ptr1 = R[2];
			ptr2 = 0;
			nowPlay.setMax(ptr1, ptr2);
		}
		else if ((R[2] == R[3] == R[4]) && (R[0] == R[1]))
		{
			Pedigree = Full_house;
			ptr1 = R[4];
			ptr2 = 0;
			nowPlay.setMax(ptr1, ptr2);
		}

		//four card 체크
		else if ((R[0] == R[1] == R[2] == R[3]) || (R[1] == R[2] == R[3] == R[4]))
		{
			Pedigree = Four_card;
			if (R[0] == R[1] == R[2] == R[3])
				ptr1 = R[3];
			if (R[1] == R[2] == R[3] == R[4])
				ptr1 = R[4];
			ptr2 = 0;
			nowPlay.setMax(ptr1, ptr2);
		}
	}
	//
	//// flush 체크 (5카드 전부 같은 문양)
	//if ((S[0] == S[1]) && (S[1] == S[2]) && (S[2] == S[3]) && (S[3] == S[4]))
	//{
	//	Pedigree = Flush;
	//	ptr2 = S[4];
	//	ptr1 = R[4];
	//	nowPlay.setMax(ptr1, ptr2);
	//}

	//// straight 체크
	//if ((R[1] == R[0] + 1) && (R[2] == R[1] + 1) && (R[3] == R[2] + 1) && (R[4] == R[3] + 1))
	//{
	//	Pedigree = Straight;
	//	ptr1 = R[4];
	//	ptr2 = S[4];
	//	nowPlay.setMax(ptr1, ptr2);
	//}

	////straight flush 체크 
	//if (((R[1] == R[0] + 1) && (R[2] == R[1] + 1) && (R[3] == R[2] + 1) && (R[4] == R[3] + 1)) && ((S[0] == S[1]) && (S[1] == S[2]) && (S[2] == S[3]) && (S[3] == S[4])))
	//{
	//	Pedigree = Straight_flush;
	//	ptr1 = R[4];
	//	ptr2 = S[4];
	//	nowPlay.setMax(ptr1, ptr2);
	//}
	//if (nowPlay.checkPlayer() == false)
	{
		Pedigree = Die;
	}

	return Pedigree;
}

// 2번째 배팅시 사용하는 족보검사 함수 (카드 6장)
int Bpedigree_check(Player& nowPlay, card dealerCard[], card playerCard[])
{
	int R[6] = { dealerCard[0].getR(),dealerCard[1].getR(),dealerCard[2].getR(),dealerCard[3].getR(),playerCard[0].getR(),playerCard[1].getR() };
	int S[6] = { dealerCard[0].getS(),dealerCard[1].getS(),dealerCard[2].getS(),dealerCard[3].getS(),playerCard[0].getS(),playerCard[1].getS() };

	// 먼저 배열 정렬
	arrsort(R,S,6);

	int ptr1, ptr2;

	int pedigree = High_card;

	// pair!
	if ((R[0] == R[1]) || (R[1] == R[2]) || (R[2] == R[3]) || (R[3] == R[4]) || (R[4] == R[5]))
	{
		// one_pair
		if ((R[0] == R[1]) && (R[1] != R[2] != R[3] != R[4] != R[5]))
		{
			pedigree = One_pair;
			ptr1 = R[1];
			if (S[1] > S[0])
				ptr2 = S[1];
			if (S[1] <= S[0])
				ptr2 = S[0];
			nowPlay.setMax(ptr1, ptr2);
		}
		else if ((R[1] == R[2]) && (R[0] != R[2] != R[3] != R[4] != R[5]))
		{
			pedigree = One_pair;
			ptr1 = R[2];
			if (S[2] > S[1])
				ptr2 = S[2];
			if (S[2] <= S[1])
				ptr2 = S[1];
			nowPlay.setMax(ptr1, ptr2);
		}
		else if ((R[2] == R[3]) && (R[0] != R[1] != R[3] != R[4] != R[5]))
		{
			pedigree = One_pair;
			ptr1 = R[3];
			if (S[3] > S[2])
				ptr2 = S[3];
			if (S[3] <= S[2])
				ptr2 = S[2];
			nowPlay.setMax(ptr1, ptr2);
		}
		else if ((R[3] == R[4]) && (R[0] != R[1] != R[2] != R[4] != R[5]))
		{
			pedigree = One_pair;
			ptr1 = R[4];
			if (S[4] > S[3])
				ptr2 = S[4];
			if (S[4] <= S[3])
				ptr2 = S[3];
			nowPlay.setMax(ptr1, ptr2);
		}
		else if ((R[4] == R[5]) && (R[0] != R[1] != R[2] != R[3] != R[5]))
		{
			pedigree = One_pair;
			ptr1 = R[5];
			if (S[5] > S[4])
				ptr2 = S[5];
			if (S[5] <= S[4])
				ptr2 = S[4];
			nowPlay.setMax(ptr1, ptr2);
		}

		// two_pair
		else if ((R[0] == R[1]) && (R[2] == R[3]) && (R[1] != R[3] != R[4] != R[5]))
		{
			pedigree = Two_pair;
			ptr1 = R[3];
			ptr2 = 0;
			nowPlay.setMax(ptr1, ptr2);
		}
		else if ((R[0] == R[1]) && (R[3] == R[4]) && (R[1] != R[2] != R[4] != R[5]))
		{
			pedigree = Two_pair;
			ptr1 = R[4];
			ptr2 = 0;
			nowPlay.setMax(ptr1, ptr2);
		}
		else if ((R[0] == R[1]) && (R[4] == R[5]) && (R[1] != R[2] != R[3] != R[5]))
		{
			pedigree = Two_pair;
			ptr1 = R[5];
			ptr2 = 0;
			nowPlay.setMax(ptr1, ptr2);
		}
		else if ((R[1] == R[2]) && (R[3] == R[4]) && (R[0] != R[2] != R[4] != R[5]))
		{
			pedigree = Two_pair;
			ptr1 = R[4];
			ptr2 = 0;
			nowPlay.setMax(ptr1, ptr2);
		}
		else if ((R[1] == R[2]) && (R[4] == R[5]) && (R[0] != R[2] != R[3] != R[5]))
		{
			pedigree = Two_pair;
			ptr1 = R[5];
			ptr2 = 0;
			nowPlay.setMax(ptr1, ptr2);
		}
		else if ((R[2] == R[3]) && (R[4] == R[5]) && (R[0] != R[1] != R[3] != R[5]))
		{
			pedigree = Two_pair;
			ptr1 = R[5];
			ptr2 = 0;
			nowPlay.setMax(ptr1, ptr2);
		}

		// Triple
		else if ((R[0] == R[1] == R[2]) && (R[2] != R[3] != R[4] != R[5]))
		{
			pedigree = Triple;
			ptr1 = R[2];
			ptr2 = 0;
			nowPlay.setMax(ptr1, ptr2);
		}
		else if ((R[1] == R[2] == R[3]) && (R[0] != R[3] != R[4] != R[5]))
		{
			pedigree = Triple;
			ptr1 = R[3];
			ptr2 = 0;
			nowPlay.setMax(ptr1, ptr2);
		}
		else if ((R[2] == R[3] == R[4]) && (R[0] != R[1] != R[4] != R[5]))
		{
			pedigree = Triple;
			ptr1 = R[4];
			ptr2 = 0;
			nowPlay.setMax(ptr1, ptr2);
		}
		else if ((R[3] == R[4] == R[5]) && (R[0] != R[1] != R[2] != R[5]))
		{
			pedigree = Triple;
			ptr1 = R[5];
			ptr2 = 0;
			nowPlay.setMax(ptr1, ptr2);
		}

		//full house
		else if ((R[0] == R[1] == R[2]) && (R[3] == R[4]) && (R[2] != R[4] != R[5]))
		{
			pedigree = Full_house;
			ptr1 = R[2];
			ptr2 = 0;
			nowPlay.setMax(ptr1, ptr2);
		}
		else if ((R[0] == R[1] == R[2]) && (R[4] == R[5]) && (R[2] != R[3] != R[5]))
		{
			pedigree = Full_house;
			ptr1 = R[2];
			ptr2 = 0;
			nowPlay.setMax(ptr1, ptr2);
		}
		else if ((R[1] == R[2] == R[3]) && (R[4] == R[5]) && (R[0] != R[3] != R[5]))
		{
			pedigree = Full_house;
			ptr1 = R[3];
			ptr2 = 0;
			nowPlay.setMax(ptr1, ptr2);
		}

		// four card
		else if (R[0] == R[1] == R[2] == R[3])
		{
			pedigree = Four_card;
			ptr1 = R[3];
			ptr2 = 0;
			nowPlay.setMax(ptr1, ptr2);
		}
		else if (R[1] == R[2] == R[3] == R[4])
		{
			pedigree = Four_card;
			ptr1 = R[4];
			ptr2 = 0;
			nowPlay.setMax(ptr1, ptr2);
		}
		else if (R[2] == R[3] == R[4] == R[5])
		{
			pedigree = Four_card;
			ptr1 = R[5];
			ptr2 = 0;
			nowPlay.setMax(ptr1, ptr2);
		}
	}

	////straight
	//if ((R[1] == R[0] + 1) && (R[2] == R[1] + 1) && (R[3] == R[2] + 1) && (R[4] == R[3] + 1))
	//{
	//	pedigree = Straight;
	//	ptr1 = R[4];
	//	ptr2 = S[4];
	//	nowPlay.setMax(ptr1, ptr2);
	//}
	//if ((R[2] == R[1] + 1) && (R[3] == R[2] + 1) && (R[4] == R[3] + 1) && (R[5] == R[4] + 1))
	//{
	//	pedigree = Straight;
	//	ptr1 = R[5];
	//	ptr2 = S[5];
	//	nowPlay.setMax(ptr1, ptr2);
	//}

	////flush
	//if ((S[0] == S[1] == S[2] == S[3] == S[4]) || (S[1] == S[2] == S[3] == S[4] == S[5]))
	//{
	//	if (S[0] == S[1] == S[2] == S[3] == S[4])
	//	{
	//		pedigree = Flush;
	//		ptr1 = R[4];
	//		ptr2 = S[4];
	//		nowPlay.setMax(ptr1, ptr2);
	//	}
	//	if (S[1] == S[2] == S[3] == S[4] == S[5])
	//	{
	//		pedigree = Flush;
	//		ptr1 = R[5];
	//		ptr2 = S[5];
	//		nowPlay.setMax(ptr1, ptr2);
	//	}
	//}

	//// straight flush
	//if (((R[1] == R[0] + 1) && (R[2] == R[1] + 1) && (R[3] == R[2] + 1) && (R[4] == R[3] + 1)) && (S[0] == S[1] == S[2] == S[3] == S[4]))
	//{
	//	pedigree = Straight_flush;
	//	ptr1 = R[4];
	//	ptr2 = S[4];
	//	nowPlay.setMax(ptr1, ptr2);
	//}
	//if (((R[2] == R[1] + 1) && (R[3] == R[2] + 1) && (R[4] == R[3] + 1) && (R[5] == R[4] + 1)) && (S[1] == S[2] == S[3] == S[4] == S[5]))
	//{
	//	pedigree = Straight_flush;
	//	ptr1 = R[5];
	//	ptr2 = S[5];
	//	nowPlay.setMax(ptr1, ptr2);
	//}
	if (nowPlay.checkPlayer() == false)
	{
		pedigree = Die;
	}
	return pedigree;
}

// 세번째 배팅용 족보 검사 함수(카드7장)
int Cpedigree_check(Player& nowPlay, card dealerCard[], card playerCard[])
{
	int R[7] = { dealerCard[0].getR(),dealerCard[1].getR(),dealerCard[2].getR(),dealerCard[3].getR(),dealerCard[4].getR(),playerCard[0].getR(),playerCard[1].getR() };
	int S[7] = { dealerCard[0].getS(),dealerCard[1].getS(),dealerCard[2].getS(),dealerCard[3].getS(),dealerCard[4].getS(),playerCard[0].getS(),playerCard[1].getS() };
	int ptr1, ptr2;

	int pedigree = High_card;
	arrsort(R, S,7);

	ptr1 = R[6];
	ptr2 = S[6];
	nowPlay.setMax(ptr1, ptr2);

	//pair
	if ((R[0] == R[1]) || (R[1] == R[2]) || (R[2] == R[3]) || (R[3] == R[4]) || (R[4] == R[5]) || (R[5] == R[6]))
	{
		// one pair
		if ((R[0] == R[1]) && (R[1] != R[2]) &&(R[2] != R[3]) && (R[3] != R[4]) && (R[4] != R[5]) && (R[5] != R[6]))
		{
			pedigree = One_pair;
			ptr1 = R[1];
			if (S[1] > S[0])
				ptr2 = S[1];
			if (S[1] < S[0])
				ptr2 = S[0];
			nowPlay.setMax(ptr1, ptr2);
		}
		else if ((R[1] == R[2]) && (R[0] != R[2]) && (R[2] != R[3]) && (R[3] != R[4]) && (R[4] != R[5]) && (R[5] != R[6]))
		{
			pedigree = One_pair;
			ptr1 = R[2];
			if (S[2] > S[1])
				ptr2 = S[2];
			if (S[2] < S[1])
				ptr2 = S[1];
			nowPlay.setMax(ptr1, ptr2);
		}
		else if ((R[2] == R[3]) && (R[0] != R[1]) && (R[1] != R[3]) && (R[3] != R[4]) && (R[4] != R[5]) && (R[5] != R[6]))
		{
			pedigree = One_pair;
			ptr1 = R[3];
			if (S[3] > S[2])
				ptr2 = S[3];
			if (S[3] < S[2])
				ptr2 = S[2];
			nowPlay.setMax(ptr1, ptr2);
		}
		else if ((R[3] == R[4]) && (R[0] != R[1]) && (R[1] != R[2]) && (R[2] != R[4]) && (R[4] != R[5]) && (R[5] != R[6]))
		{
			pedigree = One_pair;
			ptr1 = R[4];
			if (S[4] > S[3])
				ptr2 = S[4];
			if (S[4] < S[3])
				ptr2 = S[3];
			nowPlay.setMax(ptr1, ptr2);
		}
		else if ((R[4] == R[5]) && (R[0] != R[1]) && (R[1] != R[2]) && (R[2] != R[3]) && (R[3] != R[5]) && (R[5] != R[6]))
		{
			pedigree = One_pair;
			ptr1 = R[5];
			if (S[5] > S[4])
				ptr2 = S[5];
			if (S[5] < S[4])
				ptr2 = S[4];
			nowPlay.setMax(ptr1, ptr2);
		}
		else if ((R[5] == R[6]) && (R[0] != R[1]) && (R[1] != R[2]) && (R[2] != R[3]) && (R[3] != R[4]) && (R[4] != R[6]))
		{
			pedigree = One_pair;
			ptr1 = R[6];
			if (S[6] > S[5])
				ptr2 = S[6];
			if (S[6] < S[5])
				ptr2 = S[5];
			nowPlay.setMax(ptr1, ptr2);
		}

		// two pair
		else if ((R[0] == R[1]) && (R[2] == R[3]) && (R[1] != R[3]) && (R[3] != R[4]) && (R[4] != R[5]) && (R[5] != R[6]))
		{
			pedigree = Two_pair;
			ptr1 = R[3];
			ptr2 = 0;
			nowPlay.setMax(ptr1, ptr2);
		}
		else if ((R[0] == R[1]) && (R[3] == R[4]) && (R[1] != R[2]) && (R[2] != R[4]) && (R[4] != R[5]) && (R[5] != R[6]))
		{
			pedigree = Two_pair;
			ptr1 = R[4];
			ptr2 = 0;
			nowPlay.setMax(ptr1, ptr2);
		}
		else if ((R[0] == R[1]) && (R[4] == R[5]) && (R[1] != R[2]) && (R[2] != R[3]) && (R[3] != R[5]) && (R[5] != R[6]))
		{
			pedigree = Two_pair;
			ptr1 = R[5];
			ptr2 = 0;
			nowPlay.setMax(ptr1, ptr2);
		}
		else if ((R[0] == R[1]) && (R[5] == R[6]) && (R[1] != R[2]) && (R[2] != R[3]) && (R[3] != R[4]) && (R[4] != R[6]))
		{
			pedigree = Two_pair;
			ptr1 = R[6];
			ptr2 = 0;
			nowPlay.setMax(ptr1, ptr2);
		}
		else if ((R[1] == R[2]) && (R[3] == R[4]) && (R[0] != R[2]) && (R[2] != R[4]) && (R[4] != R[5]) && (R[5] != R[6]))
		{
			pedigree = Two_pair;
			ptr1 = R[4];
			ptr2 = 0;
			nowPlay.setMax(ptr1, ptr2);
		}
		else if ((R[1] == R[2]) && (R[4] == R[5]) && (R[0] != R[2]) && (R[2] != R[3]) && (R[3] != R[5]) && (R[5] != R[6]))
		{
			pedigree = Two_pair;
			ptr1 = R[5];
			ptr2 = 0;
			nowPlay.setMax(ptr1, ptr2);
		}
		else if ((R[1] == R[2]) && (R[5] == R[6]) && (R[0] != R[2]) && (R[2] != R[3]) && (R[3] != R[4]) && (R[4] != R[6]))
		{
			pedigree = Two_pair;
			ptr1 = R[6];
			ptr2 = 0;
			nowPlay.setMax(ptr1, ptr2);
		}
		else if ((R[2] == R[3]) && (R[4] == R[5]) && (R[0] != R[1]) && (R[1] != R[3]) && (R[3] != R[5]) && (R[5] != R[6]))
		{
			pedigree = Two_pair;
			ptr1 = R[5];
			ptr2 = 0;
			nowPlay.setMax(ptr1, ptr2);
		}
		else if ((R[2] == R[3]) && (R[5] == R[6]) && (R[0] != R[1]) && (R[1] != R[3]) && (R[3] != R[4]) && (R[4] != R[6]))
		{
			pedigree = Two_pair;
			ptr1 = R[6];
			ptr2 = 0;
			nowPlay.setMax(ptr1, ptr2);
		}
		else if ((R[3] == R[4]) && (R[5] == R[6]) && (R[0] != R[1]) && (R[1] != R[2]) && (R[2] != R[4]) && (R[4] != R[6]))
		{
			pedigree = Two_pair;
			ptr1 = R[6];
			ptr2 = 0;
			nowPlay.setMax(ptr1, ptr2);
		}

		// triple
		else if ((R[0] == R[1]) && (R[1] == R[2]) && (R[2] != R[3]) && (R[3] != R[4]) && (R[4] != R[5]) && (R[5] != R[6]))
		{
			pedigree = Triple;
			ptr1 = R[2];
			ptr2 = 0;
			nowPlay.setMax(ptr1, ptr2);
		}
		else if ((R[1] == R[2]) && (R[2] == R[3]) && (R[0] != R[3]) && (R[3] != R[4]) && (R[4] != R[5]) && (R[5] != R[6]))
		{
			pedigree = Triple;
			ptr1 = R[3];
			ptr2 = 0;
			nowPlay.setMax(ptr1, ptr2);
		}
		else if ((R[2] == R[3]) && (R[3] == R[4]) && (R[0] != R[1]) && (R[1] != R[4]) && (R[4] != R[5]) && (R[5] != R[6]))
		{
			pedigree = Triple;
			ptr1 = R[4];
			ptr2 = 0;
			nowPlay.setMax(ptr1, ptr2);
		}
		else if ((R[3] == R[4]) && (R[4] == R[5]) && (R[0] != R[1]) && (R[1] != R[2]) && (R[2] != R[5]) && (R[5] != R[6]))
		{
			pedigree = Triple;
			ptr1 = R[5];
			ptr2 = 0;
			nowPlay.setMax(ptr1, ptr2);
		}
		else if ((R[4] == R[5]) && (R[5] == R[6]) && (R[0] != R[1]) && (R[1] != R[2]) && (R[2] != R[3]) && (R[3] != R[6]))
		{
			pedigree = Triple;
			ptr1 = R[6];
			ptr2 = 0;
			nowPlay.setMax(ptr1, ptr2);
		}

		//full house
		else if ((R[0] == R[1]) && (R[1] == R[2]) && (R[3] == R[4]) && (R[2] != R[4]) && (R[4] != R[5]) && (R[5] != R[6]))
		{
			pedigree = Full_house;
			ptr1 = R[2];
			ptr2 = 0;
			nowPlay.setMax(ptr1, ptr2);
		}
		else if ((R[0] == R[1]) && (R[1] == R[2]) && (R[4] == R[5]) && (R[2] != R[3]) && (R[3] != R[5]) && (R[5] != R[6]))
		{
			pedigree = Full_house;
			ptr1 = R[2];
			ptr2 = 0;
			nowPlay.setMax(ptr1, ptr2);
		}
		else if ((R[0] == R[1]) && (R[1] == R[2]) && (R[5] == R[6]) && (R[2] != R[3]) && (R[3] != R[4]) && (R[4] != R[6]))
		{
			pedigree = Full_house;
			ptr1 = R[2];
			ptr2 = 0;
			nowPlay.setMax(ptr1, ptr2);
		}
		else if ((R[1] == R[2]) && (R[2] == R[3]) && (R[4] == R[5]) && (R[0] != R[3]) && (R[3] != R[5]) && (R[5] != R[6]))
		{
			pedigree = Full_house;
			ptr1 = R[3];
			ptr2 = 0;
			nowPlay.setMax(ptr1, ptr2);
		}
		else if ((R[1] == R[2]) && (R[2] == R[3]) && (R[5] == R[6]) && (R[0] != R[3]) && (R[3] != R[4]) && (R[4] != R[6]))
		{
			pedigree = Full_house;
			ptr1 = R[3];
			ptr2 = 0;
			nowPlay.setMax(ptr1, ptr2);
		}
		else if ((R[2] == R[3]) && (R[3] == R[4]) && (R[5] == R[6]) && (R[0] != R[1]) && (R[1] != R[4]) && (R[4] != R[6]))
		{
			pedigree = Full_house;
			ptr1 = R[4];
			ptr2 = S[4];
			nowPlay.setMax(ptr1, ptr2);
		}

		//four card
		else if ((R[0] == R[1]) && (R[1] == R[2]) && (R[2] == R[3]))
		{
			pedigree = Four_card;
			ptr1 = R[3];
			ptr2 = S[3];
			nowPlay.setMax(ptr1, ptr2);
		}
		else if ((R[1] == R[2]) && (R[2] == R[3]) && (R[3] == R[4]))
		{
			pedigree = Four_card;
			ptr1 = R[4];
			ptr2 = S[4];
			nowPlay.setMax(ptr1, ptr2);
		}
		else if ((R[2] == R[3]) && (R[3] == R[4]) && (R[4] == R[5]))
		{
			pedigree = Four_card;
			ptr1 = R[5];
			ptr2 = S[5];
			nowPlay.setMax(ptr1, ptr2);
		}
		else if ((R[3] == R[4]) && (R[4] == R[5]) && (R[5] == R[6]))
		{
			pedigree = Four_card;
			ptr1 = R[6];
			ptr2 = S[6];
			nowPlay.setMax(ptr1, ptr2);
		}
	}

	//straight
	if ((R[1] != R[0] + 1) && (R[2] == R[1] + 1) && (R[3] == R[2] + 1) && (R[4] == R[3] + 1))
	{
		pedigree = Straight;
		ptr1 = R[4];
		ptr2 = S[4];
		nowPlay.setMax(ptr1, ptr2);
	}
	if ((R[2] == R[1] + 1) && (R[3] == R[2] + 1) && (R[4] == R[3] + 1) && (R[5] == R[4] + 1))
	{
		pedigree = Straight;
		ptr1 = R[5];
		ptr2 = S[5];
		nowPlay.setMax(ptr1, ptr2);
	}
	if ((R[3] == R[2] + 1) && (R[4] == R[3] + 1) && (R[5] == R[4] + 1) && (R[6] == R[5] + 1))
	{
		pedigree = Straight;
		ptr1 = R[6];
		ptr2 = S[6];
		nowPlay.setMax(ptr1, ptr2);
	}

	//straight flush
	if (((R[1] != R[0] + 1) && (R[2] == R[1] + 1) && (R[3] == R[2] + 1) && (R[4] == R[3] + 1)) && ((S[0] == S[1]) && (S[1] == S[2]) && (S[2] == S[3]) && (S[3] == S[4])))
	{
		pedigree = Straight_flush;
		ptr1 = R[4];
		ptr2 = S[4];
		nowPlay.setMax(ptr1, ptr2);
	}
	if (((R[2] == R[1] + 1) && (R[3] == R[2] + 1) && (R[4] == R[3] + 1) && (R[5] == R[4] + 1)) && ((S[1] == S[2]) && (S[2] == S[3]) && (S[3] == S[4]) && (S[4] == S[5])))
	{
		pedigree = Straight_flush;
		ptr1 = R[5];
		ptr2 = S[5];
		nowPlay.setMax(ptr1, ptr2);
	}
	if (((R[3] == R[2] + 1) && (R[4] == R[3] + 1) && (R[5] == R[4] + 1) && (R[6] == R[5] + 1)) && ((S[2] == S[3]) && (S[3] == S[4]) && (S[4] == S[5]) && (S[5] == S[6])))
	{
		pedigree = Straight_flush;
		ptr1 = R[6];
		ptr2 = S[6];
		nowPlay.setMax(ptr1, ptr2);
	}

	arrsort(S, R, 7);

	//flush
	if (((S[0] == S[1]) && (S[1] == S[2]) && (S[2] == S[3]) && (S[3] == S[4])) || ((S[1] == S[2]) && (S[2] == S[3]) && (S[3] == S[4]) && (S[4] == S[5])) || ((S[2] == S[3]) && (S[3] == S[4]) && (S[4] == S[5]) && (S[5] == S[6])))
	{
		if ((S[0] == S[1]) && (S[1] == S[2]) && (S[2] == S[3]) && (S[3] == S[4]))
		{
			pedigree = Flush;

			if ((S[4] != S[5]) && (S[5] != S[6]))
			{
				ptr2 = S[4];
				ptr1 = R[4];
				nowPlay.setMax(ptr1, ptr2);
			}
			else if ((S[4] == S[5]) && (S[5] != S[6]))
			{
				ptr2 = S[5];
				ptr1 = R[5];
				nowPlay.setMax(ptr1, ptr2);
			}
			else if ((S[4] == S[5]) && (S[5] == S[6]))
			{
				ptr2 = S[6];
				ptr1 = R[6];
				nowPlay.setMax(ptr1, ptr2);
			}
		}

		if ((S[1] == S[2]) && (S[2] == S[3]) && (S[3] == S[4]) && (S[4] == S[5]))
		{
			pedigree = Flush;
			if (S[5] != S[6])
			{
				ptr2 = S[5];
				ptr1 = R[5];
				nowPlay.setMax(ptr1, ptr2);
			}
			else if (S[5] == S[6])
			{
				ptr2 = S[6];
				ptr1 = R[6];
				nowPlay.setMax(ptr1, ptr2);
			}
		}
		if ((S[2] == S[3]) && (S[3] == S[4]) && (S[4] == S[5]) && (S[5] == S[6]))
		{
			pedigree = Flush;
			ptr2 = S[6];
			ptr1 = R[6];
			nowPlay.setMax(ptr1, ptr2);
		}
	}
	// 플레이어가 die 한 경우
	if (nowPlay.checkPlayer() == false)
	{
		pedigree = Die;
	}
	return pedigree;
}