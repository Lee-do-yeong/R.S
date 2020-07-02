#include "poker_header.h"

using namespace std;

void shuffle(Player member[], Player& dealer)
{
    srand(time(NULL));
    int deck[52];
    int i;

    // 새 덱 생성
    for (i = 0; i < 52; i++)
    {
        deck[i] = i;
    }

    // 덱 셔플
    for (i = 0; i < 52; i++)// 0~12 13~25 26~38 39~51
    {
        int j = rand() % 52;
        int temp = deck[i];
        deck[i] = deck[j];
        deck[j] = temp;
    }


    int a = 0, b = 0, c = 0, d = 0, e = 0;
    int R_base[15], R0[5], R1[2], R2[2], R3[2], R4[2], R5[2]; // 카드 패 숫자 배열
    int S_base[15], S0[5], S1[2], S2[2], S3[2], S4[2], S5[2]; // 카드 패 문양 배열

        // 카드 5개 숫자 get! 기본 카드 5장 플레이어 5명 2장씩
    for (i = 0; i < 15; i++)
    {
        R_base[i] = deck[i] % 13;
        S_base[i] = deck[i] / 13;
    }
    //기본 카드 5장

    
    for (int i = 0; i < 5; i++)
    {
        R0[i] = R_base[i];
        S0[i] = S_base[i];
        dealer.setCardSR(R0[i], S0[i], i);
    }

    //cout << "De : " << dealer.numGetCard(0) << " " << dealer.patGetCard(0) << endl << "De : " << dealer.numGetCard(1) << " " << dealer.patGetCard(1) << endl;
    //플레이어 1 카드 2장
    for (int i = 5; i < 7 && member[0].getRetire() == false; i++)
    {
        R1[a] = R_base[i];
        S1[a] = S_base[i];
        member[0].setCardSR(R1[a], S1[a], a);
        a++;
    }
    //플레이어 2 카드 2장
    for (int i = 7; i < 9 && member[0].getRetire() == false; i++)
    {
        R2[b] = R_base[i];
        S2[b] = S_base[i];
        member[1].setCardSR(R2[b], S2[b], b);
        b++;
    }
    //플레이어 3 카드 2장
    for (int i = 9; i < 11 && member[0].getRetire() == false; i++)
    {
        R3[c] = R_base[i];
        S3[c] = S_base[i];
        member[2].setCardSR(R3[c], S3[c], c);
        c++;
    }
    //플레이어 4 카드 2장
    for (int i = 11; i < 13 && member[0].getRetire() == false; i++)
    {
        R4[d] = R_base[i];
        S4[d] = S_base[i];
        member[3].setCardSR(R4[d], S4[d], d);
        d++;
    }
    //플레이어 5 카드 2장
    for (int i = 13; i < 15 && member[0].getRetire() == false; i++)
    {
        R5[e] = R_base[i];
        S5[e] = S_base[i];
        member[4].setCardSR(R5[e], S5[e], e);
        e++;
    }
}


// 배열 R 정렬
void arrsort(int R[],int S[], int a)
{
    int temp1,temp2;
    bool swapped = false;
    do
    {
        // 1 pass of the bubble sort
        swapped = false;
        for (int i = 0; i < a-1; i++)
        {
            if (R[i] > R[i + 1])
            {
                temp1 = R[i];
                temp2 = S[i];
                R[i] = R[i + 1];
                S[i] = S[i + 1];
                R[i + 1] = temp1;
                S[i + 1] = temp2;
                swapped = true;
            }
        }
    } while (swapped == true);
}
