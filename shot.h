#ifndef SHOT_H_INCLUDED
#define SHOT_H_INCLUDED

#include "bullethell.h"

using namespace std;

class Shot{
	public:
		Shot(Texture *tex, int posX, int posY, float sX = 1, float sY = 1, int vel = 10, int dir = 10);
		void setCol(int x, int y, int w, int h);
		bool move(float frameTime);
		vector<SDL_Rect> *getCol();
		void render();
		int getDamage();
	private:
		int maxVel, Direction, mXpos, mYpos, mWidth, mHeight, SpritePos, frameAnimPause;
		float mScaleX, mScaleY;
		Timer curAnimFrame;
		SDL_Rect clip;
		Texture *mTexture;
		vector<SDL_Rect> mCol;
};

#endif // SHOT_H_INCLUDED
