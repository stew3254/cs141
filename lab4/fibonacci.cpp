#include<iostream>

int main()
{
	//Seed the Fibonacci Sequence
	long oldFibonacciNum = 1;
	long fibonacciNum = 1;

	//Number of terms to generate
	short n = 0;

	//Get n
	std::cout << "Please enter a number to generate Fibonacci numbers: ";
	std::cin >> n;
	
	//Check to see if n is at least 1 and loop until n >= 1
	while (n < 1)
	{
		std::cout << "ERROR: entered " << n << ", cannot generate Fibonacci numbers" << std::endl;
		std::cout << "Please enter a number to generate Fibonacci numbers: ";
		std::cin >> n;
	}


	//Loop through n terms and find fibonacci numbers
	for (short i=0; i < n; i++)
	{

		//Print the first condition
		if (i == 0)
		{
			std::cout << "The first " << n <<" Fibonacci numbers are: " << fibonacciNum << " ";
		}
		//Still print the second condition because it's special
		else if (i == 1)
		{
			std::cout << fibonacciNum << " ";
		}
		//Actually apply the formula to calculate fibonacci numbers
		else
		{
			fibonacciNum = fibonacciNum + oldFibonacciNum;
			oldFibonacciNum = fibonacciNum - oldFibonacciNum;
			
			std::cout << fibonacciNum << " ";
		}
	}
	//Make it still print pretty at the end
	std::cout << std::endl;
	return 0;
}
