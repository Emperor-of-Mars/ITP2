#include "shot.h"

using namespace std;

extern int SCREEN_HEIGHT;

Shot::Shot(Texture *tex, int posX, int posY, float sX, float sY, int vel, int dir){
	maxVel = vel;
	Direction = dir;
	SpritePos = 0;
	frameAnimPause = 120;
	mXpos = posX;
	mYpos = posY;
	mScaleX = sX;
	mScaleY = sY;
	mTexture = tex;
	mWidth = tex->getWidth();
	mHeight = tex->getHeight();
	clip = {0, 0, mWidth, mHeight};
	curAnimFrame.start();
}

bool Shot::move(float frameTime){
	if(Direction == 0) mYpos += maxVel * ((frameTime) / 10.f * mScaleY);      //schießt nach oben
	else if(Direction == 1) mYpos -= maxVel * ((frameTime) / 15.f * mScaleY);     //schießt nach unten
	for(unsigned int i = 0; i < mCol.size(); i++){
		mCol[i].x = mXpos + mWidth/2;
		mCol[i].y = mYpos;
	}
	if((mYpos <= (0-mHeight)) || (mYpos > (SCREEN_HEIGHT+mHeight)))return false;
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

Explosion* Shot::explode(){

    int exXpos, exYpos;
	exXpos = mXpos - clip.w/2;
    exYpos = mYpos - clip.h/2;

	Explosion *neue = new Explosion(exXpos, exYpos, mScaleX*0.3, mScaleY*0.3);

	return neue;

}
