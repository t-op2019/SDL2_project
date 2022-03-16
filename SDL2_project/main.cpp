#include <iostream>
#include <string>
#include "SDL_Utils.h"
#include "game_functions.h"

using namespace std;

const string windowTitle = "Guess It";

//----------------------------------------------------------------------------------------------------------------------------------------

int main() {
    bool isRunning = true;
    
    // preload all textures of the game
    loadAllTextures();
    
    bool humanVsComp = true;
    int secretNumber = generateNumber();
    int computerGuess = generateNumber();
    
    // run the game program
    while (isRunning) {
        // if player quit, then break the loop
//        if ( SDL_WaitEvent(&e) != 0 && (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) ) {
//            isRunning = false;
//        }
        
//        SDL_Delay(100);
        
        playGame(isRunning, secretNumber, computerGuess, humanVsComp);
    }
    
    return 0;
    
}


//----------------------------------------------------------------------------------------------------------------------------------------
