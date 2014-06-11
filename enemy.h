#ifndef ENEMY_H_INCLUDED
#define ENEMY_H_INCLUDED

#include "bullethell.h"
#include "shot.h"
#include "gun.h"

using namespace std;

class Enemy{
	public:
		Enemy();
		~Enemy();
		bool init(Texture *tex, vector<SDL_Rect> *col, Texture *bullet, vector<Shot*> *Shot = NULL, float sx = 1, float sy = 1, float screenScaleX = 1, float screenScaleY = 1, int animationSpeed = 120);
		void move(int frameTime);
        void render(float frameTime);
	private:
		int maxVel, mWidth, mHeight, mXpos, mYpos, SpritePos[2], BulletFired;
		unsigned int frameAnimPause;
		float mScaleX, mScaleY, mScreenScaleX, mScreenScaleY;
		Timer curAnimFrame;
		SDL_Rect clip;
		Texture *mTexture;
		vector<Gun*> mGun;
		vector<SDL_Rect> *mCol;
};

#endif // ENEMY_H_INCLUDED
