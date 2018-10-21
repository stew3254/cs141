#include <iostream>
using std::cout;
using std::endl;

int main() {
    //Grade weights
    int homeworkWeight = 25;
    int examWeight = 35;
    int finalWeight = 40;

    //Stuart Little's grades
    int homeworkScore = 92;
    int examScore = 93;
    int finalScore = 94;

    //Calculate class score
    float classScore = (homeworkWeight / 100.0 * homeworkScore) + (examWeight / 100.0 * examScore) + (finalWeight / 100.0 * finalScore);

    //Print score
    cout << classScore << endl;

    return 0;
}
