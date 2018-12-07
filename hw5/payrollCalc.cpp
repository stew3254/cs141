#include <iostream>
#include <fstream>
#include <math.h>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::ofstream;
using std::stof;
using std::trunc;
using std::pow;

//Enumerate the standard work days of the week
enum Days {MON, TUE, WED, THU, FRI};

//Define a Person
struct Person {
  string firstName;
  string middleName;
  string lastName;
};

//Define wage
struct Wage {
  float rate;
  char overtimeEligible;
  float overtimeRate;
};

//Define the time card
struct TimeCard {
  float hours;
  float lunch;
  float pay;
  float overtime;
};

//Define weekly hours and pay
struct WeeklyStats {
  float hours;
  float overtime;
  float pay;
  float lunch;

  //Initialize the values
  WeeklyStats() {
    hours = 0;
    overtime = 0;
    pay = 0;
    lunch;
  }
};

//Define an employee
struct Employee {
  Person name;
  Person manager;
  TimeCard card[5];
  Wage wage;
  WeeklyStats weekly;
  string department;
};

//All employees
Employee employees[20];


//Round the numbers to a nice decimal place
float round(float num, int power) {
  return trunc(num * pow(10, power) + .5)/((float)(pow(10, power)));
}

//Gets the hours worked
float hoursWorked(string clockIn, string clockOut) {
  short loc = clockIn.find(":");
  float hours = 0;
  float minutes = 0;

  //Get the total hours spent at work excluding lunch break (excluding the minutes)
  hours = stof(clockOut.substr(0, loc));
  hours -= stof(clockIn.substr(0, loc));

  //Get the total minutes spent at work excluding lunch break
  minutes = stof(clockOut.substr(loc + 1, loc));
  minutes -= stof(clockIn.substr(loc + 1, loc));

  //The total numbers of hours from clock in to lock out (excluding lunch break)
  hours += minutes/60;
  return hours;
}


//Get the break Length
float breakLength(string lunchClockIn, string lunchClockOut) {
  short loc = lunchClockIn.find(":");
  float hours = 0;
  float minutes = 0;

  //Get the total hours spent at lunch break (excluding the minutes)
  hours = stof(lunchClockIn.substr(0, loc));
  hours -= stof(lunchClockOut.substr(0, loc));

  //Get the total minutes spent at lunch break
  minutes = stof(lunchClockIn.substr(loc + 1, loc));
  minutes -= stof(lunchClockOut.substr(loc + 1, loc));

  //The total numbers of hours spent at lunch break
  hours += minutes/60;

  //The total time spent working
  return hours;
}


//Get the overtimeHours
float overtimeHours(float hours) {
  if (hours > 37.5 ) {
    hours -= 37.5;
  }
  return hours;
}


//Find total pay day
void totalDayPay(Employee &employee) {
  static float pay = 0;
  //If they are eligible for overtime and have a bonus rate to it, pay them it
  if (employee.wage.overtimeEligible == 'Y' && employee.wage.overtimeRate != 0) {
    pay = employee.wage.overtimeRate * employee.wage.rate * employee.weekly.overtime;
    pay += employee.wage.rate * (employee.weekly.hours - employee.weekly.overtime);
  }
  //Otherwise don't
  else {
    pay = employee.wage.rate * employee.weekly.hours;
  }
  employee.weekly.pay = pay;
}


void writeData(string file, Employee employee) {
  ofstream f;
  f.open(file, std::ios_base::app);

  //Write employee tag
  f << "\t<employee>" << endl;

  //Write employee name
  f << "\t\t<name>"  + employee.name.firstName  + " ";
  if (employee.name.middleName != "NONE") {
    f << employee.name.middleName + " ";
  }
  f << employee.name.lastName  + "</name>" << endl;

  //Write Manager
  f << "\t\t<manager>"  + employee.manager.firstName  + " ";
  if (employee.manager.middleName != "NONE") {
    f << employee.manager.middleName + " ";
  }
  f << employee.manager.lastName  + "</manager>" << endl;

  //Write the rest
  f << "\t\t<department>" + employee.department + "</department>" << endl;
  f << "\t\t<payrate>" << round(employee.wage.rate, 2) << "</payrate>" << endl;
  f << "\t\t<overtime>" << employee.wage.overtimeEligible << "</overtime>" << endl;
  f << "\t\t<multiplier>" << round(employee.wage.overtimeRate, 2) << "</multiplier>" << endl;
  f << "\t\t<hours>" << round(employee.weekly.hours, 2) << "</hours>" << endl;
  f << "\t\t<overhours>" << round(employee.weekly.overtime, 2) << "</overhours>" << endl;
  f << "\t\t<lunch>" << round(employee.weekly.lunch, 2) << "</lunch>" << endl;
  f << "\t\t<pay>" << round(employee.weekly.pay, 2) << "</pay>" << endl;

  //Close the employee tag
  f << "\t</employee>" << endl;

  //Close the file
  f.close();
}


//Read in data from the payroll data file
void readData(string inputFile, string outputFile) {
  ifstream inFile;
  ofstream outFile;

  //Open the files
  inFile.open(inputFile);
  outFile.open(outputFile);

  string clockIn;
  string clockOut;
  string lunchClockOut;
  string lunchClockIn;

  //Start to write out to the output file
  outFile << "<payroll>" << endl;
  outFile.close();

  for (int employee = 0; employee < 20; employee++) {
    for (int day = MON; day <= FRI; day++) {
      //Read in employee wage information
      inFile >> employees[employee].wage.rate
      >> employees[employee].wage.overtimeEligible
      >> employees[employee].wage.overtimeRate
      //Read in employee name
      >> employees[employee].name.firstName
      >> employees[employee].name.middleName
      >> employees[employee].name.lastName
      //Read in where they work
      >> employees[employee].department
      //Read in manager name
      >> employees[employee].manager.firstName
      >> employees[employee].manager.middleName
      >> employees[employee].manager.lastName
      //Read in clock times
      >> clockIn
      >> lunchClockOut
      >> lunchClockIn
      >> clockOut;

      //Weekly time an employee worked
      employees[employee].weekly.hours += hoursWorked(clockIn, clockOut);
      employees[employee].weekly.hours -= breakLength(lunchClockIn, lunchClockOut);
    }
    //Weekly overtime hours
    employees[employee].weekly.overtime = overtimeHours(employees[employee].weekly.hours);

    //Weekly pay
    totalDayPay(employees[employee]);

    //Write out the data
    writeData(outputFile, employees[employee]);
  }

  //Close the files
  outFile.open(outputFile, std::ios_base::app);
  outFile << "</payroll>" << endl;
  outFile.close();
  inFile.close();
}


int main() {
  string inputFile;
  string outputFile;
  bool nameOkay = false;

  //Get the name of the input file
  cout << "Please enter the name of the input file: ";
  cin >> inputFile;

  //Loop while the name isn't okay
  while (!nameOkay) {

    //If the name is not long enough to have a character in front of '.txt' then ask for a new name
    if (inputFile.length() <= 4) {
      cout << "Please enter a valid name for the input file: ";
      cin >> inputFile;
    }
    //If the extension isn't '.txt' ask for a new one
    else if (inputFile.substr(inputFile.length() - 4, 4) != ".txt") {
      cout << "Please enter a valid name for the input file: ";
      cin >> inputFile;
    }
    else {
      nameOkay = true;
    }
  }

  //Get the name of the output file
  cout << "Please enter the name of the output file: ";
  cin >> outputFile;

  //Loop again
  nameOkay = false;
  while (!nameOkay) {
    //If the name is not long enough to have a character in front of '.xml' then ask for a new name
    if (outputFile.length() < 4) {
      cout << "Please enter a valid name for the output file: ";
      cin >> outputFile;
    }
    //If the extension isn't '.xml' ask for a new one
    else if (outputFile.substr(outputFile.length() - 4, 4) != ".xml") {
      cout << "Please enter a valid name for the output file: ";
      cin >> outputFile;
    }
    else {
      nameOkay = true;
    }
  }

  //Read in the data and in the process write it out
  readData(inputFile, outputFile);
  return 0;
}
