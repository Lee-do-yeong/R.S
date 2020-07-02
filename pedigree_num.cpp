#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>

using namespace std;

enum Pedi {
	Die = 0, // 플레이어가 죽은 경우
	High_card, // 보드와 무관한 카드 숫자가 높은 사람이 이김
	  //카드 숫자가 모두 똑같으면 비김 // 1
//문양따라가는걸로 순위 매김
One_pair, // 같은숫자 2개 1쌍 // 2
Two_pair, // 같은 숫자 2개 2쌍 // 3
Triple, //같은숫자 3개 // 4
Straight, //연속된 숫자 5개 // 5
Flush, //같은문양 5개 // 6
Full_house, // 트리플 + 원페어 // 7
Four_card, // 같은숫자 4개 // 8
Straight_flush //같은문양, 숫자 오름차순 5개 // 9
};

//두명의 패 족보 서로 비교하는 함수
string pchecking(int pedigree1, int pedigree2, int amax_number, int amax_pattern, int bmax_number, int bmax_pattern);

// 세번째 배팅용 족보 검사 함수(카드7장)
int Cpedigree_check(int R[], int S[], int& ptr1, int& ptr2);

//두명의 패 족보 서로 비교하는 함수
string pchecking(int pedigree1, int pedigree2 , int amax_number, int amax_pattern, int bmax_number, int bmax_pattern)
{
	string winner;

	// 두 사람의 패 족보 등급이 다를 때
	if (pedigree1 > pedigree2)
		winner = "player1";
	else if (pedigree1 < pedigree2)
		winner = "player2";

	// 두 사람의 패 족보 등급이 같을 때
	else if (pedigree1 == pedigree2)
	{
		// highcard로 같을 때
		if (pedigree1 == High_card)
		{
			// maxnumber가 큰 사람이 winner
			if (amax_number > bmax_number)
				winner = "player 1";
			else if (amax_number > bmax_number)
				winner = "player 2";
			// maxnumber가 같으면 문양으로 승자 결정
			else if(amax_number == bmax_number)
			{
				if (amax_pattern > bmax_pattern)
					winner = "player 1";
				if (amax_pattern < bmax_pattern)
					winner = "player 2";
			}
		}

		// one pair 로 같을 때
		else if (pedigree1 == One_pair)
		{
			if (amax_number > bmax_number)
				winner = "player 1";
			else if (amax_number < bmax_number)
				winner = "player 2";
			else if (amax_number == bmax_number)
			{
				if (amax_pattern > bmax_pattern)
					winner = " player1";
				if (amax_pattern < bmax_pattern)
					winner = " player2";
			}
		}

	    // two pair 로 같을 때
		else if (pedigree1 == Two_pair)
		{
			if (amax_number > bmax_number)
				winner = "player1";
			else if (amax_number < bmax_number)
				winner = "player2";
			else if (amax_number == bmax_number)
			{
				if (amax_pattern > bmax_pattern)
					winner = "player1";
				if (amax_pattern < bmax_pattern)
					winner = "player2";
			}
		}

		//두 패 모두 트리플 인 경우
		else if (pedigree1 == Triple)
		{
			if (amax_number > bmax_number)
				winner = "player1";
			else if (amax_number < bmax_number)
				winner = "player2";
		}

		//두 패 모두 스트레이트 인 경우
		else if (pedigree1 == Straight)
		{
			if (amax_number > bmax_number)
				winner = "player1";
			else if (amax_number < bmax_number)
				winner = "player2";
			else if (amax_number == bmax_number)
			{
				if (amax_pattern > bmax_pattern)
					winner = "player1";
				else if (amax_pattern < bmax_pattern)
					winner = "player2";
			}
		}

		// 두 패 모두 flush 인 경우
		else if (pedigree1 == Flush)
		{
			if (amax_pattern > bmax_pattern)
				winner = "player1";
			else if (amax_pattern < bmax_pattern)
				winner = "player2";
			else if (amax_pattern == bmax_pattern)
			{
				if(amax_number > bmax_number)
					winner = "player1";
				else if (amax_number < bmax_number)
					winner = "player2";
			}
		}

		// 두 패 모두 full house 인 경우
		else if (pedigree1 == Full_house)
		{
			if (amax_number > bmax_number)
				winner = "player1";
			if (amax_number < bmax_number)
				winner = "player2";
		}

		//두 패 모두 four card 인 경우
		else if (pedigree1 == Four_card)
		{
			if (amax_number > bmax_number)
				winner = "player1";
			else if (amax_number < bmax_number)
				winner = "player2";
		}

		//두 패 모두 straight flush 인 경우
		else if (pedigree1 == Straight_flush)
		{
		    if (amax_number > bmax_number)
			    winner = "player1";
		    else if (amax_number < bmax_number)
			    winner = "player2";
		    else if (amax_number == bmax_number)
		    {
			    if (amax_pattern > bmax_pattern)
				    winner = "player1";
				else if (amax_pattern < bmax_pattern)
					winner = "player2";
		    }
		}
	}
	return winner;
}

// 2번째 배팅시 사용하는 족보검사 함수 (카드 6장)
int Bpedigree_check(Player& nowPlay, int R[], int S[], Player play)
{
	// 먼저 배열 정렬
	arrsort(R, S, 6);

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
			if (S[1] < S[0])
				ptr2 = S[0];
			nowPlay.setMax(ptr1, ptr2);
		}
		else if ((R[1] == R[2]) && (R[0] != R[2] != R[3] != R[4] != R[5]))
		{
			pedigree = One_pair;
			ptr1 = R[2];
			if (S[2] > S[1])
				ptr2 = S[2];
			if (S[2] < S[1])
				ptr2 = S[1];
			nowPlay.setMax(ptr1, ptr2);
		}
		else if ((R[2] == R[3]) && (R[0] != R[1] != R[3] != R[4] != R[5]))
		{
			pedigree = One_pair;
			ptr1 = R[3];
			if (S[3] > S[2])
				ptr2 = S[3];
			if (S[3] < S[2])
				ptr2 = S[2];
			nowPlay.setMax(ptr1, ptr2);
		}
		else if ((R[3] == R[4]) && (R[0] != R[1] != R[2] != R[4] != R[5]))
		{
			pedigree = One_pair;
			ptr1 = R[4];
			if (S[4] > S[3])
				ptr2 = S[4];
			if (S[4] < S[3])
				ptr2 = S[3];
			nowPlay.setMax(ptr1, ptr2);
		}
		else if ((R[4] == R[5]) && (R[0] != R[1] != R[2] != R[3] != R[5]))
		{
			pedigree = One_pair;
			ptr1 = R[5];
			if (S[5] > S[4])
				ptr2 = S[5];
			if (S[5] < S[4])
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

	//straight
	if ((R[1] == R[0] + 1) && (R[2] == R[1] + 1) && (R[3] == R[2] + 1) && (R[4] == R[3] + 1))
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

	//flush
	if ((S[0] == S[1] == S[2] == S[3] == S[4]) || (S[1] == S[2] == S[3] == S[4] == S[5]))
	{
		if (S[0] == S[1] == S[2] == S[3] == S[4])
		{
			pedigree = Flush;
			ptr1 = R[4];
			ptr2 = S[4];
			nowPlay.setMax(ptr1, ptr2);
		}
		if (S[1] == S[2] == S[3] == S[4] == S[5])
		{
			pedigree = Flush;
			ptr1 = R[5];
			ptr2 = S[5];
			nowPlay.setMax(ptr1, ptr2);
		}
	}

	// straight flush
	if (((R[1] == R[0] + 1) && (R[2] == R[1] + 1) && (R[3] == R[2] + 1) && (R[4] == R[3] + 1)) && (S[0] == S[1] == S[2] == S[3] == S[4]))
	{
		pedigree = Straight_flush;
		ptr1 = R[4];
		ptr2 = S[4];
		nowPlay.setMax(ptr1, ptr2);
	}
	if (((R[2] == R[1] + 1) && (R[3] == R[2] + 1) && (R[4] == R[3] + 1) && (R[5] == R[4] + 1)) && (S[1] == S[2] == S[3] == S[4] == S[5]))
	{
		pedigree = Straight_flush;
		ptr1 = R[5];
		ptr2 = S[5];
		nowPlay.setMax(ptr1, ptr2);
	}
	if (play.checkPlay() == fasle)
	{
		pedigree = Die;
	}
	return pedigree;
}

// 세번째 배팅용 족보 검사 함수(카드7장)
int Cpedigree_check(Player& nowPlay, int R[], int S[], Player play)
{
	arrsort(R, S, 7);

	int ptr1, ptr2;

	int pedigree = High_card;
	
	//pair
	if ((R[0] == R[1]) || (R[1] == R[2]) || (R[2] == R[3]) || (R[3] == R[4]) || (R[4] == R[5]) || (R[5] == R[6]))
	{
		// one pair
		if ((R[0] == R[1]) && (R[1] != R[2] != R[3] != R[4] != R[5] != R[6]))
		{
			pedigree = One_pair;
			ptr1 = R[1];
			if (S[1] > S[0])
				ptr2 = S[1];
			if (S[1] < S[0])
				ptr2 = S[0];
			nowPlay.setMax(ptr1, ptr2);
		}
		else if ((R[1] == R[2]) && (R[0] != R[2] != R[3] != R[4] != R[5] != R[6]))
		{
			pedigree = One_pair;
			ptr1 = R[2];
			if (S[2] > S[1])
				ptr2 = S[2];
			if (S[2] < S[1])
				ptr2 = S[1];
			nowPlay.setMax(ptr1, ptr2);
		}
		else if ((R[2] == R[3]) && (R[0] != R[1] != R[3] != R[4] != R[5] != R[6]))
		{
			pedigree = One_pair;
			ptr1 = R[3];
			if (S[3] > S[2])
				ptr2 = S[3];
			if (S[3] < S[2])
				ptr2 = S[2];
			nowPlay.setMax(ptr1, ptr2);
		}
		else if ((R[3] == R[4]) && (R[0] != R[1] != R[2] != R[4] != R[5] != R[6]))
		{
			pedigree = One_pair;
			ptr1 = R[4];
			if (S[4] > S[3])
				ptr2 = S[4];
			if (S[4] < S[3])
				ptr2 = S[3];
			nowPlay.setMax(ptr1, ptr2);
		}
		else if ((R[4] == R[5]) && (R[0] != R[1] != R[2] != R[3] != R[5] != R[6]))
		{
			pedigree = One_pair;
			ptr1 = R[5];
			if (S[5] > S[4])
				ptr2 = S[5];
			if (S[5] < S[4])
				ptr2 = S[4];
			nowPlay.setMax(ptr1, ptr2);
		}
		else if ((R[5] == R[6]) && (R[0] != R[1] != R[2] != R[3] != R[4] != R[6]))
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
		else if ((R[0] == R[1]) && (R[2] == R[3]) && (R[1] != R[3] != R[4] != R[5] != R[6]))
		{
			pedigree = Two_pair;
			ptr1 = R[3];
			ptr2 = 0;
			nowPlay.setMax(ptr1, ptr2);
		}
		else if ((R[0] == R[1]) && (R[3] == R[4]) && (R[1] != R[2] != R[4] != R[5] != R[6]))
		{
			pedigree = Two_pair;
			ptr1 = R[4];
			ptr2 = 0;
			nowPlay.setMax(ptr1, ptr2);
		}
		else if ((R[0] == R[1]) && (R[4] == R[5]) && (R[1] != R[2] != R[3] != R[5] != R[6]))
		{
			pedigree = Two_pair;
			ptr1 = R[5];
			ptr2 = 0;
			nowPlay.setMax(ptr1, ptr2);
		}
		else if ((R[0] == R[1]) && (R[5] == R[6]) && (R[1] != R[2] != R[3] != R[4] != R[6]))
		{
			pedigree = Two_pair;
			ptr1 = R[6];
			ptr2 = 0;
			nowPlay.setMax(ptr1, ptr2);
		}
		else if ((R[1] == R[2]) && (R[3] == R[4]) && (R[0] != R[2] != R[4] != R[5] != R[6]))
		{
			pedigree = Two_pair;
			ptr1 = R[4];
			ptr2 = 0;
			nowPlay.setMax(ptr1, ptr2);
		}
		else if ((R[1] == R[2]) && (R[4] == R[5]) && (R[0] != R[2] != R[3] != R[5] != R[6]))
		{
			pedigree = Two_pair;
			ptr1 = R[5];
			ptr2 = 0;
			nowPlay.setMax(ptr1, ptr2);
		}
		else if ((R[1] == R[2]) && (R[5] == R[6]) && (R[0] != R[2] != R[3] != R[4] != R[6]))
		{
			pedigree = Two_pair;
			ptr1 = R[6];
			ptr2 = 0;
			nowPlay.setMax(ptr1, ptr2);
		}
		else if ((R[2] == R[3]) && (R[4] == R[5]) && (R[0] != R[1] != R[3] != R[5] != R[6]))
		{
			pedigree = Two_pair;
			ptr1 = R[5];
			ptr2 = 0;
			nowPlay.setMax(ptr1, ptr2);
		}
		else if ((R[2] == R[3]) && (R[5] == R[6]) && (R[0] != R[1] != R[3] != R[4] != R[6]))
		{
			pedigree = Two_pair;
			ptr1 = R[6];
			ptr2 = 0;
			nowPlay.setMax(ptr1, ptr2);
		}
		else if ((R[3] == R[4]) && (R[5] == R[6]) && (R[0] != R[1] != R[2] != R[4] != R[6]))
		{
			pedigree = Two_pair;
			ptr1 = R[6];
			ptr2 = 0;
			nowPlay.setMax(ptr1, ptr2);
		}

		// triple
		else if ((R[0] == R[1] == R[2]) && (R[2] != R[3] != R[4] != R[5] != R[6]))
		{
		    pedigree = Triple;
		    ptr1 = R[2];
	     	ptr2 = 0;
	    	nowPlay.setMax(ptr1, ptr2);
		}
		else if ((R[1] == R[2] == R[3]) && (R[0] != R[3] != R[4] != R[5] != R[6]))
		{
	    	pedigree = Triple;
	    	ptr1 = R[3];
	    	ptr2 = 0;
	    	nowPlay.setMax(ptr1, ptr2);
		}
		else if ((R[2] == R[3] == R[4]) && (R[0] != R[1] != R[4] != R[5] != R[6]))
		{
	    	pedigree = Triple;
	     	ptr1 = R[4];
	     	ptr2 = 0;
	    	nowPlay.setMax(ptr1, ptr2);
		}
		else if ((R[3] == R[4] == R[5]) && (R[0] != R[1] != R[2] != R[5] != R[6]))
		{
	     	pedigree = Triple;
	    	ptr1 = R[5];
	    	ptr2 = 0;
	    	nowPlay.setMax(ptr1, ptr2);
		}
		else if ((R[4] == R[5] == R[6]) && (R[0] != R[1] != R[2] != R[3] != R[6]))
		{
	     	pedigree = Triple;
	    	ptr1 = R[6];
	     	ptr2 = 0;
	    	nowPlay.setMax(ptr1, ptr2);
		}

		//full house
		else if ((R[0] == R[1] == R[2]) && (R[3] == R[4]) && (R[2] != R[4] != R[5] != R[6]))
		{
	    	pedigree = Full_house;
	    	ptr1 = R[2];
	    	ptr2 = 0;
		    nowPlay.setMax(ptr1, ptr2);
		}
		else if ((R[0] == R[1] == R[2]) && (R[4] == R[5]) && (R[2] != R[3] != R[5] != R[6]))
		{
	    	pedigree = Full_house;
		    ptr1 = R[2];
	     	ptr2 = 0;
	    	nowPlay.setMax(ptr1, ptr2);
		}
		else if ((R[0] == R[1] == R[2]) && (R[5] == R[6]) && (R[2] != R[3] != R[4] != R[6]))
		{
		    pedigree = Full_house;
	     	ptr1 = R[2];
    		ptr2 = 0;
    		nowPlay.setMax(ptr1, ptr2);
		}
		else if ((R[1] == R[2] == R[3]) && (R[4] == R[5]) && (R[0] != R[3] != R[5] != R[6]))
		{
	    	pedigree = Full_house;
	    	ptr1 = R[3];
			ptr2 = 0;
			nowPlay.setMax(ptr1, ptr2);
		}
		else if ((R[1] == R[2] == R[3]) && (R[5] == R[6]) && (R[0] != R[3] != R[4] != R[6]))
		{
		    pedigree = Full_house;
		    ptr1 = R[3];
		    ptr2 = 0;
		    nowPlay.setMax(ptr1, ptr2);
		}
		else if ((R[2] == R[3] == R[4]) && (R[5] == R[6]) && (R[0] != R[1] != R[4] != R[6]))
		{
		    pedigree = Full_house;
		    ptr1 = R[4];
		    ptr2 = S[4];
		    nowPlay.setMax(ptr1, ptr2);
		}

		//four card
		else if (R[0] == R[1] == R[2] == R[3])
		{
		    pedigree = Four_card;
		    ptr1 = R[3];
		    ptr2 = S[3];
		    nowPlay.setMax(ptr1, ptr2);
		}
		else if (R[1] == R[2] == R[3] == R[4])
		{
		    pedigree = Four_card;
		    ptr1 = R[4];
		    ptr2 = S[4];
		    nowPlay.setMax(ptr1, ptr2);
		}
		else if (R[2] == R[3] == R[4] == R[5])
		{
		    pedigree = Four_card;
		    ptr1 = R[5];
		    ptr2 = S[5];
		    nowPlay.setMax(ptr1, ptr2);
		}
		else if (R[3] == R[4] == R[5] == R[6])
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

	//flush
	if (S[0] == S[1] == S[2] == S[3] == S[4])
	{
		pedigree = Flush;
		ptr1 = R[4];
		ptr2 = S[4];
		nowPlay.setMax(ptr1, ptr2);
	}
	if (S[1] == S[2] == S[3] == S[4] == S[5])
	{
		pedigree = Flush;
		ptr1 = R[5];
		ptr2 = S[5];
		nowPlay.setMax(ptr1, ptr2);
	}
	if (S[2] == S[3] == S[4] == S[5] == S[6])
	{
		pedigree = Flush;
		ptr1 = R[6];
		ptr2 = S[6];
		nowPlay.setMax(ptr1, ptr2);
	}

	//straight flush
	if (((R[1] != R[0] + 1) && (R[2] == R[1] + 1) && (R[3] == R[2] + 1) && (R[4] == R[3] + 1)) && (S[0] == S[1] == S[2] == S[3] == S[4]))
	{
		pedigree = Straight_flush;
		ptr1 = R[4];
		ptr2 = S[4];
		nowPlay.setMax(ptr1, ptr2);
	}
	if (((R[2] == R[1] + 1) && (R[3] == R[2] + 1) && (R[4] == R[3] + 1) && (R[5] == R[4] + 1)) && (S[1] == S[2] == S[3] == S[4] == S[5]))
	{
		pedigree = Straight_flush;
		ptr1 = R[5];
		ptr2 = S[5];
		nowPlay.setMax(ptr1, ptr2);
	}
	if (((R[3] == R[2] + 1) && (R[4] == R[3] + 1) && (R[5] == R[4] + 1) && (R[6] == R[5] + 1)) && (S[2] == S[3] == S[4] == S[5] == S[6]))
	{
		pedigree = Straight_flush;
		ptr1 = R[6];
		ptr2 = S[6];
		nowPlay.setMax(ptr1, ptr2);
	}
	if (play.checkPlay() == fasle)
	{
		pedigree = Die;
	}
	return pedigree;
}