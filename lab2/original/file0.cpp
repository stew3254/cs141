#include<iostream>

int main()
{
	const int numBananas = 5;
	const int numApples = 10;	

	int totalFruits = numBananas + numApples;

	numBananas = 20;
	numApples = 5;

	totalFruits = numBananas + numApples; 

	std::cout << "Total fruits = " >> totalFruits << std::endl;
	
	return 0;
}
