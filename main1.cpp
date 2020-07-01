#include "poker_header.h"

int main()
{
	player member[5] = { {"Player"}, {"Kim"},{"Lee"},{"Bum"},{"IM"} }, dealer; // member[0]가 플레이어
	playGame(member, dealer);

	return 0;
}
