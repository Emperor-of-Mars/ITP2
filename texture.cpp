/*
 * Author: Erik Skalla, Stefan Reinhold, Samuel Wambera, Martin Schwarz
 * Created: 01.05.2014
 * Last change: 01.05.2014 20:16
 * Purpose: Header
 */

#include "texture.h"

Texture::Texture(){
	renderQuad = {0, 0, 0, 0};
	mTexture = NULL;
	mScaleX = 1;
	mScaleY = 1;
}

Texture::~Texture(){
	free();
}

bool Texture::loadFromFile(const char *path){
	free();
	bool success = true;
	SDL_Surface *surface = NULL;
	SDL_Texture *newTexture = NULL;
	surface = IMG_Load(path);
	if(surface == NULL){
		cout << "Failed to load image! SDL_Error: " << SDL_GetError() << endl;
		success = false;
	}
	else{
		newTexture = SDL_CreateTextureFromSurface(gRenderer, surface);
		if(newTexture == NULL){
			cout << "Failed to create texture! SDL_Error: " << SDL_GetError() << endl;
			success = false;
		}
		else{
			renderQuad.w = surface->w;
			renderQuad.h = surface->h;
		}
		SDL_FreeSurface(surface);
	}
	mTexture = newTexture;
	return success;
}

bool Texture::loadFromRenderedText(const char *text, SDL_Color color){
	free();
	bool success = true;
	SDL_Surface *surface = NULL;
	SDL_Texture *newTexture = NULL;
	surface = TTF_RenderText_Solid(gFont, text, color);
	if(surface == NULL){
		cout << "Failed to render text to image! SDL_Error: " << SDL_GetError() << endl;
		success = false;
	}
	else{
		newTexture = SDL_CreateTextureFromSurface(gRenderer, surface);
		if(newTexture == NULL){
			cout << "Failed to create texture! SDL_Error: " << SDL_GetError() << endl;
			success = false;
		}
		else{
			renderQuad.w = surface->w;
			renderQuad.h = surface->h;
		}
		SDL_FreeSurface(surface);
	}
	mTexture = newTexture;
	return success;
}

void Texture::free(){
	if(mTexture != NULL){
		SDL_DestroyTexture(mTexture);
		renderQuad = {0, 0, 0, 0};
		mTexture = NULL;
		mScaleX = 1;
		mScaleY = 1;
	}
	return;
}

void Texture::setBlendMode(SDL_BlendMode blending){
	SDL_SetTextureBlendMode(mTexture, blending);
	return;
}

void Texture::setAlpha(Uint8 a){
	SDL_SetTextureAlphaMod(mTexture, a);
	return;
}

void Texture::setScale(float sx, float sy){
	mScaleX = sx;
	mScaleY = sy;
	return;
}

void Texture::setPosition(int x, int y){
	renderQuad.x = x;
	renderQuad.y = y;
	return;
}

void Texture::render(int flags, int x, int y, float sx, float sy, SDL_Rect *clip, double angle, SDL_Point* center, SDL_RendererFlip flip){
	SDL_Rect temprenderQuad = {renderQuad.x, renderQuad.y, (int)(renderQuad.w * mScaleX), (int)(renderQuad.h * mScaleY)};
	if(flags == 1)temprenderQuad = {x, y, (int)(renderQuad.w * sx), (int)(renderQuad.h * sy)};
	SDL_Rect *pRenderQuad = NULL;
	if(flags <= 1)pRenderQuad = &temprenderQuad;
	if(clip != 0){
		temprenderQuad.w = clip->w * sx;
		temprenderQuad.h = clip->h * sy;
	}
	SDL_RenderCopyEx(gRenderer, mTexture, clip, pRenderQuad, angle, center, flip);
	return;
}

int Texture::getWidth(){
	return renderQuad.w * mScaleX;
}

int Texture::getHeight(){
	return renderQuad.h * mScaleY;
}








