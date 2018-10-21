#include <iostream>
#include <string>
#include <cmath>

//Makes it so I don't need to type std:: before the following functions anymore
using std::cin;
using std::cout;
using std::endl;
using std::pow;
using std::fmod;
using std::string;


int main()
{
    //Variable Declarations
    float num1 = 0;
    float num2 = 0;
    string operation;

    //Example on how to use the calculator
    cout << "Welcome to the CS141 Calculator." << endl;
    cout << "You can enter commands as: 2.5 power 2 or 2.5 ^ 2" << endl;

    //User Input
    cin >> num1; cin >> operation; cin >> num2;

    //Check to see if user wants to exit
    if (num1 == -1 && num2 == -1)
    {
        if (operation == "quit" || operation == "x")
        {
            return 0;
        }
    }

    //Check to see which operations we are using
    if (operation == "+" || operation == "plus")
    {
        cout  << num1 + num2 << endl;
    }
    else if (operation == "-" || operation == "minus")
    {
        cout << num1 - num2 << endl;
    }
    else if (operation == "*" || operation == "multiply")
    {
        cout << num1 * num2 << endl;
    }
    else if (operation == "/" || operation == "divide")
    {
        //Check to see if trying to divide by 0
        if (num2 == 0)
        {
            cout << "Cannot divide by 0" << endl;
        }
        else
        {
            cout << num1 / num2 << endl;
        }
    }
    else if (operation == "^" || operation == "power")
    {
        cout << pow(num1, num2) << endl;
    }
    else if (operation == "%" || operation == "mod")
    {
        cout << fmod(num1, num2) << endl;
    }
    else
    {
        //Check to see if the operator is bad
        cout << "I do not recognize the operator: " + operation << endl;
    }
}

