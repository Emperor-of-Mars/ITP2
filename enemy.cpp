
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
	SpritePos[0] = 0;
	SpritePos[1] = 0;
	clip = {0, 0, 0, 0};
	frameAnimPause = 20;
	mTexture = NULL;
	curAnimFrame.start();

}

Enemy::~Enemy(){
    for(unsigned int i = 0; i < mGun.size(); i++) delete mGun[i];
}

bool Enemy::init(Texture *tex, Texture *bullet, float sx, float sy, float screenScaleX, float screenScaleY, int life, int velocity, unsigned int frameAnimPause){

    mLife = life;
	maxVel = velocity;

    mXpos = SCREEN_WIDTH / 2; //NEEDS XML VALUE
    mYpos = SCREEN_HEIGHT / 2;  //NEEDS XML VALUE


	mTexture = tex;
	if(mTexture == NULL) return false;
	clip.h = mTexture->getHeight();
	clip.w = mTexture->getWidth();
	mWidth = clip.w * sx;
	mHeight = clip.h * sy;
	mScaleX = sx;
	mScaleY = sy;
	mScreenScaleX = screenScaleX;
	mScreenScaleY = screenScaleY;
	mLife = life;
	Gun *newgun = NULL;
	mGun.push_back(newgun = new Gun(&Shots, bullet, (mWidth / 2) - 50 * mScaleX, 20 * mScaleY, mScaleX, mScaleY));
	mGun.push_back(newgun = new Gun(&Shots, bullet, (mWidth / 2) + 50 * mScaleX, 20 * mScaleY, mScaleX, mScaleY));
	return true;
}

void Enemy::setCol(int x, int y, int w, int h){
	SDL_Rect col = {x, y, w, h};
	mCol.push_back(col);
	return;
}

bool Enemy::colHandle(int dam){
	mLife -= dam;
	if(mLife <= 0) return true;
	else return false;
}

int Enemy::getWidth(){
	return mWidth;
}

int Enemy::getHeight(){
	return mHeight;
}

int Enemy::getLife(){
	return mLife;
}

vector<SDL_Rect> *Enemy::getCol(){
	return &mCol;
}

vector<Shot* > Enemy::getShots(){
	return Shots;
}

void Enemy::render(){
	clip.x = clip.w * SpritePos[0];
	clip.y = clip.h * SpritePos[1];
	mTexture->render(1, (int)mXpos, (int)mYpos, mScaleX, mScaleY, &clip);
	return;
}
