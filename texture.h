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

#ifndef TEXTURE_H
#define TEXTURE_H

extern SDL_Window *gWindow;
extern SDL_Renderer *gRenderer;
extern TTF_Font *gFont;

using namespace std;

class Texture{
	public:
		Texture();//Initialize
		~Texture();//Destroy
		bool loadFromFile(const char *path);//Load Image
		bool loadFromRenderedText(const char *text, SDL_Color color);//convert text to texture
		void free();//Free texture if exists
		void setScale(float sx, float sy);
        void setPosition(int x, int y);
		void render(int flags = 0, int x = 0, int y = 0, float sx = 1, float sy = 1, SDL_Rect *clip = NULL, double angle = 0.0, SDL_Point *center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);//render texture to position
		void setBlendMode(SDL_BlendMode blending);
		void setAlpha(Uint8 a);
		int getWidth();
		int getHeight();
	private:
		float mScaleX;
		float mScaleY;
		SDL_Rect renderQuad;
		SDL_Texture* mTexture;
};

#endif