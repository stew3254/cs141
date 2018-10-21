#include<iostream>
#include<string>

//Imports so I don't need to type std:: in front of everything
using std::cout;
using std::cin;
using std::endl;
using std::string;

int main()
{
	//Definitions
	string myStr = "the quick brown fox jumped right over the lazy dog.";
	string mySubStr;
	short newPos = 0;

	//Get a character or word
	cout << "Enter a character or a word: ";
	cin >> mySubStr;
	newPos = myStr.find(mySubStr);
	
	//Initially check to see if the character exists
	if (newPos < 0 && newPos >= myStr.length())
	{
		cout << "Not found" << endl;
	}
	else
	{
		//Since at least one character exists, define new variables to be used in looping through the string
		short pos = 0;	
		short iteration = 0;

		//Continually check to see if the substring exists in the new substring
		while (newPos > -1 && newPos < myStr.length())
		{
			//Create a new string smaller than the original string, then subsequent substrings 
			myStr = myStr.substr(newPos + 1, myStr.length() - mySubStr.length());

			//Make sure the positions line up with the current directory
			pos = pos + newPos;
			
			//Find the new substring we are searching for within the new substring
			newPos = myStr.find(mySubStr);
			
			//Print out the positions and make sure characters are right
			cout << pos + iteration << ", ";
			iteration++;
		}			
		//Print a newline character
		cout << endl;
	}

	return 0;
}
