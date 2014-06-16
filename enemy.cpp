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
	movemodulo = 0;

}

Enemy::~Enemy(){
    for(unsigned int i = 0; i < mGun.size(); i++) delete mGun[i];
}

bool Enemy::init(Texture *tex, Texture *bullet, float sx, float sy, float screenScaleX, float screenScaleY, int life, int velocity, unsigned int frameAnimPause, float wSpawn, float hSpawn, int points, vector<vector<float >> bewegungen){

    mLife = life;
	maxVel = velocity;
    score = points;
    movements = bewegungen;

    mXpos = LEFT_SCREEN_WIDTH + (RIGHT_SCREEN_WIDTH - LEFT_SCREEN_WIDTH) * wSpawn; //NEEDS XML VALUE
    mYpos = SCREEN_HEIGHT * hSpawn;  //NEEDS XML VALUE

    spawnXpos = mXpos - LEFT_SCREEN_WIDTH;
    if(mYpos < 0) spawnYpos = SCREEN_HEIGHT - mYpos*-1;
    if(mYpos >= 0) spawnYpos = SCREEN_HEIGHT - mYpos;

    spawnXscale = wSpawn;
    spawnYscale = hSpawn;

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
	SDL_Rect col = {x + (int)(w*0.15), y + (int)(h*0.15), w - (int)(w*0.15), h - (int)(h*0.15)};
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

vector<vector<float >> Enemy::getMovements(){
    return movements;
}

void Enemy::shoot(){
    if(curAnimFrame.getTicks() > 6000){
        mGun[0]->fire(mXpos, mYpos, mScaleX, mScaleY, 1);
        mGun[1]->fire(mXpos, mYpos, mScaleX, mScaleY, 1);
        curAnimFrame.start();
    }
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

bool Enemy::movement(int frameTime){

    int frameLenght = maxVel * ((frameTime) / 10.f);
    int index = movemodulo%movements.size();

    switch((int)movements[index][0]){
        case 0:
                mYpos -= frameLenght * 0.1;
                if(mYpos <= (SCREEN_HEIGHT*movements[index][1])){
                    movemodulo++;
                }
                break;

        case 1:
                mXpos += frameLenght * 0.1;
                if(mXpos >= ((LEFT_SCREEN_WIDTH + (RIGHT_SCREEN_WIDTH - LEFT_SCREEN_WIDTH)*movements[index][1]))){
                    movemodulo++;
                }
                break;

        case 2:
                mYpos += frameLenght * 0.1;
                if(mYpos >= (SCREEN_HEIGHT*movements[index][1])){
                    movemodulo++;
                }
                break;

        case 3:
                mXpos -= frameLenght * 0.1;
                if(mXpos <= ((LEFT_SCREEN_WIDTH + (RIGHT_SCREEN_WIDTH - LEFT_SCREEN_WIDTH)*movements[index][1]))){
                    movemodulo++;
                }
                break;
        default:
                break;
    }

    for(unsigned int i = 0; i < mCol.size(); i++){//update collission boxes
		mCol[i].x = mXpos + (int)(mWidth * mScreenScaleX);
		mCol[i].y = mYpos + (int)(mHeight * mScreenScaleY);
	}
	return false;
}
