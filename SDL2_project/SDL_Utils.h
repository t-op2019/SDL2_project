//
//  SDL_Utils.h
//  SDL2_project
//
//  Created by Dư Võ on 3/16/22.
//

#ifndef SDL_Utils_h
#define SDL_Utils_h

#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

using namespace std;

// basic SDL functions
// ***********************************************************

void logSDLError(const string &message, bool fatal = false);

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer, const string &windowTitle, int width, int height);

void quitSDL(SDL_Window* window, SDL_Renderer* renderer);

void waitTilKeypress();

string interpretKey(SDL_KeyboardEvent* key);

// ***********************************************************



// render images and textures functions
// ***********************************************************

// get image from file and load texture
SDL_Texture* loadTexture(const string &file, SDL_Renderer* renderer);

// render background texture
void renderTexture(SDL_Texture* texture, SDL_Renderer* renderer, int x, int y);

// render texture at coordinate (x,y) and width, height of w and h
void renderTexture(SDL_Texture* texture, SDL_Renderer* renderer, int x, int y, int w, int h);

// ***********************************************************

#endif /* SDL_Utils_h */
