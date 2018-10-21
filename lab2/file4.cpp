#include<iostream>

int main()
{
	const int usPopulation = 321418821;
	long worldPopulation = 7.5E9;
	long usWorldRatio = usPopulation / worldPopulation;	

	std::cout << "The US population is " << usWorldRatio*100 << "% of the world population." << std::endl; 

	return 0;
}
