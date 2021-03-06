//
//  game_functions.h
//  SDL2_project
//
//  Created by Dư Võ on 3/16/22.
//

#ifndef game_functions_h
#define game_functions_h

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

void loadGame(SDL_Window* &window, SDL_Renderer* &renderer, const string &windowTitle, int width, int height);

void playGame(bool &isRunning, int &secretNumber, int &computerGuess, bool &humanVsComp);

#endif /* game_functions_h */
