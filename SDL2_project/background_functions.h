//
//  background_functions.h
//  SDL2_project
//
//  Created by Dư Võ on 3/23/22.
//
//  Contains functions that run in the background, such as preloading all the textures,
//  render and rerender textures, etc...

#ifndef background_functions_h
#define background_functions_h

#include <iostream>
#include <string>
#include <SDL2/SDL.h>
using namespace std;

void loadAllTextures(const string response, const string guess);

void unloadAllTextures();

void renderPresent();

void renderChooseGamemode();

void rerender(const string response, const string guess);

// render "Guess a number" to inform the player to enter a guess
void renderPrompt(const string response, const string guess);

// render the number that the player guesses
void renderGuess(int renderNumber, int posX, int posY);

void renderLoading(const string guess);

void renderResponse(SDL_Texture* texture, int y, int textureWidth);

void renderReplay();

void renderComputerGuess(const string guess);

#endif /* background_functions_h */
