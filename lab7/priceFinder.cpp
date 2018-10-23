#include<iostream>
#include<string>

using std::cout;
using std::cin;
using std::endl;
using std::string;

//Global Price structure
struct Price {
	//Used to reference global price values
	float max;
	float min;
	float range;
	float average;
	short valid;

	//Used to intiialize all of the variables
	void initialize(short i) {
		max = i;
		min = i;
		range = i;
		average = i;
		valid = 0;
	}
};

//Create our Prices object
Price Prices;

void priceGenerator(float[], short);

//Start our program
int main()
{
	//Variable Definitions
	string name;
	bool nameOkay = true;

	//Start the price finder program
	cout << "Welcome to the price finder program." << endl << endl;
	
	//Loop while our name is okay
	while (nameOkay)
	{
		cout << "Enter a product name: ";
		cin >> name;

		//Make sure the name isn't "DONE"
		if (name == "DONE")
		{
			nameOkay = false;
		}
		else
		{
			//Definie some more variables that didn't need to be allocated before
			short pos = 0;
			float itemPrice = 0;
			float prices[10] = {0};
			bool priceEnd = false;

			//Loop for the number of prices or until the user defines the stop
			while (pos < 10 && !priceEnd)
			{
				cout << "Enter price: ";
				cin >> itemPrice;

				//Defined stop asking for prices
				if (itemPrice == -1)
				{
					priceEnd = true; 
				}
				//Make sure the item isn't negative and isn't the special stop number
				else if (itemPrice <= 0.0)
				{
					cout << "The price must be greater than 0" << endl;
				}
				else {
					//Add the prices to the array
					prices[pos] = itemPrice;
					
					//Make sure we count how many prices we have added so we don't seg fault by going over
					pos += 1;
				}
			}

			//Generate the prices gving it a defined array size
			priceGenerator(prices, 10);
			cout << endl;
			cout << "Number of valid prices: " << Prices.valid << endl;
			cout << "Maximum: $" << Prices.max << endl;
			cout << "Minimum: $" << Prices.min << endl;
			cout << "Range: $" << Prices.range << endl;
			cout << "Average: $" << Prices.average << endl;
			cout << endl;
			
		}
	}
	return 0;
}


//Used to generate all of the price conditions ie. Max, Min, Range, Average
void priceGenerator(float prices[], short size)
{

	//Initialize all of the variables with the first item in the prices array
	Prices.initialize(prices[0]);

	//Loop through all of the prices
	for (int i=0; i<size; i++)
	{
		//Make sure the price is actually user inserted. Users can't insert prices that are <= 0
		if (prices[i] > 0)
		{
			//Start forming our average here so we don't need to loop through again
			Prices.average += prices[i];

			//Make says that the price is valid so we can divide average by this later
			Prices.valid += 1;
		}

		//Finds the max price
		if (prices[i] > Prices.max)
		{
			Prices.max = prices[i];
		}
		//Finds the lowest user inputted price, ie. greater than 0
		else if (prices[i] < Prices.min && prices[i] > 0.0)
		{
			Prices.min = prices[i];
		}
	}
	
	//Calculate the range
	Prices.range = Prices.max - Prices.min;

	//Calculate the actual average of the prices
	Prices.average /= Prices.valid;
	
}
