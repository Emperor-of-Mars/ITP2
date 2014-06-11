#include "gun.h"

using namespace std;

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
