#include <iostream>
#include <string>
#include "SDL_Utils.h"
#include "game_functions.h"

using namespace std;

const int width = 800;
const int height = 600;
const string windowTitle = "Guess It";

//----------------------------------------------------------------------------------------------------------------------------------------

int main() {
    SDL_Window* window;
    SDL_Renderer* renderer;
    
    SDL_Event e;
    
    // text color
    
    bool isRunning = true;
    
//    initSDL(window, renderer, windowTitle, width, height);
//
//    SDL_Texture* background = loadTexture("SDL2_project/assets/images/background.png", renderer);
    
//    if (background == NULL) {
//        SDL_DestroyTexture(background);
//        SDL_Quit();
//    }
    
    loadAllTextures();
    
//    SDL_RenderClear(renderer);
    
//    renderTexture(background, renderer, 0, 0, width, height);
    
//    SDL_RenderPresent(renderer);
    
//    bool humanVsComp = humanVsComputer();
    bool humanVsComp = true;
    int secretNumber = generateNumber();
    int computerGuess = generateNumber();
    
    // run the game program
    while (isRunning) {
        // if player quit, then break the loop
//        if ( SDL_WaitEvent(&e) != 0 && (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) ) {
//            isRunning = false;
//        }
        
        SDL_Delay(100);
        
        playGame(isRunning, secretNumber, computerGuess, humanVsComp);
    }
    
    //    waitTilKeypress();
    
//    SDL_DestroyTexture(background);
//    unloadAllTextures();
//    quitSDL(window, renderer);
    
    return 0;
    
}


//----------------------------------------------------------------------------------------------------------------------------------------
