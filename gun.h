#ifndef GUN_H_INCLUDED
#define GUN_H_INCLUDED

#include "bullethell.h"
#include "shot.h"

using namespace std;

class Gun{
	public:
		Gun(vector<Shot*> *Shots, Texture *tex = NULL, int posX = 0, int posY = 0, float ScaleX = 1, float ScaleY = 1);
		void fire(float posX, float posY, float mScaleX = 1, float mScaleY = 1, int dir = 0);
	private:
		int maxVel, Damage;
		float mXpos, mYpos, mScaleX, mScaleY;
		Timer coolDown;
		Texture *mTexture;
		vector<Shot*> *mShots;
};

#endif // GUN_H_INCLUDED
