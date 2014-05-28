/*
 * Author: Erik Skalla, Stefan Reinhold, Samuel Wambera, Martin Schwarz
 * Created: 01.05.2014
 * Last change: 01.05.2014 20:16
 * Purpose: Header
 */

#include "button.h"

Button::Button(){
	mButtonTexture = NULL;
	renderQuad = {0, 0, 0, 0};
	clip = {0, 0, 0, 0};
	mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
}

void Button::setScale(float sx, float sy){
	mScaleX = sx;
	mScaleY = sy;
	return;
}

void Button::setPosition(int x, int y){
	renderQuad.x = x;
	renderQuad.y = y;
	return;
}

bool Button::init(Texture *ButtonTexture, int h, const char *ntext, SDL_Color color){
	if(ButtonTexture == NULL){
		return false;
	}
	mButtonTexture = ButtonTexture;
	if(!text.loadFromRenderedText(ntext, color)){
		return false;
	}
	clip.h = h;
	clip.w = mButtonTexture->getWidth();
	renderQuad.h = clip.h;
	renderQuad.w = clip.w;
	return true;
}

int Button::handleEvent(SDL_Event *e){
	int state = 0;
	if(e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP){//If mouse event happened
		int x, y;
		SDL_GetMouseState(&x, &y);//Get mouse position
		bool inside = true;//Check if mouse is in button
		if(x < renderQuad.x){//Mouse is left of the button
			inside = false;
		}
		else if(x > renderQuad.x + renderQuad.w * mScaleX){//Mouse is right of the button
			inside = false;
		}
		else if(y < renderQuad.y){//Mouse above the button
			inside = false;
		}
		else if(y > renderQuad.y + renderQuad.h * mScaleY){//Mouse below the button
			inside = false;
		}
		if(!inside){//Mouse is outside button
			mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
		}
		else{//Mouse is inside button
			switch(e->type){//Set mouse over sprite
			case SDL_MOUSEMOTION:
				mCurrentSprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
				break;
			case SDL_MOUSEBUTTONDOWN:
				mCurrentSprite = BUTTON_SPRITE_MOUSE_DOWN;
				state = 1;
				break;
			case SDL_MOUSEBUTTONUP:
				mCurrentSprite = BUTTON_SPRITE_MOUSE_UP;
				state = 0;
				break;
			}
		}
	}
	return state;
}

void Button::render(){
	clip.y = clip.h * mCurrentSprite;
	mButtonTexture->render(1, renderQuad.x, renderQuad.y, mScaleX, mScaleY, &clip);//Show current button sprite
	text.render(1, renderQuad.x + (renderQuad.w / 2 - text.getWidth() / 2) * mScaleX, renderQuad.y + (renderQuad.h / 2 - text.getHeight() / 2) * mScaleY, mScaleX, mScaleY);//Show current button sprite
	return;
}

int Button::getWidth(){
	return renderQuad.w * mScaleX;
}

int Button::getHeight(){
	return renderQuad.h * mScaleY;
}












