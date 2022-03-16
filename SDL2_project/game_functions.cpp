//
//  game_functions.cpp
//  SDL2_project
//
//  Created by Dư Võ on 3/16/22.
//

#include "game_functions.h"
#include "SDL_Utils.h"

const int width = 800, height = 600;
const string windowTitle = "Guess It!";

int startPoint = 1, endPoint = 100;

string response = "";

string guess = "";

// coordinate of first and second digit of players guess to be render at
int firstDigitPos[2] = {44, 460};
int secondDigitPos[2] = {69, 500};

// list of numbers to check player's input
string nums[10] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};

// x coordinate to show player's input at index
int positions[3] = {120, 160, 200};
int positions2[3] = {480, 520, 560};

// height of fonts
int fontHeight = 36;

SDL_Window* window;
SDL_Renderer* renderer;

SDL_Texture *background, *guessMessage, *loadingMessage, *bigMessage, *smallMessage, *correctMessage, *numMessage[10], *replayMessage;

void loadAllTextures() {
    initSDL(window, renderer, windowTitle, width, height);
    const string defaultRoute = "SDL2_project/assets/images/";
    bool numberLoaded = true;
    
    background = loadTexture(defaultRoute + "background.png", renderer);
    guessMessage = loadTexture(defaultRoute + "guess.png", renderer);
    loadingMessage = loadTexture(defaultRoute + "loading.png", renderer);
    bigMessage = loadTexture(defaultRoute + "big.png", renderer);
    smallMessage = loadTexture(defaultRoute + "small.png", renderer);
    correctMessage = loadTexture(defaultRoute + "correct.png", renderer);
    replayMessage = loadTexture(defaultRoute + "replay.png", renderer);
    
    for (int i = 0; i < 10; i++) {
        numMessage[i] = loadTexture(defaultRoute + to_string(i) + ".png", renderer);
        if (numMessage[i] == NULL) {
            numberLoaded = false;
            break;
        }
    }
    
    if (background == NULL || guessMessage == NULL || bigMessage == NULL || smallMessage == NULL || correctMessage == NULL || numberLoaded == false) {
        unloadAllTextures();
        exit(1);
    }
    
    rerender();
    
//    SDL_RenderPresent(renderer);
}



void unloadAllTextures() {
    SDL_DestroyTexture(background);
    SDL_DestroyTexture(guessMessage);
    SDL_DestroyTexture(loadingMessage);
    SDL_DestroyTexture(bigMessage);
    SDL_DestroyTexture(smallMessage);
    SDL_DestroyTexture(correctMessage);
    SDL_DestroyTexture(replayMessage);
    
    for (int i = 0; i < 10; i++) {
        SDL_DestroyTexture(numMessage[i]);
    }
    
    quitSDL(window, renderer);
}

// rerender the screen to original state
// if in the middle of the game, check the computer response to render hints instead of nothing
void rerender() {
    SDL_RenderClear(renderer);
    renderTexture(background, renderer, 0, 0, width, height);
    if (response == "big") {
        for (int i = 0; i < guess.length(); i++) {
            int currentNum = guess[i] - 48;
            renderGuess(numMessage[currentNum], positions2[i], 320);
        }
        renderResponse(bigMessage, 380, 185);
    } else if (response == "small") {
        for (int i = 0; i < guess.length(); i++) {
            int currentNum = guess[i] - 48;
            renderGuess(numMessage[currentNum], positions2[i], 320);
        }
        renderResponse(smallMessage, 380, 185);
    } else if (response == "correct") {
        renderResponse(correctMessage, 360, 185);
    }
}

// render the word "Guess a number" so that player knows to type in a number
void renderPrompt() {
    rerender();
    renderTexture(guessMessage, renderer, firstDigitPos[0], firstDigitPos[1], 260, fontHeight);
    SDL_RenderPresent(renderer);
}

// render player's input numbers
void renderGuess(SDL_Texture* texture, int posX, int posY) {
    renderTexture(texture, renderer, posX, posY, 36, fontHeight);
//    SDL_RenderPresent(renderer);
}

// render the word "Loading..." for 1.5 seconds after player enter a guess
void renderLoading() {
    SDL_RenderClear(renderer);
    renderTexture(background, renderer, 0, 0, width, height);
    for (int i = 0; i < guess.length(); i++) {
        int currentNum = guess[i] - 48;
        renderGuess(numMessage[currentNum], positions[i], 460);
    }
    renderTexture(loadingMessage, renderer, 450, 360, 160, fontHeight);
    SDL_RenderPresent(renderer);
    SDL_Delay(1500);
}

void renderResponse(SDL_Texture* texture, int y, int textureWidth) {
    renderTexture(texture, renderer, 450, y, textureWidth, fontHeight);
//    SDL_RenderPresent(renderer);
}

void renderReplay() {
    renderTexture(replayMessage, renderer, 44, 460, 240, 32);
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
    string currentGuess = "";
    bool isListening = true;
    SDL_Event event;
    while(SDL_PollEvent(&event) | isListening) {
        if (event.type == SDL_QUIT) {
            isListening = false;
            unloadAllTextures();
            quitSDL(window, renderer);
            exit(1);
        }
        if (event.type == SDL_KEYDOWN) {
            if (interpretKey(&event.key) == "Return") {
//                SDL_RenderClear(renderer);
                isListening = false;
            }
            const string pressedKey = interpretKey(&event.key);
            
            // check if the key pressed is a number
            if (find(begin(nums), end(nums), pressedKey) != end(nums)) {
                rerender();
                currentGuess += pressedKey;
                for (int i = 0; i < currentGuess.length(); i++) {
                    int currentNum = currentGuess[i] - 48;
                    renderGuess(numMessage[currentNum], positions[i], 460);
                }
                SDL_RenderPresent(renderer);
//                cout << interpretKey(&event.key) << endl;
            }
        }
    }
//    cout << guess << " guessed" << endl;
    int answer = currentGuess.length() > 0 ? stoi(currentGuess) : 1;
//    cout << "Enter your number (from 1 to 100): ";
//    cin >> guess;
    guess = currentGuess;
    renderLoading();
    return answer;
}

void printAnswer(int guess, int answer) {
    if (guess == answer) {
        response = "correct";
        cout << "You are correct!";
    } else if (guess < answer) {
        response = "small";
        cout << "Your number is too small!";
    } else {
        response = "big";
        cout << "Your number is too big!";
    }
    rerender();
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
    rerender();
    renderReplay();
    SDL_RenderPresent(renderer);
    SDL_Event event;
    string res = "";
    bool isListening = true;
    while(SDL_PollEvent(&event) | isListening) {
        if (event.type == SDL_QUIT) {
            isListening = false;
            unloadAllTextures();
            quitSDL(window, renderer);
            exit(1);
        }
        if (event.type == SDL_KEYDOWN) {
            const string pressedKey = interpretKey(&event.key);
            
            // check if the key pressed is a number
            if (pressedKey == "Y" || pressedKey == "N") {
                
                // if player doesnt want to play again, quit the program
                if (pressedKey == "N") {
                    unloadAllTextures();
                    quitSDL(window, renderer);
                    exit(0);
                }
                
                // set computer response to blank and break the loop, then return yes to replay
                response = "";
                isListening = false;
                res = "Y";
            }
        }
    }
    return (res == "Y") ? true : false;
//    string response;
//    cout << "Do you want to play again? (y/n): ";
//    cin >> response;
//    if (response == "y") {
//        return true;
//    } else {
//        return false;
//    }
}

int binarySearch(int left, int right) {
    return (left + right) / 2;
}

void playGame(bool &isRunning, int &secretNumber, int &computerGuess, bool &humanVsComp) {
    // render the prompt for user to enter guess
    renderPrompt();
    
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
                cout << "Play again";
                secretNumber = generateNumber();
                computerGuess = generateNumber();
//                humanVsComp = humanVsComputer();
                humanVsComp = true;
            } else {
                isRunning = false;
                unloadAllTextures();
                quitSDL(window, renderer);
            }
        }
    } else {
        
        // computer choose a random number as a guess
        int solution = getSolution(computerGuess);
        
        // if the guess is correct, ask player to play again
        if (solution == 0) {
            cout << "Hooray!" << endl;
            if (playAgain()) {
                startPoint = 1;
                endPoint = 100;
                secretNumber = generateNumber();
                computerGuess = generateNumber();
                humanVsComp = humanVsComputer();
            } else {
                isRunning = false;
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
