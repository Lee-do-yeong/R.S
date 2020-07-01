#include "poker_header.h"

//족보 검사 함수 Pedigree_check
// 5장의 카드 족보 검사


string Pedigree_check(Player &nowPlay,int R[], int S[]) // 덱의 숫자R[] , 문양S[] 매개변수로 전달
{
    int ptr1, ptr2;
    // 처음에 Pedigree를  high_card로 초기화
    string  Pedigree = "high_card";

    // straight 체크
    if ((R[1] == R[0] + 1) && (R[2] == R[1] + 1) && (R[3] == R[2] + 1) && (R[4] == R[3] + 1))
    {
        //cout << "straight!" << endl;
        Pedigree = "straight";
        ptr1 = R[4];
        ptr2 = S[4];
        nowPlay.setMax(ptr1, ptr2);
    }
    else
    {
        //cout << "No straight" << endl;
    }

    // pair 체크
    if (R[0] == R[1] || R[1] == R[2] || R[2] == R[3] || R[3] == R[4])
    {
        //cout << "pair!" << endl;

        //one pair 검사
        if (R[0] == R[1] && R[1] != R[2] && R[2] != R[3] && R[3] != R[4])
        {
            Pedigree = "one_pair";
            ptr1 = R[1];
            if (S[1] > S[0])
                ptr2 = S[1];
            if (S[1] < S[0])
                ptr2 = S[0];
            nowPlay.setMax(ptr1, ptr2);
        }
        else if (R[1] == R[2] && R[0] != R[1] && R[2] != R[3] && R[3] != R[4])
        {
            Pedigree = "one_pair";
            ptr1 = R[2];
            if (S[2] > S[1])
                ptr2 = S[2];
            if (S[2] < S[1])
                ptr2 = S[1];
            nowPlay.setMax(ptr1, ptr2);
        }
        else if (R[2] == R[3] && R[0] != R[1] && R[1] != R[2] && R[3] != R[4])
        {
            Pedigree = "one_pair";
            ptr1 = R[3];
            if (S[2] > S[3])
                ptr2 = S[2];
            if (S[2] < S[3])
                ptr2 = S[3];
            nowPlay.setMax(ptr1, ptr2);
        }
        else if (R[3] == R[4] && R[0] != R[1] && R[1] != R[2] && R[2] != R[3])
        {
            Pedigree = "one_pair";
            ptr1 = R[4];
            if (S[3] > S[4])
                ptr2 = S[3];
            if (S[3] < S[4])
                ptr2 = S[4];
            nowPlay.setMax(ptr1, ptr2);
        }
        // two pair  검사
        else if ((R[0] == R[1]) && (R[2] == R[3]) && (R[0] != R[2] != R[4]))
        {
            Pedigree = "two_pair";
            ptr1 = R[3];
            ptr2 = 0;
            nowPlay.setMax(ptr1, ptr2);
        }
        else if ((R[1] == R[2]) && (R[3] == R[4]) && (R[0] != R[1] != R[3]))
        {
            Pedigree = "two_pair";
            ptr1 = R[4];
            ptr2 = 0;
            nowPlay.setMax(ptr1, ptr2);
        }
        else
        {
            //cout << "No pair" << endl;
        }
    }

    //triple 체크
    if ((R[0] == R[1] == R[2] && R[2] != R[3] != R[4]) || (R[1] == R[2] == R[3] && R[0] != R[1] && R[3] != R[4]) || (R[2] == R[3] == R[4] && R[0] != R[1] != R[2]))
    {
        //cout << "Triple!" << endl;
        Pedigree = "triple";
        if (R[0] == R[1] == R[2] && R[2] != R[3] != R[4])
            ptr1 = R[2];
        if(R[1] == R[2] == R[3] && R[0] != R[1] && R[3] != R[4])
            ptr1 = R[3];
        if (R[2] == R[3] == R[4] && R[0] != R[1] != R[2])
            ptr1 = R[4];
        ptr2 = 0;
        nowPlay.setMax(ptr1, ptr2);
    }
    else
    {
        //cout << "No triple!" << endl;
    }

    //full house 체크
    if (((R[0] == R[1] == R[2]) && (R[3] == R[4]) && (R[0] != R[3])) || ((R[2] == R[3] == R[4]) && (R[0] == R[1]) && (R[2] != R[0])))
    {
        //cout << "Full house!" << endl;
        Pedigree = "full_house";
        if ((R[0] == R[1] == R[2]) && (R[3] == R[4]))
        {
            ptr1 = R[2];
        }
        else if ((R[2] == R[3] == R[4]) && (R[0] == R[1]) && (R[2] != R[0]))
        {
            ptr1 = R[4];
        }
        ptr2 = 0;
        nowPlay.setMax(ptr1, ptr2);
    }
    else
    {
        //cout << "No full house" << endl;
    }

    // flush 체크 (5카드 전부 같은 문양)
    if (S[0] == S[1] && S[1] == S[2] && S[2] == S[3] && S[3] == S[4])
    {
        //cout << "flush!" << endl;
        Pedigree = "flush";
        ptr2 = S[4];
        ptr1 = R[4];
        nowPlay.setMax(ptr1, ptr2);
    }
    else
    {
        //cout << "No flush" << endl;
    }
    //straight flush 체크 
    if (R[1] == R[0] + 1 && R[2] == R[1] + 1 && R[3] == R[2] + 1 && R[4] == R[3] + 1)
        if (S[0] == S[1] && S[1] == S[2] && S[2] == S[3] && S[3] == S[4])
        {
            //cout << "straight flush!" << endl;
            Pedigree = "straight_flush";
            ptr1 = R[4];
            ptr2 = S[4];
            nowPlay.setMax(ptr1, ptr2);
        }
        else
        {
            //cout << "No straight flush" << endl;
        }

    //four card 체크
    if ((R[0] == R[1] == R[2] == R[3]) || (R[1] == R[2] == R[3] == R[4]))
    {
        ptr1 = 0;
        //cout << "four card!" << endl;
        Pedigree = "four_card";
        if (R[0] == R[1] == R[2] == R[3] || R[3] != R[4])
            ptr1 = R[3];
        if (R[1] == R[2] == R[3] == R[4])
            ptr1 = R[4];
        ptr2 = 0;
        nowPlay.setMax(ptr1, ptr2);
    }
    else
    {
        //cout << "No four card" << endl;
    }
    return Pedigree;
}
