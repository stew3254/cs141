#include <iostream>
#include <string>
#include <fstream>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::ofstream;
using std::rename;


/*
Used to check a name for various conditions:
 * Name must be between 2 and 10 characters long
 * Name must start with a captial first letter
 * Name must have all letters after the first be lowercase
 * Name cannot have any numbers or symbols in it
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
                cout << "Name must have the all but the first letter of each name lowercase and must not contain symbols or numbers" << endl;
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
Used to check the account number for various conditions:
 * Account number must be 12 characters long
 * Account number must follow standard account number format
 ** i.e. 123-123-1234
 * Account number must have - characters where they are supposed to be
 * Account number must be numbers where appropriate
*/
bool chkAccountFormat(string accountNumber)
{
    bool accountOkay = true;
    unsigned int i = 0;

    //Check to see if the account number length is correct
    if (accountNumber.length() == 12) 
    {

        //Loop through all of the account numbers while the account number is still okay
        while (i < accountNumber.length() && accountOkay)
        {
            //Check to see if the positions are where dashes should go
            if (i == 3 || i == 7)
            {
                //Check to see if the characters are actually dashes
                if (accountNumber[i] != '-')
                {
                    cout << "Account mumber has incorrect format. Must use dashes, not '" << accountNumber[i] << "'" << endl;
                    accountOkay = false;
                }
            }
            //Otherwise make sure it's a number
            else if (!isdigit(accountNumber[i]))
            {
                cout << "Account number is invalid" << endl;
                accountOkay = false;
            }

            i++;
        }
    }
    //Account number is incorrect size
    else
    {
        cout << "Account number length is the incorrect size" << endl;
        accountOkay = false;
    }

    return accountOkay;
}


//Makes an account
void makeAccount(string firstName, string lastName, string accountNumber)
{
    ofstream accountsFile;
    ofstream accountsLog;

	//Get user account balance
    double accountBalance = 0.0;
    cout << "Please enter an initial account balance: ";
    cin >> accountBalance;

	//Make sure it's positve
    while (accountBalance < 0.0)
    {
        cout << "Please enter a positive number: ";
        cin >> accountBalance;
    }

    accountsFile.open("accounts.txt", std::ios_base::app);

    //Write account to the file
    accountsFile << firstName << ' ' << lastName << ' ' << accountNumber
        << ' ' << accountBalance << endl;

    accountsFile.close();

	//Start writing the log of the user creation
    accountsLog.open("accountlogs.txt", std::ios_base::app);

    accountsLog << "[!] New User account created!" << endl;
	accountsLog << "[*] User: " << firstName << ' ' << lastName << endl;
    accountsLog << "[*] Account ID: " << accountNumber << endl;
    accountsLog << "[*] Initial Balance: " << accountBalance << endl;

    accountsLog.close();
}


//Verify an account exists in records
bool verifyAccount(string firstName, string lastName, string accountNumber)
{
    if(ifstream("accounts.txt"))
    {
		//Define strings to read
		string readFirstName;
		string readLastName;
		string readAccountNumber;
		double readAccountBalance;

		//See if user exists
		bool userExists = false;

        ifstream f;
        f.open("accounts.txt");

		f >> readFirstName >> readLastName >> readAccountNumber >> readAccountBalance;
		cout << readFirstName << endl;

		//Loop while user isn't found and it's not the end of the file
		while (!userExists && !f.eof())
		{
			//If account found, set userExists to true
			if (firstName == readFirstName && lastName == readLastName
				&& accountNumber == readAccountNumber)
			{
				userExists = true;
			}
			f >> readFirstName >> readLastName >> readAccountNumber;
		}
        f.close();

		//If user exists, the account is verified, otherwise it doesn't exist
		if (userExists)
		{
			return true;
		}
		else
		{
			return false;
		}
    }
	return false;
}


//Used to deposit money into the account
void deposit(string firstName, string lastName, string accountNum)
{
	ifstream logIn;
	ofstream logOut;
	
	//Data read from file
	string readFirstName;
	string readLastName;
	string readAccountNum;
	double readAccountBalance = 0;
	
	bool correctUser = false;

	static double deposit = 0;

	//Ask for deposit
	cout << "How much would you like to deposit? ";
	cin >> deposit;

	//While the deposit is less than or equal to 0 keep asking for a positive number
	while (deposit <= 0)
	{
		cout << "Please enter a number greater than 0: ";
		cin >> deposit;
	}

	//Read the accounts file
	logIn.open("accounts.txt");

	//Read a whole line at a time
	logIn >> readFirstName >> readLastName >> readAccountNum >> readAccountBalance;

	//Loop while it can't find the correct account
	while (!correctUser)
	{
		if (readFirstName == firstName)
		{
			correctUser = true;
		}
		else
		{
			logIn >> readFirstName >> readLastName >> readAccountNum >> readAccountBalance;
		}

	}
	
	//Close the file for safety
	logIn.close();

	//Append to the account logs
	logOut.open("accountlogs.txt", std::ios_base::app);
	logOut << "[!] Updating balance for user" << endl;
	logOut << "[!] User: " << firstName << ' ' << lastName << endl;
	logOut << "[!] Account ID: " << accountNum << endl;
	logOut << "[*] Action: Deposit" << endl;
	logOut << "[*] Starting Balance: " << readAccountBalance << endl;
	logOut << "[*] Deposit Amount: " << deposit << endl;
	logOut << "[*] Ending Balance: " << readAccountBalance +  deposit << endl;
	logOut.close();

	//Create a temp file to put in place of old accounts.txt
	logOut.open("accountsTemp.txt", std::ios_base::app);
	logIn.open("accounts.txt");

	logIn >> readFirstName >> readLastName >> readAccountNum >> readAccountBalance;

	//Loop while it isn't the end of file
	while (!logIn.eof())
	{
		//Update the balance for the current user
		if (readFirstName == firstName)
		{
			logOut << readFirstName << ' ' << readLastName << ' ' << readAccountNum << ' '
				<< readAccountBalance + deposit << endl;
		}
		//Just rewrite the other users over again as they were
		else
		{
			logOut << readFirstName << ' ' << readLastName << ' ' << readAccountNum << ' '
				<< readAccountBalance << endl;
		}
    logIn >> readFirstName >> readLastName >> readAccountNum >> readAccountBalance;
	}

	logOut.close();
	logIn.close();

	//Rename the temp file to the original file to replace it
	rename("accountsTemp.txt", "accounts.txt");
}


//Deposits money into the account
void withdraw(string firstName, string lastName, string accountNum)
{
	ifstream logIn;
	ofstream logOut;
	
	//Data read from file
	string readFirstName;
	string readLastName;
	string readAccountNum;
	double readAccountBalance = 0;
	
	static double withdraw = 0;
	bool correctUser = false;


	//Ask for withdrawal
	cout << "How much would you like to withdraw? ";
	cin >> withdraw;

	//Open log file
	logIn.open("accounts.txt");
	logIn >> readFirstName >> readLastName >> readAccountNum >> readAccountBalance;

	//Loop while it hasn't found the correct user
	while (!correctUser)
	{
		if (readFirstName == firstName)
		{
			correctUser = true;
		}
		else
		{
			logIn >> readFirstName >> readLastName >> readAccountNum >> readAccountBalance;
		}

	}
	logIn.close();

	//Check to make sure the account balance is at least as much as the total account balance
	while (withdraw > readAccountBalance || withdraw < 0)
	{
		cout << "Please enter a number less than or equal to your overall balance: ";
		cin >> withdraw;
	}


	//Append to logs
	logOut.open("accountlogs.txt", std::ios_base::app);
	logOut << "[!] Updating balance for user" << endl;
	logOut << "[!] User: " << firstName << ' ' << lastName << endl;
	logOut << "[!] Account ID: " << accountNum << endl;
	logOut << "[*] Action: Withdraw" << endl;
	logOut << "[*] Starting Balance: " << readAccountBalance << endl;
	logOut << "[*] Withdrawal Amount: " << withdraw << endl;
	logOut << "[*] Ending Balance: " << readAccountBalance -  withdraw << endl;
	logOut.close();

	//Create a temp file to put in place of old accounts.txt
	logOut.open("accountsTemp.txt", std::ios_base::app);
	logIn.open("accounts.txt");

	logIn >> readFirstName >> readLastName >> readAccountNum >> readAccountBalance;

	correctUser = false;

	//While the log file hasn't ended
	while (!logIn.eof())
	{
		//Update balance for user
		if (readFirstName == firstName)
		{
			logOut << readFirstName << ' ' << readLastName << ' ' << readAccountNum << ' '
				<< readAccountBalance - withdraw << endl;
		}
		//Leave the rest the same and write them as is to the file
		else
		{
			logOut << readFirstName << ' ' << readLastName << ' ' << readAccountNum << ' '
				<< readAccountBalance << endl;
		}
		logIn >> readFirstName >> readLastName >> readAccountNum >> readAccountBalance;

	}

	//Close and rename
	logOut.close();
	logIn.close();
	rename("accountsTemp.txt", "accounts.txt");
}


//Shows a log of all transactions
void show(string firstName, string lastName, string accountNum)
{
	ifstream logIn;
	
	//Data read from file
	string data;
	string readAccountNum;
	string readName;
	string fullName = firstName + " " + lastName;
	short lines = 0;

	//Open logs and print first line
	logIn.open("accountlogs.txt");
	getline(logIn, data);
	cout << data << endl;

	//Look through the whole file
	while (!logIn.eof())
	{
		//If lines is greater than 1 then it should probably print what follows
		//That means it has validated the user
		if (lines > 1)
		{
			//Make sure the line isn't blank
			if (data != "")
			{
				//Grab the substrings starting after the '[!] ' part
				//If it starts with those stop printing lines
				if (data.substr(4, 8) == "Updating" || data.substr(4,3) == "New")
				{
					lines = 0;
					cout << endl;
				}
				//Print lines
				else
				{
					lines++;
					cout << data << endl;
				}
			}
		}
		//Check the length of the string to see if it might contain the user's name and ID
		else if (data.length() > 10)
		{
			//Try to grab where the name would start
			readName = data.substr(10, data.length() - 10);

			//Try to grab where the account numnber would start
			readAccountNum = data.substr(16, data.length() - 16);

			//If finds name and ID add to lines enough so it will continue to print more lines
			if (readName == fullName)
			{
				lines++;
				cout << data << endl;
			}
			else if (readAccountNum == accountNum)
			{
				lines++;
				cout << data << endl;
			}

		}
		getline(logIn, data);
	}
}


//Create a menu for the user to interact with
void menu(string firstName, string lastName, string accountNum)
{
	char action;

	//Print out the menu
	cout << "Account Verified. Please choose an action:" << endl;
	cout << "  * Press (d/D) to deposit money into your account" << endl;
	cout << "  * Press (w/W) to withdraw money from your account" << endl;
	cout << "  * Press (s/S) to show your account details" << endl;
	cout << "  * Press (q/Q) to quit" << endl;
	cout << "Action: ";
	cin >> action;

	//While not a valid action ask for one
	while (toupper(action) != 'D' && toupper(action) != 'W' &&
			toupper(action) != 'S' && toupper(action) != 'Q')
	{
		cout << "Please enter an existing action: ";
		cin >> action;
	}

	//If valid actions act on them
	if (toupper(action) == 'D')
	{
		deposit(firstName, lastName, accountNum);
	}
	if (toupper(action) == 'W')
	{
		withdraw(firstName, lastName, accountNum);
	}
	if (toupper(action) == 'S')
	{
		show(firstName, lastName, accountNum);
	}
}


int main()
{
	string firstName;
	string lastName;
	string accountNum;
	int validationFailed = -1;
	int normalExit = 0;

	//Enter and check firstname
	cout << "Please enter your first name: ";
	cin >> firstName;
	if (!chkName(firstName))
	{
		return validationFailed;
	}

	//Enter and check last name
	cout << "Please enter your last name: ";
	cin >> lastName;
	if (!chkName(lastName))
	{
		return validationFailed;
	}

	//Enter and check account number
	cout << "Please enter your account number: ";
	cin >> accountNum;
	if (!chkAccountFormat(accountNum))
	{
		return validationFailed;
	}

	//Verify the account exists
	if (verifyAccount(firstName, lastName, accountNum))
	{
		menu(firstName, lastName, accountNum);
	}
	else
	{
		string input;

		//Ask to make a new account
		cout << "It appears you do not have an account with us." << endl;
		cout << "Would you like to make one? (Y/N/Yes/No) ";
		cin >> input;

		//Wait for valid input
		while (input != "Y" && input != "Yes" && input != "N" && input != "No")
		{
			cout << "Please enter a valid input: ";
			cin >> input;
		}

		//Make the account if it doesn't exist and the user wants one
		if (input == "Y" || input == "Yes")
		{
			makeAccount(firstName, lastName, accountNum);
		}
	}
	return normalExit;
}
