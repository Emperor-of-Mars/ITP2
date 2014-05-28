/*
 * Author: Erik Skalla, Stefan Reinhold, Samuel Wambera, Martin Schwarz
 * Created: 01.05.2014
 * Last change: 01.05.2014 20:16
 * Purpose: Game Elements
 */

#include "bullethell.h"

void PlayVideo(){
	return;
}

bool check_col(vector<SDL_Rect> *col1, vector<SDL_Rect> *col2){
	for(unsigned int i = 0; i < col1->size(); i++){
		for(unsigned int j = 0; j < col2->size(); j++){
			if((*col1)[i].x < (*col2)[j].x) return false;
			if((*col1)[i].x > (*col2)[j].x + (*col2)[j].w) return false;
			if((*col1)[i].y < (*col2)[j].y) return false;
			if((*col1)[i].y > (*col2)[j].y + (*col2)[j].h) return false;
		}
	}
	return true;
}

//###############################################  Player:
Player::Player(){
	mLife = 100;
	maxVel = 10;
	mXpos = SCREEN_WIDTH / 2;
	mYpos = SCREEN_HEIGHT / 1.2;
	BulletFired = 0;
	mWidth = 0;
	mHeight = 0;
	mScaleX = 0;
	mScaleY = 0;
	mScreenScaleX = 0;
	mScreenScaleY = 0;
	SpritePos[0] = 2;
	SpritePos[1] = 1;
	frameAnimPause = 200;
	clip = {0, 0, 0, 0};
	mTexture = NULL;
	curAnimFrame.start();
}

Player::~Player(){
	for(unsigned int i = 0; i < mGun.size(); i++)delete mGun[i];
}

bool Player::init(Texture *tex, Texture *bullet, vector<Shot*> *Shots, float sx, float sy, float screenScaleX, float screenScaleY, int life, int animationSpeed){
	mTexture = tex;
	if(mTexture == NULL) return false;
	clip.h = mTexture->getHeight() / 5;
	clip.w = mTexture->getWidth() / 5;
	mWidth = clip.w * sx;
	mHeight = clip.h * sy;
	mScaleX = sx;
	mScaleY = sy;
	mScreenScaleX = screenScaleX;
	mScreenScaleY = screenScaleY;
	frameAnimPause = animationSpeed;
	mLife = life;
	Gun *newgun = NULL;
	mGun.push_back(newgun = new Gun(Shots, bullet, (mWidth / 2) - 50 * mScaleX, 20 * mScaleY, mScaleX, mScaleY));
	mGun.push_back(newgun = new Gun(Shots, bullet, (mWidth / 2) + 50 * mScaleX, 20 * mScaleY, mScaleX, mScaleY));
	return true;
}

void Player::setCol(int x, int y, int w, int h){
	SDL_Rect col = {x, y, w, h};
	mCol.push_back(col);
	return;
}

void Player::handleEvent(SDL_Event *e, int frameTime){
	int frameLenght = maxVel * ((frameTime) / 10.f);
	const Uint8 *key = SDL_GetKeyboardState(NULL);

	if(key[SDL_SCANCODE_UP]){//Move up
		mYpos -= frameLenght * mScreenScaleY;//Change position
		if(mYpos < 0)mYpos = 0;//Check if out of screen
		if(SpritePos[1] > 0 && curAnimFrame.getTicks() >= frameAnimPause){
			SpritePos[1]--;
			curAnimFrame.start();
		}
	}
	else if(SpritePos[1] < 1 && curAnimFrame.getTicks() >= frameAnimPause) {SpritePos[1]++; curAnimFrame.start();}

	if(key[SDL_SCANCODE_DOWN]){//Move down
		mYpos += frameLenght * mScreenScaleY;//Change position
		if(mYpos > SCREEN_HEIGHT - mHeight)mYpos = SCREEN_HEIGHT - mHeight;//Check if out of screen
		if(SpritePos[1] < 2 && curAnimFrame.getTicks() >= frameAnimPause){
			SpritePos[1]++;
			curAnimFrame.start();
		}
	}
	else if(SpritePos[1] > 1 && curAnimFrame.getTicks() >= frameAnimPause) {SpritePos[1]--; curAnimFrame.start();}

	if(key[SDL_SCANCODE_RIGHT]){//Move right
		mXpos += frameLenght * mScreenScaleX;//Change position
		if(mXpos > SCREEN_WIDTH - mWidth)mXpos = SCREEN_WIDTH - mWidth;//Check if out of screen
		if(SpritePos[0] < 4&& curAnimFrame.getTicks() >= frameAnimPause){
			SpritePos[0]++;
			curAnimFrame.start();
		}
	}
	else if(SpritePos[0] > 2 && curAnimFrame.getTicks() >= frameAnimPause) {SpritePos[0]--; curAnimFrame.start();}

	if(key[SDL_SCANCODE_LEFT]){//Move left
		mXpos -= frameLenght * mScreenScaleX;//Change position
		if(mXpos < 0)mXpos = 0;//Check if out of screen
		if(SpritePos[0] > 0 && curAnimFrame.getTicks() >= frameAnimPause){
			SpritePos[0]--;
			curAnimFrame.start();
		}
	}
	else if(SpritePos[0] < 2 && curAnimFrame.getTicks() >= frameAnimPause) {SpritePos[0]++; curAnimFrame.start();}

	if(key[SDL_SCANCODE_W] || key[SDL_SCANCODE_SPACE]){//fire gun
		mGun[0]->fire(mXpos, mYpos, mScaleX, mScaleY);
		mGun[1]->fire(mXpos, mYpos, mScaleX, mScaleY);
	}
	for(unsigned int i = 0; i < mCol.size(); i++){//update collission boxes
		mCol[i].x = mXpos;
		mCol[i].y = mYpos;
	}
	return;
}

bool Player::colHandle(int dam){
	mLife -= dam;
	if(mLife <= 0) return true;
	else return false;
}

int Player::getWidth(){
	return mWidth;
}

int Player::getHeight(){
	return mHeight;
}

int Player::getLife(){
	return mLife;
}

vector<SDL_Rect> *Player::getCol(){
	return &mCol;
}

void Player::render(){
	clip.x = clip.w * SpritePos[0];
	clip.y = clip.h * SpritePos[1];
	mTexture->render(1, (int)mXpos, (int)mYpos, mScaleX, mScaleY, &clip);
	return;
}

//###############################################  Gun:
Gun::Gun(vector<Shot*> *Shots, Texture *tex, int posX, int posY, float ScaleX, float ScaleY){
	coolDown.start();
	maxVel = 10;
	Damage = 0;
	mXpos = posX - ScaleX * tex->getWidth() / 2;
	mYpos = posY - ScaleY * tex->getHeight() / 8;
	mScaleX = ScaleX;
	mScaleY = ScaleY;
	mTexture = tex;
	mShots = Shots;
}

void Gun::fire(float posX, float posY, float mScaleX, float mScaleY){
	if(coolDown.getTicks() > 300){
		Shot *newshot;
		mShots->push_back(newshot = new Shot(mTexture, mXpos + (int)posX, mYpos + (int)posY, mScaleX, mScaleY, -15, 10));
		(*mShots)[mShots->size() - 1]->setCol(0, 0, 60, 100);
		coolDown.start();
	}
	return;
}

//###############################################  Shot:
Shot::Shot(Texture *tex, int posX, int posY, float sX, float sY, int vel, int dam){
	maxVel = vel;
	Damage = dam;
	SpritePos = 0;
	frameAnimPause = 120;
	mXpos = posX;
	mYpos = posY;
	mScaleX = sX;
	mScaleY = sY;
	mTexture = tex;
	mWidth = tex->getWidth();
	mHeight = tex->getHeight() / 4;
	clip = {0, 0, mWidth, mHeight};
	curAnimFrame.start();
}

bool Shot::move(float frameTime){
	mYpos += maxVel * ((frameTime) / 10.f * mScaleY);
	for(unsigned int i = 0; i < mCol.size(); i++){
		mCol[i].x = mXpos;
		mCol[i].y = mYpos;
	}
	if(mYpos > SCREEN_HEIGHT - mHeight)return false;
	else return true;
}

void Shot::render(){
	mTexture->render(1, mXpos, mYpos, mScaleX, mScaleY, &clip);
	return;
}

void Shot::setCol(int x, int y, int w, int h){
	SDL_Rect col = {x, y, w, h};
	mCol.push_back(col);
	return;
}

vector<SDL_Rect> *Shot::getCol(){
	return &mCol;
}








