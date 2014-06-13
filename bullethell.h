/*
 * Author: Erik Skalla, Stefan Reinhold, Samuel Wambera, Martin Schwarz
 * Created: 01.05.2014
 * Last change: 01.05.2014 20:16
 * Purpose: Header
 */

#ifndef LIBS
#define LIBS

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#endif

#define BASE_SCREEN_WIDTH 1920
#define BASE_SCREEN_HEIGHT 1080
#define MAX_FPS 240
#define UPDATE_TIME 8

using namespace std;

#include "timer.h"
#include "texture.h"
#include "button.h"

bool init_SDL();
void close_SDL();
void PlayVideo();
int run(SDL_Event *event);
bool check_col(vector<SDL_Rect> *col1, vector<SDL_Rect> *col2);




