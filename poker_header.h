#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;

#define UP 72
#define DOWN 80
#define RIGHT 77
#define LEFT 75
#define CHOICE 13

const char shape[5][10] = { "zero", "spade", "diamonds", "cluber", "heart" };
const char num1ber[14][7] = { "zero","two", "three", "four", "five", "six", "seven", "eight", "nine", "ten", "jack", "queen", "king", "ace" };

enum Color  //콘솔에서 사용하는 색상
{
	BLACK, BLUE, GREEN, CYAN,
	RED, MAGENTA, BROWN, LIGHTGRAY,
	DARKGRAY, LIGHTBLUE, LIGHTGREEN, LIGHTCYAN,
	LIGHTRED, LIGHTMAGENTA, YELLOW, WHITE
};

enum Pedi {
	Die = 0,
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


class card {
public:
	void setSR(int S1, int R);
	int getS();
	int getR();
private:
	int R; //숫자
	int S; //문양

};

class Player {
public:
	Player();
	Player(string setN);
	void payMoney(int pay, int& totalBet);
	void showMoney();
	bool checkPlayer(); //살아있는 플레이어 체크
	int getMoney();
	void inputBet(int& totalBet, int& betMoney); // 리더의 배팅 금액 입력.
	void playerDie(int& gambler); // play가 false로 바뀜.
	void leaderBet(int& totalMoney, int& gamlber, int& betMoney, int nowBet, int turn, Player member[], Player& dealer,int &bet);
	void doubleBet(int& betMoney, int& totalBet);
	void allMoney(int& betMoney, int& totalBet, int& gambler);
	bool canBet(int betMoney);
	void halfBet(int& betMoney, int& totalBet);
	void dieAllMoney(int& totalMoney, int& gambler);
	bool nowPlay();
	bool checkSurvivor();
	void payBet(int betMoney);
	string getName();
	void retireGame();
	void returnPlay();

	void call(int& betMoney, int& totalMoney);//,int &pastChoice);
	void setCardSR(int R, int S, int now);
	void setMax(int maxP, int maxN);
	void setMax(int maxP, int maxN, int maxP2, int maxN2);
	card* getCard();
	int numGetCard(int num);
	int patGetCard(int num);
	int getNMax();
	int getNMax2();
	int getPMax();
	int getPMax2();
	void winnerMoney(int& totalBet);
	void setDieMoney(int die);
	int getDieMoney();
	void zeroMoney();
	bool getRetire();
private:
	int gameMoney;
	card myCard[5]; // 딜러 때문에 크기 5로 변경
	bool play; //이번 판 플레이가 제한된 경우 false로 변경
	bool die; //이번판 아웃된 경우
	string name;
	int maxPattern; //max pattern
	int maxNumber; //max number
	int maxPattern2;
	int maxNumber2;
	int dieMoney;
	bool retire;
};

//-----------------------이도영
void setColor(int back, int text);
void init();
void gotoxy(int x, int y);
void introGame(); // 게임 시작화면 함수
int keyControl(); // 방향키로 메뉴 선택 함수
int menuChoice(); // 시작화면 메뉴 선택 함수
void gameImage(Player member[]); // 게임화면 이미지 출력 함수
void gameRule(); // 게임 룰 화면 함수
void player(int x, int y, int coin); // 컴퓨터 플레이어 이미지 출력 함수
int bettingNumber(); // 베팅 메뉴 선택 함수
void bettingPrint(int x); // 베팅 문자 출력 
int bettingMenuChoice(); // 베팅 메뉴 이름 출력 함수
void victoryPrint(); // 승리 시 화면 출력
void defeatPrint();  // 패배 시 화면 출력
void picture(card dealer[], Player member[]); //공유 카드 구성 함수
void playerCard(int x, int y);
void Print_result(Player& winner, Player& dealer);
void printOrder(int result);
//----
void showDealerCard(card dealerCard[], int& num1, int& j,Player member[]);
void interCall();
void interDie();
void interDouble();
void interHalf();
void interAllin();
void interInit();
void showCoin(int x, int y, int coin);
int choice_betting(int& betMoney);
int choice_betting2(int& betMoney);
void betting_coin(int x, int& betMoney);
void betting_coin2(int x, int& betMoney);
void betting_all(const int betMoney, const int totalBet);
void nowPlayName(string name);
void showObli();
void showSentence(string a, int x, int y);
int bettingLeaderChoice();
void checkStatus(Player member[], int& gambler);
void PrintMCard(int x, int y, card Player[]);
void printAll(Player member[]);
void Print_result(Player& winner, Player& dealer);
int bettingCantChoice();
void computaTurn(Player member[], int nowBet);
//-------------------------- 김강민
void obliBet(Player member[], int& totalBet,int &gambler);
void playGame(Player member[], Player& gambler);
void choiceBet(Player member[], int& gambler, int leader, int& totalBet, Player& dealer, const int turn);
int choiceLeader(Player member[], const int gambler); // 가장 금액 높은 사람이 첫 배팅 리더
void choiceFollower(Player member[], int& betMoney, int& totalBet, int& gambler, int& bet, int& nowBet, Player& dealer, const int turn);
void cant_Bet(Player& follwer, int& betMoney, int& gambler, int& totalBet, Player member[], int& nowBet, int& bet,Player &dealer,int turn);
void checkDie(Player member[], int& gambler);
void resetGame(Player &member);
void endGame(Player member[], int& gambler);
int reGame(Player member[],Player &dealer);
void resultantPlate(Player member[]);
void showCoinAll(Player member[]);
void interBetting();

//--------------------------범진혁
void arrsort(int R[], int S[], int a);
void shuffle(Player member[], Player& dealer);
Player* pchecking(Player& one, Player& two, Player& dealer);
int rating(string pedigree);
int aPedigree_check(Player& nowPlay, card dealerCard[], card playerCard[]);
int Bpedigree_check(Player& nowPlay, card dealerCard[], card playerCard[]);
int Cpedigree_check(Player& nowPlay, card dealerCard[], card playerCard[]);
Player* checkWinner(Player member[], Player& dealer, int gambler);

//-----------------------임뭐시기
int probabli(int pedigree);
int probabli_Leader(int pedigree, int& betMoney, Player nowPlay);
int probabli_Cant();