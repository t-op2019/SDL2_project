//
//  SDL_Utils.cpp
//  SDL2_project
//
//  Created by Dư Võ on 3/16/22.
//

#include "SDL_Utils.h"

// render images and textures functions
// ***********************************************************

SDL_Texture* loadTexture(const string &file, SDL_Renderer *renderer) {
    // initialize as NULL to avoid 'dangling pointer' error
    SDL_Texture *texture = NULL;
    // get image from file path
    SDL_Surface *loadedImage = IMG_Load(file.c_str());
    
    if (loadedImage != NULL) {
        texture = SDL_CreateTextureFromSurface(renderer, loadedImage);
        SDL_FreeSurface(loadedImage);
        
        if (texture == NULL) {
            logSDLError("CreateTextureFromSurface", false);
        }
        
    } else {
        logSDLError("IMG_Load");
    }
    return texture;
}

void renderTexture(SDL_Texture* texture, SDL_Renderer* renderer, int x, int y) {
    SDL_Rect destinationRec;
    destinationRec.x = x;
    destinationRec.y = y;
    
    // query the texture to get the width and height of the destination rectangle
    SDL_QueryTexture(texture, NULL, NULL, &destinationRec.w, &destinationRec.h);
    
    SDL_RenderCopy(renderer, texture, NULL, &destinationRec);
}

// draw texture onto renderer at coordinate (x,y) and with new width and height
void renderTexture(SDL_Texture* texture, SDL_Renderer* renderer, int x, int y, int w, int h) {
    // create destination rectangle
    SDL_Rect destinationRec;
    destinationRec.x = x;
    destinationRec.y = y;
    destinationRec.w = w;
    destinationRec.h = h;
    
    // query the attributes of the texture to get width and height
    // SDL_QueryTexture(texture, NULL, NULL, &destinationRec.w, &destinationRec.h);
    
    // render the texture onto the rectangle
    SDL_RenderCopy(renderer, texture, NULL, &destinationRec);
}

// ***********************************************************



// SDL basic functions
// ***********************************************************

void logSDLError(const string &message, bool fatal) {
    cout << message.c_str() << "Error: " << SDL_GetError() << endl;
    if (fatal) {
        SDL_Quit();
        exit(1);
    }
}

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer, const string &windowTitle, int width, int height) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        logSDLError("SDL_Init", true);
    }
    
    window = SDL_CreateWindow(windowTitle.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        logSDLError("create_window", true);
    }
    
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) {
        logSDLError("create_renderer", true);
    }
    
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, width, height);
}

void quitSDL(SDL_Window* window, SDL_Renderer* renderer) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void waitTilKeypress() {
    SDL_Event e;
    while (true) {
        if ( SDL_WaitEvent(&e) != 0 &&
            (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
            return;
        SDL_Delay(100);
    }
}

string interpretKey(SDL_KeyboardEvent* key) {
    return SDL_GetKeyName(key -> keysym.sym);
}

// ***********************************************************
