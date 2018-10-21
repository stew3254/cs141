#include<iostream>
#include<fstream>
#include<algorithm>

using std::ifstream;
using std::ofstream;
using std::string;
using std::tolower;


string generateEmail(string , string);

int main() {
	ifstream inpFile;
	ofstream outFile;
	string name;
	string firstName;
	string lastName;
	string email;
	bool ifFirstName = true;

	inpFile.open("employeeNames.txt");
	inpFile >> name;
	outFile.open("employeesXMLData.xml");
	outFile << "<employees>\n";

	while (!inpFile.eof())
	{
		if (ifFirstName) {
			firstName = name;
			outFile << "\t<person>\n\t\t<firstname>" + firstName + "</firstname>\n";
			ifFirstName = false;
		}
		else
		{
			lastName = name;
			outFile << "\t\t<lastname>" + lastName + "</lastname>" << "\n";

			email = generateEmail(firstName, lastName);
			outFile << "\t\t<email>" + email + "</email>\n\t</person>\n";
			ifFirstName = true;
		}
		inpFile >> name;
	}
	inpFile.close();
	outFile << "</employees>";
	outFile.close();

	return 0;
}

string generateEmail(string first, string last)
{
	string email;

	first = tolower(first[0]);
	if (last.length() > 7)
	{
		last = last.substr(0, 7);
	}
	for (int i=0;  i<last.length(); i++)
	{
		last[i] = tolower(last[i]);
	}
	email = first + last + "@company.com";

	return email;
}
