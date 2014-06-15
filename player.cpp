#include "player.h"
#include "gun.h"

using namespace std;

extern int SCREEN_HEIGHT;
extern int SCREEN_WIDTH;
extern int LEFT_SCREEN_WIDTH;
extern int RIGHT_SCREEN_WIDTH;

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
	frameAnimPause = 20;
	clip = {0, 0, 0, 0};
	mTexture = NULL;
	curAnimFrame.start();
	score = 0;
}

Player::~Player(){
	for(unsigned int i = 0; i < mGun.size(); i++)delete mGun[i];
}

bool Player::init(Texture *tex, Texture *bullet, vector<Shot*> *Shots, float sx, float sy, float screenScaleX, float screenScaleY, int life, unsigned int frameAnimPause){
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
    if(key[SDL_SCANCODE_LCTRL]) {
        	mScreenScaleX = 0.25;
            mScreenScaleY = 0.25;
    } else {
            mScreenScaleX = 0.5;
            mScreenScaleY = 0.5;
    }

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
		if(mXpos > SCREEN_WIDTH - mWidth - LEFT_SCREEN_WIDTH)mXpos = SCREEN_WIDTH - mWidth - LEFT_SCREEN_WIDTH;//Check if out of screen
		if(SpritePos[0] < 4&& curAnimFrame.getTicks() >= frameAnimPause){
			SpritePos[0]++;
			curAnimFrame.start();
		}
	}
	else if(SpritePos[0] > 2 && curAnimFrame.getTicks() >= frameAnimPause) {SpritePos[0]--; curAnimFrame.start();}

	if(key[SDL_SCANCODE_LEFT]){//Move left
		mXpos -= frameLenght * mScreenScaleX;//Change position
		if(mXpos < LEFT_SCREEN_WIDTH)mXpos = LEFT_SCREEN_WIDTH;//Check if out of screen
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

bool Player::colHandle(){
	mLife--;
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

unsigned int Player::getScore() {
    return score;
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
