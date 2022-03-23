//
//  background_functions.cpp
//  SDL2_project
//
//  Created by Dư Võ on 3/23/22.
//

#include "background_functions.h"
#include "SDL_Utils.h"

const int width = 800, height = 600;

const string windowTitle = "Guess It!";

// coordinate of first and second digit of players guess to be render at
int firstDigitPos[2] = {44, 460};
int secondDigitPos[2] = {69, 500};

// x coordinate to show player's input at index
int positions[3] = {120, 160, 200};
int posLength1[1] = {520};
int posLength2[2] = {500, 540};
int posLength3[3] = {480, 520, 560};

// height of fonts
int fontHeight = 36;

SDL_Window* window;
SDL_Renderer* renderer;

SDL_Texture *background, *gamemodeMessage, *gameOptionsMessage, *guessMessage, *loadingMessage, *bigMessage, *smallMessage, *correctMessage, *numMessage[10], *replayMessage,
    *computerGuessMessage, *playerResponseMessage;

void loadAllTextures(const string response, const string guess) {
    initSDL(window, renderer, windowTitle, width, height);
    const string defaultRoute = "SDL2_project/assets/images/";
    bool numberLoaded = true;
    
    background = loadTexture(defaultRoute + "background.png", renderer);
    gamemodeMessage = loadTexture(defaultRoute + "gamemode.png", renderer);
    gameOptionsMessage = loadTexture(defaultRoute + "game options.png", renderer);
    guessMessage = loadTexture(defaultRoute + "guess.png", renderer);
    loadingMessage = loadTexture(defaultRoute + "loading.png", renderer);
    bigMessage = loadTexture(defaultRoute + "big.png", renderer);
    smallMessage = loadTexture(defaultRoute + "small.png", renderer);
    correctMessage = loadTexture(defaultRoute + "correct.png", renderer);
    replayMessage = loadTexture(defaultRoute + "replay.png", renderer);
    computerGuessMessage = loadTexture(defaultRoute + "computer guess.png", renderer);
    playerResponseMessage = loadTexture(defaultRoute + "player response.png", renderer);
    
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
    
    rerender(response, guess);
    
//    SDL_RenderPresent(renderer);
}



void unloadAllTextures() {
    SDL_DestroyTexture(background);
    SDL_DestroyTexture(gamemodeMessage);
    SDL_DestroyTexture(gameOptionsMessage);
    SDL_DestroyTexture(guessMessage);
    SDL_DestroyTexture(loadingMessage);
    SDL_DestroyTexture(bigMessage);
    SDL_DestroyTexture(smallMessage);
    SDL_DestroyTexture(correctMessage);
    SDL_DestroyTexture(replayMessage);
    SDL_DestroyTexture(computerGuessMessage);
    SDL_DestroyTexture(playerResponseMessage);
    
    for (int i = 0; i < 10; i++) {
        SDL_DestroyTexture(numMessage[i]);
    }
    
    quitSDL(window, renderer);
}

void renderPresent() {
    SDL_RenderPresent(renderer);
}

void renderChooseGamemode() {
    renderTexture(gamemodeMessage, renderer, 80, 450, 166, fontHeight * 1.5);
    renderTexture(gameOptionsMessage, renderer, 425, 340, 238, 64);
    renderPresent();
}

// rerender the screen to original state
// if in the middle of the game, check the computer response to render hints instead of nothing
void rerender(const string response, const string guess) {
    SDL_RenderClear(renderer);
    renderTexture(background, renderer, 0, 0, width, height);
    int coordinates[3];
    if (guess.length() == 1) {
        copy(begin(posLength1), end(posLength1), begin(coordinates));
    } else if (guess.length() == 2) {
        copy(begin(posLength2), end(posLength2), begin(coordinates));
    } else {
        copy(begin(posLength3), end(posLength3), begin(coordinates));
    }
    if (response == "big") {
        for (int i = 0; i < guess.length(); i++) {
            int currentNum = guess[i] - 48;
            renderGuess(currentNum, coordinates[i], 320);
        }
        renderResponse(bigMessage, 380, 185);
    } else if (response == "small") {
        for (int i = 0; i < guess.length(); i++) {
            int currentNum = guess[i] - 48;
            renderGuess(currentNum, coordinates[i], 320);
        }
        renderResponse(smallMessage, 380, 185);
    } else if (response == "correct") {
        renderResponse(correctMessage, 360, 185);
    }
}

// render the word "Guess a number" so that player knows to type in a number
void renderPrompt(const string response, const string guess) {
    rerender(response, guess);
    renderTexture(guessMessage, renderer, firstDigitPos[0], firstDigitPos[1], 260, fontHeight);
    renderPresent();
}

// render player's input numbers
void renderGuess(int renderNumber, int posX, int posY) {
    renderTexture(numMessage[renderNumber], renderer, posX, posY, 36, fontHeight);
//    SDL_RenderPresent(renderer);
}

// render the word "Loading..." for 1 second after player enter a guess
void renderLoading(const string guess) {
    SDL_RenderClear(renderer);
    renderTexture(background, renderer, 0, 0, width, height);
    for (int i = 0; i < guess.length(); i++) {
        int currentNum = guess[i] - 48;
        renderGuess(currentNum, positions[i], 460);
    }
    renderTexture(loadingMessage, renderer, 450, 360, 160, fontHeight);
    renderPresent();
    SDL_Delay(1000);
}

void renderResponse(SDL_Texture* texture, int y, int textureWidth) {
    renderTexture(texture, renderer, 450, y, textureWidth, fontHeight);
}

void renderReplay() {
    renderTexture(replayMessage, renderer, 44, 460, 240, 32);
}

void renderComputerGuess(const string guess) {
    renderTexture(computerGuessMessage, renderer, 460, 310, 176, 64);
    renderTexture(playerResponseMessage, renderer, 44, 446, 250, 64);
    int coordinates[3];
    if (guess.length() == 1) {
        copy(begin(posLength1), end(posLength1), begin(coordinates));
    } else if (guess.length() == 2) {
        copy(begin(posLength2), end(posLength2), begin(coordinates));
    } else {
        copy(begin(posLength3), end(posLength3), begin(coordinates));
    }
    for (int i = 0; i < guess.length(); i++) {
        int currentNum = guess[i] - 48;
        renderGuess(currentNum, coordinates[i], 390);
    }
    renderPresent();
}
