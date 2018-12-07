#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>

using std::cout;
using std::cin;
using std::string;
using std::ifstream;
using std::endl;


/* -----GLOBALS----- */
//Stores the location of the vending machines
struct Location {
	string buildingName;
	int floorLevel;
};

//Stores the drink name, bottle size and price
struct Drink {
	string name;
	float bottleSize;
	float price;
};

//Stores a vending machine with 10 drinks in each
struct VendingMachine {
	Location location;
	Drink drinks[10];
};

//Store user inputs for vending machine
struct Vending {
	string buildingName;
	string drinkName;
	int floorLevel;
	float bottleSize;
};

//All vending machines on campus
VendingMachine AllVendingMachines[5];

//User vending machine request
Vending request;
/* -----GLOBALS END----- */


//Used to read all of the vending machine data for each machine
void readData()
{
	//Read in data from vending machine file
	ifstream data;
	data.open("vendingmachinedata.txt");

	//Loop through all vending machines on campus
	for (int machine = 0; machine < 5; machine++)
	{
		//Loop through all drinks per machine
		for (int drink = 0; drink < 10; drink++)
		{
			//Input all data on the line of 'vendingmachines.txt' and save to their respective variables
			data >> AllVendingMachines[machine].location.buildingName 
			>> AllVendingMachines[machine].location.floorLevel
			>> AllVendingMachines[machine].drinks[drink].name
			>> AllVendingMachines[machine].drinks[drink].bottleSize
			>> AllVendingMachines[machine].drinks[drink].price;
		}

	}
}


//Used //Used to convert a word to uppercase
string upper(string word)
{
	for (int i = 0; i < word.size(); i++)
	{
		word[i] = toupper(word[i]);
	}

	return word;
}


void buy()
{
	//Define if a condition exists and the machine number
	bool exists = false;
	int machine = 0;

	cout << "Please enter the vending machine in the following format: [BUILDING_NAME FLOOR DRINK_NAME DRINK_SIZE] ";
	cin >> request.buildingName >> request.floorLevel >> request.drinkName >> request.bottleSize;

	//Loop while condition is false and it's one of the five vending machines
	while (!exists && machine < 5)
	{
		//Check to see if the building and the floor in that building exist
		if (upper(request.buildingName) == upper(AllVendingMachines[machine].location.buildingName) && request.floorLevel == AllVendingMachines[machine].location.floorLevel)
		{
			//Define drinks in the machine and loop through each of them
			static int drink = 0;
			while (!exists && drink < 10)
			{
				//Check to see if the drink is in the machine with the corresponding size
				if (upper(request.drinkName) == upper(AllVendingMachines[machine].drinks[drink].name) && request.bottleSize == AllVendingMachines[machine].drinks[drink].bottleSize)
				{
					//End the continual looping and set the drink to purchased
					exists = true;
					AllVendingMachines[machine].drinks[drink].name = "EMPTY";
					AllVendingMachines[machine].drinks[drink].bottleSize = 0.0;
					AllVendingMachines[machine].drinks[drink].price = 0.0;
					cout << "Purchase complete!" << endl;

				}
				drink++;
			}
		}
		machine++;
	}
	//Check to see if the loop just ran out or if the condition actually exists
	//If so, then say the location doesn't exist
	if (!exists)
	{
		cout << "Sorry, a vending machine or your drink doesn't exist at this location" << endl;
	}
}


//Used to show the status of all vending machines on campus
void show()
{
	cout << "Here is a list of what is in stock" << endl << endl;

	//Loop through all vending machines on campus
	for (int machine = 0; machine < 5; machine++)
	{
		cout << AllVendingMachines[machine].location.buildingName << ' ';
		cout << "Floor " << AllVendingMachines[machine].location.floorLevel << endl;
		//Loop through all drinks per machine
		for (int drink = 0; drink < 10; drink++)
		{
			//Show the drink choices
			cout << AllVendingMachines[machine].drinks[drink].name << ", Size: ";
			cout << AllVendingMachines[machine].drinks[drink].bottleSize << ", Price: ";
			cout << AllVendingMachines[machine].drinks[drink].price << endl;
		}
		cout << endl;
	}
}


//Used to display the user interface for people to input data
bool menu()
{
	string action;

	cout << "Please enter an action [BUY, SHOW, EXIT]: "; 
	cin >> action;

	//Convert the action to uppercase characters
	action = upper(action);

	//Loop while action is incorrect
	while (action != "BUY" && action != "SHOW" && action != "EXIT")
	{
		cout << "That is not a valid input" << endl;
		cout << "Please enter an action [BUY, SHOW, EXIT]: "; 
		cin >> action;
		action = upper(action);
	}

	//Run the menu actions
	if (action == "BUY")
	{

		buy();
		return true;
	}
	else if (action == "SHOW")
	{
		show();
		return true;
	}
	else
	{
		return false;
	}
}


int main()
{
	bool displayMenu = true;

	//Read data from file to load the vending machines
	readData();

	cout << "Welcome to Clarkson's IOT Vending machine dispensers!" << endl; 
	cout << "From here, you can choose to buy from any vending machine on campus. You can also check to see what is in stock in different locations" << endl << endl;

	//Loop while not being returned false
	while (displayMenu)
	{
		displayMenu = menu();
	}

	return 0;
}
