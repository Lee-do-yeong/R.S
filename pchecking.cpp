#include "poker_header.h"

//두명의 패 족보 서로 비교하는 함수
string pchecking(string a, string b, int amax_number, int amax_pattern, int bmax_number, int bmax_pattern)
{
	int arank = rating(a);
	int brank = rating(b);

	string winner;

	// 두 사람의 패 족보 등급이 다를 때
	if (arank > brank)
		winner = "player1";
	else if (arank < brank)
		winner = "player2";

	// 두 사람의 패 족보 등급이 같을 때
	else if (arank == brank)
	{
		// highcard로 같을 때
		if (a == "high_card")
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
		else if (a == "one_pair")
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
		else if (a == "two_pair")
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
		else if (a == "triple")
		{
			if (amax_number > bmax_number)
				winner = "player1";
			else if (amax_number < bmax_number)
				winner = "player2";
		}
		//두 패 모두 스트레이트 인 경우
		else if (a == "straight")
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
		else if (a == "flush")
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
		else if (a == "fullhouse")
		{
			if (amax_number > bmax_number)
				winner = "player1";
			if (amax_number < bmax_number)
				winner = "player2";
		}

		//두 패 모두 four card 인 경우
		else if (a == "four_card")
		{
			if (amax_number > bmax_number)
				winner = "player1";
			else if (amax_number < bmax_number)
				winner = "player2";
		}

		//두 패 모두 straight flush 인 경우
		else if (a == "straight_flush")
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
