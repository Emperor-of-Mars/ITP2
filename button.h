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

#ifndef BUTTON_H
#define BUTTON_H

#include "texture.h"

enum ButtonSprite
{
	BUTTON_SPRITE_MOUSE_OUT = 0,
	BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
	BUTTON_SPRITE_MOUSE_DOWN = 2,
	BUTTON_SPRITE_MOUSE_UP = 1
};

extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;

extern SDL_Window *gWindow;
extern SDL_Renderer *gRenderer;
extern TTF_Font *gFont;

using namespace std;

class Button{
	public:
		Button();
		bool init(Texture *ButtonTexture, int h, const char *text, SDL_Color color);
		void setScale(float sx, float sy);
        void setPosition(int x, int y);
		int handleEvent(SDL_Event *e);
		void render();
		int getWidth();
		int getHeight();
	private:
		float mScaleX;
		float mScaleY;
		SDL_Rect renderQuad;
		SDL_Rect clip;
		Texture *mButtonTexture, text;
		ButtonSprite mCurrentSprite;
};

#endif