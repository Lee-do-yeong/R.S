#include "poker_header.h"

enum Pedi {
	High_card = 1, // 보드와 무관한 카드 숫자가 높은 사람이 이김
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

//카드 족보 등급 숫자 정하기(1~9)
int rating(string pedigree) // 매개변수로 pedigree (문자열) 전달
{
	int arating = 0;
	
	if (pedigree == "high_card")
	{
		arating = High_card; // 1
	}
	else if (pedigree == "one_pair")
	{
		arating = One_pair; // 2
	}
	else if (pedigree == "two_pair")
	{
		arating = Two_pair; // 3
	}
	else if (pedigree == "triple")
	{
		arating = Triple; // 4
	}
	else if (pedigree == "straight")
	{
		arating = Straight; // 5
	}
	else if (pedigree == "flush")
	{
		arating = Flush; // 6
	}
	else if (pedigree == "fullhouse")
	{
		arating = Full_house; // 7
	}
	else if (pedigree == "four_card")
	{
		arating = Four_card; // 8
	}
	else if (pedigree == "straight_flush")
	{
		arating = Straight_flush; // 9
	}
	return arating;
}
