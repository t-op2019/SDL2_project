#include <iostream>
#include <string>
#include <cstdlib>
#include <SDL2/SDL.h>

using namespace std;

int binarySearch(int left, int right);

bool humanVsComputer();

int generateNumber();

int playerGuess();

void printAnswer(int guess, int answer);

int getSolution(int guess);

bool playAgain();

int main() {
    bool continuePlay = true;
    int secretNumber = generateNumber();
    bool humanVsComp = humanVsComputer();
    
    int computerGuess = generateNumber();
    
    int start = 1;
    int end = 100;
    
    while (continuePlay) {
        
        // human vs computer gamemode
        if (humanVsComp) {
            // get player's guess
            int playerNumber = playerGuess();
            
            // print result
            printAnswer(playerNumber, secretNumber);
            
            // if play won, then ask player to play again
            if (playerNumber == secretNumber) {
                
                // if player wants to play again, set secretNumber to a new generated number; else, break the loop
                if (playAgain()) {
                    secretNumber = generateNumber();
                    computerGuess = generateNumber();
                    humanVsComp = humanVsComputer();
                } else {
                    continuePlay = false;
                }
            }
        } else {
            
            // computer choose a random number as a guess
            int solution = getSolution(computerGuess);
            
            // if the guess is correct, ask player to play again
            if (solution == 0) {
                cout << "Hooray!" << endl;
                if (playAgain()) {
                    secretNumber = generateNumber();
                    computerGuess = generateNumber();
                    humanVsComp = humanVsComputer();
                } else {
                    continuePlay = false;
                }
            } else if (solution == 1) {
                
                //if the guess is bigger than the answer, set the right boundery to be the guess number and take the new guess in the middle of the new bouderies
                start = computerGuess;
                computerGuess = (start + end) / 2;
            } else {
                
                //if the guess is smaller than the answer, set the left boundery to be the guess number and take the new guess in the middle of the new bouderies
                end = computerGuess;
                computerGuess = (start + end) / 2;
            }
        }
    }
}

bool humanVsComputer() {
    int mode;
    cout << "Choose your gamemode: (Enter 1 for human vs computer and 0 for computer vs human) ";
    cin >> mode;
    return mode;
}

int generateNumber() {
    return rand() % 100 + 1;
}

int playerGuess() {
    int guess;
    cout << "Enter your number (from 1 to 100): ";
    cin >> guess;
    return guess;
}

void printAnswer(int guess, int answer) {
    if (guess == answer) {
        cout << "You are correct!";
    } else if (guess < answer) {
        cout << "Your number is too small!";
    } else {
        cout << "Your number is too big!";
    }
    cout << endl;
}

int getSolution(int guess) {
    string answer;
    cout << "Is " << guess << " your number? (yes: y; bigger: b; smaller: s): ";
    cin >> answer;
    
    // if the guess is correct, then return 0, if the guess is smaller than the answer, then return 1, and if its bigger, return 2
    return answer == "y" ? 0 : (answer == "b" ? 1 : 2);
}

bool playAgain() {
    string response;
    cout << "Do you want to play again? (y/n): ";
    cin >> response;
    if (response == "y") {
        return true;
    } else {
        return false;
    }
}

int binarySearch(int left, int right) {
    return (left + right) / 2;
}
