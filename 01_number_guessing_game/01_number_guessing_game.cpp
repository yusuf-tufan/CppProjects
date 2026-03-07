#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include <ctime>
using namespace std;
//Number Guessing Game;
int main()
{
    srand(time(0));
    int selectEndNum, station = 1;

    while (station) {
        cout << "Enter End Number: ";
        cin >> selectEndNum;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Enter Just Number!" << endl;
            continue;
        }
        if (selectEndNum < 1 || selectEndNum>500) {
            cout << "Number must be between 1 and 500!" << endl;
            continue;
        }
        else {
            int num = rand() % selectEndNum + 1, userguess, count;
            count = 1;
            while (true) {
                cout << "Your Guess: ";
                cin >> userguess;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Enter Just Number!" << endl;
                    continue;

                }
                if (userguess == num) {
                    cout << "Congratulations! You guessed it!\nTraid " << count << " times." << endl << "Choose 1 to play again, 0 to exit: ";
                    cin >> station;
                    if (station == 1) { break; }
                    else if (station == 0) { break; }
                    else { cout << "Please Enter 1 or 0 "; }
                }
                else if (userguess > selectEndNum || userguess < 1) {
                    cout << "Number between 1-" << selectEndNum << endl;
                }
                else if (userguess < num) {
                    cout << "Too low!" << endl;
                    count += 1;
                }
                else {
                    cout << "Too high!" << endl;
                    count += 1;
                }
            }
        }
    }

    return 0;
}