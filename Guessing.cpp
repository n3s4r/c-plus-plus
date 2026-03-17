#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
    srand(time(0)); // Seed for randomness

    int randomNumber = rand() % 100 + 1; // Random number between 1 and 100
    int guess;
    int attempts = 0;

    cout << "🎯 Welcome to the Number Guessing Game!" << endl;
    cout << "Guess a number between 1 and 100." << endl;

    do {
        cout << "\nEnter your guess: ";
        cin >> guess;
        attempts++;

        if (guess > randomNumber) {
            cout << "Too high! Try again.";
        } else if (guess < randomNumber) {
            cout << "Too low! Try again.";
        } else {
            cout << "\n🎉 Correct! You guessed it in " << attempts << " attempts.";
        }

    } while (guess != randomNumber);

    return 0;
}
