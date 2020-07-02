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
    for (int i = 5; i < 7 && member[0].checkSurvivor() == false; i++)
    {
        R1[a] = R_base[i];
        S1[a] = S_base[i];
        member[0].setCardSR(R1[a], S1[a], a);
        a++;
    }
    //플레이어 2 카드 2장
    for (int i = 7; i < 9 && member[0].checkSurvivor() == false; i++)
    {
        R2[b] = R_base[i];
        S2[b] = S_base[i];
        member[1].setCardSR(R2[b], S2[b], b);
        b++;
    }
    //플레이어 3 카드 2장
    for (int i = 9; i < 11 && member[0].checkSurvivor() == false; i++)
    {
        R3[c] = R_base[i];
        S3[c] = S_base[i];
        member[2].setCardSR(R3[c], S3[c], c);
        c++;
    }
    //플레이어 4 카드 2장
    for (int i = 11; i < 13 && member[0].checkSurvivor() == false; i++)
    {
        R4[d] = R_base[i];
        S4[d] = S_base[i];
        member[3].setCardSR(R4[d], S4[d], d);
        d++;
    }
    //플레이어 5 카드 2장
    for (int i = 13; i < 15 && member[0].checkSurvivor() == false; i++)
    {
        R5[e] = R_base[i];
        S5[e] = S_base[i];
        member[4].setCardSR(R5[e], S5[e], e);
        e++;
    }
}
//void checkFamilyTree(Player member[],int R0[],int R1[], int R2[], int R3[], int R4[], int R5[],int num)
//{
//    //베이스 덱 + 플레이어들 패 -> 플레이어들 덱
//    int R1a[7], R2a[7], R3a[7], R4a[7], R5a[7], R6a[7], R7a[7]; // 배팅시 쓸 덱(숫자)
//    int S1a[7], S2a[7], S3a[7], S4a[7], S5a[7], S6a[7], S7a[7]; // 배팅시 쓸 덱(문양)
//
//    string pedigree1, pedigree2, pedigree3, pedigree4, pedigree5;
//
//    switch (num)
//    {
//    case 5:
//        R1a[0] = R0[0]; R1a[1] = R0[1]; R1a[2] = R0[2]; R1a[3] = R1[0]; R1a[4] = R1[1];
//        R2a[0] = R0[0]; R2a[1] = R0[1]; R2a[2] = R0[2]; R2a[3] = R2[0]; R2a[4] = R2[1];
//        R3a[0] = R0[0]; R3a[1] = R0[1]; R3a[2] = R0[2]; R3a[3] = R3[0]; R3a[4] = R3[1];
//        R4a[0] = R0[0]; R4a[1] = R0[1]; R4a[2] = R0[2]; R4a[3] = R4[0]; R4a[4] = R4[1];
//        R5a[0] = R0[0]; R5a[1] = R0[1]; R5a[2] = R0[2]; R5a[3] = R5[0]; R5a[4] = R5[1];
//
//        //정렬
//        arrsort(R1a, S1a, 5);
//        arrsort(R2a, S2a, 5);
//        arrsort(R3a, S3a, 5);
//        arrsort(R4a, S4a, 5);
//        arrsort(R5a, S5a, 5);
//
//        //int* ptra1 = &max_number1; int* ptrb1 = &max_number2; int* ptrc1 = &max_number3; int* ptrd1 = &max_number4; int* ptre1 = &max_number5;
//        //int* ptra2 = &max_pattern1; int* ptrb2 = &max_pattern2; int* ptrc2 = &max_pattern3; int* ptrd2 = &max_pattern4; int* ptre2 = &max_pattern5;
//
//        pedigree1 = aPedigree_check(member[0],R1a, S1a); //플레이어 1 족보
//        pedigree2 = aPedigree_check(member[1],R2a, S2a); //플레이어 2 족보
//        pedigree3 = aPedigree_check(member[2],R3a, S3a); //플레이어 3 족보
//        pedigree4 = aPedigree_check(member[3],R4a, S4a); //플레이어 4 족보
//        pedigree5 = aPedigree_check(member[4],R5a, S5a); //플레이어 5 족보
//        
//        break;
//    case 6:
//        R1a[0] = R0[0]; R1a[1] = R0[1]; R1a[2] = R0[2]; R1a[3] = R0[3]; R1a[4] = R1[0]; R1a[5] = R1[1];
//        R2a[0] = R0[0]; R2a[1] = R0[1]; R2a[2] = R0[2]; R2a[3] = R0[3]; R2a[4] = R2[0]; R2a[5] = R2[1];
//        R3a[0] = R0[0]; R3a[1] = R0[1]; R3a[2] = R0[2]; R3a[3] = R0[3]; R3a[4] = R3[0]; R3a[5] = R3[1];
//        R4a[0] = R0[0]; R4a[1] = R0[1]; R4a[2] = R0[2]; R4a[3] = R0[3]; R4a[4] = R4[0]; R4a[5] = R4[1];
//        R5a[0] = R0[0]; R5a[1] = R0[1]; R5a[2] = R0[2]; R5a[3] = R0[3]; R5a[4] = R5[0]; R5a[5] = R5[1];
//
//        //정렬
//        arrsort(R1a, S1a, 6);
//        arrsort(R2a, S2a, 6);
//        arrsort(R3a, S3a, 6);
//        arrsort(R4a, S4a, 6);
//        arrsort(R5a, S5a, 6);
//
//        //int* ptra1 = &max_number1; int* ptrb1 = &max_number2; int* ptrc1 = &max_number3; int* ptrd1 = &max_number4; int* ptre1 = &max_number5;
//        //int* ptra2 = &max_pattern1; int* ptrb2 = &max_pattern2; int* ptrc2 = &max_pattern3; int* ptrd2 = &max_pattern4; int* ptre2 = &max_pattern5;
//
//        pedigree1 = Pedigree_check(member[0], R1a, S1a); //플레이어 1 족보
//        pedigree2 = Pedigree_check(member[1], R2a, S2a); //플레이어 2 족보
//        pedigree3 = Pedigree_check(member[2], R3a, S3a); //플레이어 3 족보
//        pedigree4 = Pedigree_check(member[3], R4a, S4a); //플레이어 4 족보
//        pedigree5 = Pedigree_check(member[4], R5a, S5a); //플레이어 5 족보
//
//        break;
//    case 7:
//        R1a[0] = R0[0]; R1a[1] = R0[1]; R1a[2] = R0[2]; R1a[3] = R0[3]; R1a[4] = R0[4]; R1a[5] = R1[0]; R1a[6] = R1[1];
//        R2a[0] = R0[0]; R2a[1] = R0[1]; R2a[2] = R0[2]; R2a[3] = R0[3]; R2a[4] = R0[4]; R2a[5] = R2[0]; R2a[6] = R2[1];
//        R3a[0] = R0[0]; R3a[1] = R0[1]; R3a[2] = R0[2]; R3a[3] = R0[3]; R3a[4] = R0[4]; R3a[5] = R3[0]; R3a[6] = R3[1];
//        R4a[0] = R0[0]; R4a[1] = R0[1]; R4a[2] = R0[2]; R4a[3] = R0[3]; R4a[4] = R0[4]; R4a[5] = R4[0]; R4a[6] = R4[1];
//        R5a[0] = R0[0]; R5a[1] = R0[1]; R5a[2] = R0[2]; R5a[3] = R0[3]; R5a[4] = R0[4]; R5a[5] = R5[0]; R5a[6] = R5[1];
//
//        //정렬
//        arrsort(R1a, S1a, 7);
//        arrsort(R2a, S2a, 7);
//        arrsort(R3a, S3a, 7);
//        arrsort(R4a, S4a, 7);
//        arrsort(R5a, S5a, 7);
//
//        //int* ptra1 = &max_number1; int* ptrb1 = &max_number2; int* ptrc1 = &max_number3; int* ptrd1 = &max_number4; int* ptre1 = &max_number5;
//        //int* ptra2 = &max_pattern1; int* ptrb2 = &max_pattern2; int* ptrc2 = &max_pattern3; int* ptrd2 = &max_pattern4; int* ptre2 = &max_pattern5;
//
//        pedigree1 = Pedigree_check(member[0], R1a, S1a); //플레이어 1 족보
//        pedigree2 = Pedigree_check(member[1], R2a, S2a); //플레이어 2 족보
//        pedigree3 = Pedigree_check(member[2], R3a, S3a); //플레이어 3 족보
//        pedigree4 = Pedigree_check(member[3], R4a, S4a); //플레이어 4 족보
//        pedigree5 = Pedigree_check(member[4], R5a, S5a); //플레이어 5 족보
//
//        break;
//    }
//}

// 배열 R 정렬
void arrsort(int R[], int a)
{
    bool swapped = false;
    do
    {
        // 1 pass of the bubble sort
        swapped = false;
        for (int i = 0; i < a-1; i++)
        {
            if (R[i] > R[i + 1])
            {
                int temp = R[i];
                R[i] = R[i + 1];
                R[i + 1] = temp;
                swapped = true;
            }
        }
    } while (swapped == true);
}
