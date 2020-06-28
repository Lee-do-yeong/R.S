#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <string>

using namespace std;

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define CHOICE 4


class card { //(임시) 카드 클래스
public:
	friend ostream& operator<< (ostream& a, const card& thiscard);
private:
	bool status=false; // 뒷면 false 앞면 true
	string pat;
	int cardNumber;
	int num;
};

class player {
public:
	player();
	void payMoney(int pay,int &totalBet); 
	void showMoney();
	void getCard(card newCard1, card newCard2);
	bool checkPlayer(); //살아있는 플레이어 체크
	void takeCard();
	int getMoney();
	int inputBet(int& totalBet); // 리더의 배팅 금액 입력.
	void playerDie(int& gambler); // play가 false로 바뀜.
	int leaderBet(int &totalMoney, int& gamlber);
	void doubleBet(int& betMoney,int & totalBet);
	void allMoney(int& betMoney,int & totalBet);
	bool canBet(int betMoney);
	void halfBet(int &betMoney,int & totalBet);
	void dieAllMoney(int& totalMoney);
	bool nowPlay();
	bool checkSurvivor();
	void payBet(int betMoney);
	void setName(string setN);
	string getName();
	void retireGame();
	void returnPlay();
	void resetUsed();
	int returnUsed();
	void call(int& betMoney, int& totalMoney);
	player(string setN);
protected:
	int used; // 받은 카드 갯수
	int gameMoney;
	card myCard[5]; // 딜러 때문에 크기 5로 변경
	bool play ; //이번 판 플레이가 제한된 경우 false로 변경
	bool die; //이번판 아웃된 경우
	string name;
};





//-------------------------- 헤드 업데이트
card drawCard(); // (임시)카드 뽑기
void obliBet(player member[], int& totalBet);
void playGame(player member[],player &gambler);
int checkCard();
void choiceBet(player member[], int &gambler, int leader,int& totalBet);
int choiceLeader(player member[], const int gambler); // 가장 금액 높은 사람이 첫 배팅 리더
void choiceFollower(player member[], int &betMoney, int& totalBet, int& gambler,int &bet,int& nowBet);
void cant_Bet(player& follwer, int& betMoney, int& gambler,int& totalBet);
void resetGame(player member);

//---------------------------------- -
void checkDie(player member[], int& gambler);
void resetGame(player member);
void suppleDeck(); // 임시
void endGame(player member[], int& gambler);
void reGame(player member[], player& delaer);
void resultantPlate(player member[]);
void testPlayer(player member[]);