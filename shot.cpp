#include "shot.h"

using namespace std;

extern int SCREEN_HEIGHT;

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