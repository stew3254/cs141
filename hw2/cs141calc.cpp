#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::string;

int main() {
    //Variable Declarations
    float num1 = 0;
    float num2 = 0;
    float output = 0;
    string operation;

    while(num1 != -1 || num2 != -1 || (operation != "x" && operation != "quit"))
    {
        output = 0;
        //Example on how to use the calculator
        cout << "Enter two numbers and an operator as follows:" << endl;
        cout << "12 26 plus" << endl;
        cout << "15 12 +" << endl;
        cout << "Enter -1 -1 quit or -1 -1 x to quit" << endl;

        //User Input
        cin >> num1; cin >> num2; cin >> operation;

        //Check to see which operations we are using
        if (operation == "+" || operation == "plus")
        {
            output = num1 + num2;
            cout << "Result of " << num1 << " " << num2 << " " << operation +  " is " << output << endl;
        }
        else if (operation == "-" || operation == "minus")
        {
            output = num1 - num2;
            cout << "Result of " << num1 << " " << num2 << " " << operation +  " is " << output << endl;
        }
        else if (operation == "*" || operation == "multiply")
        {
            output = num1 * num2;
            cout << "Result of " << num1 << " " << num2 << " " << operation +  " is " << output << endl;
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
                output = num1 / num2;
                cout << "Result of " << num1 << " " << num2 << " " << operation +  " is " << output << endl;
            }
        }
        else if (operation != "x" && operation != "quit")
        {
            //Check to see if the operator is bad
            cout << "I do not recognize the operator: " + operation << endl;
        }
    }
}

