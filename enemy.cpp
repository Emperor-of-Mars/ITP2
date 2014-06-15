
#include "enemy.h"

using namespace std;

Enemy::Enemy(){

    mLife = 0;
	maxVel = 0;
    BulletFired = 0;
    mWidth = 0;
    mHeight = 0;
    mScaleX = 0;
	mScaleY = 0;
	mScreenScaleX = 0;
	mScreenScaleY = 0;
	clip = {0, 0, 0, 0};
	frameAnimPause = 20;
	mTexture = NULL;

}

Enemy::~Enemy(){

}

bool Enemy::init(Texture *tex, Texture *bullet, vector<Shot*> *Shots, float sx, float sy, float screenScaleX, float screenScaleY, int life, unsigned int frameAnimPause){

    mLife = 100;
	maxVel = 10;

    mXpos = SCREEN_WIDTH / 5; //NEEDS XML VALUE
    mYpos = SCREEN_HEIGHT / 5;  //NEEDS XML VALUE


	SpritePos[0] = 2;
	SpritePos[1] = 1;
	curAnimFrame.start();

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
