#include "poker_header.h"

int probabli(int pedigree)
{
	int pro = rand() % 10000;
	
	if (pedigree == High_card) {
		if (pro >= 0 && pro < 5000)       //콜 
			return 1;
		else if (pro >= 5000 && pro < 8000)  // 다이  
			return 2;
		else if (pro >= 8000 && pro < 9000)  // 더블  3
			return 3;
		else if (pro >= 9000 && pro <= 10000)  //  하프 4 
			return 4;
		//else if (pro >= 0 && pro < 2) // 올인 5 
		//	return 5;
	}
	else if (pedigree == One_pair) {
		if (pro >= 0 && pro < 7000)
			return 1;
		else if (pro >= 7000 && pro < 7500)                  //// 콜 1 다이 2 더블 3 하프 4 올인 5 
			return 2;
		else if (pro >= 7500 && pro < 8500)
			return 3;
		else if (pro >= 8500 && pro <= 10000)
			return 4;
	/*	else if (pro >= 0 && pro < 4)
			return 5;*/
	}
	else if (pedigree == Two_pair) {
		if (pro >= 0 && pro < 7500)
			return 1;
		else if (pro >= 7500 && pro < 7750)
			return 2;
		else if (pro >= 7750 && pro < 9000)         // 콜 1 다이 2 더블 3 하프 4 올인 5 
			return 3;
		else if (pro >=  9000&& pro <= 10000)
			return 4;
		//else if (pro >= 0 && pro < 5)
		//	return 5;
	}
	else if (pedigree == Triple) {
		if (pro >= 0 && pro < 8500)
			return 1;
		else if (pro >= 8500 && pro < 8550)
			return 2;
		else if (pro >= 8550 && pro < 9500)           // 콜 1 다이 2 더블 3 하프 4 올인 5 
			return 3;
		else if (pro >= 9500 && pro <= 10000)
			return 4;
		//else if (pro >= 0 && pro < 10)
		//	return 5;
	}
	else if (pedigree == Straight) {
		if (pro >= 0 && pro < 5500)
			return 1;
		else if (pro >= 5500 && pro < 5505)
			return 2;
		else if (pro >= 5505 && pro < 8750)
			return 3;
		else if (pro >= 8750 && pro <= 10000)          // 콜 1 다이 2 더블 3 하프 4 올인 5 
			return 4;
		//else if (pro >= 0 && pro < 50)
		//	return 5;
	}
	else if (pedigree == Flush) {
		if (pro >= 0 && pro < 5500)
			return 1;
		else if (pro >= 5500 && pro < 5501)
			return 2;
		else if (pro >= 5501 && pro < 8750)
			return 3;
		else if (pro >= 8750 && pro <= 10000)
			return 4;                                  // 콜 1 다이 2 더블 3 하프 4 올인 5 
		//else if (pro >= 0 && pro < 100)
		//	return 5;
	}
	else if (pedigree == Full_house) {
		if (pro >= 0 && pro < 5500)
			return 1;
		else if (pro >= 5500 && pro < 5501)
			return 2;
		else if (pro >= 5501 && pro < 8500)                // 콜 1 다이 2 더블 3 하프 4 올인 5 
			return 3;
		else if (pro >= 8500 && pro <= 10000)
			return 4;
		//else if (pro >= 0 && pro < 150)
		//	return 5;
	}
	else if (pedigree == Four_card) {
		if (pro >= 0 && pro < 5500)
			return 1;
		else if (pro >= 5500 && pro < 5501)
			return 2;
		else if (pro >= 5501 && pro < 8500)           // 콜 1 다이 2 더블 3 하프 4 올인 5 
			return 3;
		else if (pro >= 8500 && pro <= 10000)
			return 4;
		//else if (pro >= 0 && pro < 300)
		//	return 5;
	}
	else if (pedigree == Straight_flush) {
		if (pro >= 0 && pro < 7010)
			return 1;
		else if (pro >= 7010 && pro < 7011)
			return 2;
		else if (pro >= 7011 && pro < 8011)                // 콜 1 다이 2 더블 3 하프 4 올인 5 
			return 3;
		else if (pro >= 8011 && pro <= 10000)
			return 4;
		//else if (pro >= 0 && pro < 700)
		//	return 5;
	}
	return 1;
}

int probabli_Leader(int pedigree,int &betMoney,Player nowPlay)
{
	int pro = rand() % 10000;
		if (pedigree == High_card) {
			if (pro >= 0 && pro < 7000)
			{
				if (pro >= 2 && pro < 2300)
					betMoney = 1;
				else if (pro >= 2300 && pro < 4600)
					betMoney = 2;
				else
					betMoney = 3;
				return 1;
			}
			else if (pro >= 7000 && pro <= 10000)  // 다이  
				return 2;
			//else if (pro >= 0 && pro < 2) // 올인 5 
			//	return 3;
	}
	else if (pedigree == One_pair) {
			if (pro >= 0 && pro < 8000) 
			{   
				if (nowPlay.getMoney() >= 2)
				{
					if (pro >= 4 && pro < 3300)
						betMoney = 2;
					else if (pro <= 2300 && pro < 5600)
						betMoney = 3;
					else
						betMoney = 4;
				}
				else
					betMoney = nowPlay.getMoney();
				return 1;
			}
			else if (pro >= 8000 && pro <= 10000)  // 다이  
				return 2;
			//else if (pro >= 0 && pro < 4) // 올인 5 
			//	return 3;
	}
	else if (pedigree == Two_pair) {
		if (pro >= 0 && pro < 8500)
		{
			if (nowPlay.getMoney() >= 2)
			{
				if (pro >= 15 && pro < 5350)
					betMoney = 2;
				else if (pro <= 5350 && pro < 7000)
					betMoney = 3;
				else
					betMoney = 5;
			}
			else
				betMoney = nowPlay.getMoney();
			return 1;
		}
		else if (pro >= 8500 && pro <= 10000)  // 다이  
			return 2;
		//else if (pro >= 0 && pro < 15) // 올인 5 
		//	return 3;

	}
	else if (pedigree == Triple) {
		if (pro >= 0 && pro < 9500)
		{
			if (nowPlay.getMoney() >= 3)
			{
				if (pro >= 100 && pro < 4350)
					betMoney = 3;
				else if (pro <= 4350 && pro < 8000)
					betMoney = 4;
				else
					betMoney = 5;
			}
			else
				betMoney = nowPlay.getMoney();
			return 1;
		}
		else if (pro >= 9500 && pro <= 10000)  // 다이  
			return 2;
		//else if (pro >= 0 && pro < 100) // 올인 5 
		//	return 3;
	}
	else if (pedigree == Straight) {
		if (pro >= 0 && pro < 9900)
		{
			if (nowPlay.getMoney() >= 4)
			{
				if (pro >= 500 && pro < 5550)
					betMoney = 4;
				else if (pro <= 5550 && pro < 8000)
					betMoney = 5;
				else
					betMoney = 6;
			}
			else
				betMoney = nowPlay.getMoney();
			return 1;
		}
		else if (pro >= 9900 && pro <= 10000)  // 다이  
			return 2;
		//else if (pro >= 0 && pro < 500) // 올인 5 
		//	return 3;
	}
	else if (pedigree == Flush) {
		if (pro >= 0 && pro < 9990)
		{
			if (nowPlay.getMoney() >= 5)
			{
				if (pro >= 1000 && pro < 5550)
					betMoney = 5;
				else if (pro <= 5550 && pro < 8000)
					betMoney = 6;
				else
					betMoney = 7;
			}
			else
				betMoney = nowPlay.getMoney();
			return 1;
		}
		else if (pro >= 9990 && pro <= 10000)  // 다이  
			return 2;
		//else if (pro >= 0 && pro < 1000) // 올인 5 
		//	return 3;
	}
	else if (pedigree == Full_house) {
		if (pro >= 0 && pro < 9999)
		{
			if (nowPlay.getMoney() >= 6)
			{
				if (pro >= 1500 && pro < 6550)
					betMoney = 6;
				else if (pro <= 6550 && pro < 8000)
					betMoney = 7;
				else
					betMoney = 8;
			}
			else
				betMoney = nowPlay.getMoney();
			return 1;
		}
		else if (pro >= 9999 && pro <= 10000)  // 다이  
			return 2;
		//else if (pro >= 0 && pro < 1500) // 올인 5 
		//	return 3;
	}
	else if (pedigree == Four_card) {
	if (pro >= 0 && pro < 9999)
	{
		if (nowPlay.getMoney() >= 7)
		{
			if (pro >= 3000 && pro < 7550)
				betMoney = 7;
			else if (pro <= 7550 && pro < 8000)
				betMoney = 8;
			else
				betMoney = 9;
		}
		else
			betMoney = nowPlay.getMoney();
		return 1;
	}
	else if (pro >= 9999 && pro <= 10000)  // 다이  
		return 2;
	//else if (pro >= 0 && pro < 3000) // 올인 5 
	//	return 3;
	}
	else if (pedigree == Straight_flush) {
	if (pro >= 0 && pro < 9999)
	{
		if (nowPlay.getMoney() >= 7) 
		{
			if (pro >= 7000 && pro < 8550)
				betMoney = 8;
			else if (pro <= 8550 && pro < 9000)
				betMoney = 9;
			else
				betMoney = 10;
		}
		else
			betMoney = nowPlay.getMoney();
		return 1;
	}
	else if (pro >= 9999 && pro <= 10000)  // 다이  
		return 2;
	//else if (pro >= 0 && pro < 7000) // 올인 5 
	//	return 3;
	}
	return 1;
}

int probabli_Cant()
{
	int temp;
	temp = rand() % 8;

		return 2;
}