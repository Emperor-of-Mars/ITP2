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
        bool init(Texture *tex, Texture *bullet, float sx, float sy, float screenScaleX, float screenScaleY, int life, int velocity, unsigned int animationSpeed);
		void setCol(int x, int y, int w, int h);
		void handleEvent(SDL_Event *e, int frameTime);
		bool colHandle(int dam);
		vector<SDL_Rect> *getCol();
		vector<Shot* > getShots();
        void render();
        int getX();
        int getY();
		int getWidth();
		int getHeight();
		int getLife();
	private:
        int maxVel, mLife, mWidth, mHeight, mXpos, mYpos, SpritePos[2], BulletFired;
		unsigned int frameAnimPause;
		float mScaleX, mScaleY, mScreenScaleX, mScreenScaleY;
		Timer curAnimFrame;
		SDL_Rect clip;
		Texture *mTexture;
		vector<Gun*> mGun;
		vector<Shot* > Shots;
		vector<SDL_Rect> mCol;
};

#endif // ENEMY_H_INCLUDED
