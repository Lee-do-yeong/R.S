// 2번째 배팅시 사용하는 족보검사 함수 (카드 6장)
int Bpedigree_check(Player& nowPlay, int R[], int S[], Player play)
{
	// 먼저 배열 정렬
	arrsort(R, S, 6);

	int ptr1, ptr2;

	int pedigree = High_card;
	ptr1 = R[5];
	ptr2 = S[5];
	nowPlay.setMax(ptr1, ptr2);

	// pair!
	if ((R[0] == R[1]) || (R[1] == R[2]) || (R[2] == R[3]) || (R[3] == R[4]) || (R[4] == R[5]))
	{
		// one_pair
		if ((R[0] == R[1]) && (R[1] != R[2]) && (R[2] != R[3]) && (R[3] != R[4]) && (R[4] != R[5]))
		{
			pedigree = One_pair;
			ptr1 = R[1];
			if (S[1] > S[0])
				ptr2 = S[1];
			if (S[1] < S[0])
				ptr2 = S[0];
			nowPlay.setMax(ptr1, ptr2);
		}
		else if ((R[1] == R[2]) && (R[0] != R[2]) && (R[2] != R[3]) && (R[3] != R[4]) && (R[4] != R[5]))
		{
			pedigree = One_pair;
			ptr1 = R[2];
			if (S[2] > S[1])
				ptr2 = S[2];
			if (S[2] < S[1])
				ptr2 = S[1];
			nowPlay.setMax(ptr1, ptr2);
		}
		else if ((R[2] == R[3]) && (R[0] != R[1]) && (R[1] != R[3]) && (R[3] != R[4]) && (R[4] != R[5]))
		{
			pedigree = One_pair;
			ptr1 = R[3];
			if (S[3] > S[2])
				ptr2 = S[3];
			if (S[3] < S[2])
				ptr2 = S[2];
			nowPlay.setMax(ptr1, ptr2);
		}
		else if ((R[3] == R[4]) && (R[0] != R[1]) && (R[1] != R[2]) && (R[2] != R[4]) && (R[4] != R[5]))
		{
			pedigree = One_pair;
			ptr1 = R[4];
			if (S[4] > S[3])
				ptr2 = S[4];
			if (S[4] < S[3])
				ptr2 = S[3];
			nowPlay.setMax(ptr1, ptr2);
		}
		else if ((R[4] == R[5]) && (R[0] != R[1]) && (R[1] != R[2]) && (R[2] != R[3]) && (R[3] != R[5]))
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
		else if ((R[0] == R[1]) && (R[2] == R[3]) && (R[1] != R[3]) && (R[3] != R[4]) && (R[4] != R[5]))
		{
			pedigree = Two_pair;
			ptr1 = R[3];
			ptr2 = 0;
			nowPlay.setMax(ptr1, ptr2);
		}
		else if ((R[0] == R[1]) && (R[3] == R[4]) && (R[1] != R[2]) && (R[2] != R[4]) && (R[4] != R[5]))
		{
			pedigree = Two_pair;
			ptr1 = R[4];
			ptr2 = 0;
			nowPlay.setMax(ptr1, ptr2);
		}
		else if ((R[0] == R[1]) && (R[4] == R[5]) && (R[1] != R[2]) && (R[2] != R[3]) && (R[3] != R[5]))
		{
			pedigree = Two_pair;
			ptr1 = R[5];
			ptr2 = 0;
			nowPlay.setMax(ptr1, ptr2);
		}
		else if ((R[1] == R[2]) && (R[3] == R[4]) && (R[0] != R[2]) && (R[2] != R[4]) && (R[4] != R[5]))
		{
			pedigree = Two_pair;
			ptr1 = R[4];
			ptr2 = 0;
			nowPlay.setMax(ptr1, ptr2);
		}
		else if ((R[1] == R[2]) && (R[4] == R[5]) && (R[0] != R[2]) && (R[2] != R[3]) && (R[3] != R[5]))
		{
			pedigree = Two_pair;
			ptr1 = R[5];
			ptr2 = 0;
			nowPlay.setMax(ptr1, ptr2);
		}
		else if ((R[2] == R[3]) && (R[4] == R[5]) && (R[0] != R[1]) && (R[1] != R[3]) && (R[3] != R[5]))
		{
			pedigree = Two_pair;
			ptr1 = R[5];
			ptr2 = 0;
			nowPlay.setMax(ptr1, ptr2);
		}

		// Triple
		else if ((R[0] == R[1]) && (R[1] == R[2]) && (R[2] != R[3]) && (R[3] != R[4]) && (R[4] != R[5]))
		{
			pedigree = Triple;
			ptr1 = R[2];
			ptr2 = 0;
			nowPlay.setMax(ptr1, ptr2);
		}
		else if ((R[1] == R[2]) && (R[2] == R[3]) && (R[0] != R[3]) && (R[3] != R[4]) && (R[4] != R[5]))
		{
			pedigree = Triple;
			ptr1 = R[3];
			ptr2 = 0;
			nowPlay.setMax(ptr1, ptr2);
		}
		else if ((R[2] == R[3]) && (R[3] == R[4]) && (R[0] != R[1]) && (R[1] != R[4]) && (R[4] != R[5]))
		{
			pedigree = Triple;
			ptr1 = R[4];
			ptr2 = 0;
			nowPlay.setMax(ptr1, ptr2);
		}
		else if ((R[3] == R[4]) && (R[4] == R[5]) && (R[0] != R[1]) && (R[1] != R[2]) && (R[2] != R[5]))
		{
			pedigree = Triple;
			ptr1 = R[5];
			ptr2 = 0;
			nowPlay.setMax(ptr1, ptr2);
		}

		//full house
		else if ((R[0] == R[1]) && (R[1] == R[2]) && (R[3] == R[4]) && (R[2] != R[4]) && (R[4] != R[5]))
		{
			pedigree = Full_house;
			ptr1 = R[2];
			ptr2 = 0;
			nowPlay.setMax(ptr1, ptr2);
		}
		else if ((R[0] == R[1]) && (R[1] == R[2]) && (R[4] == R[5]) && (R[2] != R[3]) && (R[3] != R[5]))
		{
			pedigree = Full_house;
			ptr1 = R[2];
			ptr2 = 0;
			nowPlay.setMax(ptr1, ptr2);
		}
		else if ((R[1] == R[2]) && (R[2] == R[3]) && (R[4] == R[5]) && (R[0] != R[3]) && (R[3] != R[5]))
		{
			pedigree = Full_house;
			ptr1 = R[3];
			ptr2 = 0;
			nowPlay.setMax(ptr1, ptr2);
		}

		// four card
		else if ((R[0] == R[1]) && (R[1] == R[2]) && (R[2] == R[3]))
		{
			pedigree = Four_card;
			ptr1 = R[3];
			ptr2 = 0;
			nowPlay.setMax(ptr1, ptr2);
		}
		else if ((R[1] == R[2]) && (R[2] == R[3]) && (R[3] == R[4]))
		{
			pedigree = Four_card;
			ptr1 = R[4];
			ptr2 = 0;
			nowPlay.setMax(ptr1, ptr2);
		}
		else if ((R[2] == R[3]) && (R[3] == R[4]) && (R[4] == R[5]))
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

	// straight flush
	if (((R[1] == R[0] + 1) && (R[2] == R[1] + 1) && (R[3] == R[2] + 1) && (R[4] == R[3] + 1)) && (S[0] == S[1]) && (S[1] == S[2]) && (S[2] == S[3]) && (S[3] == S[4]))
	{
		pedigree = Straight_flush;
		ptr1 = R[4];
		ptr2 = S[4];
		nowPlay.setMax(ptr1, ptr2);
	}
	if (((R[2] == R[1] + 1) && (R[3] == R[2] + 1) && (R[4] == R[3] + 1) && (R[5] == R[4] + 1)) && (S[1] == S[2]) && (S[2] == S[3]) && (S[3] == S[4]) && (S[4] == S[5]))
	{
		pedigree = Straight_flush;
		ptr1 = R[5];
		ptr2 = S[5];
		nowPlay.setMax(ptr1, ptr2);
	}

	arrsort(S, R, 6);

	//flush
	if ((S[0] == S[1]) && (S[1] == S[2]) && (S[2] == S[3]) && (S[3] == S[4]))
	{
		pedigree = Flush;
		ptr1 = R[4];
		ptr2 = S[4];
		nowPlay.setMax(ptr1, ptr2);

	if ((S[1] == S[2]) && (S[2] == S[3]) && (S[3] == S[4]) && (S[4] == S[5]))
	{
		pedigree = Flush;
		ptr1 = R[5];
		ptr2 = S[5];
		nowPlay.setMax(ptr1, ptr2);
		}
	}
	//플레이어가 die 했을 경우
	if (play.checkPlay() == fasle)
	{
		pedigree = Die;
	}
	return pedigree;
}
