#include "enemy.h"

using namespace std;

extern int SCREEN_HEIGHT;
extern int SCREEN_WIDTH;
extern int LEFT_SCREEN_WIDTH;
extern int RIGHT_SCREEN_WIDTH;

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

bool Enemy::init(Texture *tex, Texture *bullet, float sx, float sy, float screenScaleX, float screenScaleY, int life, int velocity, unsigned int frameAnimPause, float wSpawn, float hSpawn, int points){

    mLife = life;
	maxVel = velocity;
    score = points;

    mXpos = LEFT_SCREEN_WIDTH + (SCREEN_WIDTH - LEFT_SCREEN_WIDTH) * wSpawn; //NEEDS XML VALUE
    mYpos = SCREEN_HEIGHT * hSpawn;  //NEEDS XML VALUE

    curAnimFrame.start();
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

int Enemy::getX(){
    return mXpos;
}

int Enemy::getY(){
    return mYpos;
}

void Enemy::shoot(){
    /*if(curAnimFrame.getTicks() > 60){
        mGun[0]->fire(mXpos, mYpos, mScaleX, mScaleY, 1);
        mGun[1]->fire(mXpos, mYpos, mScaleX, mScaleY, 1);
        curAnimFrame.start();
    }*/
}

bool Enemy::colHandle(int dam,Player *player){
    mLife -= dam;
    if(mLife <= 0)  {
        player->incScore(score);
        return true;
    }
    else return false;
}

Explosion* Enemy::explode(){

    int exXpos, exYpos;
	exXpos = mXpos - clip.w/2;
    exYpos = mYpos - clip.h/2;

	Explosion *neue = new Explosion(exXpos, exYpos, mScaleX*0.5, mScaleY*0.5);

	return neue;

}

