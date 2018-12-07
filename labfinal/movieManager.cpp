#include <iostream>
#include <fstream>

using std::string;
using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;

//Define the movie
struct Movie {
  string name;
  int year;
  float earnings;

  //Initialize some variables
  Movie() {
    year = 0;
    earnings = 0;
  }
};

//Create an array of 50 movies
Movie movies[50];

//Read in data from file
void readData() {
  //Read in from moviedata.txt file
  ifstream inFile;
  inFile.open("moviedata.txt");

  //Read in all 50 movies
  for (int i = 0; i < 50; i++) {
    inFile >> movies[i].name >> movies[i].year >> movies[i].earnings;
  }
}

//Shows all movies
void showAll() {
  //Print out all of the movies
  for (int i = 0; i < 50; i++) {
    cout << movies[i].name << " ";
    cout << movies[i].year << " ";
    cout << movies[i].earnings << endl;
  }
}

void showByYear() {
  //Define inital variables and the movies
  int year = 0;
  int total = 0;
  float average = 0;
  Movie highestGrossing;
  Movie lowestGrossing;

  //Ask for a year
  cout << "Enter a year: ";
  cin >> year;

  //Look through all of the movies
  for (int i = 0; i < 50; i++) {
    //Check to see if the movie year is correct
    if (movies[i].year == year) {
      //Add one to the total number movies
      total += 1;

      //Check to see if this is the highest grossing movie
      if (movies[i].earnings > highestGrossing.earnings) {
        //Set all of the values for the movie
        highestGrossing.name = movies[i].name;
        highestGrossing.year = movies[i].year;
        highestGrossing.earnings = movies[i].earnings;
      }
      //Check to see if this is the lowest grossing movie
      //Also make sure lowest grossing isn't 0
      else if (movies[i].earnings < lowestGrossing.earnings || lowestGrossing.earnings == 0) {
        //Set all of the values for the movie
        lowestGrossing.name = movies[i].name;
        lowestGrossing.year = movies[i].year;
        lowestGrossing.earnings = movies[i].earnings;
      }
      //Add the earnings to the average and divide later by the total
      average += movies[i].earnings;
    }
  }
  //Take the total earnings and divide by the total number of earnings to get the actual average
  average /= total;

  //If there are no movies say so
  if (total == 0) {
    cout << "No movies found" << endl;
  }
  //Otherwise print out all of their values
  else {
    cout << "Total number of movies: " << total << endl;

    cout << "Highest Grossing: " << highestGrossing.name << " ";
    cout << highestGrossing.year << " ";
    cout << highestGrossing.earnings << endl;

    cout << "Lowest Grossing: " << lowestGrossing.name << " ";
    cout << lowestGrossing.year << " ";
    cout << lowestGrossing.earnings << endl;

    cout << "Average: " << average << endl;
  }
}

//Displays a nice menu
void showMenu() {
  string input;
  bool inputOkay = false;

  //Show menu
  cout << "Welcome to movie manager! Here is a list of options" << endl;
  cout << "\t1. Show all movies" << endl;
  cout << "\t2. Show movies statistics by year" << endl;
  cout << "\t3. Quit" << endl;

  //Get input
  cout << "Please enter an option: ";
  cin >> input;

  //Make sure the input is good
  while (!inputOkay) {
    //Check to see if the inputs aren't valid
    if (input != "1" && input != "2" && input != "3" && input != "q" && input != "Q") {
      cout << "Please enter a valid option: ";
      cin >> input;
    }
    //If valid break the loop
    else {
      inputOkay = true;
    }
  }
  //Quit
  if (input == "3" || input == "q" || input == "Q") {
    cout << "Quitting" << endl;
  }
  //Show movies
  else if (input == "1") {
    showAll();
  }
  if (input == "2") {
    showByYear();
  }
}


int main() {

  //Read in the data
  readData();

  //Show the menu
  showMenu();

  return 0;
}
