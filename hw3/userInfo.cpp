#include<iostream>
#include<string>
#include<fstream>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::islower;
using std::isdigit;
using std::ifstream;

bool chkName(string);
bool chkState(string);
bool chkZip(string);
bool chkPhone(string);

int main() {

	//Variable Definitions
	string firstName;
	string middleName;
	string lastName;
	string stateCode;
	string zipCode;
	string phoneNumber;

	//Enter and check first name
	cout << "Please enter your first name: ";
	cin >> firstName;
	if (!chkName(firstName))
	{
		return -1;
	}

	//Enter and check middle name
	cout << "Please enter your middle name: ";
	cin >> middleName;
	if (middleName != "none")
	{	
		if (!chkName(middleName))
		{
			return -1;
		}
	}
	
	//Enter and check last name
	cout << "Please enter your last name: ";
	cin >> lastName;
	if (!chkName(lastName))
	{
		return -1;
	}
	
	//Enter and check state code
	cout << "Please enter your state code: ";
	cin >> stateCode;
	if (!chkState(stateCode))
	{
		return -1;
	}

	//Enter and check zip code
	cout << "Please enter your zip code: ";
	cin >> zipCode;
	if (!chkZip(zipCode))
	{
		return -1;
	}

	//Enter and check phone number
	cout << "Please enter your phone number: ";
	cin >> phoneNumber;
	if (!chkPhone(phoneNumber))
	{
		return -1;
	}

	cout << "Results OKAY!" << endl;

	return 0;
	
	
}


/*
 Used to check a name for various conditions:
	*Name must be between 2 and 10 characters long
	*Name must start with a captial first letter
	*Name must have all letters after the first be lowercase
	*Name cannot have any numbers or symbols in it
*/
bool chkName(string name)
{
	bool nameOkay = true;

	//Check length
	if (name.length() < 2 || name.length() > 10)
	{
		cout << "First name must be between 2 and 10 characters" << endl;
		nameOkay = false;
	}
	//Check if first letter isn't captial
	else if (islower(name[0]))
	{
		cout << "First name must have a capital first letter" << endl;
		nameOkay = false;
	}
	else
	{
		unsigned long i = 1;

		//Loop through all of the characters
		while(nameOkay && i < name.length())
		{
			//Check to see if the character isn't lowercase
			if (!islower(name[i]))
			{
				cout << "First name must have the all but the first letter lowercase and must not contain symbols or numbers" << endl;
				nameOkay = false;
			}
			else
			{
				//Continue onto the next letter
				i++;
			}
		}
	}
	return nameOkay;
}


/*
 Used to check the state code for various conditions:
	*State code must be 2 characters long
	*State code must have all capital letters
*/
bool chkState(string stateCode)
{
	bool stateOkay = true;
	
	//Check length
	if (stateCode.length() != 2)
	{
		cout << "State code must be exactly 2 characters long" << endl;
		stateOkay = false;
	}
	//Check to see if either character is lowercase
	else if (islower(stateCode[0]) || islower(stateCode[1]))
	{
		cout << "State code must be capital letters only" << endl;
		stateOkay = false;
	}

	return stateOkay;
}


/*
 Used to check the zip code for various conditions:
	*Zip code must be 5 characters long
	*Zip code must have only numbers
	*Zip code must be a valid zip code based off of a zip codes file
*/
bool chkZip(string zipCode)
{
	bool zipOkay = true;

	//Check length
	if (zipCode.length() != 5)
	{
		cout << "Zip code must be exactly 5 characters long";
		zipOkay = false;
	}
	else
	{
		unsigned long i = 0;
		
		//Loop through the zip code and make sure it's all numbers
		while (i < zipCode.length() && zipOkay)
		{
			if (!isdigit(zipCode[i]))
			{
				cout << "Zip code must only contain numbers" << endl;
				zipOkay = false;
			}
			i++;
		}

		//If we're still good at this point, continue to do the validation
		if (zipOkay)
		{
			string validZipCode;
			ifstream f;
			
			//Open zipcodes file to read and start reading from it
			f.open("zipcodes.txt");
			f >> validZipCode;
			
			//Loop through as long as the first 3 characters of the zip code aren't valid or 999 (The last line in the file)
			while (zipCode.substr(0, 3) != validZipCode && validZipCode != "999")
			{
				f >> validZipCode;
			}

			//Check to see if the zip code is valid one last time 
			if (zipCode.substr(0,3) != validZipCode)
			{
				cout << "Zip code is invalid" << endl;
				zipOkay = false;
			}
			else
			{
				zipOkay = true;
			}
	
			//Make sure to close the file stream
			f.close();
		}
	}
		
	return zipOkay;
}


/*
 Used to check the phone number for various conditions:
	*Phone number must be 12 or 14 characters long
	*Phone number must follow standard phone number format
		**i.e. (123)-123-123 or 123-123-1234
	*Phone number must have () or - characters where they are supposed to be
	*Phone number must be numbers where appropriate
*/
bool chkPhone(string phoneNumber)
{
	bool phoneOkay = true;
	unsigned int i = 0;

	//Check to see if the phone number length is correct
	if (phoneNumber.length() == 12) 
	{

		//Loop through all of the phone numbers while the phone number is still okay
		while (i < phoneNumber.length() && phoneOkay)
		{
			//Check to see if the positions are where dashes should go
			if (i == 3 || i == 7)
			{
				//Check to see if the characters are actually dashes
				if (phoneNumber[i] != '-')
				{
					cout << "Phone mumber has incorrect format. Must use dashes, not '" << phoneNumber[i] << "'" << endl;
					phoneOkay = false;
				}
			}
			//Otherwise make sure it's a number
			else if (!isdigit(phoneNumber[i]))
			{
				cout << "Phone number is invalid" << endl;
				phoneOkay = false;
			}

			i++;
		}
	}
	//Check to see if the other case of number length is correct
	else if(phoneNumber.length() == 14)
	{
		//Loop through all of the phone numbers while the phone number is still okay
		while (i < phoneNumber.length() && phoneOkay)
		{
			//Check for the typical position of '('
			if (i == 0)
			{
				//Make sure it's actually '('
				if (phoneNumber[i] != '(')
				{
					cout << "Phone Number has incorrect format. Must use () for area code, not '" << phoneNumber[0] << phoneNumber[4] << "'" << endl;
				}
			}
			//CHeck for the typical postion of ')'
			else if (i == 4)
			{
				//Make sure it's actually ')'
				if (phoneNumber[i] != ')')
				{
					cout << "Phone Number has incorrect format. Must use () for area code, not '" << phoneNumber[0] << phoneNumber[4] << "'" << endl;
				}
			}
			//Check for the typical postion of dashes
			else if (i == 5 || i == 9)
			{
				//Make sure they're actually dashes
				if (phoneNumber[i] != '-')
				{
					cout << "Phone mumber has incorrect format. Must use dashes, not '" << phoneNumber[i] << "'" << endl;
					phoneOkay = false;
				}
			}
			//Otherwise make sure they're numbers
			else if (!isdigit(phoneNumber[i]))
			{
				cout << "Phone number is invalid" << endl;
				phoneOkay = false;
			}

			i++;
		}
	}
	//Phone number is incorrect size
	else
	{
		cout << "Phone number length is the incorrect size" << endl;
		phoneOkay = false;
	}

	return phoneOkay;
}

