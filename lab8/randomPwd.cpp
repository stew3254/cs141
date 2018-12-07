#include <string>
#include <fstream>
#include <time.h>

using std::endl;
using std::string;
using std::ifstream;
using std::ofstream;

//Pre-define functions that are going to be used
void readEmployees(string[][2]);
void readPasswords(string[]);
void shuffle(const string[], string[]);

int main()
{
	//Variable definitions
	ofstream f;
	string employees[50][2];
	string passwords[50];
	string shuffledPasswords[50];

	//Read all employee names and store them to employees
	readEmployees(employees);

	//Read all passwords and store them to passwords
	readPasswords(passwords);

	//Shuffle all of the passwords and save the shuffled order
	shuffle(passwords, shuffledPasswords);

	//Write to file
	f.open("empPasswords.txt");

	//Iterate through all passwords / employees
	for (short i = 0; i < 50; i++)
	{
		//Iterate over each of the names in a full name
		for (short j = 0; j < 2; j++)
		{
			//Store the name to a file
			f << employees[i][j]  << ' ';
		}

		//Store the password to the file
		f << shuffledPasswords[i] << endl;
	}

	//Close the filestream
	f.close();

	return 0;
}


//Used to read all employee names from a file
void readEmployees(string employees[][2])
{
	ifstream f;

	//Open the file
	f.open("employees.txt");

	//Iterate over each of the full employee names
	for (short i = 0; i < 50; i++)
	{
		//Iterate over each name within the full name
		for (short j = 0; j< 2; j++)
		{
			f >> employees[i][j];
		}
	}

	//Close the file
	f.close();
}


//Read all of the passwords from a file
void readPasswords(string passwords[50])
{
	ifstream f;

	//Open the passwords file
	f.open("passwords.txt");
	
	//Read each line of the password file
	for (short i = 0; i < 50; i++) {
		f >> passwords[i];
	}

	//Close the file
	f.close();
}


//Shuffle all of the passwords
void shuffle(const string PASSWORDS[50], string shuffledPasswords[50])
{
	int randomNum = 0;

	//Seed the random with the semi-secure value of time so it will most likely be random every time
	srand(time(NULL));

	//Iterate over all of the passwords
	for (short i = 0; i < 50; i++) {
		//Generate a random number within our index
		randomNum = rand() % 50;

		//Set the value at the position we're at, to the value of the random position we're at
		shuffledPasswords[i] = PASSWORDS[randomNum];

		//Set the value of the random position we're at, to the value of the position we're at so it swaps the two
		shuffledPasswords[randomNum] = PASSWORDS[i];
	}
}
