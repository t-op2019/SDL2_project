//
//  game_functions.cpp
//  SDL2_project
//
//  Created by Dư Võ on 3/16/22.
//

#include "game_functions.h"
#include "SDL_Utils.h"
#include "background_functions.h"

int startPoint = 1, endPoint = 100;

string response = "";

string guess = "";

string computersGuess = "";

// x coordinate to show player's input at index
int renderPos[3] = {120, 160, 200};

// list of numbers to check player's input
string nums[10] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};

bool humanVsComputer() {
    renderChooseGamemode();
    int mode;
    bool isListening = true;
    SDL_Event event;
    while(SDL_PollEvent(&event) | isListening) {
        if (event.type == SDL_QUIT) {
            isListening = false;
            unloadAllTextures();
            exit(1);
        }
        
        if (event.type == SDL_KEYDOWN) {
            string res = interpretKey(&event.key);
            if (res == "1" | res == "2") {
                if (res == "1") {
                    mode = 1;
                } else {
                    mode = 0;
                }
                isListening = false;
            }
        }
    }
    return mode;
}

int generateNumber() {
    return rand() % 100 + 1;
}

int playerGuess() {
    string currentGuess = "";
    bool isListening = true;
    SDL_Event event;
    while(SDL_PollEvent(&event) | isListening) {
        if (event.type == SDL_QUIT) {
            isListening = false;
            unloadAllTextures();
            exit(1);
        }
        if (event.type == SDL_KEYDOWN) {
            if (interpretKey(&event.key) == "Return") {
//                SDL_RenderClear(renderer);
                isListening = false;
            }
            const string pressedKey = interpretKey(&event.key);
            
            // check if the key pressed is a number
            if ((find(begin(nums), end(nums), pressedKey) != end(nums)) && currentGuess.length() < 3) {
                rerender(response, guess);
                currentGuess += pressedKey;
                for (int i = 0; i < currentGuess.length(); i++) {
                    int currentNum = currentGuess[i] - 48;
                    renderGuess(currentNum, renderPos[i], 460);
                }
                renderPresent();
            }
        }
    }
    int answer = currentGuess.length() > 0 ? stoi(currentGuess) : 1;
    guess = currentGuess;
    renderLoading(guess);
    return answer;
}

void printAnswer(int guessNum, int answer) {
    if (guessNum == answer) {
        response = "correct";
    } else if (guessNum < answer) {
        response = "small";
    } else {
        response = "big";
    }
    rerender(response, guess);
}

int getSolution(int guess) {
    rerender("", "");
    renderComputerGuess(computersGuess);
    string answer;
    SDL_Event event;
    bool isListening = true;
    while (SDL_PollEvent(&event) || isListening) {
        if (event.type == SDL_QUIT) {
            isListening = false;
            unloadAllTextures();
            exit(1);
        }
        if (event.type == SDL_KEYDOWN) {
            string key = interpretKey(&event.key);
            if (key == "Y" || key == "B" || key == "S") {
                answer = key;
                isListening = false;
            }
        }
    }
    // if the guess is correct, then return 0, if the guess is smaller than the answer, then return 1, and if its bigger, return 2
    return answer == "Y" ? 0 : (answer == "B" ? 1 : 2);
}

bool playAgain() {
    rerender(response, guess);
    renderReplay();
    renderPresent();
    SDL_Event event;
    string res = "";
    bool isListening = true;
    while(SDL_PollEvent(&event) | isListening) {
        if (event.type == SDL_QUIT) {
            isListening = false;
            unloadAllTextures();
            exit(1);
        }
        if (event.type == SDL_KEYDOWN) {
            const string pressedKey = interpretKey(&event.key);
            
            // check if the key pressed is a number
            if (pressedKey == "Y" || pressedKey == "N") {
                
                // if player doesnt want to play again, quit the program
                if (pressedKey == "N") {
                    unloadAllTextures();
                    exit(0);
                }
                
                // set computer response to blank and break the loop, then return yes to replay
                guess = "";
                response = "";
                isListening = false;
                res = "Y";
            }
        }
    }
    rerender(response, guess);
    return (res == "Y") ? true : false;
}

int binarySearch(int left, int right) {
    return (left + right) / 2;
}

void playGame(bool &isRunning, int &secretNumber, int &computerGuess, bool &humanVsComp) {
    
    // human vs computer gamemode
    if (humanVsComp) {
        // render the prompt for user to enter guess
        renderPrompt(response, guess);
        
        // get player's guess
        int playerNumber = playerGuess();
        
        // print result
        printAnswer(playerNumber, secretNumber);
        
        // if play won, then ask player to play again
        if (playerNumber == secretNumber) {
            // if player wants to play again, set secretNumber to a new generated number; else, break the loop
            if (playAgain()) {
                humanVsComp = humanVsComputer();
                if (humanVsComp) {
                    secretNumber = generateNumber();
                } else {
                    computerGuess = generateNumber();
                }
            } else {
                isRunning = false;
                unloadAllTextures();
            }
        }
    } else {
        computersGuess = to_string(computerGuess);
        // computer choose a random number as a guess
        int solution = getSolution(computerGuess);
        
        // if the guess is correct, ask player to play again
        if (solution == 0) {
            cout << "Hooray!" << endl;
            if (playAgain()) {
                startPoint = 1;
                endPoint = 100;
                humanVsComp = humanVsComputer();
                if (humanVsComp) {
                    secretNumber = generateNumber();
                } else {
                    computerGuess = generateNumber();
                }
            } else {
                isRunning = false;
                unloadAllTextures();
            }
        } else if (solution == 1) {
            
            //if the guess is bigger than the answer, set the right boundery to be the guess number and take the new guess in the middle of the new bouderies
            startPoint = computerGuess;
            computerGuess = (startPoint + endPoint) / 2;
        } else {
            
            //if the guess is smaller than the answer, set the left boundery to be the guess number and take the new guess in the middle of the new bouderies
            endPoint = computerGuess;
            computerGuess = (startPoint + endPoint) / 2;
        }
    }
}
